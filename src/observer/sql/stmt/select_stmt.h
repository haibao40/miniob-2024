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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class View;
class FilterStmt;
class Db;
class Table;
class HierarchicalScope;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  ///这个是正常的针对select语句
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);
  ///这个函数是专门为create_table_select的select子查询创建select_stmt使用的
  static RC create(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt);
  ///这个函数是针对select view
  static RC create_with_view(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

private:
  /***
   * @brief 将表和字段的信息记录到 HierarchicalScope 变量的作用域中，包括了别名等信息，关联子查询可能会用到这些东西
   */
  static RC add_table_and_field_info_to_scope(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt);
  /***
   * @brief 在现阶段，将别名替换为真实的名字，需要处理select后面的表达式，以及where后面的表达式,
   *        TODO:目前，这里先不进行实现，因为题目中的别名使用场景相对简单，遇到问题后，再到这里进行处理
   *        case1: 表的别名.字段名 ---->  表的真实名.字段名
   *        case2: 字段别名       ---->  表的真实名.字段名
   */
  static RC replace_alias_to_real_name(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }
  FilterStmt                 *having_filter_stmt() const { return having_filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &having_expressions() {return having_expressions_;}
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  std::vector<std::unique_ptr<Expression>> &order_by() { return order_by_; }
  std::vector<FilterStmt*>   &join_filter(){return join_filter_; }
private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<Table *>                     tables_;
  FilterStmt                              *filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<std::unique_ptr<Expression>> having_expressions_;
  FilterStmt                              *having_filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> order_by_;
  std::vector<FilterStmt*> join_filter_;
public:
  HierarchicalScope* scope_ = nullptr;   //当前子查询对应的作用域
  SelectStmt*  parent_ = nullptr; //当前子查询对应的上层查询的select_stmt
public:
  static RC get_query_expressions(View *view, std::vector<unique_ptr<Expression>> &query_expressions,
                             std::vector<unique_ptr<Expression>> &true_query_expressions);

  static RC get_filter_units(View *view, std::vector<ConditionSqlNode> &conditions,
  std::vector<FilterUnit *> &filter_units);
};
