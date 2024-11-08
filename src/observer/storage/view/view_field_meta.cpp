//
// Created by lml on 2024/11/6.
//

#include "storage/view/view_field_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"

#include "json/json.h"

const static Json::StaticString FIELD_VIEW_EXPR_TYPE("expr_type");
const static Json::StaticString FIELD_VIEW_NAME("name");
const static Json::StaticString FIELD_VIEW_TABLE_NAME("table_name");
const static Json::StaticString FIELD_VIEW_FIELD_NAME("field_name");

ViewFieldMeta::ViewFieldMeta(ExprType expr_type, const char *name, const char *table_name, const char *field_name)
{
  [[maybe_unused]] RC rc = this->init(expr_type, name, table_name, field_name);
  ASSERT(rc == RC::SUCCESS, "failed to init view field meta. rc=%s", strrc(rc));
}

RC ViewFieldMeta::init(ExprType expr_type, const char *name, const char *table_name, const char *field_name)
{
  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(table_name)) {
    LOG_WARN("TableName cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(field_name)) {
    LOG_WARN("FieldName cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  expr_type_   = expr_type;
  name_        = name;
  table_name_  = table_name;
  field_name_  = field_name;

  LOG_INFO("Init a view field with name=%s", name);
  return RC::SUCCESS;
}

const char *ViewFieldMeta::name() const { return name_.c_str(); }

const char *ViewFieldMeta::table_name() const { return table_name_.c_str(); }
const char *ViewFieldMeta::field_name() const { return field_name_.c_str(); }

ExprType ViewFieldMeta::type() const { return expr_type_; }

void ViewFieldMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_VIEW_EXPR_TYPE]     = (int)expr_type_;
  json_value[FIELD_VIEW_NAME]          = name_;
  json_value[FIELD_VIEW_TABLE_NAME]    = table_name_;
  json_value[FIELD_VIEW_FIELD_NAME]    = field_name_;
}

RC ViewFieldMeta::from_json(const Json::Value &json_value, ViewFieldMeta &field)
{
  if (!json_value.isObject()) {
    LOG_ERROR("Failed to deserialize field. json is not an object. json value=%s", json_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  const Json::Value &expr_type_value     = json_value[FIELD_VIEW_EXPR_TYPE];
  const Json::Value &name_value          = json_value[FIELD_VIEW_NAME];
  const Json::Value &table_name_value    = json_value[FIELD_VIEW_NAME];
  const Json::Value &field_name_value    = json_value[FIELD_VIEW_NAME];
  
  if (!expr_type_value.isIntegral()) {
    LOG_ERROR("View expr type is not a string. json value=%d", expr_type_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!name_value.isString()) {
    LOG_ERROR("View name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!table_name_value.isString()) {
    LOG_ERROR("Table name is not a string. json value=%s", table_name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!field_name_value.isString()) {
    LOG_ERROR("Field name is not a string. json value=%s", field_name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  ExprType expr_type        = (ExprType)expr_type_value.asInt();
  const char *name          = name_value.asCString();
  const char *table_name    = table_name_value.asCString();
  const char *field_name    = field_name_value.asCString();
  
  return field.init(expr_type, name, table_name, field_name);
}
