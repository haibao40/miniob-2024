
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <unordered_map>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  Value value(0);
  ValueExpr *zero = new ValueExpr(value);
  ArithmeticExpr *expr = type == ArithmeticExpr::Type::NEGATIVE ? new ArithmeticExpr(ArithmeticExpr::Type::SUB, zero, left) : new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

ArithmeticExpr *create_arithmetic_expression_with_alias(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             char* alias)
{
  Value value(0);
  ValueExpr *zero = new ValueExpr(value);
  ArithmeticExpr *expr = type == ArithmeticExpr::Type::NEGATIVE ? new ArithmeticExpr(ArithmeticExpr::Type::SUB, zero, left) : new ArithmeticExpr(type, left, right);
  expr->set_name(alias);
  return expr;
}

VectorFunctionExpr *create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  VectorFunctionExpr *expr = new VectorFunctionExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression_with_alias(const char *aggregate_name,
                                           Expression *child,
                                           char *alias)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(alias);
  return expr;
}

std::vector<std::vector<ConditionSqlNode>*>  join_conditions;


%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        GROUP
        BY
        CREATE
        DROP
        ORDER
        TABLE
        TABLES
        VIEW
        VIEWS
        INDEX
        CALC
        SELECT
        DESC
        ASC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        VECTOR_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        LT
        GT
        LE
        GE
        NE
        NOT
        LIKE
        IS_     //后面加上_,用以区分枚举值IS
        NULL_T
        MAX
        MIN
        AVG
        SUM
        COUNT
        HAVING
        INNER
        JOIN
        AS
        UNIQUE // 唯一索引
        WITH
        DISTANCE
        TYPE
        LISTS
        PROBES
        LIMIT
        LEFT_BRACKET     //左方括号[,用于支持使用列表表示向量
        RIGHT_BRACKET    //右方括号],用于支持使用列表表示向量
        L2_DISTANCE      //向量函数L2_DISTANCE
        COSINE_DISTANCE  //向量函数COSINE_DISTANCE
        INNER_PRODUCT    //向量函数INNER_PRODUCT
        IN_T
        EXISTS_T



/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  std::vector<std::string> *                 attr_names;
  AttrInfoSqlNode *                          attr_info;
  std::vector<ViewAttrInfoSqlNode> *         view_attr_infos;
  ViewAttrInfoSqlNode *                      view_attr_info;
  UpdateUnite *                              update_unite;
  std::vector<UpdateUnite> *                 update_unite_list;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::unordered_map<std::string, std::string> *       relation_list;
  std::unordered_map<std::string, std::string> *       join_list;
  std::vector<float> *                       float_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       bools;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <number>              not_null
%type <number>              limit_
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <string>              relation
%type <number>              distance_type
%type <join_list>           join_in
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_names>          attr_name_list
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <update_unite>        update_unite
%type <update_unite_list>   update_unite_list
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <float_list>          float_list
%type <string>              storage_format
%type <relation_list>       rel_list
%type <join_list>           join_in_right_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <condition_list>      having
%type <expression_list>     order_by
%type <expression>          order_by_field
%type <expression_list>     order_by_field_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            create_view_stmt
%type <sql_node>            create_table_select_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            drop_view_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            create_index_vector_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands
%type <bools>               index_type
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | create_view_stmt
  | drop_table_stmt
  | drop_view_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | create_index_vector_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
  | create_table_select_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;
// 标记是否为唯一索引
index_type:
  {
      $$ = false;
  }| UNIQUE{
      $$ = true;
  }
  ;
create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      for (const auto& pair : *$8) {
         create_index.attribute_names.push_back(pair.first);
      }
      create_index.unique = $2;
      free($4);
      free($6);
      //free($2);
      delete($8);
    }
    ;
distance_type:
   L2_DISTANCE {
       $$  = 1;
   }|
   COSINE_DISTANCE{
      $$  =  2;
   }
   |INNER_PRODUCT{
      $$  =  3;
   }
   ;
