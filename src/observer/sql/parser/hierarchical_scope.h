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
   * @brief 根据select_stmt中的信息，为关联子查询创建作用域
   * @param select_sql_node 经过parse阶段得到的最外层查询的select_sql_node
   * @param select_stmt 经过resolve阶段得到的最外层查询的SelectStmt
   */
  static RC create_hierarchical_scope_by_select_stmt(SelectSqlNode* select_sql_node,SelectStmt* select_stmt)
  {
    return RC::SUCCESS;
  }

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
      //case2: 字段对应的表名不是空，优先使用表名，因为这里的表名可能实际上是上层查询为表设置的别名，而这个表在多个层次的查询中都被使用了
      else if(!field_info.table_name.empty() && search_scope->name2table.find(field_info.table_name) != search_scope->name2table.end()) {
        Table* table = search_scope->name2table[field_info.table_name];
        const FieldMeta* field_meta = table->table_meta().field(field_info.field_name.c_str());
        if(field_meta != nullptr) {
          FieldInfo real_field_info;
          real_field_info.table_name = table->name();
          real_field_info.field_name = field_meta->name();
          real_field_info.attr_type = field_meta->type();
          value_expr->set_field_info(real_field_info);
          value_expr->set_hierarchical_scope(search_scope);
          return RC::SUCCESS;
        }
      }
      //case3:表名是空，但是字段的真名不是空，使用真名，在表中挨个去查找
      else if(field_info.table_name.empty() &&!field_info.field_name.empty()) {
        for(auto pair : search_scope->name2table) {
          Table* table = pair.second;
          const FieldMeta* field_meta = table->table_meta().field(field_info.field_name.c_str());
          if(field_meta != nullptr) {
            FieldInfo real_field_info;
            real_field_info.table_name = table->name();
            real_field_info.field_name = field_meta->name();
            real_field_info.attr_type = field_meta->type();
            value_expr->set_field_info(real_field_info);
            value_expr->set_hierarchical_scope(search_scope);
            return RC::SUCCESS;
          }
        }
      }
      else { //说明当前作用域没有，继续向上搜索
        search_scope = search_scope->parent;
      }
    }
    return RC::NOTFOUND;  //搜索到最后也没有找到
  }

  /***
   * @brief 为某一个运行时常量表达式设置值
   */
  RC set_value_for_runtime_value_exprs(const ValueExpr* value_expr)
  {
    const HierarchicalScope* scope = value_expr->get_hierarchical_scope();
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
  ///<列的别名，真实列信息>之间的映射,方便通过别名可以定位到对应的字段，正常的无别名字段，肯定是唯一的，直接去表中挨个查找即可
  std::map<std::string, FieldInfo> name2field_info;

};



#endif //HIERARCHICAL_SCOPE_H
