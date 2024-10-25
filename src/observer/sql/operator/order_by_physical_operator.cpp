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
// Created by WangYunlai on 2024/06/11.
//
#include <algorithm>

#include "common/log/log.h"
#include "sql/operator/order_by_physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include "sql/expr/composite_tuple.h"
#include "sql/expr/expression.h"
#include "sql/expr/expression.cpp"
using namespace std;
using namespace common;
RC OrderByPhysicalOperator::sorteTuples(){

        auto comparator = [this](const Tuple* a, const Tuple* b) {  
           int result = 0;
           for (size_t i = 0; i < sorted_columns->size(); ++i) {  
              //李晓鹏 根据 列的信息 获取cell的值
               bool isAscending = (*sorted_is_asc)[i];
               TupleCellSpec* cellSpec = (*sorted_columns)[i]; 
               Value aValue ;
               Value bValue ;
               a->find_cell(*cellSpec, aValue);
               b->find_cell(*cellSpec, bValue);
               if(aValue.attr_type() == AttrType::NULLS || aValue.attr_type() == AttrType::NULLS ){
                  if(aValue.attr_type() == AttrType::NULLS && bValue.attr_type() == AttrType::NULLS){
                    result = 0;
                  }else{
                    if(aValue.attr_type() == AttrType::NULLS){ 
                        result = -1;
                    }else{
                       result = 1 ;
                    }
                  }
               }else{
                  result = aValue.compare(bValue);             
               }
               if(isAscending == false){
                result = -result;
               }
               if(result != 0){break;}
           }
           if(result<0){
            return true ;
           }else{return false;}
           
        };  
  
        std::sort(tuple_sorted->begin(), tuple_sorted->end(), comparator);  
        return RC::SUCCESS;
}
OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<unique_ptr<Expression>> &&order_by_exprs)
{
  order_expressions_  = std::move(order_by_exprs);
}
RC OrderByPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}
RC OrderByPhysicalOperator::get_all_tuple(){
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple* tuple_arr = oper->current_tuple();
    if(tuple_arr == nullptr){
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }
    ValueListTuple* v = new ValueListTuple();
    ValueListTuple::make(*tuple_arr,*v);
    tuple_sorted->push_back(v); //李晓鹏参数 std::move(tuple)  ,tuple 会让vector变成同一个元素
    size = size + 1 ;
  }
  return rc;
}
RC OrderByPhysicalOperator::sorted(){
  get_all_tuple();

  set_sorted_columns();
  sorteTuples();
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
  if(is_sorted == false)
  {
    is_sorted = true;
    sorted();
  }
  //
  if(size<=index_current){
    return RC::RECORD_EOF;
  }else{
    return RC::SUCCESS;
  }
}

RC OrderByPhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() {
  Tuple* tuple = (*tuple_sorted)[index_current];
  index_current = index_current + 1 ;
  return tuple;
}

RC OrderByPhysicalOperator::set_sorted_columns(){
   for (auto it = order_expressions_.rbegin(); it != order_expressions_.rend(); ++it) {
      ORderedFieldExpr* orderedFieldExpr = dynamic_cast<ORderedFieldExpr*>(it->get());
      if (orderedFieldExpr) { 
        TupleCellSpec * spec = new TupleCellSpec(orderedFieldExpr->table_name(), orderedFieldExpr->field_name());
        sorted_is_asc->push_back(orderedFieldExpr->get_asc());
        sorted_columns->push_back(spec);
      }
    }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  return children_[0]->tuple_schema(schema);
}