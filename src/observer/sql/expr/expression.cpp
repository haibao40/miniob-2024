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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/expr/aggregator.h"
#include <stack>
#include <cmath>
#include <common/type/null_type.h>
#include "common/global_variable.h"
#include "sql/operator/physical_operator.h"
#include "event/sql_debug.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }
  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result) const
{
  Value value;
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC  rc         = RC::SUCCESS;
  result         = false;

  //TODO:将和null值相关的各种比较运算，提取出一个函数，避免这里代码太长太乱
  //对于某些在comp_op_list中的比较类型，如果待比较的值中，包含了null_type类型的value，在这里单独处理
  std::vector<CompOp> comp_op_list = {EQUAL_TO, LESS_EQUAL, NOT_EQUAL, LESS_THAN, GREAT_EQUAL, GREAT_THAN};
  if(std::find(comp_op_list.begin(), comp_op_list.end(), comp_) != comp_op_list.end()) {
    if(left.attr_type() == AttrType::NULLS) {
      result = NullType().compare_with_null_type(left, right);
      return rc;
    }
    if(right.attr_type() == AttrType::NULLS) {
      result = NullType().compare_with_null_type(left, right);
      return rc;
    }
  }

  int cmp_result = 0;
  //只有在左右都不是null的情况下，才执行这个比较运算
  if(left.attr_type() != AttrType::NULLS && right.attr_type() != AttrType::NULLS) {
    cmp_result = left.compare(right);
  }

  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case LIKE_TO:{
      rc = like_value(left, right,result);
    }break;
    case NOT_LIKE_TO:{
      rc = (like_value(left, right,result));
      result = !result;
    }break;
    case IS: {
      rc = is(left, right, result);
    }break;
    case IS_NOT:{
      rc = is(left, right, result);
      result = !result;
    }break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

#include <iostream>
#include <string>
#include <vector>

bool is_match3(const std::string &left_data, const std::string &right_data) {
    int m = left_data.size();
    int n = right_data.size();

    // 创建 dp 数组
    std::vector<std::vector<bool> > dp(m + 1, std::vector<bool>(n + 1, false));
    dp[0][0] = true;

    // 初始化 dp[0][j]
    for (int j = 1; j <= n; ++j) {
        if (right_data[j - 1] == '%') {
            dp[0][j] = dp[0][j - 1];
        } else {
            break;
        }
    }

    // 填充 dp 数组
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (right_data[j - 1] == '%') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if (right_data[j - 1] == '_' || (left_data[i - 1] != '\'' && left_data[i - 1] == right_data[j - 1])) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }

    return dp[m][n];
}

// bool isMatch2(const std::string& left_data, const std::string& right_data) {  
//     int i = 0, j = 0;  
//     int m = left_data.size(), n = right_data.size();  
  
//     while (i < m && j < n) {  
//         if (left_data[i] == '%' && (i + 1 < m && left_data[i + 1] == '%')) {  
//             // Handle escaped %% which matches a single %  
//             if (j < n && right_data[j] == '%') {  
//                 ++i; // Skip the escaped % in left_data  
//                 ++j; // Move to the next character in right_data  
//             } else {  
//                 // Start matching %* (zero or more characters)  
//                 ++i; // Skip the initial % in left_data  
  
//                 // Try to match as much as possible with %*  
//                 while (j < n && right_data[j] != '\'' &&  
//                        (!(i < m && left_data[i] == '_' || left_data[i] == '%'))) {  
//                     ++j;  
//                 }  
  
//                 // If we hit another pattern or end of string in left_data, backtrack  
//                 if (i < m && (left_data[i] == '_' || left_data[i] == '%')) {  
//                     // Check if there's a way to continue matching  
//                     bool matchFound = false;  
//                     for (int k = j; k <= n; ++k) {  
//                         if (isMatch2(left_data.substr(i + 1), right_data.substr(k))) {  
//                             matchFound = true;  
//                             j = k; // Update j to the position where the substring match ended  
//                             break;  
//                         }  
//                     }  
//                     if (!matchFound) {  
//                         return false;  
//                     }  
//                 } else {  
//                     // No more patterns in left_data, just check if we've matched the entire right_data  
//                     if (j == n) {  
//                         return true;  
//                     } else if (i == m) {  
//                         return false;  
//                     }  
//                 }  
//             }  
//         } else if (left_data[i] == '_' || left_data[i] == right_data[j] ||  
//                    (left_data[i] == '%' && !(right_data[j] == '\''))) {  
//             // Match single character or _ matches any single character  
//             ++i;  
//             ++j;  
//         } else {  
//             // No match found  
//             return false;  
//         }  
//     }  
  
