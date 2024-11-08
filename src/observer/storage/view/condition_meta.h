//
// Created by lml on 2024/11/7.
//

#pragma once

#include "common/rc.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"

namespace Json {
class Value;
}  // namespace Json

/**
 * @brief 字段元数据
 *
 */
class ConditionMeta
{
public:
  ConditionMeta() = default;
  ConditionMeta(int left_is_attr, float left_value, std::string left_table_name, std::string left_field_name,
  CompOp comp, int right_is_attr, std::string right_table_name, std::string right_field_name, float right_value);
  ~ConditionMeta() = default;

  RC init(int left_is_attr, float left_value, std::string left_table_name, std::string left_field_name,
  CompOp comp, int right_is_attr, std::string right_table_name, std::string right_field_name, float right_value);

public:
  const int       left_is_attr() const;
  const float       left_value() const;
  const char*  left_table_name() const;
  const char*  left_field_name() const;
  CompOp                  comp() const;
  const int      right_is_attr() const;
  const float      right_value() const;
  const char* right_table_name() const;
  const char* right_field_name() const;

public:
  

public:
  void      to_json(Json::Value &json_value) const;
  static RC from_json(const Json::Value &json_value, ConditionMeta &field);
  
protected:
  int       left_is_attr_;
  float       left_value_;
  std::string  left_table_name_;
  std::string  left_field_name_;
  CompOp                  comp_;
  int      right_is_attr_;
  float      right_value_;
  std::string right_table_name_;
  std::string right_field_name_;
};
