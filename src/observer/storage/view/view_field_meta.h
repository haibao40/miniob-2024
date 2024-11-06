//
// Created by lml on 2024/11/6.
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
class ViewFieldMeta
{
public:
  ViewFieldMeta() = default;
  ViewFieldMeta(const char *name, const char *table_name, const char *field_name);
  ~ViewFieldMeta() = default;

  RC init(const char *name, const char *table_name, const char *field_name);

public:
  const char *name() const;
  AttrType    type() const;
  const char *table_name() const;
  const char *field_name() const;

public:
  

public:
  void      to_json(Json::Value &json_value) const;
  static RC from_json(const Json::Value &json_value, ViewFieldMeta &field);
  
protected:
  string   name_;
  AttrType attr_type_;
  string   table_name_;
  string   field_name_;
};
