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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"
#include <iostream>

class Table;
class FilterStmt;
class View;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, std::vector<UpdateUnite>& update_unites, FilterStmt *filter_stmt);

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);
  static RC create_with_view(Db *db, View* view, UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const { return table_; }
  std::vector<UpdateUnite>& update_unites()  {return update_unites_;}
  FilterStmt *filter_stmt() const {return filter_stmt_;}

private:
  Table *table_               = nullptr;
  std::vector<UpdateUnite>    update_unites_;   /// 要更新的字段以及对应的值,对应的值可能是常量表达式，也可能是子查询
  FilterStmt *filter_stmt_    = nullptr;

public:
  static RC get_conditions(Db* db, View *view, std::vector<ConditionSqlNode> &conditions,
  std::vector<ConditionSqlNode> &true_conditions);
};
