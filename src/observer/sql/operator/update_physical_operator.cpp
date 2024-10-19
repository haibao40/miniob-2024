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

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    Value valuetmp;
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    TupleCellSpec tuplecellspec = TupleCellSpec(table_->name(), field_name_.c_str());
    rc = row_tuple->find_cell(tuplecellspec, valuetmp);
    if(rc != RC::SUCCESS ){
      LOG_WARN("not find");
      return rc;
    }
    if(valuetmp.attr_type() != value_.attr_type()){
      LOG_WARN("type is not right");
      return RC::NOT_EXIST;
    }
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  // while (OB_SUCC(rc = child1->next())) {
  //   LOG_DEBUG("in");
  //   Tuple *tuple = child1->current_tuple();
  //   if (nullptr == tuple) {
  //     LOG_WARN("failed to get current record: %s", strrc(rc));
  //     return rc;
  //   }

  //   Value valuetmp;
  //   RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
  //   TupleCellSpec tuplecellspec = TupleCellSpec(table_->name(), field_name_.c_str());
  //   rc = row_tuple->find_cell(tuplecellspec, valuetmp);
  //   if(rc != RC::SUCCESS ){
  //     LOG_WARN("not find");
  //     return rc;
  //   }
  // }

  child->close();
  // child1->close();
  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  LOG_DEBUG("field_name:%s, value:%s", field_name_.c_str(), value_.to_string().c_str());
  for (Record &record : records_) {
    rc = trx_->update_record(table_, record, field_name_.c_str(), value_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
