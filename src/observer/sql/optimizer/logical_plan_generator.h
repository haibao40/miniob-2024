/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#pragma once

#include <memory>

#include "common/rc.h"
#include "common/type/attr_type.h"
#include "sql/expr/expression.h"

class Stmt;
class CalcStmt;
class SelectStmt;
class FilterStmt;
class InsertStmt;
class DeleteStmt;
class UpdateStmt;
class ExplainStmt;
class LogicalOperator;
class PhysicalOperator;

class LogicalPlanGenerator
{
public:
  LogicalPlanGenerator()          = default;
  virtual ~LogicalPlanGenerator() = default;

  RC create(Stmt *stmt, std::unique_ptr<LogicalOperator> &logical_operator);

private:
  RC create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(FilterStmt *filter_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(InsertStmt *insert_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(DeleteStmt *delete_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(ExplainStmt *explain_stmt, std::unique_ptr<LogicalOperator> &logical_operator);

  RC create_group_by_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_order_by_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);

  /***
  * @brief 这里是直接为子查询生成物理算子,生成的物理算子存放在子查询的物理算子中属性中,也就是说，上层查询在生成逻辑算子的时候，下层子查询就已经生成好物理算子了
  */
  RC create_sub_query_physicalOperator_plan(SubqueryExpr* subquery_expr);

  int implicit_cast_cost(AttrType from, AttrType to);
};