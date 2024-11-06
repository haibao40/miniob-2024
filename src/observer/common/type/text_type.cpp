#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "common/type/text_type.h"
#include "common/value.h"
#include "common/time/datetime.h"

#include <common/os/path.h>

//整个text就是大号的char，除了长度，名字和char不同，其他基本一样，有些转换操作就不搞了

//仅支持文本间的比较
int TextType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::TEXTS && right.attr_type() == AttrType::TEXTS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC TextType::set_value_from_str(Value &val, const string &data) const
{
  val.set_text(data.c_str());
  return RC::SUCCESS;
}



RC TextType::cast_to(const Value &val, AttrType type, Value &result) const
{
  if(val.attr_type_ != AttrType::TEXTS ) return RC::INVALID_ARGUMENT;
  RC rc = RC::SUCCESS;
  switch (type) {
    case AttrType::CHARS: {  //和char没区别，就长度问题而已，随便转
      rc = cast_text_to_char(val, result);
    } break;
    default: return RC::UNIMPLEMENTED;
  }
  return rc;
}

int TextType::cast_cost(AttrType type)
{
  if (type == AttrType::TEXTS) {
    return 0;
  }
  //表示可以将字符串类型转换为日期类型，类型转换的代价为1（代价理解为转换过程中的性能消耗）
  else if(type == AttrType::CHARS) {
    return 3;
  }
  return INT32_MAX;
}

RC TextType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}

RC TextType::cast_text_to_char(const Value &val, Value &result){
    result.set_string(val.value_.pointer_value_, val.length_);
    return RC::SUCCESS;
}