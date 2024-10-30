//
// Created by limaoliang on 2024/10/30.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class SelectStmt;
class Db;
class Table;

/**
 * @brief 表示CreateTableSelect语句
 * @ingroup Statement
 */
class CreateTableSelectStmt : public Stmt
{
public:
  CreateTableSelectStmt() = default;
  ~CreateTableSelectStmt() override;

  StmtType type() const override { return StmtType::CREATE_TABLE_SELECT; }

public:
  static RC create(Db *db, CreateTableSelectSqlNode &create_table_select_sql, Stmt *&stmt);

public:
  SelectStmt      *select_stmt() const { return select_stmt_; }
  const char      *table_name()        { return table_name_.c_str(); }
  Table           *table()       const { return table_; }
  
private:
  std::string     table_name_;
  SelectStmt      *select_stmt_ = nullptr;
  Table           *table_       = nullptr;
};
