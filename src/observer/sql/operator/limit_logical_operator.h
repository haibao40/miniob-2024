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

#include "sql/operator/logical_operator.h"

class LimitLogicalOperator : public LogicalOperator
{
public:

  LimitLogicalOperator(int limit_count);
  virtual ~LimitLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::LIMIT ;}

  int &limit_count() { return limit_count_; }

private:
    int limit_count_; ///< 输出的表达式，可能包含聚合函数
};