#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "storage/db/db.h"
#include "storage/trx/trx.h"

class Db;
class Trx;
class SelectStmt;
class SubqueryExpr;
/****
* @brief 全局变量
*/
class GlobalVariable{
public:
  //方便在任何地方都能拿到数据库对象
  static Db* db;
  //方便在任何地方都能拿到当前的事务对象，尤其是在执行子查询的时候
  static Trx *trx;
  //当前resolve阶段正在创建的select_stmt，方便在resolve阶段可以在任何地方获取到当前的select_stmt
  static SelectStmt* curren_resolve_select_stmt;
  //当前resolve阶段正在创建的SubqueryExpr，方便在resolve阶段可以在任何地方获取到当前的SubqueryExpr
  static SubqueryExpr* curren_resolve_subquery_expr;

};

#endif //GLOBAL_VARIABLE_H
