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

#pragma once

#include <memory>
#include <string>

#include "common/value.h"
#include "storage/field/field.h"
#include "sql/expr/aggregator.h"
#include "storage/common/chunk.h"
#include "sql/stmt/select_stmt.h"

class Tuple;
class PhysicalOperator;
class LogicalOperator;
class HierarchicalScope;
/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,                 ///< 星号，表示所有字段
  UNBOUND_FIELD,        ///< 未绑定的字段，需要在resolver阶段解析为FieldExpr
  UNBOUND_AGGREGATION,  ///< 未绑定的聚合函数，需要在resolver阶段解析为AggregateExpr
  UnboundORderedFieldExpr, //李晓鹏 未绑定的排序，需要在resolver阶段解析为AggregateExpr
  ORderedFieldExpr,   //用于排序的Expr
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  VECTOR_FUNCTION, ///< 向量函数运算
  AGGREGATION,  ///< 聚合运算
  UNBOUND_SUBQUERY,   ///< 未绑定的子查询
  SUBQUERY ,      ///     < 绑定后的子查询表达式
  VALUE_LIST      /// 常量列表
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 *
 * TODO 区分unbound和bound的表达式
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 判断两个表达式是否相等
   */
  virtual bool equal(const Expression &other) const { return false; }
  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLEMENTED; }

  /**
   * @brief 从 `chunk` 中获取表达式的计算结果 `column`
   */
  virtual RC get_column(Chunk &chunk, Column &column) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式值的长度
   */
  virtual int value_length() const { return -1; }

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual const char *name() const { return name_.c_str(); }
  virtual void        set_name(std::string name) { name_ = name; }

  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   */
  virtual int  pos() const { return pos_; }
  virtual void set_pos(int pos) { pos_ = pos; }

  /**
   * @brief 用于 ComparisonExpr 获得比较结果 `select`。
   */
  virtual RC eval(Chunk &chunk, std::vector<uint8_t> &select) { return RC::UNIMPLEMENTED; }

protected:
  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   * @details 当 pos_ = -1 时表示下层算子没有在返回的 chunk 中计算出该表达式的计算结果，
   * 当 pos_ >= 0时表示在下层算子中已经计算出该表达式的值（比如聚合表达式），且该表达式对应的结果位于
   * chunk 中 下标为 pos_ 的列中。
   */
  int pos_ = -1;

private:
  std::string name_;
};

class StarExpr : public Expression
{
public:
  StarExpr() : table_name_() {}
  StarExpr(const char *table_name) : table_name_(table_name) {}
  virtual ~StarExpr() = default;

  ExprType type() const override { return ExprType::STAR; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLEMENTED; }  // 不需要实现

  const char *table_name() const { return table_name_.c_str(); }

private:
  std::string table_name_;
};

class UnboundFieldExpr : public Expression
{
public:
  UnboundFieldExpr(const std::string &table_name, const std::string &field_name)
      : table_name_(table_name), field_name_(field_name)
  {}
  UnboundFieldExpr(const std::string &table_name, const std::string &field_name, const std::string &field_alias)
      : table_name_(table_name), field_name_(field_name), field_alias_(field_alias)
  {}

  virtual ~UnboundFieldExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_FIELD; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  const char *table_alias() const { return table_alias_.c_str(); }
  const char *field_alias() const { return field_alias_.c_str(); }
  void set_table_name(const string& table_name) { 
    table_alias_ = table_name_; 
    table_name_  = table_name;
  }


private:
  std::string table_name_;
  std::string table_alias_;
  std::string field_name_;
  std::string field_alias_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  int      value_length() const override { return field_.meta()->len(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }
  const char *field_name() const { return field_.field_name(); }

  RC get_column(Chunk &chunk, Column &column) override;

  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  Field field_;
};

/***
* @brief 表示一个字段的信息，为啥不用已经有的tupleCellSpec,因为感觉char*风格的C字符串用起来不方便
*/
struct FieldInfo{
  std::string table_name;   //表名
  std::string table_alias;  //表的别名
  std::string field_name;   //真实的字段名
  std::string field_alias;  //字段的别名
  AttrType attr_type;       //字段的类型
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  /***
   * @brief 运行时常量构造函数
   * @param unbound_field_expr 原有的未绑定表达式
   * @param scope 当前查询对应的作用域
   */
  explicit ValueExpr(const UnboundFieldExpr* unbound_field_expr);


  virtual ~ValueExpr() = default;

