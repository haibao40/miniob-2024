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

#include "sql/stmt/delete_stmt.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "storage/view/view.h"
#include "sql/parser/expression_binder.h"

DeleteStmt::DeleteStmt(Table *table, FilterStmt *filter_stmt) : table_(table), filter_stmt_(filter_stmt) {}

DeleteStmt::~DeleteStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC DeleteStmt::create(Db *db, const DeleteSqlNode &delete_sql, Stmt *&stmt)
{
  const char *table_name = delete_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  View* view = db->find_view(table_name);
  if(view != nullptr){
    if(!view->delete_capacity()){
      return RC::UNSUPPORTED;
    }
    return create_with_view(db, view, delete_sql, stmt);
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, delete_sql.conditions.data(), static_cast<int>(delete_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new DeleteStmt(table, filter_stmt);
  return rc;
}

RC DeleteStmt::create_with_view(Db *db, View* view, const DeleteSqlNode &delete_sql, Stmt *&stmt){
  ViewMeta view_meta = view->view_meta();
  DeleteSqlNode* d_sql = const_cast<DeleteSqlNode *>(&delete_sql);

  if(view_meta.field_num() < 1){
    return RC::UNIMPLEMENTED;
  }
  d_sql->relation_name = view_meta.field(0)->table_name();

  std::vector<ConditionSqlNode> conditions;
  get_conditions(db, view, conditions, d_sql->conditions);
  d_sql->conditions.swap(conditions);

  return create(db, *d_sql, stmt);
}

RC DeleteStmt::get_conditions(Db* db, View *view, std::vector<ConditionSqlNode> &conditions,
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
