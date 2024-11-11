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
// Created by Wangyunlai on 2024/05/29.
//

#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/expression_binder.h"

#include "hierarchical_scope.h"
#include "sql/expr/expression_iterator.h"
#include "sql/stmt/stmt.h"
#include "common/global_variable.h"

using namespace std;
using namespace common;

Table *BinderContext::find_table(const char *table_name) const
{
  auto pred = [table_name](Table *table) { return 0 == strcasecmp(table_name, table->name()); };
  auto iter = ranges::find_if(query_tables_, pred);
  if (iter != query_tables_.end()) {
    return *iter;
  }

  for(auto it: table_name2table_alias_){
    if(0 == strcasecmp(it.first.c_str(), table_name)){
      return find_table(it.second.c_str());
    }
  }
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
static void wildcard_fields(Table *table, vector<unique_ptr<Expression>> &expressions)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  //by haijun:原本只是需要跳过sys_field, 现在由于添加了空值列表null_value_list,所以还需要跳过空值列表
  for (int i = table_meta.sys_field_num() + table_meta.system_not_visible_field_number() ; i < field_num; i++) {
    Field      field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_name(field.field_name());
    expressions.emplace_back(field_expr);
  }
}

static void wildcard_fields_with_table_alias(Table *table, std::string table_alias, vector<unique_ptr<Expression>> &expressions)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  //by haijun:原本只是需要跳过sys_field, 现在由于添加了空值列表null_value_list,所以还需要跳过空值列表
  for (int i = table_meta.sys_field_num() + table_meta.system_not_visible_field_number() ; i < field_num; i++) {
    Field      field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_name(table_alias+"."+ field.field_name());
    expressions.emplace_back(field_expr);
  }
}

