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
// Created by Longda on 2021/5/2.
//

#pragma once

/**
 * @brief 这个文件定义函数返回码/错误码(Return Code)
 * @enum RC
 */

#define DEFINE_RCS                       \
  DEFINE_RC(SUCCESS)                     \
  DEFINE_RC(INVALID_ARGUMENT)            \
  DEFINE_RC(UNIMPLEMENTED)               \
  DEFINE_RC(SQL_SYNTAX)                  \
  DEFINE_RC(INTERNAL)                    \
  DEFINE_RC(NOMEM)                       \
  DEFINE_RC(NOTFOUND)                    \
  DEFINE_RC(EMPTY)                       \
  DEFINE_RC(FULL)                        \
  DEFINE_RC(EXIST)                       \
  DEFINE_RC(NOT_EXIST)                   \
  DEFINE_RC(BUFFERPOOL_OPEN)             \
  DEFINE_RC(BUFFERPOOL_NOBUF)            \
  DEFINE_RC(BUFFERPOOL_INVALID_PAGE_NUM) \
  DEFINE_RC(RECORD_OPENNED)              \
  DEFINE_RC(RECORD_INVALID_RID)          \
  DEFINE_RC(RECORD_INVALID_KEY)          \
  DEFINE_RC(RECORD_DUPLICATE_KEY)        \
  DEFINE_RC(RECORD_NOMEM)                \
  DEFINE_RC(RECORD_EOF)                  \
  DEFINE_RC(RECORD_NOT_EXIST)            \
  DEFINE_RC(RECORD_INVISIBLE)            \
  DEFINE_RC(SCHEMA_DB_EXIST)             \
  DEFINE_RC(SCHEMA_DB_NOT_EXIST)         \
  DEFINE_RC(SCHEMA_DB_NOT_OPENED)        \
  DEFINE_RC(SCHEMA_TABLE_NOT_EXIST)      \
  DEFINE_RC(SCHEMA_TABLE_EXIST)          \
  DEFINE_RC(SCHEMA_FIELD_NOT_EXIST)      \
  DEFINE_RC(SCHEMA_FIELD_MISSING)        \
  DEFINE_RC(SCHEMA_FIELD_TYPE_MISMATCH)  \
  DEFINE_RC(SCHEMA_INDEX_NAME_REPEAT)    \
  DEFINE_RC(IOERR_READ)                  \
  DEFINE_RC(IOERR_WRITE)                 \
  DEFINE_RC(IOERR_ACCESS)                \
  DEFINE_RC(IOERR_OPEN)                  \
  DEFINE_RC(IOERR_CLOSE)                 \
  DEFINE_RC(IOERR_SEEK)                  \
  DEFINE_RC(IOERR_TOO_LONG)              \
  DEFINE_RC(IOERR_SYNC)                  \
  DEFINE_RC(LOCKED_UNLOCK)               \
  DEFINE_RC(LOCKED_NEED_WAIT)            \
  DEFINE_RC(LOCKED_CONCURRENCY_CONFLICT) \
  DEFINE_RC(FILE_EXIST)                  \
  DEFINE_RC(FILE_NOT_EXIST)              \
  DEFINE_RC(FILE_NAME)                   \
  DEFINE_RC(FILE_BOUND)                  \
  DEFINE_RC(FILE_CREATE)                 \
  DEFINE_RC(FILE_OPEN)                   \
  DEFINE_RC(FILE_NOT_OPENED)             \
  DEFINE_RC(FILE_CLOSE)                  \
  DEFINE_RC(FILE_REMOVE)                 \
  DEFINE_RC(VARIABLE_NOT_EXISTS)         \
  DEFINE_RC(VARIABLE_NOT_VALID)          \
  DEFINE_RC(LOGBUF_FULL)                 \
  DEFINE_RC(LOG_FILE_FULL)               \
  DEFINE_RC(LOG_ENTRY_INVALID)           \
  DEFINE_RC(DIVIDE_ZERO)                 \
  DEFINE_RC(FIELD_CAN_NOT_BE_NULL)       \
  DEFINE_RC(UNIQUE_FAILD)                \
  DEFINE_RC(ILLEGAL_SUB_QUERY)           \
  DEFINE_RC(ILLEGAL_SUB_QUERY_zero_record) \
  DEFINE_RC(ILLEGAL_SUB_QUERY_multiple_record) \
  DEFINE_RC(WRONG_ATTR)                 \
  DEFINE_RC(UNSUPPORTED)                \
  DEFINE_RC(SCHEMA_VIEW_EXIST)          \
  DEFINE_RC(SCHEMA_VIEW_NOT_EXIST) 

enum class RC
{
#define DEFINE_RC(name) name,
  DEFINE_RCS
#undef DEFINE_RC
};

extern const char *strrc(RC rc);

extern bool OB_SUCC(RC rc);
extern bool OB_FAIL(RC rc);

/***
 * @brief 判断错误码中是否是表示某一种自定义的子查询异常
 */
extern bool OB_ILLEGAL_SUB_QUERY(RC rc);
