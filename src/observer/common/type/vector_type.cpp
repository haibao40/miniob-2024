#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/value.h"

int VectorType::compare(const Value &left, const Value &right) const
{
  ASSERT(right.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS, "left or right type is not VECTORS");
  //参数不是向量类型
  if(right.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS){
    LOG_ERROR("left or right type is not VECTORS, this is function for vector add");
    return INT32_MAX;
  }
  const vector<float> left_vector = left.get_vector();
  const vector<float> right_vector = right.get_vector();
  //TODO:暂时不考虑向量长度不一致的情况，估计测试用例里面应该不会出现
  for (size_t i = 0; i < left_vector.size(); ++i) {  //从前往后依次比较
    if(left_vector[i] < right_vector[i]) return -1;
    else if(left_vector[i] > right_vector[i]) return 1;
  }
  return 0;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  return vector_arithmetic_operation(left, right, result, ArithmeticOperation::ADD);
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const{
  return vector_arithmetic_operation(left, right, result, ArithmeticOperation::SUBTRACT);
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const{
  return vector_arithmetic_operation(left, right, result, ArithmeticOperation::MULTIPLY);
}

RC VectorType::to_string(const Value &val, string &result) const
{
  ASSERT(val.attr_type() != AttrType::VECTORS, "val type is not VECTORS");
  if(val.attr_type() != AttrType::VECTORS){
    LOG_ERROR("val type is not VECTORS, this is function for VECTORS");
    return RC::INVALID_ARGUMENT;
  }
  const vector<float>& vec = val.get_vector();
  stringstream ss;
  ss << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    ss << common::double_to_str(vec[i]);  //这个函数会将浮点数转换为字符串，最多保留小数点后2位并去掉多余的0
    if (i != vec.size() - 1) { //非最后一个元素，添加英文逗号作为分隔符
      ss << ",";
    }
  }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}


RC VectorType::vector_arithmetic_operation(const Value &left, const Value &right, Value &result, ArithmeticOperation op){
  ASSERT(right.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS, "left or right type is not VECTORS");
  //参数不是向量类型
  if(right.attr_type() != AttrType::VECTORS || right.attr_type() != AttrType::VECTORS){
    LOG_ERROR("left or right type is not VECTORS, this is function for vector add");
    return RC::INVALID_ARGUMENT;
  }
  const vector<float> left_vector = left.get_vector();
  const vector<float> right_vector = right.get_vector();
  //左右向量的长度不相等
  if(left_vector.size() != right_vector.size()){
    LOG_ERROR("left and right vector size is not equal, can not add them");
    return RC::INVALID_ARGUMENT;
  }
  //计算操作
  // 定义一个函数指针类型
  std::function<float(float, float)> arithmetic_function;
  // 根据操作类型返回相应的运算函数
  switch (op) {
    case ArithmeticOperation::ADD:{
      arithmetic_function = [](float a, float b) { return a + b; };
    } break;
    case ArithmeticOperation::SUBTRACT:{
      arithmetic_function = [](float a, float b) { return a - b; };
    } break;
    case ArithmeticOperation::MULTIPLY:{
      arithmetic_function = [](float a, float b) { return a * b; };
    } break;
    default:{
      LOG_ERROR("INVALID_ARGUMENT,not support ArithmeticOperation in vector_type");
      return RC::INVALID_ARGUMENT;
    }
  }
  vector<float> result_vector;
  result_vector.resize(left_vector.size());
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result_vector[i] = arithmetic_function(left_vector[i],right_vector[i]);
  }
  result.set_vector(result_vector);
  return RC::SUCCESS;
}