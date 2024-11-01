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
// Created by Wangyunlai on 2023/06/25.
//

#pragma once

#include "net/communicator.h"
#include "common/lang/vector.h"

class SqlResult;
class TupleSchema;
/**
 * @brief 与客户端进行通讯
 * @ingroup Communicator
 * @details 使用简单的文本通讯协议，每个消息使用'\0'结尾
 */
class PlainCommunicator : public Communicator
{
public:
  PlainCommunicator();
  virtual ~PlainCommunicator() = default;

  RC read_event(SessionEvent *&event) override;
  RC write_result(SessionEvent *event, bool &need_disconnect) override;

private:
  RC write_state(SessionEvent *event, bool &need_disconnect);
  RC write_debug(SessionEvent *event, bool &need_disconnect);
  RC write_result_internal(SessionEvent *event, bool &need_disconnect);
  RC write_tuple_result(SqlResult *sql_result);
  RC write_chunk_result(SqlResult *sql_result);

  /***
   * @brief 发送查询结果的字段名，即查询结果的表头，原本这段代码不是一个单独的函数，但是我为了更改这部分的逻辑，将这个函数单独提取了出来
   *
   */
  RC write_result_field_header(SqlResult *sql_result);

protected:
  vector<char> send_message_delimiter_;  ///< 发送消息分隔符
  vector<char> debug_message_prefix_;    ///< 调试信息前缀
};
