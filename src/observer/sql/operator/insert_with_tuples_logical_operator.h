//
// Created by lml on 2024/10/30.
//

#pragma once

#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 插入tuple逻辑算子,顾名思义，把子算子的tuple插入对应表中
 * @ingroup LogicalOperator
 */
class InsertTuplesLogicalOperator : public LogicalOperator
{
public:
  InsertTuplesLogicalOperator(Table *table);
  virtual ~InsertTuplesLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::INSERT_TUPLES; }

  Table                    *table() const { return table_; }

private:
  Table             *table_ = nullptr;
};