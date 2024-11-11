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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    if(conditions[i].conjunction_with_or == true) {
      tmp_stmt->conjunction_with_or = true;
    }

    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    // auto iter = tables->find(attr.relation_name);

    auto iter = tables->begin();
    for(; iter != tables->end(); iter++){
      if(iter->first.find(attr.relation_name) != std::string::npos){
        break;
      }
    }

    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  //替换掉relAttrSqlNode，变成对应的UnboundFieldExpr,让它走表达式的绑定流程，方便处理
  replace_relAttrSqlNode_to_expr(const_cast<ConditionSqlNode&>(condition));

  filter_unit = new FilterUnit;

  if(condition.left_is_expr){
    FilterObj filter_obj(condition.left_expr);

    BinderContext binder_context;
    for(const auto &name_table :*tables){
      Table* table = name_table.second;
      binder_context.add_table(table);
    }

    if(filter_obj.expr->type() == ExprType::UNBOUND_FIELD){
      auto unbound_field_expr = static_cast<UnboundFieldExpr *>(filter_obj.expr.get());
      for(const auto& pair : *tables){
        if(pair.first.find(unbound_field_expr->table_name()) != std::string::npos){
          const char* table_name = pair.second->name();//strcasecmp(pair.first.c_str(), unbound_field_expr->table_name()) == 0
          unbound_field_expr->set_table_name(table_name);
          binder_context.add_table_alias(table_name, unbound_field_expr->table_name());
          break;
        }
      }
    }

    vector<unique_ptr<Expression>> bound_expressions;
    ExpressionBinder expression_binder(binder_context);

    RC rc = expression_binder.bind_expression(filter_obj.expr, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    filter_unit->set_left(std::move(bound_expressions[0]));
  } else if (condition.left_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(std::move(filter_obj));
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(std::move(filter_obj));
  }

  if(condition.right_is_expr){
    FilterObj filter_obj(condition.right_expr);

    BinderContext binder_context;
    for(const auto &name_table :*tables){
      Table* table = name_table.second;
      binder_context.add_table(table);
    }
    vector<unique_ptr<Expression>> bound_expressions;
    ExpressionBinder expression_binder(binder_context);

    RC rc = expression_binder.bind_expression(filter_obj.expr, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    filter_unit->set_right(std::move(bound_expressions[0]));
  } else if (condition.right_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(std::move(filter_obj));
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(std::move(filter_obj));
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}


void FilterStmt::replace_relAttrSqlNode_to_expr(ConditionSqlNode &condition)
{
  if(condition.left_is_attr) {
    auto left_attr_node = condition.left_attr;
    UnboundFieldExpr *unbound_field_expr = new UnboundFieldExpr(left_attr_node.relation_name.c_str(),
      left_attr_node.attribute_name.c_str(), left_attr_node.alias.c_str());
    condition.left_expr = unbound_field_expr;
    condition.left_is_attr = 0;
    condition.left_is_expr = 1;
  }
  if(condition.right_is_attr) {
    auto right_attr_node = condition.right_attr;
    UnboundFieldExpr *unbound_field_expr = new UnboundFieldExpr(right_attr_node.relation_name.c_str(),
      right_attr_node.attribute_name.c_str(), right_attr_node.alias.c_str());
    condition.right_expr = unbound_field_expr;
    condition.right_is_attr = 0;
    condition.right_is_expr = 1;
  }
}
