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

RC VectorIndexPhysicalOperator::sorteTuples(){
  auto comparator = [this](const Tuple* a, const Tuple* b) {  
    Value aValue ;
    Value bValue ;
    TupleCellSpec * spec = new TupleCellSpec(table_->name(), field_name_.c_str());
    a->find_cell(*spec, aValue);
    b->find_cell(*spec, bValue);
    const vector<float> aVector = aValue.get_vector();
    const vector<float> bVector = bValue.get_vector();
    float af = index_->get_instance(aVector,base_vector_);
    float bf = index_->get_instance(bVector,base_vector_);
    if(af <= bf ){
      return true;
    }else{
      return false ;
    }
  };
  std::sort(tuples_->begin(), tuples_->end(), comparator);
  return RC::SUCCESS;
}






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

VectorIndexPhysicalOperator::VectorIndexPhysicalOperator(Table *table,IvfflatIndex*index,
                     int limit,vector<float> base_vector,string field_name){
   table_ = table;
   index_=index;
   limit_=limit;
   base_vector_=base_vector;
   field_name_ = field_name;
}
std::string VectorIndexPhysicalOperator::param() const {
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
RC VectorIndexPhysicalOperator::open(Trx *trx)
{
  records_ = table_->ann_search(base_vector_,limit_,index_);
  for(size_t i = 0 ;i < records_->size(); i++){
   Record* record = records_->at(i);
   Tuple* tuple  = get_data_from_record(table_,record);
   tuples_->push_back(tuple);
  }
  sorteTuples();
  delete records_;
  return RC::SUCCESS;
}

RC VectorIndexPhysicalOperator::next()
{
  if(count < limit_ && (size_t)count < tuples_->size()){
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
  Tuple* tuple = (*tuples_)[count];
  count++;
  return tuple;
  
}



