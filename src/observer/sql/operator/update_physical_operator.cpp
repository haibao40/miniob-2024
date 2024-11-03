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

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, const char* field_name, Value &&value)
    : table_(table), field_name_(field_name), value_(std::move(value))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  const FieldMeta *field = table_->table_meta().field(field_name_.c_str());
  if(field == nullptr){
    LOG_WARN("field_name is not exist");
    return RC::NOTFOUND;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  // std::unique_ptr<PhysicalOperator> &child1 = children_[1];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  // rc = child1->open(trx);
  // if (rc != RC::SUCCESS) {
  //   LOG_WARN("failed to open child operator: %s", strrc(rc));
  //   return rc;
  // }

  trx_ = trx;

  vector<vector<Value> > record_values;
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    Value valuetmp;
    vector<Value> values;
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    
    //首先，先判断要更新的数据类型与原类型是否一致，空值则跳过判断
    TupleCellSpec tuplecellspec = TupleCellSpec(table_->name(), field_name_.c_str());
    rc = row_tuple->find_cell(tuplecellspec, valuetmp);
    // if(rc != RC::SUCCESS ){
    //   LOG_WARN("not find");
    //   return rc;
    // }
    if(valuetmp.attr_type() != value_.attr_type() && value_.attr_type() != AttrType::NULLS){
      auto cost = DataType::type_instance(value_.attr_type())->cast_cost(valuetmp.attr_type());
      if(cost != INT32_MAX){
        value_.cast_to(value_, valuetmp.attr_type(), value_);
      }else{
        LOG_WARN("type is not right");
        return RC::NOT_EXIST;
      }
    }

    //从1开始，是因为第0个位置是空值列表,这里把所有字段值保存起来
    for(int i = 1; i < row_tuple->cell_num(); i++) {
      Value value;
      row_tuple->cell_at(i, value);
      values.push_back(value);
    }

    //找到要更新的值的位置，在这里把它更新
    int pos = 1;
    for (int i = 0; i < row_tuple->cell_num(); ++i) {
      TupleCellSpec spec ;
      row_tuple->spec_at(i, spec);
      if(spec.field_name() == field_name_) {
        pos = i;
        break;
      }
    }
    values[pos - 1] = value_; //更新value

    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
    record_values.push_back(values);
  }

  child->close();

  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  for (size_t i = 0; i < records_.size(); i++) {
    rc = trx_->update_record(table_, records_[i], record_values[i],field_name_.c_str(), value_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