create_index_vector_stmt:
  CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE  WITH LBRACE TYPE EQ ID COMMA DISTANCE EQ distance_type COMMA LISTS EQ NUMBER COMMA PROBES EQ NUMBER RBRACE
  {
     $$ = new ParsedSqlNode(SCF_CREATE_VECTOR_INDEX);
     CreateVectorIndexSqlNode &create_index = $$->create_vector_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      for (const auto& pair : *$8) {
         create_index.attribute_names.push_back(pair.first);
      }
      create_index.lists = $22;
      create_index.probes = $26;
      create_index.distance_type = $18;
  }
  ;




drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE not_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      if($$->type == AttrType::VECTORS){$$->set_vector_type_length($4);}
      $6 == 1 ? $$->not_null = true : $$->not_null = false;
      free($1);
    }
    | ID type not_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if($$->type == AttrType::TEXTS){
        $$->length = 65535;
      }else{
        $$->length = 4;
      }
      $3 == 1 ? $$->not_null = true : $$->not_null = false;
      free($1);
    }
    ;
not_null:
    /* empty */
    {$$ = 0;}
    | NULL_T {$$ = 0;}
    | NOT NULL_T {$$ = 1;}
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T  { $$ = static_cast<int>(AttrType::DATES); }
    | TEXT_T   { $$ = static_cast<int>(AttrType::TEXTS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    | INSERT INTO ID LBRACE ID attr_name_list RBRACE VALUES LBRACE value value_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;

      std::vector<std::string> *p = $6;
      p->push_back($5);

      $$->insertion.attr_names.swap(*p);
      std::reverse($$->insertion.attr_names.begin(), $$->insertion.attr_names.end());

      if ($11 != nullptr) {
        $$->insertion.values.swap(*$11);
        delete $11;
      }
      $$->insertion.values.emplace_back(*$10);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $10;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | NULL_T {
      $$ = new Value();
      $$->set_null();
    }
    | LEFT_BRACKET float_list RIGHT_BRACKET  /* 匹配[1,1.2,5]这种列表，这是向量的一种表示方式 */
    {
      $$ = new Value();
      $$->set_vector(*$2);
    }
    ;
float_list:
     /* empty*/
    { $$ = nullptr;}
    | FLOAT
    {
      $$ = new std::vector<float>;
      $$->push_back($1);
    }
    | NUMBER
    {
      $$ = new std::vector<float>;
      $$->push_back($1);
    }
    | NUMBER COMMA float_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<float>;
      }
      $$->insert($$->begin(), $1);
    }
    | FLOAT COMMA float_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<float>;
      }
      $$->insert($$->begin(), $1);
    }
    ;

storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_unite_list where
    {
      printf("解析update语句");
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.table_name = $2;
      $$->update.update_unites.swap(*$4);
      if( $5 != nullptr){
        $$->update.conditions.swap(*$5);
      }
    }
    ;
update_unite_list:
    update_unite
    {
      printf("解析update_unite_list为单个 unite list");
      $$ = new std::vector<UpdateUnite>;
      $$->push_back(*$1);
    }
    | update_unite COMMA update_unite_list
    {
      printf("解析不是空的 unite list");
      if($3 != nullptr){
        $$ = $3;
      }
      else{
        $$ = new std::vector<UpdateUnite>;
      }
      $$->push_back(*$1);
    }
    ;
update_unite:
    ID EQ expression
    {
      printf("解析update unite");
      $$ = new UpdateUnite();
      $$->field_name = $1;
      $$->expression = $3;
    }
    ;
create_view_stmt:              /*  create_view 语句的语法解析树*/
    CREATE VIEW ID AS select_stmt{
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      $$->create_view.view_name    = $3;
      $$->create_view.sql_node      = $5; 
      free($3);
    }
    | CREATE VIEW ID LBRACE ID attr_name_list RBRACE  AS select_stmt{
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      $$->create_view.view_name    = $3;

      std::vector<std::string> *p = $6;
      p->push_back($5);

      $$->create_view.attr_names.swap(*p);
      std::reverse($$->create_view.attr_names.begin(), $$->create_view.attr_names.end());
      $$->create_view.sql_node      = $9; 
      free($3);
    }
    ;
attr_name_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID attr_name_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      free($2);
    }
    ;
drop_view_stmt:
    DROP VIEW ID{
      //do nothing
    }
    ;
