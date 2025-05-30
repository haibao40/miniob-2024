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
// Created by Wangyunlai on 2023/4/25.
//

#pragma once

#include <string>

#include "sql/stmt/stmt.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateIndexStmt : public Stmt
{
public:
  CreateIndexStmt(Table *table, const FieldMeta *field_meta, const std::string &index_name)
      : table_(table), field_meta_(field_meta), index_name_(index_name)
  {}
  CreateIndexStmt(Table *table, const vector<const FieldMeta*>* field_metas, const std::string &index_name,bool is_unique)
      : table_(table), field_metas_(field_metas), index_name_(index_name),is_unique_(is_unique)
  {}

  virtual ~CreateIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table             *table() const { return table_; }
  const FieldMeta   *field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }
  const bool & is_unique() const {return is_unique_;}
  const vector<const FieldMeta*>*  field_metas() const {return field_metas_;}

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table           *table_      = nullptr;
  const FieldMeta *field_meta_ = nullptr;
  const vector<const FieldMeta*>*  field_metas_ ; //要写在index_name_前面
  std::string      index_name_;
  bool is_unique_ = false;
};


class CreateVectorIndexStmt : public Stmt
{
  public:
  CreateVectorIndexStmt(Table *table, const FieldMeta *field_meta, const std::string &index_name)
      : table_(table), field_meta_(field_meta), index_name_(index_name)
  {}
  CreateVectorIndexStmt(Table *table, const vector<const FieldMeta*>* field_metas, const std::string &index_name,
                       int lists,int distance_type,int probes)
      : table_(table), field_metas_(field_metas), index_name_(index_name),lists_(lists),distance_type_(distance_type)
        ,probes_(probes)
  {}

  virtual ~CreateVectorIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VECTOR_INDEX; }

  Table             *table() const { return table_; }
  const FieldMeta   *field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }
  //const bool & is_unique() const {return is_unique_;}
  const vector<const FieldMeta*>*  field_metas() const {return field_metas_;}
  const int &lists(){return lists_;}
  const int &probes(){return probes_;}
  const int &distance_type(){return distance_type_;}
public:
  static RC create(Db *db, const CreateVectorIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table           *table_      = nullptr;
  const FieldMeta *field_meta_ = nullptr;
  const vector<const FieldMeta*>*  field_metas_ ; //要写在index_name_前面
  std::string      index_name_;
  //bool is_unique_ = false;
  int lists_;
  int distance_type_; 
  int probes_;
  
};