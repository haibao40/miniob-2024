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
// Created by Wangyunlai on 2024/05/29.
//

#include "sql/expr/aggregator.h"
#include "common/log/log.h"

RC SumAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  Value::add(value, value_, value_);
  return RC::SUCCESS;
}
//-1< 0= 1>
RC SumAggregator::evaluate(Value& result)
{
  if(value_.attr_type() == AttrType::UNDEFINED){
    Value zero(0);
    result = zero;
    return RC::SUCCESS;
  }
  result = value_;
  return RC::SUCCESS;
}

RC MaxAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  int comp = value_.compare(value);
  if(comp < 0)
    value_ = value;
  return RC::SUCCESS;
}
//-1< 0= 1>
RC MaxAggregator::evaluate(Value &result)
{
  result = value_;
  return RC::SUCCESS;
}

RC MinAggregator::accumulate(const Value& value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  int comp = value_.compare(value);
  if(comp > 0)
    value_ = value;
  return RC::SUCCESS;
}
//-1< 0= 1>
RC MinAggregator::evaluate(Value &result)
{
  result = value_;
  return RC::SUCCESS;
}

RC AvgAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  Value::add(value, value_, value_);
  add_len();
  return RC::SUCCESS;
}

RC AvgAggregator::evaluate(Value &result)
{
  if(value_.attr_type() == AttrType::UNDEFINED){
    Value zero(0);
    result = zero;
    return RC::SUCCESS;
  }
  bool is_int = value_.attr_type() == AttrType::INTS;
  const Value& length = Value(len_); 
  value_.set_type(AttrType::FLOATS);
  if(is_int) value_.int2float();
  Value::divide(value_, length, value_);
  result = value_;
  // if(is_int)
  //   result.set_type(AttrType::INTS);
  return RC::SUCCESS;
}

RC CountAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  Value one(1);
  if(!flag){
    flag = true;
    value_ = one;
  }
  Value::add(one, value_, value_);
  count++;
  return RC::SUCCESS;
}
//-1< 0= 1>
RC CountAggregator::evaluate(Value &result)
{
  if(value_.attr_type() == AttrType::UNDEFINED){
    Value zero(0);
    result = zero;
    return RC::SUCCESS;
  }
  if(count == 1){
    Value one(1);
    value_ = one;
  }
  result = value_;
  return RC::SUCCESS;
}