  bool equal(const Expression &other) const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_column(Chunk &chunk, Column &column) override;
  RC try_get_value(Value &value) const override
  {
    if(is_runtime_) {  //运行时常量，不支持这个方法
      return RC::UNIMPLEMENTED;
    }
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }
  AttrType value_type() const override
  {
    if(is_runtime_) {  //运行时常量，值的类型就是绑定的字段的类型
      return field_info_.attr_type;
    }
    return value_.attr_type();
  }
  int      value_length() const override { return value_.length(); }

  void         get_value(Value &value) const { value = value_; }
  const Value &get_value() const { return value_; }
  void set_value(Value &value) const { value_ = value; }
  bool is_runtime() const { return is_runtime_;}
  ///将这个常量表达式设置为运行时常量
  void set_runtime(FieldInfo field_info) const
  {
    field_info_ = field_info;
    is_runtime_ = true;
  }

  FieldInfo& get_field_info() const{ return field_info_; }
  void set_field_info(FieldInfo& field_info) const{ field_info_ = field_info; }

  void set_hierarchical_scope(HierarchicalScope* scope) const {scope_ = scope;}
  HierarchicalScope* get_hierarchical_scope() const { return scope_;}

private:
  mutable Value value_;
  ///标志位：用来表示是否是一个运行时常量,运行时常量用于子查询中，具体的值依赖于上层查询，在子查询执行之前才能确定常量的值
  mutable bool is_runtime_ = false;
  ///运行时常量对应的字段信息
  mutable FieldInfo field_info_;
  ///之后要去获取值的作用域
  mutable HierarchicalScope* scope_ = nullptr;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }
  RC       get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  CompOp   comp() const { return comp_; }

  /**
   * @brief 根据 ComparisonExpr 获得 `select` 结果。
   * select 的长度与chunk 的行数相同，表示每一行在ComparisonExpr 计算后是否会被输出。
   */
  RC eval(Chunk &chunk, std::vector<uint8_t> &select) override;

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

  /***
   * @brief 专门处理比较表达式中包含列子查询的情况,即in、not in、exists、 not exists这几种情况
   */
  RC compare_with_column_subquery(const Tuple& tuple, Value& value) const;

  /***
   * @brief 专门处理比较表达式中包含常量列表的情况 ，比如 id in （1,2,3）
   */
  RC compare_with_value_list(const Tuple& tuple, Value& value) const;

  RC like_value(const Value &left, const Value &right, bool &value) const;
  template <typename T>
  RC compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const;

  /***
   * @brief 实现in的运算
   */
  RC in_value_list(const Value& left, const vector<Value>& value_list, Value &value) const;



private:
  /***
   * @brief is运算符
   */
  RC is(const Value &left, const Value &right, bool &value) const;
private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  bool     equal(const Expression &other) const override;
  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;
  int      value_length() const override
  {
    if (!right_) {
      return left_->value_length();
    }
    return 4;  // sizeof(float) or sizeof(int)
  };

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }
  void set_expr(const char* expr) { expr_ = expr; }
  const char * expr() { return expr_.c_str(); }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

  RC calc_column(const Column &left_column, const Column &right_column, Column &column) const;

  template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
  RC execute_calc(const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
  std::string                 expr_;
};

class UnboundAggregateExpr : public Expression
{
public:
  UnboundAggregateExpr(const char *aggregate_name, Expression *child);
  UnboundAggregateExpr(UnboundAggregateExpr * expr);
  virtual ~UnboundAggregateExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_AGGREGATION; }

  const char *aggregate_name() const { return aggregate_name_.c_str(); }

  std::unique_ptr<Expression> &child() { return child_; }
  std::unique_ptr<Expression> &copy_child() { return copy_child_; }

  RC       get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }
  AttrType value_type() const override { return child_->value_type(); }
  void set_expr(const char * expr) { expr_ = expr; }
  const char * expr() { return expr_.c_str(); }

  void set_flag() { flag_ = true; }
  bool flag() {return flag_; }

private:
  std::string                 aggregate_name_;
  std::unique_ptr<Expression> child_;
  std::string                 expr_;
  std::unique_ptr<Expression> copy_child_;
  bool                        flag_ = false;
};

