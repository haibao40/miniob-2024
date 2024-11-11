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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include "common/value.h"
#include "common/rc.h"
#include <iostream>

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;

protected:
  Value value_;
};

class SumAggregator : public Aggregator //官方提供了sum的聚合算子,其余的都是仿写，具体进cpp文件查看
{
public:
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
};

class MaxAggregator : public Aggregator{ 
  public:
    RC accumulate(const Value &value) override;
    RC evaluate(Value &result) override;
};

class MinAggregator : public Aggregator{
  public:
    RC accumulate(const Value &value) override;
    RC evaluate(Value &result) override;
};

class AvgAggregator : public Aggregator{
  public:
    RC accumulate(const Value &value) override;
    RC evaluate(Value &result) override;
    void add_len() { len_++; }
  private:
    int len_=1;
};

class CountAggregator : public Aggregator{
  public:
    CountAggregator() = default;
    CountAggregator(bool flag){
      if(flag){
        set_count1();
      }
    }
    bool count_1 = false;
    void set_count1();
    RC accumulate(const Value &value) override;
    RC evaluate(Value &result) override;
};