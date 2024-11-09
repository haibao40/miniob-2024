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

  if(create_view.attr_names.size() > 0){
    // SelectSqlNode* select = &(create_view.sql_node->selection);
    for(size_t i = 0 ; i < create_view.attr_names.size(); i++){
      std::string alias = create_view.attr_names[i];
      select_stmt->query_expressions()[i].get()->set_name(alias);
      // set_name(alias);
    }
  }

  std::vector<ViewAttrInfoSqlNode> view_attr_infos;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  //根据绑定好的表达式，来获取建表的字段属性
  CreateViewStmt::get_attr_infos(db, query_expressions, view_attr_infos);

  std::vector<ConditionSqlNode> view_con_infos;
  vector<FilterUnit *> filter_units = select_stmt->filter_stmt()->filter_units();
  rc = CreateViewStmt::get_con_infos(db, filter_units, view_con_infos);
  if(rc != RC::SUCCESS && rc != RC::VIEW_WITH_CHILD) return rc;
  
  std::vector<ViewAttrInfoSqlNode> child_attr_infos;
  std::vector<ConditionSqlNode> child_con_infos;

  if(rc == RC::VIEW_WITH_CHILD) //存在子查询的情况下
  {
    FilterUnit *filter_unit = filter_units[0];
    SubqueryExpr* expr = static_cast<SubqueryExpr *>(filter_unit->right().expr.get());
    SelectStmt *child_select_stmt = expr->select_stmt();

    vector<unique_ptr<Expression>> &child_query_expressions = child_select_stmt->query_expressions();
    CreateViewStmt::get_attr_infos(db, child_query_expressions, child_attr_infos);

    vector<FilterUnit *> child_filter_units = child_select_stmt->filter_stmt()->filter_units();
    rc = CreateViewStmt::get_con_infos(db, child_filter_units, child_con_infos);
  }

  create_view_stmt->view_attr_infos_.swap(view_attr_infos);
  create_view_stmt->view_con_infos_.swap(view_con_infos);
  create_view_stmt->child_attr_infos_.swap(child_attr_infos);
  create_view_stmt->child_con_infos_.swap(child_con_infos);

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
      if(strcasecmp("", expr->expr()) != 0){
        size_t pos = std::string(expr->expr()).find("as");
        attr_info.field_name = std::string(expr->expr()).substr(0, pos-1);
      }
      attr_infos.push_back(attr_info);
    }else if(expression.get()->type() == ExprType::ARITHMETIC){
      auto expr = static_cast<ArithmeticExpr *>(expression.get());
      ViewAttrInfoSqlNode attr_info;
      attr_info.expr_type = ExprType::ARITHMETIC;
      std::string view_field_name = std::string(expr->name());
      size_t pos = view_field_name.find(std::string("as"));
      if(pos != std::string::npos){
        attr_info.name = view_field_name.substr(pos+3); 
        attr_info.field_name = view_field_name.substr(0, pos-1);
      }else{
        attr_info.name = expr->name();
        attr_info.field_name = expr->name();
      }
      attr_info.table_name = default_table->name(); //仅考虑了一个表内字段运算的情况
      attr_infos.push_back(attr_info);
    }
  }
  return RC::SUCCESS;
}

RC CreateViewStmt::get_con_infos(Db *db, std::vector<FilterUnit *> &filter_units, std::vector<ConditionSqlNode> &con_infos){
  bool has_sub_query = false;
  for(size_t i = 0; i < filter_units.size(); i++){
    FilterUnit *filter_unit = filter_units[i];
    Expression* left  = filter_unit->left().expr.get();
    Expression* right = filter_unit->right().expr.get();
    ConditionSqlNode condition;

    condition.comp = filter_unit->comp();
    if(left->type() == ExprType::FIELD){
      condition.left_is_attr = 1;
      FieldExpr *expr = static_cast<FieldExpr *>(left);
      condition.left_attr.relation_name  = expr->table_name();
      condition.left_attr.attribute_name = expr->field_name();
    }else if(left->type() == ExprType::VALUE){
      condition.left_is_attr = 0;
      ValueExpr *expr = static_cast<ValueExpr *>(left);
      Value value = expr->get_value();
      if(value.attr_type() == AttrType::FLOATS){
        
      }else if(value.attr_type() == AttrType::INTS){
        value.int2float();
      }else{
        return RC::UNIMPLEMENTED;
      }
      condition.left_value = value;
    }

    if(right->type() == ExprType::FIELD){
      condition.right_is_attr = 1;
      FieldExpr *expr = static_cast<FieldExpr *>(right);
      condition.right_attr.relation_name  = expr->table_name();
      condition.right_attr.attribute_name = expr->field_name();
    }else if(right->type() == ExprType::VALUE){
      condition.right_is_attr = 0;
      ValueExpr *expr = static_cast<ValueExpr *>(right);
      Value value = expr->get_value();
      if(value.attr_type() == AttrType::FLOATS){
        
      }else if(value.attr_type() == AttrType::INTS){
        value.int2float();
      }else{
        return RC::UNIMPLEMENTED;
      }
      // ValueExpr *value_expr = new ValueExpr(value);
      condition.right_value = value;
    }
    else if(right->type() == ExprType::SUBQUERY){
      has_sub_query =  true;
    }

    con_infos.push_back(condition);
  }
  if(has_sub_query){
    return RC::VIEW_WITH_CHILD;
  }
  return RC::SUCCESS;
}