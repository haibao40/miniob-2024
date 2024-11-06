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
#include "storage/field/field_meta.h"
#include "storage/index/index_meta.h"

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

public:
  int32_t             view_id() const { return view_id_; }
  const char         *name() const;
  const ViewFieldMeta    *field(int index) const;
  const ViewFieldMeta    *field(const char *name) const;
  const ViewFieldMeta    *find_field_by_offset(int offset) const;
  auto                field_metas() const -> const std::vector<ViewFieldMeta>                *{ return &view_fields_; }

  int field_num() const;  

  int record_size() const;

public:
  int  serialize(std::ostream &os) const override;
  int  deserialize(std::istream &is) override;
  int  get_serial_size() const override;
  void to_string(std::string &output) const override;
  void desc(std::ostream &os) const;

protected:
  int32_t                view_id_ = -1;
  std::string            name_;
  std::vector<ViewFieldMeta> view_fields_; 
};
