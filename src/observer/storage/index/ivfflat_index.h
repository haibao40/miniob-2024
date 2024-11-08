/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "storage/index/index.h"
#include "common/rc.h"
#include "storage/record/record_manager.h"
#include <cmath>
//#include <map.h>
/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */




class IvfflatIndex : public Index
{
public:
  IvfflatIndex(){};
  virtual ~IvfflatIndex() noexcept {};
  float l2_distance(const std::vector<float>& left_vector, const std::vector<float>& right_vector)
{
    float sum = 0.0;
    for (size_t i = 0; i < left_vector.size(); ++i) {
        float diff = left_vector[i] - right_vector[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

  float cosine_distance(const std::vector<float>& left_vector, const std::vector<float>& right_vector)
{
    float dot_product = 0;
    float norm_left = 0;
    float norm_right = 0;

    for (size_t i = 0; i < left_vector.size(); ++i) {
        dot_product += left_vector[i] * right_vector[i];
        norm_left += left_vector[i] * left_vector[i];
        norm_right += right_vector[i] * right_vector[i];
    }

    norm_left = std::sqrt(norm_left);
    norm_right = std::sqrt(norm_right);

    if (norm_left == 0.0 || norm_right == 0.0) {
      return 1.0;  // 如果任一向量的范数为0，余弦距离为1
    }

    float cosine_similarity = dot_product / (norm_left * norm_right);
    return 1.0f - cosine_similarity;
}

  float inner_product(const std::vector<float> &left_vector, const std::vector<float> &right_vector)
{
  float result = 0.0f;
  for (size_t i = 0; i < left_vector.size(); ++i) {
    result += left_vector[i] * right_vector[i];
  }
  return result;
}
  float get_instance(const std::vector<float> &left_vector, const std::vector<float> &right_vector){
   if(distance_type_ == 1){
      return l2_distance(left_vector,right_vector);
   }else if(distance_type_ == 2){
     return cosine_distance(left_vector,right_vector);
   }else{
     return inner_product(left_vector,right_vector);
   }
 }
  //RC open(Table *table, const char *file_name, const IndexMeta &index_meta, vector<const FieldMeta*>* &field_metas);
  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, vector<const FieldMeta*>* &field_meta);
  RC Cluster();
  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
  {
    return RC::SUCCESS;
  };
  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
  {

    return RC::SUCCESS;
  };
  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, vector<const FieldMeta*>* &field_metas){
  index_meta_ = index_meta;
  field_meta_ = *((*field_metas)[0]);
  table_ = table;
  RC rc = RC::SUCCESS;
  return rc;
  }
  bool is_vector_index() override { return true; }
  vector<RID> ann_search(const vector<float> &base_vector, size_t limit);
  
  RC close() { return RC::UNIMPLEMENTED; }

  RC insert_entry(const char *record, const RID *rid) override ;
  RC delete_entry(const char *record, const RID *rid) override ;
  RC sync() override { return RC::UNIMPLEMENTED; };
  RC set_data(std::vector<Record *>* records);
  int lists(){return lists_;}
  int probes(){return probes_;}
  int distance_type(){return distance_type_;}
  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override{return NULL;}
  RC destroy()override {return RC::SUCCESS;}
  RC init(int list,int distance_type,int probes){
    lists_ = list;
    probes_ = probes;
    distance_type_ = distance_type;
    return RC::SUCCESS;
  }

  map<std::vector<float>, std::vector<RID>>* kmeans(const std::vector<std::vector<float>>& data
                                                                ,int k,vector<RID>* rids) ;
  std::vector<float> mean_of_vectors(const std::vector<std::vector<float>>& vectors);
  RC init_cluster();
private:
  bool   inited_ = false;
  Table *table_  = nullptr;
  int    lists_  = 1;
  int    probes_ = 1;
  int    distance_type_ = 0;
  // IndexMeta index_meta_;
  // FieldMeta field_meta_;
  map<std::vector<float>, std::vector<RID>>* kmeans_ = new map<std::vector<float>, std::vector<RID>>(); //聚类的结果
  std::vector<Record *>* records_ = new std::vector<Record *>();
  vector<RID>* rids_ = new vector<RID>();
  //RecordFileScanner scanner_;
  int count_vector_;
  int num_of_dimensions_; //操作的次数
  vector<vector<float>>* data_ = new vector<vector<float>>();
};
