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
// Created by Wangyunlai on 2022/12/15
//

#include "sql/operator/vector_index_logical_operator.h"

VectorIndexLogicalOperator::VectorIndexLogicalOperator(Table *table, ReadWriteMode mode)
    : table_(table), mode_(mode)
{}

VectorIndexLogicalOperator::VectorIndexLogicalOperator(Table *table, ReadWriteMode mode,int limit,std::vector<std::unique_ptr<Expression>>& expressions){
  table_=table;
   mode_=mode;
   limit_=limit;
   if(expressions.size()!=0){
   Expression* exp = expressions[0].get();
   if(exp->type()!=ExprType::VECTOR_FUNCTION){
      limit_ = -1;
   }else{
       VectorFunctionExpr* vexp = static_cast<VectorFunctionExpr*>(exp);
       Expression* left = vexp->left().get();
       Expression* right = vexp->right().get();
       distance_type_ = ((int)(vexp->vector_function_type()) + 1);
       if(left->type()==ExprType::FIELD && right->type()==ExprType::VALUE){
            FieldExpr* field_temp = static_cast<FieldExpr*>(left);
            ValueExpr* value_temp = static_cast<ValueExpr*>(right);
            index_name_p_ = field_temp->field_name();
            Value value_ ;
            value_temp->get_value(value_);
            Value value_vector ;
            value_.cast_to(value_,AttrType::VECTORS,value_vector);
            base_vector_ = value_vector.get_vector();
       }else if(left->type()==ExprType::VALUE && right->type()==ExprType::FIELD){
            FieldExpr* field_temp = static_cast<FieldExpr*>(right);
            ValueExpr* value_temp = static_cast<ValueExpr*>(left);
            index_name_p_ = field_temp->field_name();
            Value value_ ;
            value_temp->get_value(value_);
            Value value_vector ;
            value_.cast_to(value_,AttrType::VECTORS,value_vector);
            base_vector_ = value_vector.get_vector();
       }else{
        distance_type_ = -1 ;
        limit_ = -1 ;
       }
   }
   for(int i =0 ;i <table_->table_meta().index_num();i++){
      const IndexMeta* index_meta = table_->table_meta().index(i);
      if(index_meta->distance_type() == distance_type_){
        const std::vector<FieldMeta>*  fieldMetas = index_meta->fields();
        FieldMeta field_meta = (*fieldMetas)[0];
        if(field_meta.name() == index_name_p_ && limit_ >0){
            Index* temp = table_->find_index(index_meta->name());
            if(temp->is_vector_index() == true){
                index_ = static_cast<IvfflatIndex*>(temp);
            }
        }
      }
   }
   }
}

