/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "event/sql_debug.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, std::vector<UpdateUnite> update_unites)
    : table_(table), update_unites_(update_unites)
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  trx_ = trx;
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  //TODO:这种先执行子查询，避免锁冲突的方式只适合非相关子查询，如果这里出现非相关子查询，需要用其它的手段来调整
  //先执行子查询，因为上层的update语句要使用读写锁，当上层的物理算子打开后，这个读写锁就会加上去，
  //此时，如果下层的子查询对应的表和上层查询是同一张表，就会导致下层的物理算子在打开时，加读锁失败，
  //从而导致整个执行失败,由于update中这个查询一定是非相关子查询，所以，先让子查询执行一次，把结果缓存起来
  //后面再去调用子查询的get_value方法，就会走缓存，而不会再去执行子查询
  for(auto update_unite :update_unites_) {
    if(update_unite.expression->type() == ExprType::SUBQUERY) {
      Value new_value;
      // 获取表达式的值
      rc = update_unite.expression->get_value(RowTuple(), new_value); //这个tuple参数可以随便传，非相关子查询用不到
      if(rc != RC::SUCCESS) {
        sql_debug("在执行update之前，获取表达式的值失败,rc = %s", strrc(rc));
        LOG_ERROR("在执行update之前，获取表达式的值失败");
        // 这里先不返回，因为根据正常的update-select逻辑，外层的过滤会先执行，有可能过滤后没有符合条件的数据，那么子查询即使有问题，也是不会被执行的，应该返回success
        // return rc;
      }
    }
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  rc = child->open(trx);   //打开下层算子
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  vector<Record> old_records;
  vector<vector<Value> > new_record_values;
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    vector<Value> new_values;
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    rc = get_new_record_values(row_tuple, new_values);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("获取记录更新后的value列表失败");
      return rc;
    }
    Record   &record    = row_tuple->record();
    old_records.emplace_back(std::move(record));
    new_record_values.push_back(new_values);
  }

  child->close();       //关闭下层算子

  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  for (size_t i = 0; i < old_records.size(); i++) {
    rc = trx_->update_record(table_, old_records[i], new_record_values[i]);
    if (rc != RC::SUCCESS) {
      sql_debug("执行update_record失败,rc = %s", strrc(rc));
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }

RC UpdatePhysicalOperator::get_new_record_values(RowTuple* old_data_tuple, vector<Value>& values)
{
  RC rc = RC::SUCCESS;

  //拿到这个记录之前的value值列表，存入values
  for(int i = 1; i < old_data_tuple->cell_num(); i++) {  //从1开始，是因为第0个位置是空值列表,这里把所有字段值保存起来
    Value value;
    old_data_tuple->cell_at(i, value);
    values.push_back(value);
  }

  //根据每一个update_unite,去更新values中对应位置的值
  for(auto update_unite :update_unites_) {
    Value valuetmp;
    std::string field_name = update_unite.field_name;
    Value new_value;
    // 获取表达式的值
    rc = update_unite.expression->get_value(*old_data_tuple, new_value);
    if(rc != RC::SUCCESS) {
      sql_debug("在执行update更新的过程中，获取表达式的值失败,rc = %s", strrc(rc));
      LOG_ERROR("更新过程中，获取表达式的值失败");
      if(rc == RC::ILLEGAL_SUB_QUERY_zero_record) {  //update_select中，子查询为空的情况下，要返回success;
        return RC::SUCCESS;
      }
      return rc;      //其它情况的失败，还是返回false
    }

    //判断要更新的数据类型与原类型是否一致，不一致尝试进行类型转换，空值则跳过判断
    TupleCellSpec tuplecellspec = TupleCellSpec(table_->name(), field_name.c_str());
    rc = old_data_tuple->find_cell(tuplecellspec, valuetmp);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("在原有数据中查找更新字段失败，要更新的字段不存在");
      return rc;
    }
    if(valuetmp.attr_type() != new_value.attr_type() &&valuetmp.attr_type()!= AttrType::NULLS &&new_value.attr_type() != AttrType::NULLS){
      Value cast_to_result;
      rc = Value::cast_to(new_value, valuetmp.attr_type(), cast_to_result);
      if(rc != RC::SUCCESS) {
        LOG_WARN("提供的新值和该字段原本的类型不匹配，且无法转换为该字段原本的类型");
        return RC::NOT_EXIST;
      }
      new_value = cast_to_result;
    }

    //找到要更新的值的位置，在这里把它更新
    int pos = 1;
    for (int i = 0; i < old_data_tuple->cell_num(); ++i) {
      TupleCellSpec spec ;
      old_data_tuple->spec_at(i, spec);
      if(spec.field_name() == field_name) {
        pos = i;
        break;
      }
    }
    values[pos - 1] = new_value; //更新对应位置的值为new_value
  }
  return rc;
}