RC ExpressionBinder::bind_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  switch (expr->type()) {
    case ExprType::STAR: {
      return bind_star_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_FIELD: {
      return bind_unbound_field_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_AGGREGATION: {
      return bind_aggregate_expression(expr, bound_expressions);
    } break;

    case ExprType::FIELD: {
      return bind_field_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE_LIST: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::CAST: {
      return bind_cast_expression(expr, bound_expressions);
    } break;

    case ExprType::COMPARISON: {
      return bind_comparison_expression(expr, bound_expressions);
    } break;

    case ExprType::CONJUNCTION: {
      return bind_conjunction_expression(expr, bound_expressions);
    } break;

    case ExprType::ARITHMETIC: {
      return bind_arithmetic_expression(expr, bound_expressions);
    } break;

    case ExprType::AGGREGATION: {
      // ASSERT(false, "shouldn't be here");
      return bind_aggregate_expression(expr, bound_expressions);
    } break;
    case ExprType::UnboundORderedFieldExpr:{
       // 李晓鹏笔记 此处解析order by 的内容
       return bind_unbound_order_field_expression(expr, bound_expressions);
    }break;

    case ExprType::VECTOR_FUNCTION: {
      // 目前,先将向量函数表达式的绑定，按照arithmetic处理，流程应该是完全一致的
      return bind_arithmetic_expression(expr, bound_expressions);
    }

    case ExprType::UNBOUND_SUBQUERY: {
      // 对子查询表达式进行绑定，会让表达式中的sql_node走一次resolve流程
      return bind_subquery_expression(expr, bound_expressions);
    }

    default: {
      LOG_WARN("unknown expression type: %d", static_cast<int>(expr->type()));
      return RC::INTERNAL;
    }
  }
  return RC::INTERNAL;
}

RC ExpressionBinder::bind_star_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto star_expr = static_cast<StarExpr *>(expr.get());

  vector<Table *> tables_to_wildcard;
  bool use_table_alias = false;

  const char *table_name = star_expr->table_name();
  if (!is_blank(table_name) && 0 != strcmp(table_name, "*")) {
    Table *table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    if(strcmp(table_name, table->name()) != 0) { //查到的真实的表的表名，和表达式中使用的表名不一致，说明表达式中使用的是别名
      use_table_alias = true;
    }

    tables_to_wildcard.push_back(table);
  } else {
    const vector<Table *> &all_tables = context_.query_tables();
    tables_to_wildcard.insert(tables_to_wildcard.end(), all_tables.begin(), all_tables.end());
  }

  for (Table *table : tables_to_wildcard) {
    if(use_table_alias == false) {
      wildcard_fields(table, bound_expressions);
    }
    else {
      wildcard_fields_with_table_alias(table, table_name,  bound_expressions);  //这里给表达式设置名字的时候，会使用别名
    }
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_unbound_field_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

  const char *table_name      = unbound_field_expr->table_name();
  const char *field_name      = unbound_field_expr->field_name();
  // const char *table_alias     = unbound_field_expr->table_alias();
  const char *field_alias     = unbound_field_expr->field_alias();
  std::string field_expr_name = ""; //表达式的名字

  Table *table = nullptr;
  if (is_blank(table_name)) {
    if (context_.query_tables().size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table = context_.query_tables()[0];
  } else {

    table = context_.find_table(table_name);
    if (nullptr == table) {  //by haijun: 为了适应关联子查询，这里找不到表，就尝试创建常量表达式
      RC rc = RC::SCHEMA_TABLE_NOT_EXIST;
      ValueExpr* runtime_value_expr = new ValueExpr(unbound_field_expr);
      if(GlobalVariable::curren_resolve_subquery_expr != nullptr) {  //说明是子查询的情况
        rc = GlobalVariable::curren_resolve_select_stmt->scope_->bind_scope_for_runtime_value_exprs(runtime_value_expr);
      }
      if(rc != RC::SUCCESS) {   //常量表达式绑定作用域失败，说明没有在上级作用域找到可以绑定的作用域，这个字段真的有问题
        LOG_INFO("no such table in from list or no such field: %s", table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      else {  //成功为常量表达式绑定作用域，说明这真的是一个常量表达式
        GlobalVariable::curren_resolve_subquery_expr->set_is_correlated();
        bound_expressions.emplace_back(runtime_value_expr);
        return RC::SUCCESS;
      }
    }
    else{
      //有别名取别名，无别名取表名
      // field_expr_name += strcasecmp(table_name, table_alias) == 0 ? string(table_name) + "." : string(table_alias) + ".";
      if(strcasecmp(table->table_meta().name(), table_name) == 0){
        field_expr_name = field_expr_name + std::string(table_name) + ".";
      }else{
        field_expr_name = field_expr_name + std::string(table->table_meta().name()) + ".";
      }
    }
  }

  if (0 == strcmp(field_name, "*")) {
    wildcard_fields(table, bound_expressions);
  } else {  //TODO:万一字段使用了别名怎么办
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {  //by haijun: 为了适应关联子查询，这里找不到对应的字段，就尝试创建常量表达式
      RC rc = RC::SCHEMA_TABLE_NOT_EXIST;
      ValueExpr* runtime_value_expr = new ValueExpr(unbound_field_expr);
      if(GlobalVariable::curren_resolve_subquery_expr != nullptr) {  //说明是子查询的情况
        rc = GlobalVariable::curren_resolve_select_stmt->scope_->bind_scope_for_runtime_value_exprs(runtime_value_expr);
      }
      if(rc != RC::SUCCESS) {   //常量表达式绑定作用域失败，说明没有在上级作用域找到可以绑定的作用域，这个字段真的有问题
        LOG_INFO("no such table in from list or no such field: %s", table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      else {  //成功为常量表达式绑定作用域，说明这真的是一个常量表达式
        GlobalVariable::curren_resolve_subquery_expr->set_is_correlated();  //将当前这个子查询设置为相关子查询
        bound_expressions.emplace_back(runtime_value_expr);
        return RC::SUCCESS;
      }
    }

    Field      field(table, field_meta);
    FieldExpr *field_expr = new FieldExpr(field);
    //有别名取别名，没别名用字段名
    field_expr_name += strcasecmp(field_alias, "") == 0 ? field_name : field_alias;
    if(strcasecmp(field_alias, "") == 0){
      field_expr->set_name(field_expr_name);
    }else{
      field_expr->set_name(field_alias);
    }
    bound_expressions.emplace_back(field_expr);
  }

  return RC::SUCCESS;
}
// 李晓鹏 照着绑定field抄就行了 ,注意在.c文件中添加一下函数的声明
RC ExpressionBinder::bind_field_expression(
    unique_ptr<Expression> &field_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(field_expr));
  return RC::SUCCESS;
}
RC ExpressionBinder::bind_unbound_order_field_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions){
   if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_order_field_expr = static_cast<UnboundORderedFieldExpr *>(expr.get());

  const char *table_name = unbound_order_field_expr->table_name();
  const char *field_name = unbound_order_field_expr->field_name();
  const bool is_asc = unbound_order_field_expr->get_asc(); //这行是新加入的

  Table *table = nullptr;
  if (is_blank(table_name)) {
    if (context_.query_tables().size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table = context_.query_tables()[0];
  } else {
    table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }

  if (0 == strcmp(field_name, "*")) {
    wildcard_fields(table, bound_expressions);
  } else {
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_INFO("no such field in table: %s.%s", table_name, field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    Field      field(table, field_meta);
    ORderedFieldExpr *field_expr = new ORderedFieldExpr(field,is_asc);
    field_expr->set_name(field_name);
    bound_expressions.emplace_back(field_expr);
  }

  return RC::SUCCESS;
}
RC ExpressionBinder::bind_value_expression(
    unique_ptr<Expression> &value_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_cast_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto cast_expr = static_cast<CastExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &child_expr = cast_expr->child();

  RC rc = bind_expression(child_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid children number of cast expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &child = child_bound_expressions[0];
  if (child.get() == child_expr.get()) {
    return RC::SUCCESS;
  }

  child_expr.reset(child.release());
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_comparison_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = comparison_expr->left();
  unique_ptr<Expression>        &right_expr = comparison_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_conjunction_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());

  vector<unique_ptr<Expression>>  child_bound_expressions;
  vector<unique_ptr<Expression>> &children = conjunction_expr->children();

  for (unique_ptr<Expression> &child_expr : children) {
    child_bound_expressions.clear();

    RC rc = bind_expression(child_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of conjunction expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &child = child_bound_expressions[0];
    if (child.get() != child_expr.get()) {
      child_expr.reset(child.release());
    }
  }

  bound_expressions.emplace_back(std::move(expr));

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_arithmetic_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = arithmetic_expr->left();
  unique_ptr<Expression>        &right_expr = arithmetic_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC check_aggregate_expression(AggregateExpr &expression)
{
  // 必须有一个子表达式
  Expression *child_expression = expression.child().get();
  if (nullptr == child_expression) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  // 校验数据类型与聚合类型是否匹配
  AggregateExpr::Type aggregate_type   = expression.aggregate_type();
  AttrType            child_value_type = child_expression->value_type();
  switch (aggregate_type) {
    case AggregateExpr::Type::SUM:
    case AggregateExpr::Type::AVG: {
      // 仅支持数值类型
      if (child_value_type != AttrType::INTS && child_value_type != AttrType::FLOATS) {
        LOG_WARN("invalid child value type for aggregate expression: %d", static_cast<int>(child_value_type));
        return RC::INVALID_ARGUMENT;
      }
    } break;

    case AggregateExpr::Type::COUNT:
    case AggregateExpr::Type::MAX:
    case AggregateExpr::Type::MIN: {
      // 任何类型都支持
    } break;
  }

  // 子表达式中不能再包含聚合表达式
  function<RC(std::unique_ptr<Expression>&)> check_aggregate_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      LOG_WARN("aggregate expression cannot be nested");
      return RC::INVALID_ARGUMENT;
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, check_aggregate_expr);
    return rc;
  };

  RC rc = ExpressionIterator::iterate_child_expr(expression, check_aggregate_expr);

  return rc;
}

RC ExpressionBinder::bind_aggregate_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_aggregate_expr = static_cast<UnboundAggregateExpr *>(expr.get());
  const char *aggregate_name = unbound_aggregate_expr->aggregate_name();
  bool flag = unbound_aggregate_expr->flag();

  AggregateExpr::Type aggregate_type;
  RC rc = AggregateExpr::type_from_string(aggregate_name, aggregate_type);
  if (OB_FAIL(rc)) {
    LOG_WARN("invalid aggregate name: %s", aggregate_name);
    return rc;
  }

  if(unbound_aggregate_expr->child() == nullptr){
    LOG_WARN("there is no child");
    return RC::NOT_EXIST;
  }
  unique_ptr<Expression>        &child_expr = unbound_aggregate_expr->child();
  vector<unique_ptr<Expression>> child_bound_expressions;

  if (child_expr->type() == ExprType::STAR && aggregate_type == AggregateExpr::Type::COUNT) {
    ValueExpr *value_expr = new ValueExpr(Value(1));
    child_expr.reset(value_expr);
  } else {
    rc = bind_expression(child_expr, child_bound_expressions);
    if (OB_FAIL(rc)) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of aggregate expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    if (child_bound_expressions[0].get() != child_expr.get()) {
      child_expr.reset(child_bound_expressions[0].release());
    }
  }

  auto aggregate_expr = make_unique<AggregateExpr>(aggregate_type, std::move(child_expr));

  if(flag){
    aggregate_expr.get()->set_count1();
  }
  aggregate_expr->set_expr(unbound_aggregate_expr->expr());
  aggregate_expr->set_name(unbound_aggregate_expr->name());
  rc = check_aggregate_expression(*aggregate_expr);
  if (OB_FAIL(rc)) {
    return rc;
  }

  bound_expressions.emplace_back(std::move(aggregate_expr));
  return RC::SUCCESS;
}


RC ExpressionBinder::bind_subquery_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  auto unbound_sub_query_expr = static_cast<UnboundSubqueryExpr *>(expr.get());
  ParsedSqlNode* parsed_sql_node = unbound_sub_query_expr->parsed_sql_node();  // 子查询对应的sql_node
  Stmt          *stmt     = nullptr;
  // 对子查询进行resolve TODO:如果是相关子查询，这里需要适当的调整
  SubqueryExpr *subquery_expr = new SubqueryExpr();
  SubqueryExpr *pre_resolve_subquery_expr = GlobalVariable::curren_resolve_subquery_expr;
  GlobalVariable::curren_resolve_subquery_expr = subquery_expr;           //在全局变量中记录当前正在处理的子查询
  RC rc = Stmt::create_stmt(GlobalVariable::db, *parsed_sql_node, stmt);  // 对子查询进行resolve
  subquery_expr->set_select_stmt((SelectStmt*) stmt);
  GlobalVariable::curren_resolve_subquery_expr = pre_resolve_subquery_expr;  //回溯全局变量到之前的值
  if (rc != RC::SUCCESS && rc != RC::UNIMPLEMENTED) {
    LOG_WARN("failed to create stmt for sub query . rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  bound_expressions.emplace_back(std::move(subquery_expr));
  return RC::SUCCESS;
}

bool ExpressionBinder::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int ExpressionBinder::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string ExpressionBinder::getNextToken(const std::string& expr, size_t& pos) {
    while (std::isspace(expr[pos])) ++pos; // 跳过空格
    size_t start = pos;
    if (std::isdigit(expr[start])) { // 数字
        while (std::isdigit(expr[pos])) ++pos;
    } else if (expr[start] == '-' && std::isdigit(expr[start + 1])) { // 负数
        ++pos;
        while (std::isdigit(expr[pos])) ++pos;
    } else if (isOperator(expr[start])) { // 操作符
        ++pos;
    } else { // 标识符
        while (std::isalnum(expr[pos]) || expr[pos] == '.') ++pos;
    }
    return expr.substr(start, pos - start);
}

bool ExpressionBinder::isInteger(const std::string& str) {
    // Check if the string is empty or has only digits
    for (char ch : str) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}
 
bool ExpressionBinder::isWord(const std::string& str) {
    // Check if the string contains at least one alphabetic character
    for (char ch : str) {
        if (isalpha(static_cast<unsigned char>(ch))) {
            return true;
        }
    }
    // If no alphabetic character is found, it's not a word
    return false;
}

bool ExpressionBinder::startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.compare(0, prefix.length(), prefix) == 0;
}