//     // Check if we've matched all characters in both strings  
//     return i == m && j == n;  
// }  
// bool isMatch(const std::string& left_data, const std::string& right_data) {  
//     int i = 0, j = 0;  
//     int m = left_data.size(), n = right_data.size();  
  
//     while (i < m && j < n) {  
//         if (left_data[i] == '%' && (i + 1 < m && left_data[i + 1] == '%')) {  
//             // Handle escaped %% which matches a single %  
//             if (j < n && right_data[j] == '%') {  
//                 ++i; // Skip the escaped % in left_data  
//                 ++j; // Move to the next character in right_data  
//             } else {  
//                 // Start matching %* (zero or more characters)  
//                 ++i; // Skip the initial % in left_data  
  
//                 // Try to match as much as possible with %*  
//                 while (j < n && right_data[j] != '\'' &&  
//                        (!(i < m && left_data[i] == '_' || left_data[i] == '%'))) {  
//                     ++j;  
//                 }  
  
//                 // If we hit another pattern or end of string in left_data, backtrack  
//                 if (i < m && (left_data[i] == '_' || left_data[i] == '%')) {  
//                     // Check if there's a way to continue matching  
//                     bool matchFound = false;  
//                     for (int k = j; k <= n; ++k) {  
//                         if (isMatch(left_data.substr(i + 1), right_data.substr(k))) {  
//                             matchFound = true;  
//                             j = k; // Update j to the position where the substring match ended  
//                             break;  
//                         }  
//                     }  
//                     if (!matchFound) {  
//                         return false;  
//                     }  
//                 } else {  
//                     // No more patterns in left_data, just check if we've matched the entire right_data  
//                     if (j == n) {  
//                         return true;  
//                     } else if (i == m) {  
//                         return false;  
//                     }  
//                 }  
//             }  
//         } else if (left_data[i] == '_' || left_data[i] == right_data[j] ||  
//                    (left_data[i] == '%' && !(right_data[j] == '\''))) {  
//             // Match single character or _ matches any single character  
//             ++i;  
//             ++j;  
//         } else {  
//             // No match found  
//             return false;  
//         }  
//     }  
  
//     // Check if we've matched all characters in both strings  
//     return i == m && j == n;  
// }  

RC ComparisonExpr::like_value(const Value &left, const Value &right, bool &result) const{
  RC  rc         = RC::SUCCESS;
  //判断左右操作数的类型，必须是两个字符串类型，result随便设置一个值吧，反正也不会
  if(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS){
    string left_data = left.get_string();
    string right_data = right.get_string();
    //result = isMatch2(left_data, right_data);
    result = is_match3(left_data,right_data);
    return RC::SUCCESS;
  }else{
    result = false ;
  }
  return rc;
}