create_table_select_stmt:      /*  create_table_select 语句的语法解析树*/
    CREATE TABLE ID AS select_stmt{
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      $$->create_table_select.table_name    = $3;
      $$->create_table_select.sql_node      = $5; 
      free($3);
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      $$->create_table_select.table_name    = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        $$->create_table_select.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      $$->create_table_select.attr_infos.emplace_back(*$5);
      std::reverse($$->create_table_select.attr_infos.begin(), $$->create_table_select.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        $$->create_table_select.storage_format = $8;
        free($8);
      }
      $$->create_table_select.sql_node      = $9; 
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM rel_list where group_by having order_by limit_
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if ($5 != nullptr) {
        $$->selection.conditions.swap(*$5);
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.group_by.swap(*$6);
        delete $6;
      }

      if($7 != nullptr){
        $$->selection.having.swap(*$7);
        delete $7;
      }

      if ($8 != nullptr) {
        $$->selection.order_by.swap(*$8);
        delete $8;
      }
      $$->selection.join_conditions.swap(join_conditions);
      $$->selection.limit_count = $9;
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '+' expression ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, $1, $3, $4);
      //expr->set_expr(token_name(sql_string, llocp));
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '+' expression AS ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, $1, $3, $5);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '-' expression ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, $1, $3, $4);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '-' expression AS ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, $1, $3, $5);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '*' expression ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, $1, $3, $4);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '*' expression AS ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, $1, $3, $5);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | expression '/' expression ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, $1, $3, $4);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | expression '/' expression AS ID{
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, $1, $3, $5);
      expr->set_expr(sql_string);
      $$ = expr;
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | LBRACE value RBRACE{
      $$ = new ValueExpr(*$2);
      $$->set_name(token_name(sql_string, &@$));
      delete $2;
    }
    | LBRACE '-' value RBRACE{
      ValueExpr* expr = new ValueExpr(*$3);
      expr->set_name(token_name(sql_string, &@$));
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, expr, nullptr, sql_string, &@$);
      delete $3;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | ID DOT '*' {
      $$ = new StarExpr($1);
    }
    | L2_DISTANCE LBRACE expression COMMA expression RBRACE       /* l2_distance(vector A, vector B) */
    {
      $$ = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, $3, $5, sql_string, &@$);
    }
    | COSINE_DISTANCE LBRACE expression COMMA expression RBRACE   /* cosine_distance(vector A, vector B) */
    {
      $$ = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, $3, $5, sql_string, &@$);
    }
    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE     /* inner_product(vector A, vector B) */
    {
      $$ = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, $3, $5, sql_string, &@$);
    }
    | SUM LBRACE RBRACE {
      $$ = create_aggregate_expression("SUM", nullptr, sql_string, &@$);
    }
    | MAX LBRACE RBRACE{
      $$ = create_aggregate_expression("MAX", nullptr, sql_string, &@$);
    }
    | MIN LBRACE RBRACE{
      $$ = create_aggregate_expression("MIN", nullptr, sql_string, &@$);
    }
    | AVG LBRACE RBRACE{
      $$ = create_aggregate_expression("AVG", nullptr, sql_string, &@$);
    }
    | COUNT LBRACE RBRACE{
      $$ = create_aggregate_expression("COUNT", nullptr, sql_string, &@$);
    }
    | SUM LBRACE expression RBRACE{
      $$ = create_aggregate_expression("SUM", $3, sql_string, &@$);
    }
    | SUM LBRACE expression RBRACE ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("SUM", $3, $5);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | SUM LBRACE expression RBRACE AS ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("SUM", $3, $6);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | MAX LBRACE expression RBRACE{
      $$ = create_aggregate_expression("MAX", $3, sql_string, &@$);
    }
    | MAX LBRACE expression RBRACE ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MAX", $3, $5);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | MAX LBRACE expression RBRACE AS ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MAX", $3, $6);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | MIN LBRACE expression RBRACE{
      $$ = create_aggregate_expression("MIN", $3, sql_string, &@$);
    }
    | MIN LBRACE expression RBRACE ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MIN", $3, $5);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | MIN LBRACE expression RBRACE AS ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MIN", $3, $6);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | AVG LBRACE expression RBRACE{
      $$ = create_aggregate_expression("AVG", $3, sql_string, &@$);
    }
    | AVG LBRACE expression RBRACE ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("AVG", $3, $5);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | AVG LBRACE expression RBRACE AS ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("AVG", $3, $6);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | COUNT LBRACE expression RBRACE{
      $$ = create_aggregate_expression("COUNT", $3, sql_string, &@$);
    }
    | COUNT LBRACE expression RBRACE ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("COUNT", $3, $5);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | COUNT LBRACE expression RBRACE AS ID{
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("COUNT", $3, $6);
      expr->set_expr(token_name(sql_string, &@$).c_str());
      $$ = expr; 
    }
    | SUM LBRACE expression_list RBRACE {
      $$ = create_aggregate_expression("SUM", nullptr, sql_string, &@$);
    }
    | SUM LBRACE expression_list RBRACE ID{
      $$ = create_aggregate_expression_with_alias("SUM", nullptr, $5);
    }
    | SUM LBRACE expression_list RBRACE AS ID{
      $$ = create_aggregate_expression_with_alias("SUM", nullptr, $6);
    }
    | MAX LBRACE expression_list RBRACE{
      $$ = create_aggregate_expression("MAX", nullptr, sql_string, &@$);
    }
    | MAX LBRACE expression_list RBRACE ID{
      $$ = create_aggregate_expression_with_alias("MAX", nullptr, $5);
    }
    | MAX LBRACE expression_list RBRACE AS ID{
      $$ = create_aggregate_expression_with_alias("MAX", nullptr, $6);
    }
    | MIN LBRACE expression_list RBRACE{
      $$ = create_aggregate_expression("MIN", nullptr, sql_string, &@$);
    }
    | MIN LBRACE expression_list RBRACE ID{
      $$ = create_aggregate_expression_with_alias("MIN", nullptr, $5);
    }
    | MIN LBRACE expression_list RBRACE AS ID{
      $$ = create_aggregate_expression_with_alias("MIN", nullptr, $6);
    }
    | AVG LBRACE expression_list RBRACE{
      $$ = create_aggregate_expression("AVG", nullptr, sql_string, &@$);
    }
    | AVG LBRACE expression_list RBRACE ID{
      $$ = create_aggregate_expression_with_alias("AVG", nullptr, $5);
    }
    | AVG LBRACE expression_list RBRACE AS ID{
      $$ = create_aggregate_expression_with_alias("AVG", nullptr, $6);
    }
    | COUNT LBRACE expression_list RBRACE{
      $$ = create_aggregate_expression("COUNT", nullptr, sql_string, &@$);
    }
    | COUNT LBRACE expression_list RBRACE ID{
      $$ = create_aggregate_expression_with_alias("COUNT", nullptr, $5);
    }
    | COUNT LBRACE expression_list RBRACE AS ID{
      $$ = create_aggregate_expression_with_alias("COUNT", nullptr, $6);
    }
    | LBRACE select_stmt RBRACE {
      printf("解析子查询");
      $$ = new UnboundSubqueryExpr($2);
    }
    | LBRACE value value_list RBRACE{
      if($3 == nullptr){
        $3 = new vector<Value>();
      }
      $3->push_back(*$2);
      $$ = new ValueListExpr(*$3);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    | ID AS ID{
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      $$->alias          = $3;
      free($1);
      free($3);
    }
    | '*' ID{
      $$ = new RelAttrSqlNode;
      $$->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      $$->alias          = "";
      free($2);
    }
    | '*' AS ID{
      $$ = new RelAttrSqlNode;
      $$->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      $$->alias          = "";
      free($3);
    }
    | ID DOT ID AS ID{
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->alias          = $5;
      free($1);
      free($3);
      free($5);
    }
    | ID DOT ID ID{
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->alias          = $4;
      free($1);
      free($3);
      free($4);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation {
      $$ = new std::unordered_map<std::string, std::string>();
      $$->insert({$1, $1});
      free($1);
    }
    | relation COMMA rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }

      $$->insert($$->begin(), {$1, $1});
      free($1);
    }
    | relation AS ID{
      $$ = new std::unordered_map<std::string, std::string>();
      $$->insert({$3, $1});
      free($1);
      free($3);
    }
    | relation ID{
      $$ = new std::unordered_map<std::string, std::string>();
      $$->insert({$2, $1});
      free($1);
      free($2);
    }
    | relation AS ID COMMA rel_list{
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$3, $1});
      free($1);
      free($3);
    }
    | relation ID COMMA rel_list{
      if ($4!= nullptr) {
        $$ = $4;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$2, $1});
      free($1);
      free($2);
    }
    | join_in{
      if($$ == nullptr){
        $$ = $1;
      }else{
        //$$->insert($$->begin(), $1);
        $$ = $1;
      }
    }
    ;


