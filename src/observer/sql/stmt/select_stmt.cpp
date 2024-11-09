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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "storage/view/view.h"
#include "sql/parser/expression_binder.h"
#include "sql/parser/hierarchical_scope.h"

#include "common/global_variable.h"

using namespace std;
using namespace common;

unordered_map<string, AggregateExpr::Type> string2type = {
  {"sum", AggregateExpr::Type::SUM },
  {"max", AggregateExpr::Type::MAX},
  {"min", AggregateExpr::Type::MIN},
  {"avg", AggregateExpr::Type::AVG},
  {"count", AggregateExpr::Type::COUNT}
};

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  //如果查询的是视图
  for(auto it:select_sql.relations){
    if(db->find_view(it.first.c_str()) != nullptr){
      return create_with_view(db, select_sql, stmt);
    }
  }

  // 将表和字段的信息记录到 当前查询的作用域中，包括了别名等信息，关联子查询可能会用到这些东西
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->scope_ = new HierarchicalScope(); 
  //如果是子查询，parent会指向上一级查询，如果是最外层查询，parent会指向空指针nullptr
  select_stmt->parent_ = GlobalVariable::curren_resolve_select_stmt;
  if(GlobalVariable::curren_resolve_select_stmt != nullptr) {
    select_stmt->scope_->parent = GlobalVariable::curren_resolve_select_stmt->scope_;
  }
  // 将表和字段的信息记录到 当前查询的作用域中，包括了别名等信息，关联子查询可能会用到这些东西
  RC rc = SelectStmt::add_table_and_field_info_to_scope(db,select_sql, select_stmt);
  if(rc != RC::SUCCESS) {
    return rc;
  }
  GlobalVariable::curren_resolve_select_stmt = select_stmt;   //在全局变量中，记录当前的select_stmt，以便在解析子查询时使用

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    auto it = select_sql.relations.begin(); // 获取指向第一个元素的迭代器
    std::advance(it, i);
    const char *table_name = it->first.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table_alias(table_name, it->second.c_str());
    binder_context.add_table(table);
    tables.push_back(table);
    // table_map.insert({table_name, table});
    table_map.insert({it->second, table});
  }
  //李晓鹏 这里是处理未绑定的问题 将unbound... Expr 转化为 普通的expr
  // collect query fields in `select` statement 
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    //如果有字段表达式，就要检查表名是否为设置的别名，是则把名字改回来
    if(expression.get()->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expression.get());
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
    
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  /*   找到条件表达式中的未绑定字段表达式   */
  for(ConditionSqlNode condition : select_sql.conditions){
    if(condition.left_is_expr && condition.left_expr->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(condition.left_expr);
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
    if(condition.right_is_expr && condition.right_expr->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(condition.right_expr);
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
  }
  /*   找到条件表达式中的未绑定字段表达式   */

  vector<unique_ptr<Expression>> having_expressions;
  for(ConditionSqlNode condition: select_sql.having){
    //找到聚合表达式指针,讲其加入到having_expressions_中去,找到就给它绑定咯
    if(condition.left_is_expr && condition.left_expr->type() == ExprType::UNBOUND_AGGREGATION)
    {
      Expression * tmp = new UnboundAggregateExpr(dynamic_cast<UnboundAggregateExpr*>(condition.left_expr));
      unique_ptr <Expression> having_expression(static_cast<Expression *>(tmp));
      RC rc = expression_binder.bind_expression(having_expression, having_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind having_expression failed. rc=%s", strrc(rc));
        return rc;
      }
    }
    //左右都要找
    if(condition.right_is_expr && condition.right_expr->type() == ExprType::UNBOUND_AGGREGATION)
    {
      Expression * tmp = new UnboundAggregateExpr(dynamic_cast<UnboundAggregateExpr*>(condition.right_expr));
      unique_ptr <Expression> having_expression(static_cast<Expression *>(tmp));
      RC rc = expression_binder.bind_expression(having_expression, having_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind having_expression failed. rc=%s", strrc(rc));
        return rc;
      }
    }
  }

  // 李晓鹏笔记 select_sql_order_by 是解析出来后面的条件
  vector<unique_ptr<Expression>> order_by_expressions;
    for (unique_ptr<Expression> &expression : select_sql.order_by) {
    RC rc = expression_binder.bind_expression(expression, order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind order_by_expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }


  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  //多加一个过滤stmt
  FilterStmt *having_filter_stmt = nullptr;
  rc                             = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.having.data(),
      static_cast<int>(select_sql.having.size()),
      having_filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having_filter stmt");
    return rc;
  }
  //处理on条件的 和上面的where是一样的 只是这里是个循环 有多个on条件
  std::vector<std::vector<ConditionSqlNode>*>  join_conditions_sql_node = select_sql.join_conditions;
  std::vector<FilterStmt*> join_filter;
  for(std::vector<ConditionSqlNode>* &on_conditions_ptr : join_conditions_sql_node){
     std::vector<ConditionSqlNode> on_conditions = *on_conditions_ptr;
     FilterStmt * join_filter_stmt = nullptr;
     RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      on_conditions.data(),
      static_cast<int>(on_conditions.size()),
      join_filter_stmt);
      if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
    }
      join_filter.push_back(join_filter_stmt);
  }

  // everything alright

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_        = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->having_expressions_.swap(having_expressions);
  select_stmt->having_filter_stmt_ = having_filter_stmt;
  select_stmt->order_by_.swap(order_by_expressions);
  select_stmt->join_filter_.swap(join_filter);
  stmt                      = select_stmt;
  GlobalVariable::curren_resolve_select_stmt = select_stmt->parent_;   //回溯,因为可能存在一个外层查询有多个子查询的情况
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    auto it = select_sql.relations.begin(); // 获取指向第一个元素的迭代器
    std::advance(it, i);
    const char *table_name = it->first.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table_alias(table_name, it->second.c_str());
    binder_context.add_table(table);
    tables.push_back(table);
    // table_map.insert({table_name, table});
    table_map.insert({it->second, table});
  }
  //李晓鹏 这里是处理未绑定的问题 将unbound... Expr 转化为 普通的expr
  // collect query fields in `select` statement 
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    //如果有字段表达式，就要检查表名是否为设置的别名，是则把名字改回来
    if(expression.get()->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expression.get());
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
    
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  /*   找到条件表达式中的未绑定字段表达式   */
  for(ConditionSqlNode condition : select_sql.conditions){
    if(condition.left_is_expr && condition.left_expr->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(condition.left_expr);
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
    if(condition.right_is_expr && condition.right_expr->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(condition.right_expr);
      for(const auto& pair : select_sql.relations){
        if(strcasecmp(pair.second.c_str(), unbound_field_expr->table_name()) == 0){
          unbound_field_expr->set_table_name(pair.first);
          break;
        }
      }
    }
  }
  /*   找到条件表达式中的未绑定字段表达式   */

  vector<unique_ptr<Expression>> having_expressions;
  for(ConditionSqlNode condition: select_sql.having){
    //找到聚合表达式指针,讲其加入到having_expressions_中去,找到就给它绑定咯
    if(condition.left_is_expr && condition.left_expr->type() == ExprType::UNBOUND_AGGREGATION)
    {
      Expression * tmp = new UnboundAggregateExpr(dynamic_cast<UnboundAggregateExpr*>(condition.left_expr));
      unique_ptr <Expression> having_expression(static_cast<Expression *>(tmp));
      RC rc = expression_binder.bind_expression(having_expression, having_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind having_expression failed. rc=%s", strrc(rc));
        return rc;
      }
    }
    //左右都要找
    if(condition.right_is_expr && condition.right_expr->type() == ExprType::UNBOUND_AGGREGATION)
    {
      Expression * tmp = new UnboundAggregateExpr(dynamic_cast<UnboundAggregateExpr*>(condition.right_expr));
      unique_ptr <Expression> having_expression(static_cast<Expression *>(tmp));
      RC rc = expression_binder.bind_expression(having_expression, having_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind having_expression failed. rc=%s", strrc(rc));
        return rc;
      }
    }
  }

  // 李晓鹏笔记 select_sql_order_by 是解析出来后面的条件
  vector<unique_ptr<Expression>> order_by_expressions;
    for (unique_ptr<Expression> &expression : select_sql.order_by) {
    RC rc = expression_binder.bind_expression(expression, order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind order_by_expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }


  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  //多加一个过滤stmt
  FilterStmt *having_filter_stmt = nullptr;
  rc                             = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.having.data(),
      static_cast<int>(select_sql.having.size()),
      having_filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having_filter stmt");
    return rc;
  }
  //处理on条件的 和上面的where是一样的 只是这里是个循环 有多个on条件
  std::vector<std::vector<ConditionSqlNode>*>  join_conditions_sql_node = select_sql.join_conditions;
  std::vector<FilterStmt*> join_filter;
  for(std::vector<ConditionSqlNode>* &on_conditions_ptr : join_conditions_sql_node){
     std::vector<ConditionSqlNode> on_conditions = *on_conditions_ptr;
     FilterStmt * join_filter_stmt = nullptr;
     RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      on_conditions.data(),
      static_cast<int>(on_conditions.size()),
      join_filter_stmt);
      if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
    }
      join_filter.push_back(join_filter_stmt);
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_        = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->having_expressions_.swap(having_expressions);
  select_stmt->having_filter_stmt_ = having_filter_stmt;
  select_stmt->order_by_.swap(order_by_expressions);
  select_stmt->join_filter_.swap(join_filter);
  stmt                      = select_stmt;
  return RC::SUCCESS;
}