class AggregateExpr : public Expression
{
public:
  enum class Type
  {
    COUNT,
    SUM,
    AVG,
    MAX,
    MIN,
  };

public:
  AggregateExpr(Type type, Expression *child);
  AggregateExpr(Type type, std::unique_ptr<Expression> child);
  virtual ~AggregateExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::AGGREGATION; }

  AttrType value_type() const override { return child_->value_type(); }
  int      value_length() const override { return child_->value_length(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  Type aggregate_type() const { return aggregate_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  const std::unique_ptr<Expression> &child() const { return child_; }
  void set_expr(const char * expr) { expr_ = expr; }
  const char * expr() { return expr_.c_str(); }

  std::unique_ptr<Aggregator> create_aggregator() const;

public:
  static RC type_from_string(const char *type_str, Type &type);
  static RC string_from_type(std::string &str, const Type type);
  void set_count1(){
    count1_ = true;
  }

private:
  Type                        aggregate_type_;
  std::unique_ptr<Expression> child_;
  std::string                 expr_;
  bool                        count1_ = false;
};


class UnboundORderedFieldExpr: public UnboundFieldExpr
{
    public:
      bool asc ;
     ExprType type() const override { return ExprType::UnboundORderedFieldExpr; }
    UnboundORderedFieldExpr(const std::string &table_name, const std::string &field_name, const bool &asc_)
          : UnboundFieldExpr(table_name, field_name), asc(asc_) {
          // 构造函数体可以为空，因为所有初始化已经在初始化列表中完成
      }
    bool get_asc() const { return asc; }
};


class ORderedFieldExpr : public FieldExpr
{
public:
  ExprType type() const override { return ExprType::ORderedFieldExpr; }
  bool asc;
  ORderedFieldExpr(const Table *table, const FieldMeta *field, const bool asc_) : FieldExpr(table, field), asc(asc_) {}
  ORderedFieldExpr(const Field &field,const bool asc_) : FieldExpr(field), asc(asc_) {}
  bool get_asc() const { return asc; }


};

/***
 *@brief 定义向量函数表达式，用于支持向量数据的函数运算
 */
class VectorFunctionExpr : public Expression
{
public:
  ///定义向量函数表达式支持的函数操作,函数具体的运算规则，查看文档：https://oceanbase.github.io/miniob/game/miniob-vectordb/
  enum class VECTOR_FUNCTION
  {
    L2_DISTANCE,
    COSINE_DISTANCE,
    INNER_PRODUCT
  };

  /***
   * @brief 构造函数，注意，左右表达式的计算结果，必须是向量类型，且维度相同，目前，两个构造函数中没有做任何的检查，但是错误的参数会导致执行的时候出错
   */
  VectorFunctionExpr(VECTOR_FUNCTION type, Expression *left, Expression *right);
  VectorFunctionExpr(VECTOR_FUNCTION type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~VectorFunctionExpr() = default;

  /***
   * @brief 比较两个表达式是否相等，copy了ArithmeticExpr中的实现
   */
  bool     equal(const Expression &other) const override;
  ExprType type() const override;

  AttrType value_type() const override;

  int value_length() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;

  // 暂时不支持这个函数，等之后如果用到了再进行实现
  // RC get_column(Chunk &chunk, Column &column) override;

  RC try_get_value(Value &value) const override;

  /***
   * @brief 获取向量函数表达式中，具体要执行的函数类型
   */
  VECTOR_FUNCTION vector_function_type() const { return vector_function_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  /// L2距离
  static float l2_distance(const std::vector<float> &left_vector, const std::vector<float> &right_vector);
  /// 余弦距离
  static float cosine_distance(const std::vector<float>& left_vector, const std::vector<float>& right_vector);
  /// 内积
  static float inner_product(const std::vector<float>& left_vector, const std::vector<float>& right_vector);

  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

  // 暂时不支持这个函数，等之后如果用到了再进行实现
  // RC calc_column(const Column &left_column, const Column &right_column, Column &column) const;

private:
  ///向量函数的类型
  VECTOR_FUNCTION  vector_function_type_;
  ///向量函数的第一个向量参数
  std::unique_ptr<Expression> left_;
  ///向量函数的第二个向量参数
  std::unique_ptr<Expression> right_;
};

/***
 * @brief 子查询表达式，还未和表以及表的字段进行绑定
 */
class UnboundSubqueryExpr : public Expression
{
public:
  UnboundSubqueryExpr(ParsedSqlNode* parsed_sql_node)
      : parsed_sql_node_(parsed_sql_node)
  {}

  virtual ~UnboundSubqueryExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_SUBQUERY; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  ParsedSqlNode *parsed_sql_node() const { return parsed_sql_node_; }

private:
  //子查询对应的ParsedSqlNode
  ParsedSqlNode* parsed_sql_node_;
};


/***
 * @brief 子查询表达式
 */
class SubqueryExpr : public Expression
{
public:
  SubqueryExpr() = default;
  SubqueryExpr(SelectStmt* select_stmt)
      : select_stmt_(select_stmt)
  {}

  virtual ~SubqueryExpr() = default;

  ExprType type() const override { return ExprType::SUBQUERY; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  /***
   * @brief 对于标量子查询，通过这个方法拿到子查询表达式的值，目前，还只是支持非相关的标量子查询
   *        说明：对于标量子查询，继续使用get_value这个方法，是为了减少代码的改动
   */
  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_value_list(const Tuple &tuple, vector<Value>& value_list) const;

  SelectStmt  *select_stmt() const { return select_stmt_; }

  void set_physical_operator(PhysicalOperator* physical_operator)
  {
    physical_operator_ = physical_operator;
  }

  void set_select_stmt(SelectStmt* select_stmt)
  {
    select_stmt_ = select_stmt;
  }

  void set_is_correlated(){ is_correlated = true;}

  PhysicalOperator* physical_operator() {return physical_operator_;}

private:
  ///子查询对应的ParsedSqlNode
  SelectStmt* select_stmt_ = nullptr;
  ///子查询对应的LogicalOperator;
  LogicalOperator* logical_operator_ = nullptr;
  ///子查询对应的PhysicalOperator
  PhysicalOperator* physical_operator_ = nullptr;
  ///当前子查询对应的作用域
  HierarchicalScope* scope_ = nullptr;

  ///标志位，表示子查询是否是关联子查询，默认为false,即不是关联子查询,为了方便处理复杂子查询，这里先默认设置为true
  mutable bool is_correlated = true;

  ///标志位，表示非关联子查询是否已经执行，如果为true，获取表达式的值的时候，就不需要再次执行子查询了
  mutable bool non_correlated_query_completed = false;

  ///用来存储非相关子查询执行结束后的rc,方便在update_select中，走缓存时，也能够拿到之前执行子查询时对应的rc
  ///否则，可能导致调用方拿不到真实的rc，做出错误的判断
  mutable RC non_correlated_query_completed_rc = RC::SUCCESS;

  ///记录非相关子查询返回的单个值,即非相关标量子查询
  mutable Value signal_result_value_;

  ///记录非相关子查询返回多个值，即非相关行子查询
  mutable std::vector<Value> vec_result_values_;

  /***
   * @brief 获取“非相关-标量子查询”的值
   */
  RC get_signal_value_in_non_correlated_query(Value& value) const;
  /***
   * @brief 获取“非相关-列子查询”的值
   */
  RC get_value_list_in_non_correlated_query(vector<Value>& value_list) const;
  /***
   * @brief 获取“相关-标量子查询”的值
   */
  RC get_signal_value_in_correlated_query(Value& value) const;
  /***
   * @brief 获取“相关-列子查询”的值
   */
  RC get_value_list_in_correlated_query(vector<Value>& value_list) const;

  /***
   * @brief 将上层传下来的tuple，绑定到对应的作用域中
   */
  void bind_tuple_to_scope(const Tuple& tuple) const;
};


/**
 * @brief 常量列表表达式, 即由常量组成的列表，例如：(1,2,3)，一般用在in 操作符中，例如：select * from t where a in (1,2,3)
 * @ingroup Expression
 */
class ValueListExpr : public Expression
{
public:
  ValueListExpr() = default;
  explicit ValueListExpr(const vector<Value>& value_list) : value_list_(value_list) {}

  virtual ~ValueListExpr() = default;

  /// 这个函数暂时不支持，虽然返回的false，但是没啥实际意义
  bool equal(const Expression &other) const override{ return false;}

  ///注意：列表中可能有多个常量表达式Value,所以，对于这个表达式而言，不支持通过get_value来获取值
  RC get_value(const Tuple &tuple, Value &value) const override {return RC::UNSUPPORTED;}
  RC get_column(Chunk &chunk, Column &column) override{ return  RC::UNSUPPORTED;}
  RC try_get_value(Value &value) const override{ return  RC::UNSUPPORTED;}

  RC get_value_list(vector<Value>& value_list)
  {
    value_list.insert(value_list.begin(), value_list_.begin(), value_list_.end());
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE_LIST; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }
  /// 这个函数暂时不支持，虽然返回的0，但是没啥实际意义
  int      value_length() const override { return 0; }


private:
  ///这里可以存放多个常量，组成一个列表
  mutable vector<Value> value_list_;
};