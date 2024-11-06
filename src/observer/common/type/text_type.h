#pragma once

#include "common/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 固定长度的字符串类型,很长很长
 * @ingroup TextType
 */
class TextType : public DataType
{
public:
  TextType() : DataType(AttrType::TEXTS) {}

  virtual ~TextType() = default;

  int compare(const Value &left, const Value &right) const override;

  /***
   * @brief 将val 转换为 type类型，并将结果保存在result中，
   *        目前，支持【字符串类型】-->【日期类型】, 【字符串类型】-->【向量类型】
   * @left 待转换值，必须满足 val.attr_type_ == AttrType::CHARS
   * @result 转换的结果
   */
  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;

private:
  /// 将char类型转换为其他类型的代码封装为函数,text暂时不考虑
//   static RC cast_char_to_date(const Value &val, Value &result);
//   static RC cast_char_to_vector(const Value &val, Value &result);
    static RC cast_text_to_char(const Value &val, Value &result);
};