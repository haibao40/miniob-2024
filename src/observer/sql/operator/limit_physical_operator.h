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
class LimitPhysicalOperator : public PhysicalOperator
{

public:
  LimitPhysicalOperator(int limit_count);
  virtual ~LimitPhysicalOperator() = default;
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
  RC tuple_schema(TupleSchema &schema) const override;
  PhysicalOperatorType type() const override { return PhysicalOperatorType::LIMIT; }
protected:
  int limit_count_;
  int current_count_ = 0 ;
};