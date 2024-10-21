#pragma once

#include "common/type/data_type.h"

/**
 * @brief 日期类型，在Value中，日期类型以8位整数的形式存储，这里定义了针对日期类型的各种运算
 */
class DateType : public DataType
{
public:
  DateType() : DataType(AttrType::DATES) {}
  virtual ~DateType() {}

  /***
   * @brief 实现日期类型之间的比较
   */
  int compare(const Value &left, const Value &right) const override;

  /***
   @brief 将日期类型中存储的数据转换为字符串，存储在result中
   @result 返回的日期字符串，日期格式为"YYYY-MM-DD"
   */
  RC to_string(const Value &val, string &result) const override;
};
