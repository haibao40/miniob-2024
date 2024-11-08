/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */


#include "storage/index/index.h"
#include "storage/index/ivfflat_index.h"
#include "common/rc.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse.h"
#include "common/value.h"
#include "storage/record/record.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include <limits>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
struct KeyDifference {
    vector<float> key;
    float difference;
};
bool compareByDifference(const KeyDifference& a, const KeyDifference& b) {
    return a.difference < b.difference;
}

vector<RID> IvfflatIndex::ann_search(const vector<float> &base_vector, size_t limit) { 
    std::vector<KeyDifference>* differences = new std::vector<KeyDifference>() ;
    for (const auto& pair : *kmeans_) {
        float diff = get_instance(base_vector, pair.first);
        differences->push_back({pair.first, diff});
    }
    vector<RID>* temp = new vector<RID>();
    vector<RID>* result = new vector<RID>();
    std::sort(differences->begin(), differences->end(), compareByDifference);
        for (const auto& diff : *differences) {
          const auto& key = diff.key;
          const auto& values = kmeans_->at(key);
          for (RID value : values) {
            temp->push_back(value);
          }
          if(temp->size() >= limit){
            break;
          }
    }
    for (int i = 0; i < temp->size() && i <= limit; i++) {
      result->push_back(temp->at(i));
    }
    delete temp ;
    return *result;
}


static vector<float> get_data_from_record(Table* table,char* record_data,  const char* field_name)
  {
    //RC rc = RC::SUCCESS;
    Record record;
    record.set_data(record_data, table->table_meta().record_size());
    RowTuple row_tuple;
    row_tuple.set_schema(table, table->table_meta().field_metas());
    row_tuple.set_record(&record);
    
    TupleCellSpec spec(table->table_meta().name(), field_name);
    Value value;
    row_tuple.find_cell(spec, value);
    return value.get_vector();
  }


 RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta, vector<const FieldMeta*>* &field_meta){
  index_meta_ = index_meta;
  field_meta_ = *((*field_meta)[0]);
  table_ = table;
  RC rc = RC::SUCCESS;
  return rc;
 }


 
 RC IvfflatIndex::Cluster(){
  kmeans_->clear();
  kmeans_ = kmeans(*data_,lists_,rids_);
  return RC::SUCCESS;
  }

std::vector<float> IvfflatIndex::mean_of_vectors(const std::vector<std::vector<float>>& vectors){
    if (vectors.empty()) return {};
    std::vector<float> mean(vectors[0].size(), 0.0f);
    for (const auto& vec : vectors) {
        for (size_t i = 0; i < vec.size(); ++i) {
            mean[i] += vec[i];
        }
    }
    for (auto& val : mean) {
        val /= static_cast<float>(vectors.size());
    }
    return mean;
   }
  std::map<std::vector<float>, std::vector<RID>>* IvfflatIndex::kmeans(const std::vector<std::vector<float>>& data
  , int k,vector<RID>* rids ) {
      // 初始化随机种子
        std::srand(std::time(0));
        if(data.size() == 0){
            return new std::map<std::vector<float>, std::vector<RID>>();
        } 
        if(k > data.size()){
            k = data.size();
        }

        // 随机选择k个质心
        std::vector<std::vector<float>> centroids(k);
        for (int i = 0; i < k; ++i) {
            centroids[i] = data[rand() % data.size()];
        }

        bool centroids_changed = true;
        int iteration = 0;
       std::map<std::vector<float>, std::vector<std::pair<std::vector<float>, RID>>> clusters;
        while (centroids_changed && iteration < 150) {
            centroids_changed = false;
            

            // 分配数据点到最近的质心
            for (size_t i = 0; i < data.size(); ++i) {
                float min_dist = std::numeric_limits<float>::max();
                std::vector<float> closest_centroid;
                for (const auto& centroid : centroids) {
                    float dist = get_instance(data[i], centroid);
                    if (dist < min_dist) {
                        min_dist = dist;
                        closest_centroid = centroid;
                    }
                }
                clusters[closest_centroid].emplace_back(data[i], (*rids)[i]);
            }

            // 更新质心
            std::vector<std::vector<float>> new_centroids;
            for (const auto& cluster : clusters) {
                std::vector<std::vector<float>> points;
                for (const auto& pair : cluster.second) {
                    points.push_back(pair.first);
                }
                new_centroids.push_back(mean_of_vectors(points));
            }
            //new_centroids.resize(k);

            // 检查质心是否发生变化
            for (int i = 0; i < k; ++i) {
                if (get_instance(centroids[i], new_centroids[i]) > 0.001) { // 设置阈值以判断质心是否改变
                    centroids_changed = true;
                    centroids[i] = new_centroids[i];
                }
            }

            iteration++;
        }

        // 构建返回值
        std::map<std::vector<float>, std::vector<RID>>* result = new std::map<std::vector<float>, std::vector<RID>>();

        for (const auto& cluster : clusters) {
            std::vector<RID> rids;
            for (const auto& pair : cluster.second) {
                rids.push_back(pair.second);
            }
            (*result)[cluster.first] = rids;
        }

        return result;
    }


RC IvfflatIndex::insert_entry(const char *record, const RID *rid){
    data_->push_back(get_data_from_record(table_,const_cast<char*>(record),field_meta_.name()));
    rids_->push_back(*rid);
    Cluster();
    return RC::SUCCESS;
}
RC IvfflatIndex::delete_entry(const char *record, const RID *rid){

    auto it = std::find(rids_->begin(), rids_->end(),*rid);
    if (it != rids_->end()) {
        rids_->erase(it);
    }
    auto it2 = std::find(data_->begin(), data_->end(),get_data_from_record(table_,const_cast<char*>(record),field_meta_.name()));
    if(it2 != data_->end()){
        data_->erase(it2);
    }
    Cluster();
    return RC::SUCCESS;
}


  RC IvfflatIndex::set_data(std::vector<Record *>* records){
    records_ = records;
    vector<vector<float>>* data = new vector<vector<float>>();
    vector<RID>* rids = new vector<RID>();
    for(size_t i = 0;i<records_->size();i++){
        rids->push_back((*records_)[i]->rid());
        vector<float> p = get_data_from_record(table_,(*records_)[i]->data(),field_meta_.name());
        data->push_back(std::move(p));
    }
    rids_ = rids;
    data_ = data;
    count_vector_ = data->size();
    return RC::SUCCESS;
  }