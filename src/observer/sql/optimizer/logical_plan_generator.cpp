/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "common/value.h"

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/limit_logical_operator.h"
#include "sql/operator/insert_with_tuples_logical_operator.h"
#include "sql/operator/vector_index_logical_operator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/create_table_select_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression_iterator.h"

#include "sql/optimizer/optimize_stage.h"

#include <regex>

class PhysicalOperator;

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;

    case StmtType::CREATE_TABLE_SELECT: {
      CreateTableSelectStmt *create_table_select_stmt = static_cast<CreateTableSelectStmt *>(stmt);

      rc = create_plan(create_table_select_stmt, logical_operator);
    } break;

    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
   unique_ptr<VectorIndexLogicalOperator> index_scan(
    new VectorIndexLogicalOperator((select_stmt->tables())[0], ReadWriteMode::READ_ONLY,select_stmt->limit_count(),
                                    select_stmt->order_by()));
    if(index_scan->index() != nullptr){
      auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
      unique_ptr<LogicalOperator> log_scan = std::move(index_scan);
      project_oper->add_child(std::move(log_scan));
      logical_operator = std::move(project_oper);
      return RC::SUCCESS;
    }
   



  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  const std::vector<Table *> &tables = select_stmt->tables();
  if(select_stmt->join_filter().size() == 0){ //这是原来的多表查询逻辑,没有使用join 这里有更好的方案
    for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }
  }else{
    int on_predicate_oper_current = 0;
    std::vector<FilterStmt*> join_filters = select_stmt->join_filter();
    for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    }else{
      unique_ptr<LogicalOperator> on_predicate_oper;
      //创建过滤算子，放在当前join算子的上面
      RC RC_JOIN_ON_RC = create_plan(join_filters[join_filters.size() - on_predicate_oper_current -1], on_predicate_oper);
      if (OB_FAIL(RC_JOIN_ON_RC)) {
          LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(RC_JOIN_ON_RC));
          return RC_JOIN_ON_RC;
      }
      on_predicate_oper_current++;
      LogicalOperator* join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      if(on_predicate_oper){
         on_predicate_oper->add_child(std::move(unique_ptr<LogicalOperator>(join_oper)));
         table_oper =std::move(on_predicate_oper);
      
      }else{
        table_oper = std::move(std::move(unique_ptr<LogicalOperator>(join_oper)));
      }
    }
    }


  }
  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  /*     这一段都是新加的having过滤算子    */
  unique_ptr<LogicalOperator> having_predicate_oper;

  rc = create_plan(select_stmt->having_filter_stmt(), having_predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create having_predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (having_predicate_oper) {
    if (*last_oper) {
      having_predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &having_predicate_oper;
  }
  /*     这一段都是新加的having过滤算子    */

  unique_ptr<LogicalOperator> order_by_oper; //李晓鹏笔记 将逻辑计划加入到逻辑计划树形结构里面 在视图下面 在group by 上面
  rc = create_order_by_plan(select_stmt, order_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if(order_by_oper){
      if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &order_by_oper;
  }
  unique_ptr<LogicalOperator> limit_oper; 
  rc = create_limit_plan(select_stmt, limit_oper);
  if(limit_oper){
    if (*last_oper) {
       limit_oper->add_child(std::move(*last_oper));
    }
    last_oper = &limit_oper;
  }
  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_without_limit_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  const std::vector<Table *> &tables = select_stmt->tables();
  if(select_stmt->join_filter().size() == 0){ //这是原来的多表查询逻辑,没有使用join 这里有更好的方案
    for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }
  }else{
    int on_predicate_oper_current = 0;
    std::vector<FilterStmt*> join_filters = select_stmt->join_filter();
    for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    }else{
      unique_ptr<LogicalOperator> on_predicate_oper;
      //创建过滤算子，放在当前join算子的上面
      RC RC_JOIN_ON_RC = create_plan(join_filters[join_filters.size() - on_predicate_oper_current -1], on_predicate_oper);
      if (OB_FAIL(RC_JOIN_ON_RC)) {
          LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(RC_JOIN_ON_RC));
          return RC_JOIN_ON_RC;
      }
      on_predicate_oper_current++;
      LogicalOperator* join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      if(on_predicate_oper){
         on_predicate_oper->add_child(std::move(unique_ptr<LogicalOperator>(join_oper)));
         table_oper =std::move(on_predicate_oper);
      
      }else{
        table_oper = std::move(std::move(unique_ptr<LogicalOperator>(join_oper)));
      }
    }
    }


  }
  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  /*     这一段都是新加的having过滤算子    */
  unique_ptr<LogicalOperator> having_predicate_oper;

  rc = create_plan(select_stmt->having_filter_stmt(), having_predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create having_predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (having_predicate_oper) {
    if (*last_oper) {
      having_predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &having_predicate_oper;
  }
  /*     这一段都是新加的having过滤算子    */

  unique_ptr<LogicalOperator> order_by_oper; //李晓鹏笔记 将逻辑计划加入到逻辑计划树形结构里面 在视图下面 在group by 上面
  rc = create_order_by_plan(select_stmt, order_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if(order_by_oper){
      if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &order_by_oper;
  }
  
  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC                                  rc = RC::SUCCESS;
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  unique_ptr <Expression> left, right;  //用来存比较表达式的左表达式和右表达式

  for (FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();

    right = std::move(filter_unit->right().expr);//右边默认为表达式
    if(filter_obj_left.is_expr) //左右都为表达式的情况
    {
      left = std::move(filter_unit->left().expr);
    }
    else if(!filter_obj_left.is_expr) //左边不是表达式，右边是表达式
    {
      left = std::move(unique_ptr<Expression> (filter_obj_left.is_attr
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value))));
    }

    //比较表达式左右两边类型不一致，都不为null，都不是子查询，都不是列表表达式，要进行类型转换
    if(left->value_type() != right->value_type() && left->value_type() != AttrType::NULLS && right->value_type() != AttrType::NULLS
      && left->type() != ExprType::SUBQUERY && right->type() != ExprType::SUBQUERY
      && left->type() != ExprType::VALUE_LIST && right->type() != ExprType::VALUE_LIST)
    {
      auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
      auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
      if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
          ExprType left_type = left->type();
          auto cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
          if (left_type == ExprType::VALUE) {
            Value left_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(left_val)))
            {
              LOG_WARN("failed to get value from left child", strrc(rc));
              return rc;
            }
            left = make_unique<ValueExpr>(left_val);
          } else {
            left = std::move(cast_expr);
          }
      } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
        ExprType right_type = right->type();
        auto cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());
        if (right_type == ExprType::VALUE) {
          Value right_val;
          if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
          {
            LOG_WARN("failed to get value from right child", strrc(rc));
            return rc;
          }
          right = make_unique<ValueExpr>(right_val);
        } else {
          right = std::move(cast_expr);
        }
      } else {
        rc = RC::UNSUPPORTED;
        LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
        return rc;
      }
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  //TODO:这个阶段，外层查询正在生成逻辑计划，也就是说，子查询生成物理计划的时间比外层查询早，只是单纯不想再到物理计划生成里面再去修改一次了，后面如果有问题再调整
  //处理子查询表达式，生成子查询对应的物理计划（之后，外层查询生成物理计划的时候，就不再单独处理子查询了，因为这里已经生成了物理计划）
  for (auto &expr : cmp_exprs) {
    ComparisonExpr *cmp_expr = static_cast<ComparisonExpr *>(expr.get());
    if(cmp_expr->left()->type() == ExprType::SUBQUERY) {
      create_sub_query_physicalOperator_plan((SubqueryExpr*) cmp_expr->left().get());
    }
    if(cmp_expr->right()->type() == ExprType::SUBQUERY) {
      create_sub_query_physicalOperator_plan((SubqueryExpr*) cmp_expr->right().get());
    }
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    if(filter_stmt->conjunction_with_or == true) {
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
    else {
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

RC LogicalPlanGenerator::create_sub_query_physicalOperator_plan(SubqueryExpr* subquery_expr)
{
  RC rc = RC::SUCCESS;
  OptimizeStage optimizeStage;
  unique_ptr<PhysicalOperator> physical_operator;
  rc = optimizeStage.handle_sql_stmt(subquery_expr->select_stmt(), physical_operator);
  if(rc != RC::SUCCESS) {
    LOG_WARN("为子查询生成物理计划失败");
    return rc;
  }
  subquery_expr->set_physical_operator(physical_operator.release());
  return  rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table         *table       = update_stmt->table();
  FilterStmt    *filter_stmt  = update_stmt->filter_stmt();

  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));
  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  //处理update 中可能包含的子查询，为其创建物理计划（虽然上层查询还在创建逻辑计划，但是这里的子查询是独立的，可以直接一步到位生成物理计划）
  for(int i = 0; i < update_stmt->update_unites().size();i++) {
    UpdateUnite& update_unite = update_stmt->update_unites()[i];
    Expression* expr = update_unite.expression;
    if(expr->type() == ExprType::SUBQUERY) {
      auto sub_query_expr = static_cast<SubqueryExpr *>(expr);
      rc = create_sub_query_physicalOperator_plan(sub_query_expr);  //走完创建逻辑计划和物理计划的全过程
      if(rc != RC::SUCCESS) {
        LOG_ERROR("update-select：为子查询生成物理计划失败");
        return rc;
      }
    }
  }

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, update_stmt->update_unites()));
 
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper)); 
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
RC LogicalPlanGenerator::create_limit_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator){
  int limit_count = select_stmt->limit_count();
  if(limit_count < 0){
    logical_operator = NULL;
    return RC::SUCCESS;
  }else{
      logical_operator = make_unique<LimitLogicalOperator>(limit_count);
      return RC::SUCCESS;
  }
}
// 李晓鹏笔记 搞一个 order_by的逻辑计划 几乎照抄 group_by_plan
RC LogicalPlanGenerator::create_order_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator){
  vector<unique_ptr<Expression>> &order_by_expressions = select_stmt->order_by();
  if(order_by_expressions.empty()){
    logical_operator = NULL;
    return RC::SUCCESS;
  }
  // 这里应该先遍历一下，看看有没有未绑定的字段，如果有那么报错 不搞了
  // 如果这个物理计划需要其他的Expression 那么合并 不搞了
    auto order_by_oper = make_unique<OrderByLogicalOperator>(std::move(order_by_expressions)); //李晓鹏笔记 没有这一行 logical_operator会更新不了
    logical_operator = std::move(order_by_oper);
    return RC::SUCCESS;

}
RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>> &group_by_expressions = select_stmt->group_by();
  vector<Expression *> aggregate_expressions;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  vector<unique_ptr<Expression>> &having_expressions = select_stmt->having_expressions();

  //把having里的聚合表达式加到query_expressions里去
  // for(std::unique_ptr<Expression> &having_expression:select_stmt->having_expressions()){
  //   query_expressions.emplace_back(std::move(having_expression));
  // }
  
  function<RC(std::unique_ptr<Expression>&)> collector = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression>&)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

 bool found_unbound_column = false;
  function<RC(std::unique_ptr<Expression>&)> find_unbound_column = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    }else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };
  

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper = make_unique<GroupByLogicalOperator>(std::move(group_by_expressions),
                                                           std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CreateTableSelectStmt *create_table_select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = create_table_select_stmt->table();
  SelectStmt                 *select_stmt = create_table_select_stmt->select_stmt();


  unique_ptr<LogicalOperator> project_oper;

  // RC rc = create_plan(select_stmt, project_oper);
  RC rc = create_without_limit_plan(select_stmt, project_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> create_table_select_oper(new InsertTuplesLogicalOperator(table));

  create_table_select_oper->add_child(std::move(project_oper));

  logical_operator = std::move(create_table_select_oper);
  return rc;
}

// RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
// {
//   RC                                  rc = RC::SUCCESS;
//   std::vector<unique_ptr<Expression>> cmp_exprs;
//   const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
//   for (FilterUnit *filter_unit : filter_units) {
//     const FilterObj &filter_obj_left  = filter_unit->left();
//     const FilterObj &filter_obj_right = filter_unit->right();

//     if(filter_obj_left.is_expr || filter_obj_right.is_expr){
//       if(filter_obj_left.is_expr == false){
//         unique_ptr<Expression> left(filter_obj_left.is_attr
//                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
//                                     : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));
//         unique_ptr<Expression> right(std::move(filter_unit->right().expr));
//         if((filter_obj_left.is_attr && filter_obj_left.field.attr_type() == AttrType::DATES) ||
//           (!filter_obj_left.is_attr && filter_obj_left.value.attr_type() == AttrType::DATES)){
//           auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
//           if(right_to_left_cost < INT32_MAX ){
//             ExprType right_type = right->type();
//             auto cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());
//             if (right_type == ExprType::VALUE) {
//               Value right_val;
//               if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
//               {
//                 LOG_WARN("failed to get value from right child", strrc(rc));
//                 return rc;
//               }
//               right = make_unique<ValueExpr>(right_val);
//             } else {
//               right = std::move(cast_expr);
//             }

//           }
//         }
//         ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
//         cmp_exprs.emplace_back(cmp_expr);
//       }else if(filter_obj_right.is_expr == false){
//         unique_ptr<Expression> right(filter_obj_right.is_attr
//                                       ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
//                                       : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));
//         ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(filter_unit->left().expr), std::move(right));
//         cmp_exprs.emplace_back(cmp_expr);
//       }else{
//         ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(filter_unit->left().expr), std::move(filter_unit->right().expr));
//         cmp_exprs.emplace_back(cmp_expr);
//       }
//       //unique_ptr<Expression> left(std::move(filter_obj_left.expr));
//     }else{
//       unique_ptr<Expression> left(filter_obj_left.is_attr
//                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
//                                     : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));
//       unique_ptr<Expression> right(filter_obj_right.is_attr
//                                       ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
//                                       : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

//       if (left->value_type() != right->value_type()) {
//         auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
//         auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
//         if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
//           ExprType left_type = left->type();
//           auto cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
//           if (left_type == ExprType::VALUE) {
//             Value left_val;
//             if (OB_FAIL(rc = cast_expr->try_get_value(left_val)))
//             {
//               LOG_WARN("failed to get value from left child", strrc(rc));
//               return rc;
//             }
//             left = make_unique<ValueExpr>(left_val);
//           } else {
//             left = std::move(cast_expr);
//           }
//         } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
//           ExprType right_type = right->type();
//           auto cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());
//           if (right_type == ExprType::VALUE) {
//             Value right_val;
//             if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
//             {
//               LOG_WARN("failed to get value from right child", strrc(rc));
//               return rc;
//             }
//             right = make_unique<ValueExpr>(right_val);
//           } else {
//             right = std::move(cast_expr);
//           }

//         } else {
//           rc = RC::UNSUPPORTED;
//           LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
//           return rc;
//         }
//       }
//       ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
//       cmp_exprs.emplace_back(cmp_expr);
//     }

//   }

//   unique_ptr<PredicateLogicalOperator> predicate_oper;
//   if (!cmp_exprs.empty()) {
//     unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
//     predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
//   }

//   logical_operator = std::move(predicate_oper);
//   return rc;
// }