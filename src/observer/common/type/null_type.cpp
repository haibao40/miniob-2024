#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/null_type.h"
#include "common/value.h"

bool NullType::compare_with_null_type(const Value &left, const Value &right)
{
  ASSERT(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS, "left type is not null_type and right type is not null_type, there is compare function for null_type");
  if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS) {
    return false;
  }
  else {
    throw "参数不合法: 传入的参数中，left和right至少有一个是null_type类型的value";
  }
}


//int NullType::compare(const Value &left, const Value &right) const
//{
//  ASSERT(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS, "left type is not null_type and right type is not null_type, there is function for null_type");
//  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS){
//    return -1;
//  }
//  return INT32_MAX;
//}

RC NullType::add(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS, "left type is not null_type and right type is not null_type, there is function for null_type");
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS){
    result.set_null();
  }
  return RC::UNSUPPORTED;
}

RC NullType::subtract(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS, "left type is not null_type and right type is not null_type, there is function for null_type");
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS){
    result.set_null();
  }
  return RC::UNSUPPORTED;
}

RC NullType::multiply(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS, "left type is not null_type and right type is not null_type, there is function for null_type");
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS){
    result.set_null();
  }
  return RC::UNSUPPORTED;
}

RC NullType::negative(const Value &val, Value &result) const
{
  ASSERT(val.attr_type() == AttrType::NULLS, "val type is not null_type , there is function for null_type");
  if(val.attr_type() == AttrType::NULLS){
    result.set_null();
  }
  return RC::UNSUPPORTED;
}

RC NullType::to_string(const Value &val, string &result) const
{
  ASSERT(val.attr_type() == AttrType::NULLS, "val type is not null_type , there is function for null_type");
  stringstream ss;
  ss << "NULL";
  result = ss.str();
  return RC::SUCCESS;
}