/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 固定长度的字符串类型
 * @ingroup DataType
 */
class CharType : public DataType
{
public:
  CharType() : DataType(AttrType::CHARS) {}

  virtual ~CharType() = default;

  int compare(const Value &left, const Value &right) const override;

  /***
   * @brief 将val 转换为 type类型，并将结果保存在result中，
   *        目前，支持【字符串类型】-->【日期类型】, 【字符串类型】-->【向量类型】
   * @left 待转换值，必须满足 val.attr_type_ == AttrType::CHARS
   * @result 转换的结果
   */
  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;

private:
  /// 将char类型转换为其他类型的代码封装为函数
  static RC cast_char_to_date(const Value &val, Value &result);
  static RC cast_char_to_vector(const Value &val, Value &result);
};