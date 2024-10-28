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

#include "common/type/data_type.h"

/**
 * @brief 向量类型
 * @ingroup DataType
 */
class VectorType : public DataType
{
public:
  VectorType() : DataType(AttrType::VECTORS) {}
  virtual ~VectorType() {}

  /***
   * @brief 向量类型的比较运算，即两个向量比较时，从左到右逐个数值进行比较，如果某个位置的数值不同，则根据该位置的数值大小比较结果作为向量的比较结果
   * 举例：[1,2,3]<[1,2,4], [2,1,2]>[1,2,2]
   */
  int compare(const Value &left, const Value &right) const override;

  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;

  /***
   * @brief 将向量转换为字符串，输出的格式为：[x1,x2,...,xn],其中，数值最多保留小数点后2位，并去掉多余的0
   */
  RC to_string(const Value &val, string &result) const override;

private:
  //仅限于内部使用的枚举类型，用来方便传参表示算数操作的类型
  enum ArithmeticOperation
  {
    ADD,
    SUBTRACT,
    MULTIPLY
  };

  /***
   * @brief 封装向量的各种运算，传入不同的运算符号，最终根据这个运算符，将左右向量的值依次对应执行运算操作，得到结果
   */
  static RC vector_arithmetic_operation(const Value &left, const Value &right, Value &result, ArithmeticOperation op);
};