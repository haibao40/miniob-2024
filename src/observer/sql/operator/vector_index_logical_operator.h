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
// Created by Wangyunlai on 2022/12/07.
//
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "common/types.h"

/**
 * @brief 表示从表中获取数据的算子
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class VectorIndexLogicalOperator : public LogicalOperator
{
public:
  VectorIndexLogicalOperator(Table *table, ReadWriteMode mode);
  VectorIndexLogicalOperator(Table *table, ReadWriteMode mode,int limit,std::vector<std::unique_ptr<Expression>>& expressions);
  virtual ~VectorIndexLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::VectorIndex; }

  Table        *table() const { return table_; }
  int limit(){return limit_;}
  int distance_type(){return distance_type_;}
  string index_name_P(){return index_name_p_; }
  vector<float> base_vector(){return base_vector_;}
  IvfflatIndex* index(){return index_;}
private:
private:
  Table        *table_ = nullptr;
  ReadWriteMode mode_  = ReadWriteMode::READ_WRITE;
  vector<float> base_vector_;
  int limit_ = -1;
  int distance_type_ = -1;
  std::string index_name_p_;
  IvfflatIndex* index_ = nullptr;
  // 与当前表相关的过滤操作，可以尝试在遍历数据时执行
  // 这里的表达式都是比较简单的比较运算，并且左右两边都是取字段表达式或值表达式
  // 不包含复杂的表达式运算，比如加减乘除、或者conjunction expression
  // 如果有多个表达式，他们的关系都是 AND
  std::vector<std::unique_ptr<Expression>> predicates_;
};
