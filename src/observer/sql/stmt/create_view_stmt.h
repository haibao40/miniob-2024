#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class SelectStmt;
class Db;
class Table;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
    CreateViewStmt(const std::string &view_name)
      : view_name_(view_name) {}
  CreateViewStmt(
      const std::string &view_name, const std::vector<ViewAttrInfoSqlNode> &attr_infos)
      : view_name_(view_name), view_attr_infos_(attr_infos)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string                  &view_name() const { return view_name_; }
  const std::vector<ViewAttrInfoSqlNode> &attr_infos() const { return view_attr_infos_; }
  const std::vector<ConditionSqlNode> &con_infos() const { return view_con_infos_; }
  const std::vector<ViewAttrInfoSqlNode> &child_attr_infos() const { return child_attr_infos_; }
  const std::vector<ConditionSqlNode> &child_con_infos() const { return child_con_infos_; }

  static RC            create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt);
  static RC get_attr_infos(Db *db, vector<unique_ptr<Expression>> &query_expressions, std::vector<ViewAttrInfoSqlNode>& attr_infos);
  static RC get_con_infos(Db *db, std::vector<FilterUnit *> &filter_units, std::vector<ConditionSqlNode> &con_infos);

private:
  std::string                  view_name_;
  std::vector<ViewAttrInfoSqlNode> view_attr_infos_;
  std::vector<ConditionSqlNode> view_con_infos_;
  std::vector<ViewAttrInfoSqlNode> child_attr_infos_;
  std::vector<ConditionSqlNode> child_con_infos_;
//   SelectStmt      *select_stmt_ = nullptr;
};