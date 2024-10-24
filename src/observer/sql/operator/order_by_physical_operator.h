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
// Created by WangYunlai on 2024/05/29.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/composite_tuple.h"

/**
 * @brief Group By 物理算子基类
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{

public:
  int index_current = 0 ;
  int size = 0 ;
  bool is_sorted = false ;
  std::unique_ptr<std::vector<Tuple*>> tuple_sorted = std::make_unique<std::vector<Tuple*>>();
  std::unique_ptr<std::vector<TupleCellSpec *>> sorted_columns = std::make_unique<std::vector<TupleCellSpec *>>();
  std::unique_ptr<std::vector<bool>> sorted_is_asc = std::make_unique<std::vector<bool>>();
  OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>  &&expressions);
  virtual ~OrderByPhysicalOperator() = default;
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  RC get_all_tuple();
  RC sorted()  ;
  RC sorteTuples();
  Tuple *current_tuple() override;
  RC tuple_schema(TupleSchema &schema) const override;
  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }
  RC set_sorted_columns(); //初始化排序的资源
protected:
  std::vector<unique_ptr<Expression>> order_expressions_;  /// 排序表达式
};