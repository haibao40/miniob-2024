/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//
#include <limits.h>
#include <string.h>
//#include "storage/index/ivfflat_index.h"
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
#include "storage/index/bplus_tree_index.h"

#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"


Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
    span<const AttrInfoSqlNode> attributes, StorageFormat storage_format)
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  const vector<FieldMeta> *trx_fields = db->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attributes, storage_format)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  string             data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = db->buffer_pool_manager();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop(const char *path)
{
  RC rc = RC::SUCCESS;

  if(::remove(path) < 0){
    LOG_ERROR("Failed to delete table, filename:%s, errmsg:%s", path, strerror(errno));
    return RC::INTERNAL;
  }

  string             data_file = table_data_file(base_dir_.c_str(), table_meta_.name());
  BufferPoolManager &bpm       = db_->buffer_pool_manager();
  rc                           = bpm.remove_file(data_file.c_str());
  if(rc != RC::SUCCESS){
    LOG_ERROR("Failed to remove file from buffer pool. filename=%s", data_file.c_str());
    return RC::INTERNAL;
  }

  data_buffer_pool_ = nullptr;
  
  //删除record_handler
  if(record_handler_ != nullptr){
    delete record_handler_;
    record_handler_ = nullptr;
  }

  for(auto &index : indexes_){
    index->destroy();
    delete index;
    index = nullptr;
  }

  LOG_INFO("Successfully drop table %s:%s", base_dir_.c_str(), table_meta_.name());
  return rc;
}

RC Table::open(Db *db, const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  const int index_num = table_meta_.index_num();

  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    std::vector<const FieldMeta*>* field_metas_point = new std::vector<const FieldMeta*>();
    //const FieldMeta *field_meta = table_meta_.field(index_meta->field());
    const std::vector<FieldMeta>* field_metas = index_meta->fields();
    for(std::size_t i=0;i< field_metas->size();i++){
       field_metas_point->push_back(&((*field_metas)[i]));
    }
    
    if(index_meta->distance_type()<0){
       BplusTreeIndex *index      = new BplusTreeIndex();
       string   index_file = table_index_file(base_dir, name(), index_meta->name());
       rc = index->open(this, index_file.c_str(), *index_meta, field_metas_point);
       if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
    }else{
       IvfflatIndex *index      = new IvfflatIndex();
       string   index_file = table_index_file(base_dir, name(), index_meta->name());
       rc = index->open(this, index_file.c_str(), *index_meta, field_metas_point);
       if (rc != RC::SUCCESS) {
       delete index;
       LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      indexes_.push_back(index);
       return rc;
      }
       indexes_.push_back(index);
  }
  }
  return rc;
}

