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
  std::vector<AttrInfoSqlNode> create_attr_infos = create_table_select_sql.attr_infos;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  //根据绑定好的表达式，来获取建表的字段属性
  CreateTableSelectStmt::get_attr_infos(db, query_expressions, attr_infos);
  
  if(0 != create_attr_infos.size() && attr_infos.size() != create_attr_infos.size()){
    return RC::WRONG_ATTR;
  }else if(0 != create_attr_infos.size() && attr_infos.size() == create_attr_infos.size()){
    for(size_t i = 0; i < attr_infos.size(); i++){
        if(!(attr_infos[i] == create_attr_infos[i])){
            return RC::WRONG_ATTR; //要新建的表字段属性和拿到的字段属性不一致,除了名字以外，其他的都需要相等
        }
        attr_infos[i].name = create_attr_infos[i].name;//以建表属性名为准
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

RC CreateTableSelectStmt::get_attr_infos(Db *db, vector<unique_ptr<Expression>> &query_expressions, std::vector<AttrInfoSqlNode>& attr_infos){
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
    }else if(expression.get()->type() == ExprType::STAR){
        auto expr = static_cast<StarExpr *>(expression.get());
        Table *table = db->find_table(expr->table_name());
        const std::vector<FieldMeta>* fieldmetas = table->table_meta().field_metas();
        for(auto fieldmeta:*fieldmetas){
            AttrInfoSqlNode attr_info;
            attr_info.length   = fieldmeta.len();
            attr_info.name     = fieldmeta.name();
            attr_info.not_null = fieldmeta.not_null();
            attr_info.type     = fieldmeta.type();
            attr_info.visible  = fieldmeta.visible();
            attr_infos.push_back(attr_info);
        }
    }else if(expression.get()->type() == ExprType::ARITHMETIC){
      auto expr = static_cast<ArithmeticExpr *>(expression.get());
      AttrInfoSqlNode attr_info;
      attr_info.length   = expr->value_length();              
      attr_info.name     = expr->name();
      attr_info.not_null = false;               //默认可以取空值，实际应该对算术表达式的每个子表达式检查是否可以取空值
      attr_info.type     = expr->value_type();  //
      attr_info.visible  = true;                //默认可以显示
      attr_infos.push_back(attr_info);
    }else if(expression.get()->type() == ExprType::AGGREGATION){
      auto expr = static_cast<AggregateExpr *>(expression.get());
      AttrInfoSqlNode attr_info;
      attr_info.length   = expr->value_length();
      attr_info.name     = expr->name();
      attr_info.not_null = false;               //默认可以取空值，实际应该对算术表达式的每个子表达式检查是否可以取空值
      attr_info.type     = expr->value_type();  //
      attr_info.visible  = true;                //默认可以显示
      attr_infos.push_back(attr_info);
    }else if(expression.get()->type() == ExprType::VALUE){
      auto expr = static_cast<ValueExpr *>(expression.get());
      AttrInfoSqlNode attr_info;
      attr_info.length   = expr->value_length();
      attr_info.name     = expr->name();
      attr_info.not_null = false;               //默认可以取空值，实际应该对算术表达式的每个子表达式检查是否可以取空值
      attr_info.type     = expr->value_type();  //
      attr_info.visible  = true;                //默认可以显示
      attr_infos.push_back(attr_info);
    }
  }
  return RC::SUCCESS;
}