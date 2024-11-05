#include "common/global_variable.h"


Db* GlobalVariable::db = nullptr;
Trx* GlobalVariable::trx = nullptr;
SelectStmt* GlobalVariable::curren_resolve_select_stmt = nullptr;
SubqueryExpr* GlobalVariable::curren_resolve_subquery_expr = nullptr;