RC Table::update_record(Record &old_record, vector<Value> &new_values){
  RC rc = RC::SUCCESS;
  Record new_record;

  rc = make_record(new_values.size(), new_values.data(), new_record);
  if(OB_FAIL(rc)) {  //make_record失败，可能是values的值不合法，比如某些字段不能为null
    return rc;
  }

  //这里加一个步骤，查找唯一索引是否重复
  rc = unique_index_contor(new_record.data());
  if(rc !=RC::SUCCESS){
    return rc ;
  }

  rc = insert_record(new_record);       //插入新的记录
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to insert record. table name:%s", table_meta_.name());
    return rc;
  }

  rc = delete_record(old_record);          //删除旧记录
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to delete old record when update record. table name:%s", table_meta_.name());
    return rc;
  }
  return rc;
}
//这个方法就是给一个record 我们查看一下满不满足唯一索引
RC Table::unique_index_contor(const char* record){
  RC rc = RC::SUCCESS;
   for(auto index : indexes_){
    IndexMeta index_meta  =index->index_meta();
    if(index_meta.is_unique() == true){
          std::list<RID> rids;
          //list<RID>* list = new vector<RID>();
          BplusTreeIndex* b_index = dynamic_cast<BplusTreeIndex*>(index);
          if (b_index) {
            rc = b_index->get_entry(record,rids);
            if(rc!=RC::SUCCESS){
              return rc  ;
            }
         } else {
             continue; //当前索引不是b+树索引
         }
         if(rids.size()!=0){
                return RC::UNIQUE_FAILD;
        }
    }
   }
    return RC::SUCCESS;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  //在这里加一个步骤判断唯一索引是否重复
  rc = unique_index_contor(record.data());
  if(rc !=RC::SUCCESS){
    return rc ;
  }
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

RC Table::visit_record(const RID &rid, function<bool(Record &)> visitor)
{
  return record_handler_->visit_record(rid, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  RC rc = record_handler_->get_record(rid, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid());
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  RC rc = RC::SUCCESS;
  // 检查字段类型是否一致, 注意，系统自带一个空值列表的隐藏字段
  if (value_num + table_meta_.system_not_visible_field_number() + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  //在创建record记录时，将隐藏字段空值列表null_value_list对应的数据一起添加到record中
  Value *new_values = new Value[value_num+1];
  Value null_value_list = Value();
  rc = get_null_value_list(value_num, values, null_value_list);
  if(rc != RC::SUCCESS) {
    LOG_INFO("make_record过程中，获取隐藏字段空值列表失败\n");
    return rc;
  }
  new_values[0] = null_value_list;
  for(int i = 1; i < value_num+1; i++) {
    new_values[i] = values[i-1];
  }
  values = new_values;
  value_num = value_num + 1; //因为添加了隐藏字段，所以value_num需要+1

  const int normal_field_start_index = table_meta_.sys_field_num();
  // 复制所有字段的值
  int   record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  memset(record_data, 0, record_size);

  for (int i = 0; i < value_num && OB_SUCC(rc); i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &    value = values[i];
    if (field->type() != value.attr_type() && value.attr_type() != AttrType::NULLS) { //只有类型不一致，且提供的不是null值，才进行类型转换
      Value real_value;
      rc = Value::cast_to(value, field->type(), real_value);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name(), value.to_string().c_str());
        break;
      }
      rc = set_value_to_record(record_data, real_value, field);
    } else {
      rc = set_value_to_record(record_data, value, field);
    }
  }
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to make record. table name:%s", table_meta_.name());
    free(record_data);
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::get_null_value_list(int value_num, const Value *values, Value& result)
{
  std::vector<FieldMeta> field_metas = *(table_meta_.field_metas()); //注意：第一个是null值列表对应的字段元信息
  FieldMeta null_value_list_field_meta = field_metas[table_meta_.sys_field_num()];
  LOG_INFO("len:%d",null_value_list_field_meta.len());
  char* null_value_list_data = (char *) malloc(null_value_list_field_meta.len());
  null_value_list_data[value_num] = '\0'; //字符串结束符
  for(int i = 0; i < value_num;i++) {
    if(field_metas[i+1].not_null()) {//字段元信息要求不是null
      if(values[i].attr_type() != AttrType::NULLS) { //提供的数据不是null
        null_value_list_data[i] = '0';
      }
      else { //提供的数据是null
        LOG_INFO("字段:%s不能为空值\n",field_metas[i+1].name());
        return RC::FIELD_CAN_NOT_BE_NULL;
      }
    }
    else if(!field_metas[i+1].not_null()) //字段元信息没有要求不是null
    {
      if(values[i].attr_type() != AttrType::NULLS) { //提供的数据不是null
        null_value_list_data[i] = '0';
      }
      else { //提供的数据是null
        null_value_list_data[i] = '1';
      }
    }
  }
  result.set_type(AttrType::CHARS);
  result.set_data(null_value_list_data, strlen(null_value_list_data));
  free(null_value_list_data); //释放临时内存
  return RC::SUCCESS;
}

RC Table::set_value_to_record(char *record_data, const Value &value, const FieldMeta *field)
{
  if(field == nullptr){
    LOG_WARN("filed is empty");
    return RC::EMPTY;
  }
  if(field->len() < value.length()) {
    LOG_WARN("传入value的存储长度，超过了字段元数据FieldMeta中定义的长度");
    return RC::INVALID_ARGUMENT;
  }
  size_t       copy_len = field->len();
  const size_t data_len = value.length();
  if (field->type() == AttrType::CHARS) {
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
 
  memcpy(record_data + field->offset(), value.data(), copy_len);
  
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  string data_file = table_data_file(base_dir, table_meta_.name());

  BufferPoolManager &bpm = db_->buffer_pool_manager();
  RC                 rc  = bpm.open_file(db_->log_handler(), data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler(table_meta_.storage_format());

  rc = record_handler_->init(*data_buffer_pool_, db_->log_handler(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, db_->log_handler(), mode, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan_chunk(this, *data_buffer_pool_, db_->log_handler(), mode);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}
RC Table::create_vector_index(Trx *trx, const vector<const FieldMeta*> *field_metas, const char *index_name,
                        int lists,int distance_type,int probes){
                           vector<const FieldMeta*> *field_meta_not_const = new vector<const FieldMeta*> ();
  for(auto field : *field_metas){
    field_meta_not_const->push_back(field);
  }
  if(common::is_blank(index_name)){
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }
  for(auto field_meta:*field_metas){
    if(nullptr == field_meta){
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
    }
  }
  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, *field_metas,distance_type);
  if(rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s",
             name(), index_name);
    return rc;
  }
  // 创建索引相关数据
  IvfflatIndex *index      = new IvfflatIndex();
  string          index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  index->init(lists,distance_type,probes);
  rc = index->create(this, index_file.c_str(), new_index_meta, field_meta_not_const);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  Record* record = new Record();
  std::vector<Record *>* records_ = new std::vector<Record *>();
  while (OB_SUCC(rc = scanner.next(*record))) {
    records_->push_back(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  index->set_data(records_);
  index->Cluster();
  // Record record;
  // while (OB_SUCC(rc = scanner.next(record))) {
  //   rc = index->insert_entry(record.data(), &record.rid());
  //   if (rc != RC::SUCCESS) {
  //     LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
  //              name(), index_name, strrc(rc));
  //     return rc;
  //   }
  // }
  // if (RC::RECORD_EOF == rc) {
  //   rc = RC::SUCCESS;
  // } else {
  //   LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
  //            name(), index_name, strrc(rc));
  //   return rc;
  // }
  // scanner.close_scan();
  // LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);
  (*vector_index_)[index_name] = index;
   indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    //LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
  return rc;
  }

RC Table::create_index(Trx *trx, const vector<const FieldMeta*> *field_metas, const char *index_name,bool is_unique){
  vector<const FieldMeta*> *field_meta_not_const = new vector<const FieldMeta*> ();
  for(auto field : *field_metas){
    field_meta_not_const->push_back(field);
  }
  if(common::is_blank(index_name)){
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }
  for(auto field_meta:*field_metas){
    if(nullptr == field_meta){
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
    }
  }
  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, *field_metas,is_unique);
  if(rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s",
             name(), index_name);
    return rc;
  }
  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  string          index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, index_file.c_str(), new_index_meta, field_meta_not_const);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

   indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}


RC Table::create_index(Trx *trx, const FieldMeta *field_meta, const char *index_name)
{
  if (common::is_blank(index_name) || nullptr == field_meta) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta new_index_meta;

  RC rc = new_index_meta.init(index_name, *field_meta);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s", 
             name(), index_name, field_meta->name());
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  string          index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, index_file.c_str(), new_index_meta, *field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", 
             name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const RID &rid)
{
  RC     rc = RC::SUCCESS;
  Record record;
  rc = get_record(rid, record);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return delete_record(record);
}

RC Table::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
       rc = index->delete_entry(record.data(), &record.rid());
       ASSERT(RC::SUCCESS == rc, 
            "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
            name(), index->index_meta().name(), record.rid().to_string().c_str(), strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
  }
  }
  return rc;
}


vector<Record*>* Table::ann_search(vector<float> base_vector, int limit,IvfflatIndex* index){
  vector<Record*>* result = new vector<Record*>();
  vector<RID> ids = index->ann_search(base_vector,limit);
  for(int i=0;i<ids.size();i++){
      Record* record = new Record();
      this->get_record((ids[i]),*record);
      result->push_back(record);
  }
  return result;

}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    if(index->is_vector_index() == false){
      rc = index->delete_entry(record, &rid);
      if (rc != RC::SUCCESS) {
        if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
          break;
        }
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }

  rc = data_buffer_pool_->flush_all_pages();
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
