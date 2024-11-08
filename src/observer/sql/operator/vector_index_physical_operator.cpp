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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/vector_index_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"

using namespace std;
static RowTuple* get_data_from_record(Table* table,Record* record)
  {
    //RC rc = RC::SUCCESS;
    //Record record;
    //record.set_data(record_data, table->table_meta().record_size());
    RowTuple* row_tuple = new RowTuple();
    row_tuple->set_schema(table, table->table_meta().field_metas());
    row_tuple->set_record(record);
    
    return row_tuple;
  }


VectorIndexPhysicalOperator::VectorIndexPhysicalOperator(Table *table,IvfflatIndex*index,int limit,vector<float> base_vector){
   table_ = table;
   index_=index;
   limit_=limit;
   base_vector_=base_vector;
}
std::string VectorIndexPhysicalOperator::param() const {
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
RC VectorIndexPhysicalOperator::open(Trx *trx)
{
  records_ = table_->ann_search(base_vector_,limit_,index_);
  return RC::SUCCESS;
}

RC VectorIndexPhysicalOperator::next()
{
  if(count < records_->size()){
    return RC::SUCCESS;
  }else{
    return RC::RECORD_EOF;
  }
}

RC VectorIndexPhysicalOperator::close() { 
  return RC::SUCCESS;
}

Tuple *VectorIndexPhysicalOperator::current_tuple()
{
  Record* record = records_->at(count);
  Tuple* tuple  = get_data_from_record(table_,record);
  //cout<<tuple->to_string();
  count++;
  return tuple;
}



