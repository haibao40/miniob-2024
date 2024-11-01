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
    case AttrType::INTS:{
      string stringValue = val.get_string();
      int number = 0;  
      bool hasDigits = false;  
  
      for (char ch : stringValue) {  
          if (std::isdigit(static_cast<unsigned char>(ch))) {  
            number = number * 10 + (ch - '0');  
            hasDigits = true;  
        }else {  
          // 如果遇到非数字字符，停止扫描  
          break;   
        }  
    }  
    // 如果字符串不以数字字符开头，则返回 0  否则返回转化的Number
    result.set_int(hasDigits ? number : 0);
    }break;
    case AttrType::FLOATS:{
      string stringValue = val.get_string();
      double number = 0.0;  
      double decimalMultiplier = 0.1; // 用于累加小数点后的数字  
      bool hasDigits = false;  
      bool hasDecimal = false;  
  
    for (char ch : stringValue) {  
        if (std::isdigit(static_cast<unsigned char>(ch))) {  
            if (hasDecimal) {  
                number += (ch - '0') * decimalMultiplier;  
                decimalMultiplier *= 0.1; // 移动到下一个小数位  
            } else {  
                number = number * 10.0 + (ch - '0');  
            }  
            hasDigits = true;  
        } else if (ch == '.') {  
            if (hasDecimal) { // 如果已经遇到了小数点，则忽略后续的小数点  
                break;  
            }  
            hasDecimal = true;  
        } else {  
            // 如果遇到非数字字符，则停止扫描  
                break;  
        }  
    }  
  
    // 如果没有遇到任何数字字符，则返回0  
    result.set_float(hasDigits ? number : 0.0);  
    }break ;
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
  }else if(type == AttrType::INTS || type == AttrType::FLOATS){ //表示可以将字符串转化为int 转化的代价为1
    return 1 ;
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