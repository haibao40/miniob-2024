//
// Created by lml on 2024/11/8.
//

#include "storage/view/view_field_meta.h"
#include "storage/view/condition_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"

#include "json/json.h"

const static Json::StaticString FIELD_CON_LEFT_TYPE("left_is_attr");
const static Json::StaticString FIELD_CON_LEFT_VALUE("left_value");
const static Json::StaticString FIELD_CON_LEFT_TABLE_NAME("left_table_name");
const static Json::StaticString FIELD_CON_LEFT_FIELD_NAME("left_field_name");
const static Json::StaticString FIELD_CON_RIGHT_TYPE("right_is_attr");
const static Json::StaticString FIELD_CON_RIGHT_VALUE("right_value");
const static Json::StaticString FIELD_CON_RIGHT_TABLE_NAME("right_table_name");
const static Json::StaticString FIELD_CON_RIGHT_FIELD_NAME("right_field_name");
const static Json::StaticString FIELD_CON_COMP("comp");

ConditionMeta::ConditionMeta(int left_is_attr, float left_value, std::string left_table_name, std::string left_field_name,
  CompOp comp, int right_is_attr, std::string right_table_name, std::string right_field_name, float right_value){
  [[maybe_unused]] RC rc = this->init(left_is_attr, left_value, left_table_name, left_field_name,
  comp, right_is_attr, right_table_name, right_field_name, right_value);
  ASSERT(rc == RC::SUCCESS, "failed to init view field meta. rc=%s", strrc(rc));
}

RC ConditionMeta::init(int left_is_attr, float left_value, std::string left_table_name, std::string left_field_name,
  CompOp comp, int right_is_attr, std::string right_table_name, std::string right_field_name, float right_value){
    //这里不做判别了，因为字符串为空也可能是合法的
    left_is_attr_     = left_is_attr;
    left_value_       = left_value;
    left_table_name_  = left_table_name;
    left_field_name_  = left_field_name;
    comp_             = comp;
    right_is_attr_    = right_is_attr;
    right_value_      = right_value;
    right_table_name_ = right_table_name;
    right_field_name_ = right_field_name;

    LOG_INFO("Init a view con with comp=%d", (int)comp);
    return RC::SUCCESS;
}

const int       ConditionMeta::left_is_attr() const { return left_is_attr_; }
const float       ConditionMeta::left_value() const { return left_value_; }
const char* ConditionMeta:: left_table_name() const { return left_table_name_.c_str(); }
const char*  ConditionMeta::left_field_name() const { return left_field_name_.c_str(); }
CompOp                  ConditionMeta::comp() const { return comp_; }
const int      ConditionMeta::right_is_attr() const { return right_is_attr_; }
const float      ConditionMeta::right_value() const { return right_value_; }
const char* ConditionMeta::right_table_name() const { return right_table_name_.c_str(); }
const char* ConditionMeta::right_field_name() const { return right_field_name_.c_str(); }

void ConditionMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_CON_LEFT_TYPE]        = left_is_attr_;
  json_value[FIELD_CON_LEFT_VALUE]       = left_value_;
  json_value[FIELD_CON_LEFT_TABLE_NAME]  = left_table_name_;
  json_value[FIELD_CON_LEFT_FIELD_NAME]  = left_field_name_;
  json_value[FIELD_CON_RIGHT_TYPE]       = right_is_attr_;
  json_value[FIELD_CON_RIGHT_VALUE]      = right_value_;
  json_value[FIELD_CON_RIGHT_TABLE_NAME] = right_table_name_;
  json_value[FIELD_CON_RIGHT_FIELD_NAME] = right_field_name_;
  json_value[FIELD_CON_COMP]             = (int)comp_;
}

RC ConditionMeta::from_json(const Json::Value &json_value, ConditionMeta &con)
{
  if (!json_value.isObject()) {
    LOG_ERROR("Failed to deserialize condition. json is not an object. json value=%s", json_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  const Json::Value &left_type_value     = json_value[FIELD_CON_LEFT_TYPE];
  const Json::Value &left_value_value    = json_value[FIELD_CON_LEFT_VALUE];
  const Json::Value &left_table_value    = json_value[FIELD_CON_LEFT_TABLE_NAME];
  const Json::Value &left_field_value    = json_value[FIELD_CON_LEFT_FIELD_NAME];
  const Json::Value &right_type_value    = json_value[FIELD_CON_RIGHT_TYPE];
  const Json::Value &right_value_value   = json_value[FIELD_CON_RIGHT_VALUE];
  const Json::Value &right_table_value   = json_value[FIELD_CON_RIGHT_TABLE_NAME];
  const Json::Value &right_field_value   = json_value[FIELD_CON_RIGHT_FIELD_NAME];
  const Json::Value &comp_value          = json_value[FIELD_CON_COMP];
  
  //不做判断，是因为条件可能为空
//   if(!comp_value.isIntegral()){
//     LOG_ERROR("Condition comp type is not a string. json value=%d", comp_value.toStyledString().c_str());
//     return RC::INTERNAL;
//   }
//   if(!left_type_value.isIntegral()){
//     LOG_ERROR("Condition left_type type is not a string. json value=%d", comp_value.toStyledString().c_str());
//     return RC::INTERNAL;
//   }
//   if(!right_type_value.isIntegral()){
//     LOG_ERROR("Condition right_type type is not a string. json value=%d", comp_value.toStyledString().c_str());
//     return RC::INTERNAL;
//   }

    int left_is_attr             = left_type_value.asInt();
    float left_value             = left_value_value.asFloat();
    const char* left_table_name  = left_table_value.asCString();
    const char* left_field_name  = left_field_value.asCString();
    CompOp comp                  = (CompOp)comp_value.asInt();
    int right_is_attr            = right_type_value.asInt();
    float right_value            = right_value_value.asInt();
    const char* right_table_name = right_table_value.asCString();
    const char* right_field_name = right_field_value.asCString();
  
  return con.init(left_is_attr, left_value, left_table_name, left_field_name,
  comp, right_is_attr, right_table_name, right_field_name, right_value);
}