RC SelectStmt::add_table_and_field_info_to_scope(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt)
{
  vector<Table *> tables; //用来记录这个select用到的所有表
  //将表及其别名的信息添加进入当前查询对应的作用域
  for (const auto &table_name2alias_pair : select_sql.relations) {
    Table* table = db->find_table(table_name2alias_pair.first.c_str());
    if(table == nullptr) {
      LOG_WARN("要查找的表不存在，table_name:%s", table_name2alias_pair.first.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    if(stmt->scope_->name2table.find(table_name2alias_pair.second) != stmt->scope_->name2table.end()) {
      LOG_WARN("别名已经存在，在同一层的查询中使用了重复的别名，sql不合法");
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    stmt->scope_->name2table[table_name2alias_pair.first] = table;  // 添加<表名，表对象>的映射
    stmt->scope_->name2table[table_name2alias_pair.second] = table; // 添加<表别名，表对象>的映射
    tables.push_back(table);
  }

  //将字段名及其别名添加进入当前查询对应的作用域，只需要查找select_sql.expressions，因为字段的别名只会在这里定义
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    if(expression->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expression.get());
      Table* match_table = nullptr;
      std::string table_name = unbound_field_expr->table_name();
      std::string field_alias = unbound_field_expr->field_alias();
      if(!field_alias.empty()) {  //别名属性不是空，说明这里为字段设置了别名,需要记录进对应的map
        //尝试通过表名找到表,注意，这里的表名也可能是别名，但是解析阶段是将它当做表名记录的
        if(stmt->scope_->name2table.find(table_name) != stmt->scope_->name2table.end()) {
          match_table = stmt->scope_->name2table[table_name];
        }
        else { //没有通过表名找到，就是没有使用表名,那么这个列的名字不应该重复，直接扫描所有的表去查找即可
          for(Table* table: tables) {
            const FieldMeta* field_meta = table->table_meta().field(unbound_field_expr->field_name());
            if(field_meta != nullptr) {
              match_table = table;
              break;
            }
          }
        }
        if(match_table != nullptr) {
          const FieldMeta* field_meta = match_table->table_meta().field(unbound_field_expr->field_name());
          if(field_meta != nullptr) { //找到了
            FieldInfo field_info;
            field_info.table_name = match_table->name();
            field_info.field_alias = field_alias;
            field_info.field_name = field_meta->name();
            field_info.attr_type = field_meta->type();
            stmt->scope_->name2field_info[field_alias] = field_info;
            break;
          }
        }
        else {
          LOG_ERROR("没有找到别名实际对应的字段，别名：%s", unbound_field_expr->field_alias());
          return RC::FILE_NOT_EXIST;
        }
      }
    }
  }
  return RC::SUCCESS;
}


RC SelectStmt::replace_alias_to_real_name(Db *db, SelectSqlNode &select_sql, SelectStmt *&stmt)
{
  return RC::SUCCESS;
}

RC SelectStmt::create_with_view(Db *db, SelectSqlNode &select_sql, Stmt *&stmt){
  //手搓一个selectsqlnode出来
  SelectSqlNode new_select_sql;
  //get View and ViewMeta
  //这里假设一次就查一个view
  View* view = db->find_view(select_sql.relations.begin()->first.c_str());
  ViewMeta view_meta = view->view_meta();

  /* get tables */
  std::unordered_map<std::string, std::string> tables;
  const std::vector<ViewFieldMeta>* view_field_metas = view_meta.field_metas();
  for(int i = 0; i < view_meta.field_num(); i++){
    ViewFieldMeta view_field_meta =  (*view_field_metas)[i];
    if(tables.find(view_field_meta.table_name()) == tables.end()){
      tables.insert({view_field_meta.table_name(), view_field_meta.table_name()});
    }
  }
  new_select_sql.relations.swap(tables);

  /* handle query_expressions */
  std::vector<unique_ptr<Expression>> query_expressions;
  get_query_expressions(view, query_expressions, select_sql.expressions);
  new_select_sql.expressions.swap(query_expressions);
  /* handle query_expressions */
  
  /* handle conditionss : 有两个条件需要处理，一个是view的，一个是select的，且都可能为空 */
  std::vector<ConditionSqlNode> conditions;
  get_conditions(db, view, conditions, select_sql.conditions);
  new_select_sql.conditions.swap(conditions);
  /* handle conditionss */

  return create(db, new_select_sql, stmt);
  // return RC::SUCCESS;
}

RC SelectStmt::get_query_expressions(View *view, std::vector<unique_ptr<Expression>> &query_expressions,
                             std::vector<unique_ptr<Expression>> &true_query_expressions){
    ViewMeta view_meta = view->view_meta();

    for (unique_ptr<Expression> &expression : true_query_expressions){
      if(expression.get()->type() == ExprType::UNBOUND_FIELD){
        auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expression.get());
        const char* query_field_name = unbound_field_expr->field_name(); //拿个名字
        const ViewFieldMeta *view_field_meta = view_meta.field(query_field_name); //根据名字找到对应的元数据

        if(view_field_meta->type() == ExprType::FIELD){
          UnboundFieldExpr* expr = new UnboundFieldExpr(view_field_meta->table_name(),
          view_field_meta->field_name(), query_field_name);
          expr->set_name(query_field_name);
          query_expressions.emplace_back(std::move(expr));
        }  
        else if(view_field_meta->type() == ExprType::ARITHMETIC){
          BinderContext binder_context;
          ExpressionBinder expression_binder(binder_context); //不干啥，就是调用了下函数

          size_t pos = 0;
          //如果表达式有多个表的字段，暂时干不了这活
          ArithmeticExpr* expr = static_cast<ArithmeticExpr *>(expression_binder.parseExpression(view_field_meta->field_name(),
          pos, view_field_meta->table_name()));
          expr->set_name(query_field_name);
          query_expressions.emplace_back(std::move(expr));
        }
        else if(view_field_meta->type()  == ExprType::AGGREGATION){
          if(std::string(query_field_name).find("(") != std::string::npos){
            const char* field_name = std::string(query_field_name).substr(std::string(query_field_name).find("(") + 1,
            std::string(query_field_name).find(")")- std::string(query_field_name).find("(") - 1).c_str();
            UnboundFieldExpr* child = new UnboundFieldExpr("", field_name);
            UnboundAggregateExpr* expr = new UnboundAggregateExpr(
              std::string(query_field_name).substr(0, std::string(query_field_name).find("(")).c_str(), child
            );
            expr->set_name(query_field_name);
            query_expressions.emplace_back(std::move(expr));
          }else{
            std::string sql_text = view_field_meta->field_name();
            const char* field_name = sql_text.substr(sql_text.find("(")+1,
            sql_text.find(")") - sql_text.find("(") - 1).c_str();
            UnboundFieldExpr* child = new UnboundFieldExpr("", field_name);
            UnboundAggregateExpr* expr = new UnboundAggregateExpr(
              sql_text.substr(0, sql_text.find("(")).c_str(), child
            );
            expr->set_name(query_field_name);
            query_expressions.emplace_back(std::move(expr));
          }
        }
      }
      else if(expression.get()->type() == ExprType::STAR){
        for(int i = 0; i < view_meta.field_num(); i++){
          const ViewFieldMeta *view_field_meta = view_meta.field(i);
          const char* query_field_name = view_field_meta->name();
          if(view_field_meta->type() == ExprType::FIELD){
            UnboundFieldExpr* expr = new UnboundFieldExpr(view_field_meta->table_name(),
            view_field_meta->field_name(), query_field_name);
            expr->set_name(query_field_name);
            query_expressions.emplace_back(std::move(expr));
          }  
          else if(view_field_meta->type() == ExprType::ARITHMETIC){
            BinderContext binder_context;
            ExpressionBinder expression_binder(binder_context); //不干啥，就是调用了下函数

            size_t pos = 0;
            //如果表达式有多个表的字段，暂时干不了这活
            ArithmeticExpr* expr = static_cast<ArithmeticExpr *>(expression_binder.parseExpression(view_field_meta->field_name(),
            pos, view_field_meta->table_name()));
            expr->set_name(query_field_name);
            query_expressions.emplace_back(std::move(expr));
          }
          else if(view_field_meta->type()  == ExprType::AGGREGATION){
            if(std::string(query_field_name).find("(") != std::string::npos){
              const char* field_name = std::string(query_field_name).substr(std::string(query_field_name).find("(") + 1,
              std::string(query_field_name).find(")")- std::string(query_field_name).find("(") - 1).c_str();
              UnboundFieldExpr* child = new UnboundFieldExpr("", field_name);
              UnboundAggregateExpr* expr = new UnboundAggregateExpr(
                std::string(query_field_name).substr(0, std::string(query_field_name).find("(")).c_str(), child
              );
              expr->set_name(query_field_name);
              query_expressions.emplace_back(std::move(expr));
            }else{
              std::string sql_text = view_field_meta->field_name();
              const char* field_name = sql_text.substr(sql_text.find("(")+1,
              sql_text.find(")") - sql_text.find("(") - 1).c_str();
              UnboundFieldExpr* child = new UnboundFieldExpr("", field_name);
              UnboundAggregateExpr* expr = new UnboundAggregateExpr(
                sql_text.substr(0, sql_text.find("(")).c_str(), child
              );
              expr->set_name(query_field_name);
              query_expressions.emplace_back(std::move(expr));
            }
          }
        }
      }else if(expression.get()->type() == ExprType::UNBOUND_AGGREGATION){
        auto unbound_agg_expr = static_cast<UnboundAggregateExpr *>(expression.get());
        Expression* child = nullptr;
        if(unbound_agg_expr->child().get()->type() == ExprType::UNBOUND_FIELD){
          auto child_expr = static_cast<UnboundFieldExpr* >(unbound_agg_expr->child().get());
          const char* query_field_name = child_expr->field_name(); //拿个名字
          const ViewFieldMeta *view_field_meta = view_meta.field(query_field_name); //根据名字找到对应的元数据

          child = new UnboundFieldExpr(view_field_meta->table_name(), query_field_name, query_field_name);
          child->set_name(query_field_name);
        }else if(unbound_agg_expr->child().get()->type() == ExprType::STAR){
          child = new StarExpr();
        }
        UnboundAggregateExpr* expr = new UnboundAggregateExpr(unbound_agg_expr->aggregate_name(), child);
        expr->set_name(unbound_agg_expr->name());
        query_expressions.emplace_back(expr);
      }
    }
  
    return RC::SUCCESS;
}

