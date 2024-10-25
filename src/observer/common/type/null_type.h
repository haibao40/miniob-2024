#pragma once

#include "common/type/data_type.h"

/**
 * @brief null类型
 * @ingroup DataType
 */
class NullType : public DataType
{
public:
  NullType() : DataType(AttrType::NULLS) {}
  virtual ~NullType() {}

  /***
    * @brief  计算left compare right，必须满足left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS,
    *        即参与比较的左值和右值，至少有一个是null类型，满足这个条件。这里的compare，包含sql比较表达式中的：<,>,<>,=,
    *        注意，包含null_type的比较运算，一般情况下不满满足对称性！！！
    *        当比较表达式包含null值时，不能够根据a < b的结果去推导 b < a的结果或者b > a的结果！！！
    *        只要是比较表达式中设计到了null，比较的结果全部为false！在实现ComparisonExpr时，尤其注意这一点！！！
    *        具体情况参考以下的sql示例（来源：test/case/result/primary-null.result）：
              SELECT * FROM null_table;
              ID | NUM | PRICE | BIRTHDAY
              1 | 18 | 10 | 2020-01-01
              2 | NULL | 20 | 2010-01-11
              3 | 12 | 30 | NULL
              4 | 15 | 30 | 2021-01-31
              SELECT * FROM null_table where null=1;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table where 1=null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table where 1<>null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table where 1<null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table where 1>null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table WHERE null=null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table WHERE null<>null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table WHERE null>null;
              ID | NUM | PRICE | BIRTHDAY
              SELECT * FROM null_table WHERE null<null;
              ID | NUM | PRICE | BIRTHDAY
    * @param left 左值
    * @param right 右值
    */
  bool compare_with_null_type(const Value &left, const Value &right);


//   null_type暂时不支持调用compare函数，因为ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
//   函数中，将compare方法理解为一个对称函数，但是跟null值相关的比较不具备对称性，无论这里的compare函数怎么写，都会有bug
//   /***
//   * @brief  计算left > right，必须满足left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS,
//   *        即参与比较的左值和右值，至少有一个是null类型，参数满足函数要求的情况下，返回的结果为-1，即
//   *        注意，包含null_type的比较运算，一般情况下不满满足对称性！！！
//   *        当比较表达式包含null值时，不能够根据a < b的结果去推导 b < a的结果或者b > a的结果！！！在实现ComparisonExpr时，尤其注意这一点！！！
//   *        为了避免ComparisonExpr在调用value的compare()函数时出错，避免在ComparisonExpr中添加过多的条件判断，所以才将这个函数进行实现，
//   *        出现null值相关的比较，推荐使用compare_with_null_type()函数来完成null值相关的比较
//
//   * @param left 左值
//   * @param right 右值
//   * @return
//   *  -1 表示 left < right：左侧是DataType中的定义，在这里的代码中，默认返回-1，可以理解成left > right比较的结果为false（暂时这样，后面有问题再改）
//   *  0 表示 left = right
//   *  1 表示 left > right
//   *  INT32_MAX 表示不支持这种操作
//   */
//   int compare(const Value &left, const Value &right) const override;

  /***
  * @brief 将null值和其它类型相加，必须满足left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS,
  *        即参与相加的左值和右值，至少有一个是null类型。按照数据库规定，任何值+null = null, null+任何值 = null
  * @param left 左值
  * @param right 右值
  */
  RC add(const Value &left, const Value &right, Value &result) const override;

  /***
  * @brief 将null值和其它类型相减，必须满足left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS,
  *        即参与相加的左值和右值，至少有一个是null类型。按照数据库规定，任何值-null = null, null-任何值 = null
  * @param left 左值
  * @param right 右值
  */
  RC subtract(const Value &left, const Value &right, Value &result) const override;

  /***
  * @brief 将null值和其它类型相乘，必须满足left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS,
  *        即参与相加的左值和右值，至少有一个是null类型。按照数据库规定，任何值*null = null, null*任何值 = null
  * @param left 左值
  * @param right 右值
  */
  RC multiply(const Value &left, const Value &right, Value &result) const override;

  /***
  * @brief 对null值取负，必须满足val.attr_type_ == AttrType::NULLS，结果为“NULL”
  */
  RC negative(const Value &val, Value &result) const override;

  /***
  * @brief 将null值转换为字符串，必须满足val.attr_type_ == AttrType::NULLS，结果为“NULL”
  */
  RC to_string(const Value &val, string &result) const override;
};