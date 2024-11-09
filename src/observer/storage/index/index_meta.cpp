/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELDS("fields");  
const static Json::StaticString IS_UNIQUE("is_unique"); 
const static Json::StaticString DISTANCE_TYPE("distance_type");
RC IndexMeta::init(const char *name,const vector<FieldMeta> &fields,bool is_unique,int distance_type){
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  distance_type_ = distance_type;
  is_unique_ = is_unique;
  vector<FieldMeta> *fields_temp = new vector<FieldMeta>;
  for(auto field : fields){
    fields_temp->push_back(field);
  }
  fields_ = *fields_temp;
  return RC::SUCCESS;
}
RC IndexMeta::init(const char *name, const FieldMeta &field)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_  = name;
  field_ = field.name();
  return RC::SUCCESS;
}
RC IndexMeta::init(const char *name,const vector<const FieldMeta*> &fields,bool is_unique){
    if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  is_unique_ = is_unique;
  vector<FieldMeta> *fields_temp = new vector<FieldMeta>;
  for(auto field : fields){
    fields_temp->push_back(*field);
  }
  fields_ = *fields_temp;
  return RC::SUCCESS;

}
RC IndexMeta::init(const char *name,const vector<const FieldMeta*>&fields,int distanace_type){
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  distance_type_ = distanace_type;
  vector<FieldMeta> *fields_temp = new vector<FieldMeta>;
  for(auto field : fields){
    fields_temp->push_back(*field);
  }
  fields_ = *fields_temp;
  return RC::SUCCESS;
}
RC IndexMeta::init(const char *name,const vector<FieldMeta> &fields,int distance_type){
   if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  distance_type_ = distance_type;
  vector<FieldMeta> *fields_temp = new vector<FieldMeta>;
  for(auto field : fields){
    fields_temp->push_back(field);
  }
  fields_ = *fields_temp;
  return RC::SUCCESS;
}
RC IndexMeta::init(const char *name,const vector<FieldMeta> &fields,bool is_unique){
    if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_  = name;
  is_unique_ = is_unique;
vector<FieldMeta> *fields_temp = new vector<FieldMeta>;
  for(auto field : fields){
    fields_temp->push_back(field);
  }
  fields_ = *fields_temp;
  return RC::SUCCESS;
}
void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME]       = name_;
  json_value[IS_UNIQUE] = is_unique_;  
  json_value[DISTANCE_TYPE] = distance_type_;
  Json::Value fields_value;
  for (const FieldMeta &field : fields_) {
    Json::Value field_value;
    field.to_json(field_value);
    fields_value.append(std::move(field_value));
  }
  json_value[FIELDS] = std::move(fields_value);
  
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value  = json_value[FIELD_NAME];
  const Json::Value& fields_value = json_value[FIELDS];  
  const Json::Value& is_unique_value = json_value[IS_UNIQUE]; 
  const Json::Value& distance_type_value = json_value[DISTANCE_TYPE];
  //const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  } 
  if (!fields_value.isArray()) {  
    LOG_ERROR("Fields of index are not an array. json value=%s", fields_value.toStyledString().c_str());  
    return RC::INTERNAL;  
  }  
  if(!distance_type_value.isInt()){
    LOG_ERROR("Is unique of index is not a boolean. json value=%s", distance_type_value.toStyledString().c_str());  
    return RC::INTERNAL;  
  }
  if (!is_unique_value.isBool()) {  
    LOG_ERROR("Is unique of index is not a boolean. json value=%s", is_unique_value.toStyledString().c_str());  
    return RC::INTERNAL;  
  }
  int field_num = fields_value.size();
  std::vector<FieldMeta> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    FieldMeta &field = fields[i];
    const Json::Value &field_value = fields_value[i];
    FieldMeta::from_json(field_value, field);
  }


   return index.init(name_value.asCString(), fields,is_unique_value.asBool(),distance_type_value.asInt());
}

const char *IndexMeta::name() const { return name_.c_str(); }

const char *IndexMeta::field() const { return field_.c_str(); }

const std::vector<FieldMeta>* IndexMeta::fields() const{return &fields_;}
const bool IndexMeta::is_unique() const{return is_unique_;}
void IndexMeta::desc(ostream &os) const { os << "index name=" << name_ << ", field=" << field_; }