join_in_right_list:
  INNER JOIN relation ON condition_list {
    $$ = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back($5);
    $$->insert({$3, $3});
  }
  | INNER JOIN relation AS ID ON condition_list {
    $$ = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back($7);
    $$->insert({$5, $3});
  }
  | INNER JOIN  relation {
    $$ = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    $$->insert({$3,$3});
  }
  | INNER JOIN  relation AS ID {
    $$ = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    $$->insert({$5,$3});
  }
  | INNER JOIN  relation join_in_right_list{
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$3, $3});
      free($3);
  }
  | INNER JOIN  relation AS ID join_in_right_list{
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ($6 != nullptr) {
        $$ = $6;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$5, $3});
      free($3);
      free($5);
  }
  | INNER JOIN relation ON condition_list join_in_right_list{
    join_conditions.push_back($5);
    if ($6 != nullptr) {
        $$ = $6;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$3, $3});
      free($3);
  }
  | INNER JOIN relation AS ID ON condition_list join_in_right_list{
    join_conditions.push_back($7);
    if ($8 != nullptr) {
        $$ = $8;
      } else {
        $$ = new std::unordered_map<std::string, std::string>();
      }
      $$->insert($$->begin(), {$5, $3});
      free($3);
      free($5);
  }
  ;

join_in:
  relation join_in_right_list{
    if ($2 != nullptr) {
      $$ = $2;
    } else{
      $$ = new std::unordered_map<std::string, std::string>();
    }
    $$->insert($$->begin(), {$1, $1});
    free($1);
  }
  | relation AS ID join_in_right_list{
    if ($4 != nullptr) {
      $$ = $4;
    } else{
      $$ = new std::unordered_map<std::string, std::string>();
    }
    $$->insert($$->begin(), {$3, $1});
    free($1);
    free($3);
  }
  ;

