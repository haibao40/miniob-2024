#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/create_view_stmt.h"
#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h"
#include "sql/parser/expression_binder.h"

#include "storage/db/db.h"

Table * default_table = nullptr;

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  CreateViewStmt *create_view_stmt = new CreateViewStmt(create_view.view_name);
  const char* table_name = create_view.sql_node->selection.relations.begin()->first.c_str();
  default_table = db->find_table(table_name);

  SelectStmt *select_stmt = nullptr;
  RC rc = SelectStmt::create(db, create_view.sql_node->selection, select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct select stmt");
    return rc;
  }

  std::vector<ViewAttrInfoSqlNode> view_attr_infos;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  //根据绑定好的表达式，来获取建表的字段属性
  CreateViewStmt::get_attr_infos(db, query_expressions, view_attr_infos);
  
  create_view_stmt->view_attr_infos_.swap(view_attr_infos);

  stmt = create_view_stmt;
  if(select_stmt != nullptr){
    delete select_stmt;
  }

  sql_debug("create view statement: view name %s", create_view.view_name.c_str());
  return RC::SUCCESS;
}

RC CreateViewStmt::get_attr_infos(Db *db, vector<unique_ptr<Expression>> &query_expressions, std::vector<ViewAttrInfoSqlNode>& attr_infos){
  for(unique_ptr<Expression> &expression:query_expressions){
    if(expression.get()->type() == ExprType::FIELD){
        auto expr = static_cast<FieldExpr *>(expression.get());
        ViewAttrInfoSqlNode attr_info;
        attr_info.expr_type = ExprType::FIELD;
        attr_info.name     = expr->name();
        attr_info.table_name = expr->table_name();
        attr_info.field_name = expr->field_name();
        attr_infos.push_back(attr_info);
    }else if(expression.get()->type() == ExprType::STAR){
        auto expr = static_cast<StarExpr *>(expression.get());
        Table *table = db->find_table(expr->table_name());
        const std::vector<FieldMeta>* fieldmetas = table->table_meta().field_metas();
        for(auto fieldmeta:*fieldmetas){
            ViewAttrInfoSqlNode attr_info;
            attr_info.expr_type = ExprType::FIELD;
            attr_info.name = fieldmeta.name();
            attr_info.table_name = expr->table_name();
            attr_info.field_name = fieldmeta.name();
            attr_infos.push_back(attr_info);
        }
    }else if(expression.get()->type() == ExprType::AGGREGATION){
      auto expr = static_cast<AggregateExpr *>(expression.get());
      auto child_expr = static_cast<FieldExpr *>(expr->child().get());
      ViewAttrInfoSqlNode attr_info;
      attr_info.expr_type = ExprType::AGGREGATION;
      attr_info.name = expr->name();
      attr_info.table_name = child_expr->table_name();
      attr_info.field_name = child_expr->field_name();
      attr_infos.push_back(attr_info);
    }else if(expression.get()->type() == ExprType::ARITHMETIC){
      auto expr = static_cast<ArithmeticExpr *>(expression.get());
      ViewAttrInfoSqlNode attr_info;
      attr_info.expr_type = ExprType::ARITHMETIC;
      attr_info.name = expr->name();
      attr_info.table_name = default_table->name();
      attr_info.field_name = "many";
      attr_infos.push_back(attr_info);
    }
  }
  return RC::SUCCESS;
}