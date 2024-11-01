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
// Created by Longda on 2021/4/13.
//

#include <string.h>
#include <string>

#include "parse_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "sql/parser/parse.h"

using namespace common;

RC ParseStage::handle_request(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  SqlResult         *sql_result = sql_event->session_event()->sql_result();
  const std::string &sql        = sql_event->sql();

  ParsedSqlResult parsed_sql_result;

  parse(sql.c_str(), &parsed_sql_result);
  if (parsed_sql_result.sql_nodes().empty()) {
    sql_result->set_return_code(RC::SUCCESS);
    sql_result->set_state_string("");
    return RC::INTERNAL;
  }

  if (parsed_sql_result.sql_nodes().size() > 1) {
    LOG_WARN("got multi sql commands but only 1 will be handled");
  }

  std::unique_ptr<ParsedSqlNode> sql_node = std::move(parsed_sql_result.sql_nodes().front());
  if (sql_node->flag == SCF_ERROR) {
    // set error information to event
    rc = RC::SQL_SYNTAX;
    sql_result->set_return_code(rc);
    sql_result->set_state_string("Failed to parse sql");
    return rc;
  }

  bool is_match = false;
  check_match_in_comparison_with_subquery(sql_node.get(), is_match);
  if(!is_match) {
    LOG_WARN("带有子查询的比较表达式校验失败,SQL不合法");
    return RC::SQL_SYNTAX;
  }

  sql_event->set_sql_node(std::move(sql_node));

  return RC::SUCCESS;
}

RC ParseStage::check_match_in_comparison_with_subquery(ParsedSqlNode* parsed_sql_node, bool& is_match)
{
  RC rc = RC::SUCCESS;
  is_match = true;
  if(parsed_sql_node->flag != SqlCommandFlag::SCF_SELECT) { //目前只是针对select做了这个检测,其余的类型就直接放过
    return RC::SUCCESS;
  }
  vector<CompOp> subquery_comp_ops = {IN,NOT_IN,EXISTS,NOT_EXISTS};
  for(auto condition: parsed_sql_node->selection.conditions) {
    if(condition.right_is_expr == 1 && condition.right_expr->type() == ExprType::UNBOUND_SUBQUERY) {
      UnboundSubqueryExpr* unbound_subquery_expr = (UnboundSubqueryExpr*) condition.right_expr;
      ParsedSqlNode* subquery_parsedSqlNode = unbound_subquery_expr->parsed_sql_node();
      std::vector<std::unique_ptr<Expression>>& subquery_expressions = subquery_parsedSqlNode->selection.expressions;
      //in和 exists的表达式中，左边和右边的，字段的数量必须对应，目前，只考虑左右都是1个字段的情况
      if(std::find(subquery_comp_ops.begin(), subquery_comp_ops.end(), condition.comp) != subquery_comp_ops.end()) {
        if(subquery_expressions.size() == 1 && subquery_expressions[0]->type() != ExprType::STAR) {
          is_match = true;
        }
        else {
          is_match = false;
          return RC::INTERNAL;
        }
      }
      else { //非in 和exists的比较表达式中，右边的子查询select后面必须只有一个表达式
        if(subquery_expressions.size() != 1 ) {
          is_match = false;
          return RC::INTERNAL;
        }
      }
    }
  }
  return rc;
}
