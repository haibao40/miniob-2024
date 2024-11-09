//
// Created by lml on 2024/11/6.
//

#pragma once

#include <string>
#include <vector>
#include <span>

#include "common/lang/serializable.h"
#include "common/rc.h"
#include "common/types.h"
#include "storage/view/view_field_meta.h"
#include "storage/view/condition_meta.h"
#include "storage/field/field_meta.h"
#include "storage/index/index_meta.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 表元数据
 *
 */
class ViewMeta : public common::Serializable
{
public:
  ViewMeta()          = default;
  virtual ~ViewMeta() = default;

  ViewMeta(const ViewMeta &other);

  void swap(ViewMeta &other) noexcept;

  RC init(int32_t view_id, const char *name, std::span<const ViewAttrInfoSqlNode> attributes);
  RC init(int32_t view_id, const char *name, std::vector<ConditionSqlNode> conditions,
                                             std::span<const ViewAttrInfoSqlNode> attributes);
  RC init(int32_t view_id, const char *name, std::vector<ConditionSqlNode> conditions, 
  std::vector<ConditionSqlNode> child_conditions,  std::vector<ViewAttrInfoSqlNode> child_attributes,
                                    std::span<const ViewAttrInfoSqlNode> attributes);

public:
  int32_t             view_id() const { return view_id_; }
  const char         *name() const;
  const ViewFieldMeta    *field(int index) const;
  const ViewFieldMeta    *field(const char *name) const;
  const ViewFieldMeta    *child_field(int index) const;
  const ViewFieldMeta    *child_field(const char *name) const;
  const ConditionMeta      *con(int index) const;
  const ConditionMeta    *child_con(int index) const;

  auto                field_metas() const -> const std::vector<ViewFieldMeta>                *{ return &view_fields_; }
  auto                  con_metas() const -> const std::vector<ConditionMeta>                *{ return &view_cons_; }
  auto          child_field_metas() const -> const std::vector<ViewFieldMeta>                *{ return &child_fields_; }
  auto            child_con_metas() const -> const std::vector<ConditionMeta>                *{ return &child_cons_; }

  int       field_num() const;  
  int         con_num() const;
  int child_field_num() const;  
  int   child_con_num() const;
public:
  int  serialize(std::ostream &os) const override;
  int  deserialize(std::istream &is) override;
  int  get_serial_size() const override;
  void to_string(std::string &output) const override;
  void desc(std::ostream &os) const;

public:
  bool insert_capacity();
  bool update_capacity(const std::vector<UpdateUnite>& update_units);

protected:
  int32_t                view_id_ = -1;
  std::string            name_;
  std::vector<ViewFieldMeta> view_fields_;
  std::vector<ConditionMeta> view_cons_; 
  std::vector<ViewFieldMeta> child_fields_;
  std::vector<ConditionMeta> child_cons_;
};
