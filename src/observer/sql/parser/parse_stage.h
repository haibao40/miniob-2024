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

#pragma once

#include "common/rc.h"

class SQLStageEvent;
class ParsedSqlNode;
/**
 * @brief 解析SQL语句，解析后的结果可以参考parse_defs.h
 * @ingroup SQLStage
 */
class ParseStage
{
public:
  RC handle_request(SQLStageEvent *sql_event);
private:
  /***
  * @brief 检测在存在只查询的情况下，where后面的比较表达式是否合法，比如下面这些select语句where后面的表达式就是不合法的，
  *        具体情况，参考primary-simple-sub-query.test测试文件，以下是测试文件中给出的不合法sql测试用例
  *        CREATE TABLE ssq_1(id int, col1 int, feat1 float);
  *        CREATE TABLE ssq_2(id int, col2 int, feat2 float);
  *        CREATE TABLE ssq_3(id int, col3 int, feat3 float);
  *        select * from ssq_1 where col1 = (select ssq_2.col2 from ssq_2); 左侧是标量，右侧是列查询，不合法
  *        select * from ssq_1 where col1 = (select * from ssq_2);          左侧是标量，右侧是表查询，不合法
  *        select * from ssq_1 where col1 in (select * from ssq_2);         左侧是标量，右侧是表查询，不合法
  *        select * from ssq_1 where col1 not in (select * from ssq_2);     左侧是标量，右侧是表查询，不合法
  */
  RC check_match_in_comparison_with_subquery(ParsedSqlNode* parsed_sql_node, bool& is_match);
};
