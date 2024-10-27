/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"
#include "common/time/datetime.h"

#include <common/os/path.h>

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  if(val.attr_type_ != AttrType::CHARS) return RC::INVALID_ARGUMENT;
  RC rc = RC::SUCCESS;
  switch (type) {
    case AttrType::DATES: {  //字符串类型可以转换为日期类型，如果日期不合法，会转换失败
      rc = cast_char_to_date(val, result);
    } break;
    case AttrType::VECTORS: {  //字符串类型可以转换为向量类型
      rc = cast_char_to_vector(val, result);
    } break;
    default: return RC::UNIMPLEMENTED;
  }
  return rc;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  //表示可以将字符串类型转换为日期类型，类型转换的代价为1（代价理解为转换过程中的性能消耗）
  else if(type == AttrType::DATES) {
    return 1;
  }
  //表示可以将字符串类型转换为向量类型，类型转换的代价为1
  else if(type == AttrType::VECTORS) {
    return 1;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}

RC CharType::cast_char_to_date(const Value &val, Value &result)
{
  int year, month, day;
  if(sscanf(val.value_.pointer_value_, "%d-%d-%d", &year, &month, &day) != 3) {
    LOG_WARN("日期字符串的格式不合法：%s", val.value_.pointer_value_);
    return RC::INVALID_ARGUMENT;
  }
  bool is_valid = common::check_date(year,month, day);
  if(!is_valid) {
    LOG_WARN("日期不在合法的范围内:year=%d, month=%d, day=%d", year, month, day);
    return RC::INVALID_ARGUMENT;
  }
  result.set_date(year, month, day);
  return RC::SUCCESS;
}

RC CharType::cast_char_to_vector(const Value &val, Value &result)
{
  //字符串中的数据格式为[1.5,2.3,3.3]， 指针val.value_.pointer_value_指向这个字符串
  std::string str(val.value_.pointer_value_);
  std::vector<float> vec;
  std::stringstream ss(str.substr(1, str.size() - 2)); // 去掉首尾的方括号
  float num;
  char comma;
  while (ss >> num) {
    vec.push_back(num);
    ss >> comma; // 读取逗号，如果有的话
  }
  if (ss.fail() && !ss.eof()) {
    LOG_WARN("将字符串转换为向量时发生错误，字符串中存储的数据不能转换为向量");
    return RC::INVALID_ARGUMENT  ; // 解析失败
  }
  result.set_vector(vec);
  return RC::SUCCESS;
}