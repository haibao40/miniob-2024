//
// Created by lml on 2024/11/6.
//

#include <limits.h>
#include <string.h>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/table/table.h"
#include "storage/view/view.h"
#include "storage/trx/trx.h"

View::~View()
{
  //do nothing
  LOG_INFO("View has been closed: %s", name());
}

RC View::create(Db *db, int32_t view_id, const char *path, const char *name, const char *base_dir,
    std::vector< ConditionSqlNode> conditions, span<const ViewAttrInfoSqlNode> attributes)
{
  if (view_id < 0) {
    LOG_WARN("invalid view id. view_id=%d, view_name=%s", view_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create view %s", name);

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. view_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 view_name.view记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create view file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_VIEW_EXIST;
    }
    LOG_ERROR("Create view file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);
  
  // 创建文件
  if ((rc = view_meta_.init(view_id, name, conditions, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init view meta. name:%s, ret:%d", name, rc);
    drop(path);
    return rc;  // delete view file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  view_meta_.serialize(fs);
  fs.close();

  db_       = db;
  base_dir_ = base_dir;
  return rc;
}

RC View::drop(const char *path)
{
  RC rc = RC::SUCCESS;

  if(::remove(path) < 0){
    LOG_ERROR("Failed to delete view, filename:%s, errmsg:%s", path, strerror(errno));
    return RC::INTERNAL;
  }
  LOG_INFO("Successfully drop view %s:%s", base_dir_.c_str(), view_meta_.name());
  return rc;
}

RC View::open(Db *db, const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (view_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize view meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  return RC::SUCCESS;
}

const char *View::name() const { return view_meta_.name(); }

const ViewMeta &View::view_meta() const { return view_meta_; }

RC View::sync()
{
  RC rc = RC::SUCCESS;
  
  LOG_INFO("Sync view over. view=%s", name());
  return rc;
}

bool View::update_capacity(){
    if(view_meta_.field_num() <= 1){
        return true;
    }
    bool res = true;
    const char* name = view_meta_.field_metas()->at(0).table_name();
    for(const ViewFieldMeta &fieldmeta:*view_meta_.field_metas()){
        if(strcmp(name, fieldmeta.table_name()) != 0){
            res = false;
            break;
        }
    }
    return res;
}

bool View::insert_capacity() { return view_meta_.insert_capacity(); }