//
// Created by lml on 2024/11/6.
//

#pragma once

#include "storage/table/table_meta.h"
#include "storage/view/view_meta.h"
#include "common/types.h"
#include "common/lang/span.h"
#include "common/lang/functional.h"

class Trx;
class Db;

/**
 * @brief 表
 *
 */
class View
{
public:
  View() = default;
  ~View();

  /**
   * 创建一个视图
   * @param path 元数据保存的文件(完整路径)
   * @param name 视图名
   * @param base_dir 视图数据存放的路径
   * @param attributes 字段
   */
  RC create(Db *db, int32_t view_id, const char *path, const char *name, const char *base_dir,
      span<const ViewAttrInfoSqlNode> attributes);
  RC create(Db *db, int32_t view_id, const char *path, const char *name, const char *base_dir,
      std::vector<ConditionSqlNode> conditions, span<const ViewAttrInfoSqlNode> attributes);
  RC create(Db *db, int32_t view_id, const char *path, const char *name, const char *base_dir,
      std::vector<ConditionSqlNode> conditions, std::vector<ConditionSqlNode> child_conditions,
      std::vector<ViewAttrInfoSqlNode> child_attributes, span<const ViewAttrInfoSqlNode> attributes);

  /**
   * 删除一个视图
   * @param path 元数据保存的文件(完整路径)
   */
  RC drop(const char *path);

  /**
   * 打开一个表
   * @param meta_file 保存表元数据的文件完整路径
   */
  RC open(Db *db, const char *meta_file, const char *base_dir);

  //检查该视图能否更新
//   bool update_capacity();
  bool update_capacity(const std::vector<UpdateUnite> &update_units);
  bool insert_capacity();
  bool insert_capacity(std::vector<std::string> field_names);
  bool delete_capacity();

public:
  int32_t     view_id() const { return view_meta_.view_id(); }
  const char *name() const;

  Db *db() const { return db_; }

  const ViewMeta &view_meta() const;

  RC sync();

private:
  Db                *db_ = nullptr;
  string             base_dir_;
  ViewMeta          view_meta_;
};