RC SelectStmt::get_conditions(Db* db, View *view, std::vector<ConditionSqlNode> &conditions,
  std::vector<ConditionSqlNode> &true_conditions){
  const ViewMeta view_meta = view->view_meta();

  for(int i = 0; i < view_meta.con_num(); i++){
    const ConditionMeta *view_con_meta = view_meta.con(i);
    ConditionSqlNode condition;
    condition.comp = view_con_meta->comp();
    condition.left_is_expr = 1;
    condition.right_is_expr = 1;

    //将左表达式初始化过滤单元
    if(view_con_meta->left_is_attr()){
      Table* table = db->find_table(view_con_meta->left_table_name());
      const FieldMeta* field_meta = table->table_meta().field(view_con_meta->left_field_name());
      FieldExpr* expr = new FieldExpr(table, field_meta);
      condition.left_expr = expr;
    }else{
      ValueExpr* expr = new ValueExpr(Value(view_con_meta->left_value()));
      condition.left_expr = expr;
    }

    //将右表达式初始化过滤单元
    if(view_con_meta->right_is_attr()){
      Table* table = db->find_table(view_con_meta->right_table_name());
      const FieldMeta* field_meta = table->table_meta().field(view_con_meta->right_field_name());
      FieldExpr* expr = new FieldExpr(table, field_meta);
      condition.right_expr = expr;
    }else{
      ValueExpr* expr = new ValueExpr(Value(view_con_meta->right_value()));
      condition.right_expr = expr;
    }

    conditions.emplace_back(condition);
  }

  for(int i = 0; i < true_conditions.size(); i++){
    ConditionSqlNode condition = true_conditions[i];
    condition.left_is_expr = 1;

    if(condition.left_is_attr){
      const char* query_field_name = condition.left_attr.attribute_name.c_str(); //拿个名字
      const ViewFieldMeta *view_field_meta = view_meta.field(query_field_name); //根据名字找到对应的元数据

      if(view_field_meta->type() == ExprType::FIELD){
        UnboundFieldExpr* expr = new UnboundFieldExpr(view_field_meta->table_name(),
        view_field_meta->field_name(), query_field_name);
        expr->set_name(query_field_name);
        condition.left_expr = expr;
      }  //算术表达式绑定不了
      else if(view_field_meta->type() == ExprType::ARITHMETIC){
        BinderContext binder_context;
        ExpressionBinder expression_binder(binder_context); //不干啥，就是调用了下函数

        size_t pos = 0;
        //如果表达式有多个表的字段，暂时干不了这活
        ArithmeticExpr* expr = static_cast<ArithmeticExpr *>(expression_binder.parseExpression(view_field_meta->field_name(),
        pos, view_field_meta->table_name()));
        expr->set_name(query_field_name);
        condition.left_expr = expr;
      }
    }else{
      condition.left_expr = new ValueExpr(condition.left_value);
    }

    if(condition.right_expr->type() == ExprType::UNBOUND_FIELD){
      UnboundFieldExpr* unbound_field_expr = static_cast<UnboundFieldExpr *>(condition.right_expr);
      const char* query_field_name = unbound_field_expr->field_name() ; //拿个名字
      const ViewFieldMeta *view_field_meta = view_meta.field(query_field_name); //根据名字找到对应的元数据

      if(view_field_meta->type() == ExprType::FIELD){
        UnboundFieldExpr* expr = new UnboundFieldExpr(view_field_meta->table_name(),
        view_field_meta->field_name(), query_field_name);
        expr->set_name(query_field_name);
        condition.right_expr = expr;
      }  //算术表达式绑定不了
      else if(view_field_meta->type() == ExprType::ARITHMETIC){
        BinderContext binder_context;
        ExpressionBinder expression_binder(binder_context); //不干啥，就是调用了下函数

        size_t pos = 0;
        //如果表达式有多个表的字段，暂时干不了这活
        ArithmeticExpr* expr = static_cast<ArithmeticExpr *>(expression_binder.parseExpression(view_field_meta->field_name(),
        pos, view_field_meta->table_name()));
        expr->set_name(query_field_name);
        condition.right_expr = expr;
      }
    }
    conditions.emplace_back(condition);
  }
  return RC::SUCCESS;
}