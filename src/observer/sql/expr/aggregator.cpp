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

//这里没有考虑value为null的情况，应该先确定value是否为null，如果是，直接返回success，什么都不干
RC SumAggregator::accumulate(const Value &value)
{
  if(value.attr_type() == AttrType::NULLS) return RC::SUCCESS;
  //sum是官方提供的，这句的意思是，如果value_未被初始化，对应了第一次传入参数的情况，除了count以外，其他的都是直接把参数赋值给value_
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  Value::add(value, value_, value_);
  return RC::SUCCESS;
}

//这个函数是用来得到最终结果
RC SumAggregator::evaluate(Value& result)
{
  //这里是自己加了一个判断，如果到取结果的时候，value_还是没有初始化，那就是0条记录,这里统一输出0,而不是输出为空
  if(value_.attr_type() == AttrType::UNDEFINED){
    result.set_null();
    return RC::SUCCESS;
  }
  result = value_;
  return RC::SUCCESS;
}

RC MaxAggregator::accumulate(const Value &value)
{
  if(value.attr_type() == AttrType::NULLS) return RC::SUCCESS;
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
  if(value_.attr_type() == AttrType::UNDEFINED){
    result.set_null();
    return RC::SUCCESS;
  }
  result = value_;
  return RC::SUCCESS;
}

RC MinAggregator::accumulate(const Value& value)
{
  if(value.attr_type() == AttrType::NULLS) return RC::SUCCESS;
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
  if(value_.attr_type() == AttrType::UNDEFINED){
    result.set_null();
    return RC::SUCCESS;
  }
  result = value_;
  return RC::SUCCESS;
}

RC AvgAggregator::accumulate(const Value &value)
{
  if(value.attr_type() == AttrType::NULLS) return RC::SUCCESS;
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

//avg有点小情况，写的有点小乱，实现的方法是每次accumulate都把值加到value_里去，然后用len_表示记录长度
//问题在与，int类型的除法不对，有位截断(所以官方没有写int类型的除法)，所以必须先把value_转成float类型
//主要就是用一个变量记录value_的类型是否为int，是的话，就转换类型
RC AvgAggregator::evaluate(Value &result)
{
  if(value_.attr_type() == AttrType::UNDEFINED){
    result.set_null();
    return RC::SUCCESS;
  }

  bool is_int = value_.attr_type() == AttrType::INTS;
  const Value& length = Value(len_); 
  value_.set_type(AttrType::FLOATS);
  if(is_int) value_.int2float();//直接settype没用，还要把value_里的float值拿正确,所以写了个将int转float的函数

  Value::divide(value_, length, value_);
  result = value_;
  return RC::SUCCESS;
}

RC CountAggregator::accumulate(const Value &value)
{
  if(value.attr_type() == AttrType::NULLS) return RC::SUCCESS;
  if (value_.attr_type() == AttrType::UNDEFINED) {
    Value one(1);
    value_ = one;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  Value one(1);
  Value::add(one, value_, value_);
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

  result = value_;
  return RC::SUCCESS;
}