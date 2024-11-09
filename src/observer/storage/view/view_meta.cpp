//
// Created by lml on 2024/11/6.
//

#include "common/lang/string.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/view/view_meta.h"
#include "storage/table/table_meta.h"
#include "storage/trx/trx.h"
#include "json/json.h"
#include "sql/parser/parse_defs.h"

static const Json::StaticString FIELD_VIEW_ID("view_id");
static const Json::StaticString FIELD_VIEW_NAME("view_name");
static const Json::StaticString FIELD_VIEW_FIELDS("view_fields");
static const Json::StaticString FIELD_VIEW_CONS("view_conditions");
static const Json::StaticString CHILD_VIEW_FIELDS("child_fields");
static const Json::StaticString CHILD_VIEW_CONS("child_conditions");


ViewMeta::ViewMeta(const ViewMeta &other)
    : view_id_(other.view_id_),
      name_(other.name_),
      view_fields_(other.view_fields_),
      view_cons_(other.view_cons_),
      child_fields_(other.child_fields_),
      child_cons_(other.child_cons_)
{}

void ViewMeta::swap(ViewMeta &other) noexcept
{
  name_.swap(other.name_);
  view_fields_.swap(other.view_fields_);
  view_cons_.swap(other.view_cons_);
  child_fields_.swap(other.child_fields_);
  child_cons_.swap(other.child_cons_);
}

RC ViewMeta::init(int32_t view_id, const char *name, std::vector<ConditionSqlNode> conditions,
                   span<const ViewAttrInfoSqlNode> attributes)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (attributes.size() == 0) {
    LOG_ERROR("Invalid argument. name=%s, field_num=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  view_fields_.resize(attributes.size());
  view_cons_.resize(conditions.size());

  for (size_t i = 0; i < attributes.size(); i++) {
    const ViewAttrInfoSqlNode &attr_info = attributes[i];
    // `i` is the col_id of fields[i]
    rc = view_fields_[i].init(attr_info.expr_type,
      attr_info.name.c_str(), attr_info.table_name.c_str(), attr_info.field_name.c_str());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init view field meta. view name=%s, field name: %s", name, attr_info.name.c_str());
      return rc;
    }
  }

  for(size_t i = 0; i < conditions.size(); i++){
    const ConditionSqlNode &con = conditions[i];
    float left = con.left_value.get_float(), right = con.right_value.get_float();
    rc = view_cons_[i].init( con.left_is_attr, left, con.left_attr.relation_name, con.left_attr.attribute_name,
        con.comp, con.right_is_attr, con.right_attr.relation_name, con.right_attr.attribute_name, right
    );
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init view field meta. view name=%s, view con comp: %d", name, (int)con.comp);
      return rc;
    }
  }

  view_id_ = view_id;
  name_     = name;
//   storage_format_ = storage_format;
  LOG_INFO("Sussessfully initialized view meta. view id=%d, name=%s", view_id, name);
  return RC::SUCCESS;
}

RC ViewMeta::init(int32_t view_id, const char *name, std::vector<ConditionSqlNode> conditions,
std::vector<ConditionSqlNode> child_conditions,  std::vector<ViewAttrInfoSqlNode> child_attributes,
                   span<const ViewAttrInfoSqlNode> attributes)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (attributes.size() == 0) {
    LOG_ERROR("Invalid argument. name=%s, field_num=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  view_fields_.resize(attributes.size());
  view_cons_.resize(conditions.size());
  child_fields_.resize(child_attributes.size());
  child_cons_.resize(child_conditions.size());

  for (size_t i = 0; i < attributes.size(); i++) {
    const ViewAttrInfoSqlNode &attr_info = attributes[i];
    // `i` is the col_id of fields[i]
    rc = view_fields_[i].init(attr_info.expr_type,
      attr_info.name.c_str(), attr_info.table_name.c_str(), attr_info.field_name.c_str());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init view field meta. view name=%s, field name: %s", name, attr_info.name.c_str());
      return rc;
    }
  }

  for(size_t i = 0; i < conditions.size(); i++){
    const ConditionSqlNode &con = conditions[i];
    float left = con.left_value.get_float(), right = con.right_value.get_float();
    rc = view_cons_[i].init( con.left_is_attr, left, con.left_attr.relation_name, con.left_attr.attribute_name,
        con.comp, con.right_is_attr, con.right_attr.relation_name, con.right_attr.attribute_name, right
    );
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init view field meta. view name=%s, view con comp: %d", name, (int)con.comp);
      return rc;
    }
  }

  for (size_t i = 0; i < child_attributes.size(); i++) {
    const ViewAttrInfoSqlNode &attr_info = child_attributes[i];
    // `i` is the col_id of fields[i]
    rc = child_fields_[i].init(attr_info.expr_type,
      attr_info.name.c_str(), attr_info.table_name.c_str(), attr_info.field_name.c_str());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init child field meta. view name=%s, child field name: %s", name, attr_info.name.c_str());
      return rc;
    }
  }

  for(size_t i = 0; i < child_conditions.size(); i++){
    const ConditionSqlNode &con = child_conditions[i];
    float left = con.left_value.get_float(), right = con.right_value.get_float();
    rc = child_cons_[i].init( con.left_is_attr, left, con.left_attr.relation_name, con.left_attr.attribute_name,
        con.comp, con.right_is_attr, con.right_attr.relation_name, con.right_attr.attribute_name, right
    );
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init child condition meta. view name=%s, child view con comp: %d", name, (int)con.comp);
      return rc;
    }
  }

  view_id_ = view_id;
  name_     = name;
