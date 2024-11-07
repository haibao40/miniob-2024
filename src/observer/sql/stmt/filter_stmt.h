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

#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/expr/expression.h"
#include "sql/stmt/stmt.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class Field;
class FieldMeta;

struct FilterObj
{
  bool  is_expr=false;
  bool  is_attr;
  Field field;
  Value value;
  std::unique_ptr<Expression> expr;

  void init_attr(const Field &field)
  {
    is_attr     = true;
    this->field = field;
  }

  void init_value(const Value &value)
  {
    is_attr     = false;
    this->value = value;
  }

  FilterObj(){}
  FilterObj(Expression *expr) : expr(expr){
    is_expr=true;
  }

  // void init_expr(ValueExpr *expr){
  //   is_expr = true;
  //   this->expr = std::make_unique<ValueExpr>(std::move(*expr));
  // }

  // void init_expr(ArithmeticExpr *expr){
  //   is_expr = true;
  //   this->expr = std::make_unique<ArithmeticExpr>(expr);
  // }

  // void init_expr(Expression *expr){
  //   Value value(0);
  //   ValueExpr *valexpr = new ValueExpr(value);
  //   ArithmeticExpr *arithexpr = new ArithmeticExpr(ArithmeticExpr::Type::ADD, valexpr, expr);
  //   is_expr = true;
  //   this->expr = std::make_unique<ArithmeticExpr>(arithexpr);
  //   // this->expr = std::move(*expr);
  //   //delete expr;
  // }

  void init_expr(std::unique_ptr<Expression> &&expr){
    is_expr = true;
    this->expr = std::move(expr);
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  // void set_left(const FilterObj &obj) { left_ = obj; }
  // void set_right(const FilterObj &obj) { right_ = obj; }
  void set_left(FilterObj &&obj) { 
    left_.is_attr = obj.is_attr;
    left_.is_expr = obj.is_expr;
    if(left_.is_expr){
      left_.init_expr(std::move(obj.expr));
    } else if(left_.is_attr){
      left_.init_attr(obj.field);
    } else{
      left_.init_value(obj.value);
    }
  }
  void set_right(FilterObj &&obj) { 
    right_.is_attr = obj.is_attr;
    right_.is_expr = obj.is_expr;
    right_.expr = std::move(obj.expr);  
    if(right_.is_expr){
      right_.init_expr(std::move(obj.expr));
    } else if(right_.is_attr){
      right_.init_attr(obj.field);
    } else{
      right_.init_value(obj.value);
    }
  }
  void set_left(std::unique_ptr<Expression> &&expr){ left_.init_expr(std::move(expr));}
  void set_right(std::unique_ptr<Expression> &&expr){ right_.init_expr(std::move(expr));}
  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }
  FilterObj &left() {return left_;}
  FilterObj &right() {return right_;}

private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  bool conjunction_with_or = false;  //表示这些条件是否使用or进行组合
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }
  std::vector<FilterUnit *> filter_units() {return filter_units_;}

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, FilterUnit *&filter_unit);

  /***
   * @brief 将conditionsqlnode中的relAttrSqlNode替换为UNboundFieldExpr，让它走expression的bind流程，
   *        因为在那里实现了对关联子查询中运行时常量的处理逻辑
   */
  static void replace_relAttrSqlNode_to_expr(ConditionSqlNode &condition);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};
