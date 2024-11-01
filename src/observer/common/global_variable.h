#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "storage/db/db.h"
#include "storage/trx/trx.h"

class Db;
class Trx;
/****
* @brief 全局变量
*/
class GlobalVariable{
public:
  //方便在任何地方都能拿到数据库对象
  static Db* db;
  //方便在任何地方都能拿到当前的事务对象，尤其是在执行子查询的时候
  static Trx *trx;
};

#endif //GLOBAL_VARIABLE_H
