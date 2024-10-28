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
  switch (type) {
    case AttrType::DATES: {  //字符串类型可以转换为日期类型
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
    } break;
    case AttrType::INTS:{
      string stringValue = val.get_string();
      int number = 0;  
    bool hasDigits = false;  
  
    for (char ch : stringValue) {  
        if (std::isdigit(static_cast<unsigned char>(ch))) {  
            number = number * 10 + (ch - '0');  
            hasDigits = true;  
        } else {  
            // 如果遇到非数字字符，停止扫描  
            if (hasDigits) {  
                break;  
            }  
        }  
    }  
  
    // 如果字符串不以数字字符开头，则返回 0  否则返回转化的Number
    result.set_int(hasDigits ? number : 0);
    }
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  //表示可以将字符串类型转换为日期类型，类型转换的代价为1（代价理解为转换过程中的性能消耗）
  else if(type == AttrType::DATES) {
    return 1;
  }else if(type == AttrType::INTS){ //表示可以将字符串转化为int 转化的代价为1
    return 1 ;
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