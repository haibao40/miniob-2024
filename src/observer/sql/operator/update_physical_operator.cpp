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

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, Value &&value)
    : table_(table), value_(std::move(value))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  std::size_t i = 1;
  while(i < children_.size()){
    std::unique_ptr<PhysicalOperator> &child1 = children_[i++];
    rc = child1->open(trx);
    if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
    }
    child1->close();

  }

  trx_ = trx;

  // while (OB_SUCC(rc = child->next())) {
  //   Tuple *tuple = child->current_tuple();
  //   if (nullptr == tuple) {
  //     LOG_WARN("failed to get current record: %s", strrc(rc));
  //     return rc;
  //   }

  //   RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
  //   Record   &record    = row_tuple->record();
  //   records_.emplace_back(std::move(record));
  // }

  child->close();

  return RC::SUCCESS;
  
  // RC rc = RC::INTERNAL;
  // Record record;
  // return rc;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
