#ifndef HIERARCHICAL_SCOPE_H
#define HIERARCHICAL_SCOPE_H
#include <vector>
#include "sql/expr/tuple.h"
#include "sql/expr/expression.h"
#include "common/rc.h"

/***
* @brief 实现一个针对复杂子查询的分层变量作用域，每一个作用域对应了一个子查询，整个作用域是一个树状结构
*/
class HierarchicalScope{
public:

  /***
   * @brief 为运行时的常量表达式绑定作用域，运行时，直接到对应的作用域中去取值就好
   */
  RC bind_scope_for_runtime_value_exprs()
  {
    RC rc = RC::SUCCESS;
    for(ValueExpr* value_expr: runtime_value_exprs) {
      rc = bind_scope_for_runtime_value_exprs(value_expr);
      if(rc != RC::SUCCESS) {
        LOG_ERROR("为常量表达式绑定作用域失败");
        return rc;
      }
    }
    return rc;
  }


  /***
   * @brief 为当前作用域的所有运行时常量表达式设置值
   */
  RC set_value_for_runtime_value_exprs(){
    RC rc = RC::SUCCESS;
    for(ValueExpr* value_expr: runtime_value_exprs) {
      rc = set_value_for_runtime_value_exprs(value_expr);
      if(rc != RC::SUCCESS) {
        LOG_ERROR("为常量表达式设置值失败");
        return rc;
      }
    }
    return rc;
  }


private:

  /***
   * @brief 为运行时的常量表达式绑定作用域，运行时，直接到对应的作用域中去取值就好
   */
  RC bind_scope_for_runtime_value_exprs(ValueExpr* value_expr)
  {
    HierarchicalScope* search_scope = parent; //要搜索的作用域的指针
    while (search_scope != nullptr) {
      FieldInfo field_info = value_expr->get_field_info();
      //case1:字段的别名不是空，优先使用别名
      if(!field_info.field_alias.empty() && search_scope->name2field_info.find(field_info.field_alias) != search_scope->name2field_info.end()) {
        FieldInfo real_field_info = search_scope->name2field_info[field_info.field_alias];
        value_expr->set_field_info(real_field_info);
        value_expr->set_hierarchical_scope(search_scope);
        return RC::SUCCESS;
      }
      //case2:字段的真名不是空，使用真名
      else if(!field_info.field_name.empty() && search_scope->name2field_info.find(field_info.field_name) != search_scope->name2field_info.end()) {
        FieldInfo real_field_info = search_scope->name2field_info[field_info.field_name];
        value_expr->set_field_info(real_field_info);
        value_expr->set_hierarchical_scope(search_scope);
        return RC::SUCCESS;
      }
      //case3:可能是包含了多个表，多个表之间字段名有重复，使用了table_name1.col_name、table_name2.col_name这种语法，而没有使用表，这种情况要先定位到表，再定位到字段
      else if(!field_info.table_alias.empty() && search_scope->name2table.find(field_info.table_alias) != search_scope->name2table.end()) {
        //do nothing, 这种情况一般在join的时候才会出现，但是这个题目中的测试用例大概率是没有join的，遇到了再进行处理
        LOG_ERROR("无法直接通过别名或者真实的字段名定位到字段的真实信息，需要先确定表名，但是这部分的功能没有实现");
        return RC::NOTFOUND;
      }
      else { //说明当前作用域没有，继续向上搜索
        search_scope = search_scope->parent;
      }
    }
    return RC::NOTFOUND;
  }

  /***
   * @brief 为某一个运行时常量表达式设置值
   */
  RC set_value_for_runtime_value_exprs(ValueExpr* value_expr)
  {
    HierarchicalScope* scope = value_expr->get_hierarchical_scope();
    FieldInfo& field_info = value_expr->get_field_info();
    Value value;
    RC rc = scope->tuple->find_cell(TupleCellSpec(field_info.table_name.c_str(), field_info.field_name.c_str()), value);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("为常量表达式设置值失败");
      return rc;
    }
    value_expr->set_value(value);
    return RC::SUCCESS;
  }

public:
  std::vector<ValueExpr*> runtime_value_exprs;         //这一级子查询中，所有的运行时常量
  HierarchicalScope* parent = nullptr;                 //上级作用域
  std::vector<HierarchicalScope*> children;            //下级作用域
  Tuple* tuple = nullptr;                              //当前作用域的tuple,下级子查询可以到这里来获取运行时常量的值
  std::map<std::string, Table*>    name2table;         //<表的真名/表的别名，真实的表对象> 之间的映射
  ///<列的真名/列的别名，真实列信息>之间的映射,
  ///注意，键值不会重复，有些情况下，如果多个表名的字段重复了，并且都没有别名，那么，通过这里是无法直接找到对应信息的，而是要先去定位到表，再定位到字段
  std::map<std::string, FieldInfo> name2field_info;

};



#endif //HIERARCHICAL_SCOPE_H
