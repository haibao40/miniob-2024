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

#pragma once

#include <vector>
#include <map>

#include "sql/expr/expression.h"
#include <unordered_map>

class BinderContext
{
public:
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(Table *table) { query_tables_.push_back(table); }
  void add_table_alias(const char* table_name, const char* table_alias){
    table_name2table_alias_.insert({table_name, table_alias}); 
  }
  

  Table *find_table(const char *table_name) const;

  const std::vector<Table *> &query_tables() const { return query_tables_; }

private:
  std::vector<Table *> query_tables_;
  std::map<std::string, std::string> table_name2table_alias_;
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  RC bind_star_expression(
      std::unique_ptr<Expression> &star_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_unbound_field_expression(
      std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
   RC bind_unbound_order_field_expression(
      std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  /***
   * @brief 实现对子查询表达式的绑定操作，让子查询表达式内部持有的select_sql_node走一遍resolve流程
   */
  RC bind_subquery_expression(
      std::unique_ptr<Expression> &subquery_expr, std::vector<unique_ptr<Expression>> &bound_expressions);
private:
  BinderContext &context_;

public:
  std::unordered_map<char, ArithmeticExpr::Type> char2type = {{'+',ArithmeticExpr::Type::ADD },
                                                              {'-',ArithmeticExpr::Type::SUB },
                                                              {'*',ArithmeticExpr::Type::MUL },
                                                              {'/',ArithmeticExpr::Type::DIV },};

  bool isOperator(char c);
  int precedence(char op);
  std::string getNextToken(const std::string& expr, size_t& pos);
  //parse会把所有的加减法都解析出来
  Expression* parseExpression(const std::string& expr, size_t& pos, const char *table_name) {
    // Expression *node = nullptr;
    size_t lpos = pos, rpos, start = pos;
    Expression *left = nullptr, *right = nullptr;
    bool has_op = false;
    char op;
    while (pos < expr.length()) {
        op = expr[pos++];
        if(op == '+' || op == '-'){
          left = parseExpression(expr.substr(lpos, pos-lpos-1), lpos, table_name);
          rpos = 0;
          right = parseExpression(expr.substr(pos, expr.length()-pos), rpos, table_name);
          break;
        }else if(op == '*' || op == '/'){
          has_op = true;
          break;
        }
    }

    if(left == nullptr && right == nullptr && !has_op){
      std::string str = getNextToken(expr, start);
      if(isInteger(str)){
        return new ValueExpr(Value(std::stoi(str)));
      }else{
        UnboundFieldExpr* unbound_fieldexpr = new UnboundFieldExpr(table_name, expr);
        return unbound_fieldexpr;
      }
    }else if(left == nullptr && right == nullptr && has_op){
      return nullptr;
    }
    return new ArithmeticExpr(char2type[op], left, right);
  }

  bool isInteger(const std::string& str);
  bool isWord(const std::string& str);
  bool startsWith(const std::string& str, const std::string& prefix);
};