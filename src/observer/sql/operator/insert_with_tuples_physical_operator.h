//
// Created by WangYunlai on 2024/10/30.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/tuple.h"
#include <vector>

class CreateTableSelectStmt;

/**
 * @brief 插入tuple物理算子
 * @ingroup PhysicalOperator
 */
class InsertTuplesPhysicalOperator : public PhysicalOperator
{
public:
  InsertTuplesPhysicalOperator(Table *table);

  virtual ~InsertTuplesPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::INSERT_TUPLES; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table             *table_ = nullptr;
  Trx                *trx_   = nullptr;
};