//   storage_format_ = storage_format;
  LOG_INFO("Sussessfully initialized view meta. view id=%d, name=%s", view_id, name);
  return RC::SUCCESS;
}

const char *ViewMeta::name() const { return name_.c_str(); }

const ViewFieldMeta *ViewMeta::field(int index) const { return &view_fields_[index]; }
const ViewFieldMeta *ViewMeta::child_field(int index) const { return &child_fields_[index]; }
const ConditionMeta *ViewMeta::con(int index) const { return &view_cons_[index]; }
const ConditionMeta *ViewMeta::child_con(int index) const { return &child_cons_[index]; }
const ViewFieldMeta *ViewMeta::field(const char *name) const
{
  if (nullptr == name) {
    return nullptr;
  }
  for (const ViewFieldMeta &field : view_fields_) {
    if (0 == strcmp(field.name(), name)) {
      return &field;
    }
  }
  return nullptr;
}
const ViewFieldMeta *ViewMeta::child_field(const char *name) const
{
  if (nullptr == name) {
    return nullptr;
  }
  for (const ViewFieldMeta &field : child_fields_) {
    if (0 == strcmp(field.name(), name)) {
      return &field;
    }
  }
  return nullptr;
}

int ViewMeta::field_num() const { return view_fields_.size(); }
int ViewMeta::con_num() const { return view_cons_.size(); }
int ViewMeta::child_field_num() const { return child_fields_.size(); }
int ViewMeta::child_con_num() const { return child_cons_.size(); }

int ViewMeta::serialize(std::ostream &ss) const
{
  Json::Value view_value;
  view_value[FIELD_VIEW_ID]   = view_id_;
  view_value[FIELD_VIEW_NAME] = name_;

  Json::Value fields_value;
  for (const ViewFieldMeta &field : view_fields_) {
    Json::Value field_value;
    field.to_json(field_value);
    fields_value.append(std::move(field_value));
  }

  view_value[FIELD_VIEW_FIELDS] = std::move(fields_value); //

  Json::Value cons_value;
  for (const ConditionMeta &con : view_cons_) {
    Json::Value con_value;
    con.to_json(con_value);
    cons_value.append(std::move(con_value));
  }

  view_value[FIELD_VIEW_CONS] = std::move(cons_value);

//   static const Json::StaticString CHILD_VIEW_FIELDS("child_conditions");
//   static const Json::StaticString CHILD__VIEW_CONS("child_conditions");
  Json::Value child_fields_value;
  for (const ViewFieldMeta &field : child_fields_) {
    Json::Value field_value;
    field.to_json(field_value);
    child_fields_value.append(std::move(field_value));
  }

  view_value[CHILD_VIEW_FIELDS] = std::move(child_fields_value); //

  Json::Value child_cons_value;
  for (const ConditionMeta &con : child_cons_) {
    Json::Value con_value;
    con.to_json(con_value);
    child_cons_value.append(std::move(con_value));
  }

  view_value[CHILD_VIEW_CONS] = std::move(child_cons_value);

  Json::StreamWriterBuilder builder;
  Json::StreamWriter       *writer = builder.newStreamWriter();

  std::streampos old_pos = ss.tellp();
  writer->write(view_value, &ss);
  int ret = (int)(ss.tellp() - old_pos);

  delete writer;
  return ret;
}

