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
// Created by WangYunlai on 2024/06/11.
//
#include <algorithm>

#include "common/log/log.h"
#include "sql/operator/limit_physical_operator.h"
using namespace std;
using namespace common;


LimitPhysicalOperator::LimitPhysicalOperator(int limit_count){
  limit_count_ = limit_count;
}


RC LimitPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}


RC LimitPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if(current_count_ < limit_count_){
    if((rc = children_[0]->next()) == RC::SUCCESS){
      current_count_++; 
      return rc ;
    }else{
      return rc ;
    }
  }else{
     return RC::RECORD_EOF;
  }
}

RC LimitPhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *LimitPhysicalOperator::current_tuple() {
  return children_[0] ->current_tuple();
}



RC LimitPhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  return children_[0]->tuple_schema(schema);
}