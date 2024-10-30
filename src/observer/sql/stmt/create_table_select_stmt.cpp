//
// Created by limaoliang on 2022/6/6.
//

#include "sql/stmt/create_table_select_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

CreateTableSelectStmt::~CreateTableSelectStmt()
{
  if (nullptr != select_stmt_) {
    delete select_stmt_;
    select_stmt_ = nullptr;
  }
}

RC CreateTableSelectStmt::create(Db *db, CreateTableSelectSqlNode &create_table_select_sql, Stmt *&stmt){
    if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  SelectStmt *select_stmt = nullptr;
  RC rc = SelectStmt::create(db, create_table_select_sql.sql_node->selection, select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct select stmt");
    return rc;
  }

  std::vector<AttrInfoSqlNode> attr_infos;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  for(unique_ptr<Expression> &expression:query_expressions){
    if(expression.get()->type() == ExprType::FIELD){
        auto expr = static_cast<FieldExpr *>(expression.get());
        Field field = expr->field();
        const FieldMeta* fieldmeta = field.meta();
        AttrInfoSqlNode attr_info;
        attr_info.length   = fieldmeta->len();
        attr_info.name     = fieldmeta->name();
        attr_info.not_null = fieldmeta->not_null();
        attr_info.type     = fieldmeta->type();
        attr_info.visible  = fieldmeta->visible();
        attr_infos.push_back(attr_info);
    }
  }

  //开始建表,因为一次只能执行一句sql语句，所以在resolve层就建表实属无奈
  rc = db->create_table(create_table_select_sql.table_name.c_str(), attr_infos, StorageFormat::ROW_FORMAT);
  if (OB_SUCC(rc)) {
    // 每次做完DDL之后，做一次sync，保证元数据与日志保持一致
    rc = db->sync();
    LOG_INFO("sync db after ddl. rc=%d", rc);
 }
  //StorageFormat::ROW_FORMAT,目前仅考虑行存储的方式

  CreateTableSelectStmt *create_table_select_stmt = new CreateTableSelectStmt();
  create_table_select_stmt->table_name_           = create_table_select_sql.table_name;
  create_table_select_stmt->select_stmt_          = select_stmt;
  create_table_select_stmt->table_                = db->find_table(create_table_select_sql.table_name.c_str());

  stmt                                            = create_table_select_stmt;
  return RC::SUCCESS;
}