int ViewMeta::deserialize(std::istream &is)
{
  Json::Value             view_value;
  Json::CharReaderBuilder builder;
  std::string             errors;

  std::streampos old_pos = is.tellg();
  if (!Json::parseFromStream(builder, is, &view_value, &errors)) {
    LOG_ERROR("Failed to deserialize view meta. error=%s", errors.c_str());
    return -1;
  }

  const Json::Value &view_id_value = view_value[FIELD_VIEW_ID];
  if (!view_id_value.isInt()) {
    LOG_ERROR("Invalid view id. json value=%s", view_id_value.toStyledString().c_str());
    return -1;
  }

  int32_t view_id = view_id_value.asInt();

  const Json::Value &view_name_value = view_value[FIELD_VIEW_NAME];
  if (!view_name_value.isString()) {
    LOG_ERROR("Invalid view name. json value=%s", view_name_value.toStyledString().c_str());
    return -1;
  }

  std::string view_name = view_name_value.asString();

  const Json::Value &fields_value = view_value[FIELD_VIEW_FIELDS];
  if (!fields_value.isArray() || fields_value.size() <= 0) {
    LOG_ERROR("Invalid view meta. view fields is not array, json value=%s", fields_value.toStyledString().c_str());
    return -1;
  }

  RC  rc        = RC::SUCCESS;
  int field_num = fields_value.size();

  std::vector<ViewFieldMeta> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    ViewFieldMeta &field = fields[i];

    const Json::Value &field_value = fields_value[i];
    rc                             = ViewFieldMeta::from_json(field_value, field);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to deserialize view meta. view name =%s", view_name.c_str());
      return -1;
    }
  }
  
  const Json::Value &cons_value = view_value[FIELD_VIEW_CONS];
  std::vector<ConditionMeta> cons;
  
  if(!cons_value.isNull()){
    if (!cons_value.isArray() || cons_value.size() <= 0) {
        LOG_ERROR("Invalid view meta. view cons is not array, json value=%s", cons_value.toStyledString().c_str());
        return -1;
    }

    rc        = RC::SUCCESS;
    int con_num = cons_value.size();

    cons.resize(con_num);
    for (int i = 0; i < con_num; i++) {
        ConditionMeta &con = cons[i];

        const Json::Value &con_value = cons_value[i];
        rc                             = ConditionMeta::from_json(con_value, con);
        if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to deserialize view meta. view name =%s", view_name.c_str());
        return -1;
        }
    }
  }
  

//   auto comparator = [](const FieldMeta &f1, const FieldMeta &f2) { return f1.offset() < f2.offset(); };
//   std::sort(fields.begin(), fields.end(), comparator);

  view_id_ = view_id;
  name_.swap(view_name);
  view_fields_.swap(fields);
  view_cons_.swap(cons);

  return (int)(is.tellg() - old_pos);
}

int ViewMeta::get_serial_size() const { return -1; }

void ViewMeta::to_string(std::string &output) const {}

bool ViewMeta::insert_capacity(){
    bool res = true;
    if(view_fields_.size() <= 1){
        return true;
    }
    const char* table_name = view_fields_[0].table_name();
    for(size_t i = 1; i < view_fields_.size(); i++){
        if(strcasecmp(table_name, view_fields_[i].table_name()) != 0){
            res = false;
            break;
        }
    }
    return res;
}

bool ViewMeta::delete_capacity(){
    bool res = true;
    if(view_fields_.size() <= 1){
        return true;
    }
    const char* table_name = view_fields_[0].table_name();
    if(view_fields_[0].type() != ExprType::FIELD){
        return false;
    }
    for(size_t i = 1; i < view_fields_.size(); i++){
        if(strcasecmp(table_name, view_fields_[i].table_name()) != 0 || view_fields_[i].type() != ExprType::FIELD){
            res = false;
            break;
        }
    }
    return res;
}

bool ViewMeta::update_capacity(const std::vector<UpdateUnite>& update_units){
    bool res = true;
    for(auto update_unit:update_units){
        std::string field_name = update_unit.field_name;
        const ViewFieldMeta* view_field_meta = field(field_name.c_str());
        if(view_field_meta == nullptr || view_field_meta->type() != ExprType::FIELD){
            res = false;
            break;
        }
    }
    return res;
}