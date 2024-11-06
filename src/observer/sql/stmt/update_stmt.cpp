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

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <vector>
#include "common/global_variable.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<UpdateUnite>& update_unites, FilterStmt *filter_stmt)
    : table_(table), update_unites_(update_unites) , filter_stmt_(filter_stmt)
{}


RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  //确定更新的表是否存在
  const char* table_name = update.table_name.c_str();
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  //确定要更新的字段是否存在
  for(size_t i = 0; i < update.update_unites.size();i++) {
    const char* update_field_name = update.update_unites[i].field_name.c_str();
    const FieldMeta* field_meta = table->table_meta().field(update_field_name);
    if(field_meta == nullptr) {
      LOG_INFO("要更新的字段不存在");
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  //表达式中可能存在子查询，为子查询创建stmt,实现将UnboundSubqueryExpr转换为BoundSubqueryExpr
  for(size_t i = 0; i < update.update_unites.size();i++) {
    UpdateUnite& update_unite = update.update_unites[i];
    Expression* expr = update_unite.expression;
    if(expr->type() == ExprType::UNBOUND_SUBQUERY) {
      auto unbound_sub_query_expr = static_cast<UnboundSubqueryExpr *>(expr);
      ParsedSqlNode* parsed_sql_node = unbound_sub_query_expr->parsed_sql_node();  // 子查询对应的sql_node
      Stmt          *stmt     = nullptr;
      // 对子查询进行resolve TODO:如果是相关子查询，这里需要适当的调整
      RC rc = Stmt::create_stmt(GlobalVariable::db, *parsed_sql_node, stmt);  // 对子查询进行resolve
      SubqueryExpr *subquery_expr = new SubqueryExpr((SelectStmt*) stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create stmt for sub query . rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      update_unite.expression = subquery_expr;  //将update_unite中的表达式替换为subquery_expr
    }
  }

  //根据where过滤条件构造FilterStmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(update.table_name, table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions.data(),
                             static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, update.update_unites , filter_stmt);
  
  return RC::SUCCESS;
}