RC ComparisonExpr::is(const Value &left, const Value &right, bool &value) const
{
  value = false;
  if(left.attr_type() == right.attr_type()) {
    if(left.attr_type() == AttrType::NULLS) { //sql中，null=null返回的是false，因此null_type的is运算不能依靠比较函数
      value = true;
    }
    else {
      value = (left.compare(right) == 0);   //比较函数返回0，表示相等
    }
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr *  right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  Value left_value;
  Value right_value;

  //case1:对于列子查询的情况，需要调用子查询表达另外的函数去获取子查询的执行结果,对于标量子查询，可以像普通的表达式一样走get_value
  //由于列子查询只会出现在in 或者exists 的右侧，所有这里只是对右侧进行判断
  vector<CompOp> subquery_comp_ops = {IN,NOT_IN,EXISTS,NOT_EXISTS};
  if(right_->type() == ExprType::SUBQUERY
    && std::find(subquery_comp_ops.begin(), subquery_comp_ops.end(), comp_) != subquery_comp_ops.end()) {
    rc = compare_with_column_subquery(tuple, value);
    return rc;
  }

  //case2:对于右侧是常量列表表达式的情况
  if(right_->type() == ExprType::VALUE_LIST
    && std::find(subquery_comp_ops.begin(), subquery_comp_ops.end(), comp_) != subquery_comp_ops.end()) {
    rc = compare_with_value_list(tuple, value);
    return rc;
  }

  //case3:普通情况
  rc = left_->get_value(tuple, left_value);
  if(rc == RC::DIVIDE_ZERO){
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    value.set_boolean(false);
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if(rc == RC::DIVIDE_ZERO){
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    value.set_boolean(false);
    return rc;
  }

  bool bool_value = false;

  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}


RC ComparisonExpr::in_value_list(const Value& left, const vector<Value>& value_list, Value &value) const
{
  value.set_boolean(false);
  if(left.attr_type() != AttrType::NULLS) { //left 不是null的情况
    for(auto right: value_list) {
      if(left.compare(right) == 0) {
        value.set_boolean(true);
      }
    }
  }
  else {  //left 是null的情况
    for(auto right: value_list) {
      if(right.attr_type() == AttrType::NULLS) {
        value.set_boolean(true);
      }
    }
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::compare_with_column_subquery(const Tuple& tuple, Value& value) const
{
  RC rc = RC::SUCCESS;
  SubqueryExpr* subquery_expr = (SubqueryExpr* ) right_.get();
  vector<Value> value_list;
  rc = subquery_expr->get_value_list(tuple, value_list);
  if(rc != RC::SUCCESS) {
    LOG_ERROR("比较表达式求值过程中，获取子查询结果失败");
    return rc;
  }
  if(comp_ == EXISTS) {
    value_list.size() > 0 ? value.set_boolean(true): value.set_boolean(false);
  }
  else if(comp_ == NOT_EXISTS) {
    value_list.size() == 0 ? value.set_boolean(true): value.set_boolean(false);
  }
  else {
    Value left_value;
    rc = left_->get_value(tuple, left_value);
    if(rc == RC::DIVIDE_ZERO){
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
    if(comp_ == IN) {
      rc = in_value_list(left_value, value_list, value);
    }
    else if(comp_ == NOT_IN){
      rc = in_value_list(left_value, value_list, value);
      bool result = value.get_boolean();
      value.set_boolean(!result);
    }
  }
  return rc;
}

RC ComparisonExpr::compare_with_value_list(const Tuple& tuple, Value& value) const
{
  RC rc = RC::SUCCESS;
  Value left_value;
  rc = left_->get_value(tuple, left_value);
  if(rc == RC::DIVIDE_ZERO){
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  ValueListExpr* value_list_expr = (ValueListExpr*) right_.get();
  vector<Value> value_list;
  value_list_expr->get_value_list(value_list);
  switch(comp_) {
    case IN: {
      rc = in_value_list(left_value, value_list, value);
    }break;
    case NOT_IN: {
      rc = in_value_list(left_value, value_list, value);
      bool result = value.get_boolean();
      value.set_boolean(!result);
    }break;
    case EXISTS: {
      value.set_boolean(value_list.size() != 0);
    }break;
    case NOT_EXISTS:{
      value.set_boolean(value_list.size() == 0);
    }break;
    default: {
      LOG_ERROR("这是专门处理比较表达式中包含常量列表的情况，不支持这种运算符，comp_= %d", comp_);
      rc = RC::INVALID_ARGUMENT;
    }break;
  }
  return rc;
}


////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }
  //当算数运算的左右操作数，有一个向量类型时，返回的也是向量类型
  if (left_->value_type() == AttrType::VECTORS || right_->value_type() == AttrType::VECTORS) {
    return AttrType::VECTORS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      if(right_value.get_int() == 0 || right_value.get_float() == 0){
        return RC::DIVIDE_ZERO;
      }
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if(right_ == nullptr){
    LOG_WARN("you sql have divide 0");
    return RC::DIVIDE_ZERO;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name)
{
  if(child == nullptr){
    child_ = nullptr;
    copy_child_ = nullptr;
    return ;
  }
  if(child->type() == ExprType::UNBOUND_FIELD){
    Expression* copied = new UnboundFieldExpr(*dynamic_cast<UnboundFieldExpr*>(child)); 
    copy_child_ =  std::unique_ptr<Expression> (copied);
  }else if(child->type() == ExprType::STAR){
    Expression* copied = new StarExpr(*dynamic_cast<StarExpr*>(child)); 
    copy_child_ =  std::unique_ptr<Expression> (copied);
  }
  child_ =  std::unique_ptr<Expression>(child);
}

UnboundAggregateExpr::UnboundAggregateExpr(UnboundAggregateExpr * expr){
  this->set_name(expr->name());
  this->aggregate_name_ = expr->aggregate_name();
  this->child_ = std::move(expr->copy_child());
}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(name()), value);
}

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
VectorFunctionExpr::VectorFunctionExpr(VECTOR_FUNCTION type, Expression *left, Expression *right)
    : vector_function_type_(type), left_(left), right_(right)
{
}
VectorFunctionExpr::VectorFunctionExpr(VECTOR_FUNCTION type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : vector_function_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool VectorFunctionExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &vector_function_expr = static_cast<const VectorFunctionExpr &>(other);
  return vector_function_type_ == vector_function_expr.vector_function_type() && left_->equal(*vector_function_expr.left_) &&
         right_->equal(*vector_function_expr.right_);
}

ExprType VectorFunctionExpr::type() const
{
  return ExprType::VECTOR_FUNCTION;
}

AttrType VectorFunctionExpr::value_type() const
{
  return AttrType::FLOATS;  //向量函数运算的结果是一个浮点数
}

int VectorFunctionExpr::value_length() const
{
  return sizeof(float);     //向量函数运算的结果是一个浮点数
};

RC VectorFunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC VectorFunctionExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

float VectorFunctionExpr::l2_distance(const std::vector<float>& left_vector, const std::vector<float>& right_vector)
{
    float sum = 0.0;
    for (size_t i = 0; i < left_vector.size(); ++i) {
        float diff = left_vector[i] - right_vector[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

float VectorFunctionExpr::cosine_distance(const std::vector<float>& left_vector, const std::vector<float>& right_vector)
{
    float dot_product = 0;
    float norm_left = 0;
    float norm_right = 0;

    for (size_t i = 0; i < left_vector.size(); ++i) {
        dot_product += left_vector[i] * right_vector[i];
        norm_left += left_vector[i] * left_vector[i];
        norm_right += right_vector[i] * right_vector[i];
    }

    norm_left = std::sqrt(norm_left);
    norm_right = std::sqrt(norm_right);

    if (norm_left == 0.0 || norm_right == 0.0) {
      return 1.0;  // 如果任一向量的范数为0，余弦距离为1
    }

    float cosine_similarity = dot_product / (norm_left * norm_right);
    return 1.0f - cosine_similarity;
}

float VectorFunctionExpr::inner_product(const std::vector<float> &left_vector, const std::vector<float> &right_vector)
{
  float result = 0.0f;
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result += left_vector[i] * right_vector[i];
  }
  return result;
}

RC VectorFunctionExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  // 进行类型转换，将不是vector类型的转换成vector类型
  Value left_vector_value;
  Value right_vector_value;
  if (left_value.attr_type() != AttrType::VECTORS) {
    RC rc = Value::cast_to(left_value, AttrType::VECTORS, left_vector_value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else {
    left_vector_value = left_value;
  }
  if (right_value.attr_type() != AttrType::VECTORS) {
    RC rc = Value::cast_to(right_value, AttrType::VECTORS, right_vector_value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else {
    right_vector_value = right_value;
  }
  // 执行计算逻辑
  float result       = 0;
  auto  vector_left  = left_vector_value.get_vector();
  auto  vector_right = right_vector_value.get_vector();
  switch (vector_function_type_) {
    case VECTOR_FUNCTION::L2_DISTANCE: {
      result = l2_distance(vector_left, vector_right);
    } break;

    case VECTOR_FUNCTION::COSINE_DISTANCE: {
      result = cosine_distance(vector_left, vector_right);
    } break;

    case VECTOR_FUNCTION::INNER_PRODUCT: {
      result = inner_product(vector_left, vector_right);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported VECTOR_FUNCTION type. %d", vector_function_type_);
    } break;
  }
  value.set_type(AttrType::FLOATS);
  value.set_data((char *) &result, 4);
  return rc;
}


RC SubqueryExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if(!is_correlated) { //非相关子查询获取结果
    rc = get_signal_value_in_non_correlated_query(value);
    non_correlated_query_completed_rc = rc;   //记录rc,保证之后拿到的rc都和第一次相同
  }
  else {  //相关子查询获取结果，暂时未实现
    rc = RC::UNIMPLEMENTED;
  }
  return rc;
}

RC SubqueryExpr::get_value_list(const Tuple &tuple, vector<Value>& vector) const
{
  RC rc = RC::SUCCESS;
  if(!is_correlated) { //非相关子查询获取结果
    rc = get_value_list_in_non_correlated_query(vector);
  }
  else {  //相关子查询获取结果，暂时未实现
    rc = RC::UNIMPLEMENTED;
  }
  return rc;
}


RC SubqueryExpr::get_signal_value_in_non_correlated_query(Value& value) const
{
  RC rc = RC::SUCCESS;
  if(non_correlated_query_completed) { //非相关子查询已经执行过，直接返回结果
    value = signal_result_value_;
    return non_correlated_query_completed_rc; //使用之前执行时记录下的rc，返回码也是缓存的一部分
  }
  else {
    //子查询还未执行，执行子查询
    rc =physical_operator_->open(GlobalVariable::trx);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("执行子查询时，打开子查询的物理算子失败");
      return rc;
    }
    rc = physical_operator_->next();
    Value value_temp;
    vector<Value> value_list;
    while (rc == RC::SUCCESS) {
      Tuple* current_tuple = physical_operator_->current_tuple();
      if(current_tuple->cell_num() != 1) {
        LOG_ERROR("在执行标量子查询的过程中，子查询单次next方法返回的值不是1个，即没有返回数据或者返回了一行数据，SQL不合法");
        rc = physical_operator_->close();
        if(rc != RC::SUCCESS) {
          LOG_ERROR("关闭子查询物理算子失败");
        }
        return RC::ILLEGAL_SUB_QUERY;
      }
      current_tuple->cell_at(0, value_temp);
      value_list.push_back(value_temp);
      rc = physical_operator_->next();
    }
    if(rc == RC::RECORD_EOF) {
      rc = RC::SUCCESS;
    }
    else if(rc != RC::SUCCESS) {
      LOG_ERROR("子查询在执行过程中出现异常情况");
      physical_operator_->close();
      return rc;
    }
    if(value_list.size() != 1) {
      LOG_ERROR("在执行标量子查询的过程中，子查询实际返回了%d个值，SQL不合法", (int)value_list.size());
      sql_debug("在执行标量子查询的过程中，子查询实际返回了%d个值，SQL不合法", (int)value_list.size());
      rc = physical_operator_->close();
      if(rc != RC::SUCCESS) {
        LOG_ERROR("关闭子查询物理算子失败");
      }
      return RC::ILLEGAL_SUB_QUERY;
    }
    signal_result_value_ = value_list[0];
    physical_operator_->close();
    non_correlated_query_completed = true;  //修改标志位，避免非相关子查询多次执行
    value = signal_result_value_;
  }
  return rc;
}

RC SubqueryExpr::get_value_list_in_non_correlated_query(vector<Value>& value_list) const
{
  RC rc = RC::SUCCESS;
  if(non_correlated_query_completed) { //非相关子查询已经执行过，直接返回结果
    value_list.insert(value_list.begin(), vec_result_values_.begin(), vec_result_values_.end());
  }
  else {
    //子查询还未执行，执行子查询
    rc =physical_operator_->open(GlobalVariable::trx);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("执行子查询时，打开子查询的物理算子失败");
      return rc;
    }
    //这个方法是列子查询，所以有多个值,这里将值保存到vec_result_values_，方便之后重复使用
    rc = physical_operator_->next();
    Value value;
    while (rc == RC::SUCCESS) {
      Tuple* current_tuple = physical_operator_->current_tuple();
      current_tuple->cell_at(0, value);  //列子查询，所以每次next只有一个值
      vec_result_values_.push_back(value);
      rc = physical_operator_->next();
    }
    if(rc == RC::RECORD_EOF) {     //列子查询正常结束
      rc = RC::SUCCESS;
    }
    else if(rc != RC::SUCCESS) {   //列子查询执行过程中出错
      LOG_ERROR("列子查询在执行过程中出现异常情况");
      physical_operator_->close();
      return rc;
    }
    non_correlated_query_completed = true;  //修改标志位，避免非相关子查询多次执行
    value_list.insert(value_list.begin(), vec_result_values_.begin(), vec_result_values_.end());
  }
  return rc;
}