limit_:
    {
      $$ = -1;
    }
    | LIMIT number{
        $$ = $2;
    }

order_by_field:
    rel_attr DESC {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }|
    rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }| rel_attr ASC {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
      }
    | expression {
      $$ = $1;
    }
    ;
order_by_field_list:
    order_by_field{
      $$ = new std::vector<std::unique_ptr<Expression>> ;
      $$->emplace_back($1);
      //delete $1;
    }
    | order_by_field COMMA order_by_field_list {
      $$ = $3;
      $$->emplace_back($1);
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    };
order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_field_list
    {
      if($3 != nullptr){
        $$ = $3;
      }else{
        $$ = nullptr;
      }
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->conjunction_with_or = true;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | expression comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_expr = 1;
      $$->left_expr = $1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $3;
    }
    | value comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_expr = 1;
      $$->right_expr = $3;
      $$->comp = $2;

      delete $1;
    }
    | expression comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_expr = 1;
      $$->left_expr = $1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $3;
    }
    | rel_attr comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_expr = 1;
      $$->right_expr = $3;
      $$->comp = $2;

      delete $1;
    }
    | expression comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_is_expr = 1;
      $$->left_expr = $1;
      $$->right_is_expr = 1;
      $$->right_expr = $3;
      $$->comp = $2;
    }
    ;
    
comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_TO; }
    | NOT LIKE { $$ = NOT_LIKE_TO; }
    | IS_ { $$ = IS ;}
    | IS_ NOT { $$ = IS_NOT ;}
    | IN_T { $$ = IN ; }
    | NOT IN_T { $$ = NOT_IN ; }
    | EXISTS_T { $$ = EXISTS ; }
    | NOT EXISTS_T { $$ = NOT_EXISTS ; }
    ;

group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->swap(*$3);
      delete $3;
    }
    ;

having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list
    {
      $$ = new std::vector<ConditionSqlNode>;
      $$->swap(*$2);
      delete $2;
    }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
