/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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



#line 165 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_GROUP = 4,                      /* GROUP  */
  YYSYMBOL_BY = 5,                         /* BY  */
  YYSYMBOL_CREATE = 6,                     /* CREATE  */
  YYSYMBOL_DROP = 7,                       /* DROP  */
  YYSYMBOL_ORDER = 8,                      /* ORDER  */
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_TABLES = 10,                    /* TABLES  */
  YYSYMBOL_VIEW = 11,                      /* VIEW  */
  YYSYMBOL_VIEWS = 12,                     /* VIEWS  */
  YYSYMBOL_INDEX = 13,                     /* INDEX  */
  YYSYMBOL_CALC = 14,                      /* CALC  */
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_ASC = 17,                       /* ASC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 32,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 33,                    /* TEXT_T  */
  YYSYMBOL_VECTOR_T = 34,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 35,                      /* HELP  */
  YYSYMBOL_EXIT = 36,                      /* EXIT  */
  YYSYMBOL_DOT = 37,                       /* DOT  */
  YYSYMBOL_INTO = 38,                      /* INTO  */
  YYSYMBOL_VALUES = 39,                    /* VALUES  */
  YYSYMBOL_FROM = 40,                      /* FROM  */
  YYSYMBOL_WHERE = 41,                     /* WHERE  */
  YYSYMBOL_AND = 42,                       /* AND  */
  YYSYMBOL_OR = 43,                        /* OR  */
  YYSYMBOL_SET = 44,                       /* SET  */
  YYSYMBOL_ON = 45,                        /* ON  */
  YYSYMBOL_LOAD = 46,                      /* LOAD  */
  YYSYMBOL_DATA = 47,                      /* DATA  */
  YYSYMBOL_INFILE = 48,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 49,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 50,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 51,                    /* FORMAT  */
  YYSYMBOL_EQ = 52,                        /* EQ  */
  YYSYMBOL_LT = 53,                        /* LT  */
  YYSYMBOL_GT = 54,                        /* GT  */
  YYSYMBOL_LE = 55,                        /* LE  */
  YYSYMBOL_GE = 56,                        /* GE  */
  YYSYMBOL_NE = 57,                        /* NE  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_LIKE = 59,                      /* LIKE  */
  YYSYMBOL_IS_ = 60,                       /* IS_  */
  YYSYMBOL_NULL_T = 61,                    /* NULL_T  */
  YYSYMBOL_MAX = 62,                       /* MAX  */
  YYSYMBOL_MIN = 63,                       /* MIN  */
  YYSYMBOL_AVG = 64,                       /* AVG  */
  YYSYMBOL_SUM = 65,                       /* SUM  */
  YYSYMBOL_COUNT = 66,                     /* COUNT  */
  YYSYMBOL_HAVING = 67,                    /* HAVING  */
  YYSYMBOL_INNER = 68,                     /* INNER  */
  YYSYMBOL_JOIN = 69,                      /* JOIN  */
  YYSYMBOL_AS = 70,                        /* AS  */
  YYSYMBOL_UNIQUE = 71,                    /* UNIQUE  */
  YYSYMBOL_WITH = 72,                      /* WITH  */
  YYSYMBOL_DISTANCE = 73,                  /* DISTANCE  */
  YYSYMBOL_TYPE = 74,                      /* TYPE  */
  YYSYMBOL_LISTS = 75,                     /* LISTS  */
  YYSYMBOL_PROBES = 76,                    /* PROBES  */
  YYSYMBOL_LIMIT = 77,                     /* LIMIT  */
  YYSYMBOL_LEFT_BRACKET = 78,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 79,             /* RIGHT_BRACKET  */
  YYSYMBOL_L2_DISTANCE = 80,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 81,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 82,             /* INNER_PRODUCT  */
  YYSYMBOL_IN_T = 83,                      /* IN_T  */
  YYSYMBOL_EXISTS_T = 84,                  /* EXISTS_T  */
  YYSYMBOL_NUMBER = 85,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 86,                     /* FLOAT  */
  YYSYMBOL_ID = 87,                        /* ID  */
  YYSYMBOL_SSS = 88,                       /* SSS  */
  YYSYMBOL_89_ = 89,                       /* '+'  */
  YYSYMBOL_90_ = 90,                       /* '-'  */
  YYSYMBOL_91_ = 91,                       /* '*'  */
  YYSYMBOL_92_ = 92,                       /* '/'  */
  YYSYMBOL_UMINUS = 93,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_commands = 95,                  /* commands  */
  YYSYMBOL_command_wrapper = 96,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 97,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 98,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 99,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 100,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 101,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 102,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 103,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 104,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 105,          /* desc_table_stmt  */
  YYSYMBOL_index_type = 106,               /* index_type  */
  YYSYMBOL_create_index_stmt = 107,        /* create_index_stmt  */
  YYSYMBOL_distance_type = 108,            /* distance_type  */
  YYSYMBOL_create_index_vector_stmt = 109, /* create_index_vector_stmt  */
  YYSYMBOL_drop_index_stmt = 110,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 111,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 112,            /* attr_def_list  */
  YYSYMBOL_attr_def = 113,                 /* attr_def  */
  YYSYMBOL_not_null = 114,                 /* not_null  */
  YYSYMBOL_number = 115,                   /* number  */
  YYSYMBOL_type = 116,                     /* type  */
  YYSYMBOL_insert_stmt = 117,              /* insert_stmt  */
  YYSYMBOL_value_list = 118,               /* value_list  */
  YYSYMBOL_value = 119,                    /* value  */
  YYSYMBOL_float_list = 120,               /* float_list  */
  YYSYMBOL_storage_format = 121,           /* storage_format  */
  YYSYMBOL_delete_stmt = 122,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 123,              /* update_stmt  */
  YYSYMBOL_update_unite_list = 124,        /* update_unite_list  */
  YYSYMBOL_update_unite = 125,             /* update_unite  */
  YYSYMBOL_create_view_stmt = 126,         /* create_view_stmt  */
  YYSYMBOL_attr_name_list = 127,           /* attr_name_list  */
  YYSYMBOL_drop_view_stmt = 128,           /* drop_view_stmt  */
  YYSYMBOL_create_table_select_stmt = 129, /* create_table_select_stmt  */
  YYSYMBOL_select_stmt = 130,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 131,                /* calc_stmt  */
  YYSYMBOL_expression_list = 132,          /* expression_list  */
  YYSYMBOL_expression = 133,               /* expression  */
  YYSYMBOL_rel_attr = 134,                 /* rel_attr  */
  YYSYMBOL_relation = 135,                 /* relation  */
  YYSYMBOL_rel_list = 136,                 /* rel_list  */
  YYSYMBOL_join_in_right_list = 137,       /* join_in_right_list  */
  YYSYMBOL_join_in = 138,                  /* join_in  */
  YYSYMBOL_limit_ = 139,                   /* limit_  */
  YYSYMBOL_order_by_field = 140,           /* order_by_field  */
  YYSYMBOL_order_by_field_list = 141,      /* order_by_field_list  */
  YYSYMBOL_order_by = 142,                 /* order_by  */
  YYSYMBOL_where = 143,                    /* where  */
  YYSYMBOL_condition_list = 144,           /* condition_list  */
  YYSYMBOL_condition = 145,                /* condition  */
  YYSYMBOL_comp_op = 146,                  /* comp_op  */
  YYSYMBOL_group_by = 147,                 /* group_by  */
  YYSYMBOL_having = 148,                   /* having  */
  YYSYMBOL_load_data_stmt = 149,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 150,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 151,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 152             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   567

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  221
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  419

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    91,    89,     2,    90,     2,    92,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   290,   290,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   325,   331,   336,
     342,   348,   354,   360,   367,   373,   381,   383,   388,   405,
     408,   411,   416,   435,   445,   469,   472,   485,   495,   511,
     512,   513,   516,   519,   520,   521,   522,   523,   524,   527,
     540,   564,   567,   578,   582,   586,   592,   596,   604,   605,
     610,   615,   624,   637,   640,   647,   659,   671,   677,   690,
     699,   705,   720,   723,   735,   740,   746,   769,   806,   815,
     820,   831,   834,   840,   845,   848,   853,   858,   861,   866,
     871,   874,   879,   884,   888,   891,   896,   902,   905,   908,
     912,   916,   920,   923,   926,   929,   932,   935,   938,   943,
     948,   951,   956,   961,   964,   969,   974,   977,   982,   987,
     990,   995,  1000,  1003,  1006,  1009,  1012,  1015,  1018,  1021,
    1024,  1027,  1030,  1033,  1036,  1039,  1042,  1045,  1049,  1059,
    1064,  1071,  1078,  1084,  1090,  1099,  1111,  1116,  1121,  1131,
    1137,  1143,  1153,  1163,  1175,  1180,  1185,  1191,  1197,  1208,
    1220,  1230,  1244,  1253,  1266,  1269,  1274,  1280,  1285,  1291,
    1296,  1301,  1308,  1311,  1322,  1325,  1331,  1334,  1339,  1344,
    1352,  1364,  1376,  1388,  1400,  1411,  1422,  1433,  1444,  1456,
    1457,  1458,  1459,  1460,  1461,  1462,  1463,  1464,  1465,  1466,
    1467,  1468,  1469,  1474,  1477,  1487,  1490,  1499,  1512,  1520,
    1530,  1531
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "GROUP",
  "BY", "CREATE", "DROP", "ORDER", "TABLE", "TABLES", "VIEW", "VIEWS",
  "INDEX", "CALC", "SELECT", "DESC", "ASC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "VECTOR_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE", "NOT", "LIKE",
  "IS_", "NULL_T", "MAX", "MIN", "AVG", "SUM", "COUNT", "HAVING", "INNER",
  "JOIN", "AS", "UNIQUE", "WITH", "DISTANCE", "TYPE", "LISTS", "PROBES",
  "LIMIT", "LEFT_BRACKET", "RIGHT_BRACKET", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "IN_T", "EXISTS_T", "NUMBER",
  "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "index_type", "create_index_stmt",
  "distance_type", "create_index_vector_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "not_null", "number",
  "type", "insert_stmt", "value_list", "value", "float_list",
  "storage_format", "delete_stmt", "update_stmt", "update_unite_list",
  "update_unite", "create_view_stmt", "attr_name_list", "drop_view_stmt",
  "create_table_select_stmt", "select_stmt", "calc_stmt",
  "expression_list", "expression", "rel_attr", "relation", "rel_list",
  "join_in_right_list", "join_in", "limit_", "order_by_field",
  "order_by_field_list", "order_by", "where", "condition_list",
  "condition", "comp_op", "group_by", "having", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-284)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     510,    -2,    26,   424,   424,   -57,    28,  -284,    11,    43,
       4,  -284,  -284,  -284,  -284,  -284,    31,    33,   510,   141,
     148,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,    76,    82,   160,  -284,   162,
      96,    98,   108,   169,  -284,   156,   190,   223,   225,   235,
      37,   251,   257,   258,  -284,  -284,   -18,  -284,   424,   -45,
    -284,  -284,    75,  -284,   242,  -284,  -284,   196,   211,   255,
     248,   254,  -284,  -284,  -284,  -284,   -15,    -9,   217,   219,
    -284,  -284,   263,   137,   288,    97,   229,   273,   317,   349,
     393,   293,   296,   234,   424,   424,   424,   -23,   236,  -284,
     237,  -284,   424,   424,   424,   424,   424,   238,     1,   286,
     241,    92,   244,   243,   314,   261,   314,   304,   305,   265,
      92,   332,  -284,  -284,  -284,   333,    -4,  -284,   338,    47,
    -284,   341,    53,  -284,   342,    57,  -284,   343,    65,    37,
      37,  -284,   115,   174,   187,   -43,  -284,  -284,  -284,  -284,
     -25,   123,   -41,   -34,  -284,   -12,   286,  -284,   281,   346,
     424,  -284,   318,   286,   350,  -284,   336,   313,   351,  -284,
     352,  -284,   297,   298,  -284,   361,  -284,    63,    89,   104,
     124,   151,   157,   158,   197,   198,   199,  -284,  -284,   424,
     424,   424,   300,  -284,   301,  -284,   302,  -284,   303,  -284,
     306,  -284,   238,   322,   307,   371,  -284,   396,   352,    92,
     366,   408,   366,  -284,   129,   424,  -284,   241,   392,  -284,
    -284,  -284,  -284,  -284,  -284,    -7,   243,   382,   345,   385,
     405,   410,  -284,   354,  -284,   355,  -284,   356,  -284,   357,
    -284,   358,  -284,   359,  -284,   364,  -284,   365,  -284,   383,
    -284,   389,  -284,   111,   128,   134,  -284,  -284,  -284,  -284,
    -284,  -284,   238,    -8,   238,   433,   381,   429,   361,  -284,
    -284,  -284,  -284,  -284,  -284,   -36,  -284,   411,  -284,  -284,
     424,   424,   424,   424,   424,   181,  -284,   390,   387,   421,
    -284,  -284,   351,   443,   352,   425,   238,   238,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,   -11,   238,  -284,  -284,   424,   424,   486,   457,   477,
    -284,  -284,  -284,  -284,  -284,   181,  -284,  -284,   181,  -284,
    -284,   181,  -284,  -284,  -284,  -284,  -284,   479,  -284,  -284,
     456,   314,  -284,   314,   484,   489,   424,   431,  -284,  -284,
    -284,  -284,   514,   444,   497,  -284,   -30,   470,  -284,  -284,
     451,  -284,   459,   -27,   424,   387,  -284,    92,  -284,   446,
     511,  -284,   424,  -284,   181,   165,   515,  -284,  -284,   361,
    -284,   461,   459,  -284,  -284,   424,   517,   487,  -284,  -284,
    -284,   455,   518,   471,   495,    49,  -284,  -284,  -284,   523,
     474,   498,   466,   527,   481,   501,   473,   531,  -284
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    36,     0,     0,     0,     0,     0,    29,     0,     0,
       0,    30,    31,    32,    28,    27,     0,     0,     0,     0,
     220,    25,    24,    17,    18,    19,    20,    10,    12,    13,
      14,    15,    16,     8,     5,     7,     6,     9,    11,    26,
       4,     3,    21,    22,    23,     0,     0,     0,    37,     0,
       0,     0,     0,     0,    66,     0,     0,     0,     0,     0,
      68,     0,     0,     0,    63,    64,   149,    65,     0,   107,
     105,    88,    89,   106,     0,    35,    34,     0,     0,     0,
       0,     0,   218,     1,   221,     2,     0,     0,     0,     0,
      33,    84,     0,   105,     0,     0,     0,     0,     0,     0,
       0,    70,    69,     0,     0,     0,     0,     0,     0,   104,
       0,   152,     0,     0,     0,     0,     0,     0,     0,   184,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   147,   103,   113,     0,     0,   114,     0,     0,
     115,     0,     0,   112,     0,     0,   116,     0,     0,    68,
      68,    67,     0,     0,     0,   150,   108,   151,   153,    90,
      91,    94,    97,   100,   156,   157,   184,   163,     0,     0,
     186,    75,     0,   184,    77,   219,     0,     0,    45,    85,
      82,    80,     0,     0,    43,    61,   148,   135,   120,   138,
     123,   141,   126,   132,   117,   144,   129,    71,    72,     0,
       0,     0,     0,   155,     0,    92,     0,    95,     0,    98,
       0,   101,     0,     0,     0,   160,   172,   213,    82,     0,
     105,     0,   106,   185,   187,     0,    76,     0,     0,    53,
      54,    55,    56,    57,    58,    49,     0,     0,     0,     0,
       0,     0,    62,     0,   136,     0,   121,     0,   139,     0,
     124,     0,   142,     0,   127,     0,   133,     0,   118,     0,
     145,     0,   130,     0,     0,     0,   154,    93,    96,    99,
     102,   158,     0,   159,     0,     0,   215,     0,    61,   199,
     200,   201,   202,   203,   204,     0,   205,   207,   209,   211,
       0,     0,     0,   186,   186,    79,    78,     0,     0,     0,
      50,    48,    45,    73,    82,     0,     0,     0,   137,   122,
     140,   125,   143,   128,   134,   119,   146,   131,   109,   110,
     111,   166,     0,   173,   162,     0,   186,   182,     0,     0,
     206,   210,   212,   208,   105,   195,   106,   105,   198,   106,
     105,   197,   106,   188,   189,   217,    52,     0,    51,    46,
       0,    44,    83,     0,     0,     0,   186,     0,   168,   161,
     214,   216,     0,   174,     0,    59,    49,     0,    86,    81,
       0,    38,   164,   167,     0,     0,    87,     0,    47,     0,
       0,   170,   186,   169,   179,   106,   180,   183,   175,    61,
      74,     0,   165,   176,   178,     0,     0,     0,   171,   181,
      60,     0,     0,     0,     0,     0,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -284,  -284,   542,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,   259,   326,
     200,   188,  -284,  -284,  -180,   -51,    87,  -284,  -284,  -284,
     337,  -284,  -284,  -212,  -284,  -284,   -50,  -284,     8,    -3,
    -166,   295,  -190,  -258,  -284,  -284,  -284,   170,  -284,  -140,
    -283,  -284,    40,  -284,  -284,  -284,  -284,  -284,  -284
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    49,    30,   409,    31,    32,    33,   237,   178,
     301,   347,   235,    34,   131,    70,   103,   351,    35,    36,
     173,   174,    37,   239,    38,    39,    40,    41,    71,   221,
      73,   165,   166,   216,   167,   376,   386,   387,   363,   171,
     223,   224,   290,   276,   327,    42,    43,    44,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    72,    93,    94,   222,   242,   277,    45,   123,    46,
     343,   344,    74,   212,   125,   323,   298,   322,   382,   107,
     188,   112,   271,   330,   168,   110,   217,   202,   299,   208,
      75,   300,    47,   226,   356,    50,   210,    51,    76,    52,
     169,   213,   111,   361,   203,   204,   209,   331,   332,    77,
      95,   299,   108,   211,   300,   124,   213,   213,   214,   357,
     213,   126,   205,   358,   155,   109,   115,   116,   156,    48,
     175,   190,   112,   372,   179,   215,   181,   192,   112,   185,
      81,   194,   112,    78,   324,   113,   114,   115,   116,   196,
     112,    79,   352,   136,   139,   142,   145,   148,   329,   392,
     112,   152,   153,   154,   135,   138,   141,   144,   147,    72,
     160,   161,   162,   163,   381,   383,   354,   355,    80,   220,
     159,   133,   101,   102,   336,   339,   342,   222,   222,   406,
     407,   408,   359,   243,   398,   318,   113,   114,   115,   116,
     199,    83,   113,   114,   115,   116,   113,   114,   115,   116,
     244,    84,   319,    54,   113,   114,   115,   116,   320,   245,
     222,   -61,   130,    86,   113,   114,   115,   116,   278,    87,
      60,   293,   294,    88,   247,    89,   246,    64,    65,    96,
      67,   393,   394,    90,     4,    91,   113,   114,   115,   116,
     222,   248,    53,   206,   249,    92,   263,   264,   265,   200,
     113,   114,   115,   116,   113,   114,   115,   116,   385,   396,
     207,   250,   201,    97,   115,   116,   222,   113,   114,   115,
     116,   251,   295,   113,   114,   115,   116,   253,   255,   385,
      54,    55,    56,    57,    58,    59,   197,   198,   252,   334,
     337,   340,   220,   220,   254,   256,    98,    60,    99,    61,
      62,    63,    53,   134,    64,    65,    66,    67,   100,    68,
      69,   291,   292,   113,   114,   115,   116,   257,   259,   261,
     113,   114,   115,   116,   104,   220,   113,   114,   115,   116,
     105,   106,   117,   118,   258,   260,   262,   335,   338,   341,
      54,    55,    56,    57,    58,    59,    53,   137,   119,   120,
     121,   368,   122,   369,   127,   220,   128,    60,   129,    61,
      62,    63,   132,   151,    64,    65,    66,    67,   149,    68,
      69,   150,    72,   157,   158,   164,   389,   170,   172,     4,
     177,   220,   176,   360,    54,    55,    56,    57,    58,    59,
      53,   140,   229,   230,   231,   232,   233,   234,   180,   182,
     183,    60,   184,    61,    62,    63,   186,   187,    64,    65,
      66,    67,   189,    68,    69,   191,   193,   195,   218,   219,
     225,   384,    53,   143,   228,   227,   236,   238,    54,    55,
      56,    57,    58,    59,   240,   241,   130,   266,   267,   268,
     269,   272,   384,   270,   273,    60,   274,    61,    62,    63,
     275,   297,    64,    65,    66,    67,   303,    68,    69,   305,
      54,    55,    56,    57,    58,    59,    53,   146,   279,   280,
     281,   282,   283,   284,   285,   286,   287,    60,   306,    61,
      62,    63,   304,   307,    64,    65,    66,    67,   325,    68,
      69,   308,   309,   310,   311,   312,   313,    53,   326,   288,
     289,   314,   315,   328,    54,    55,    56,    57,    58,    59,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   333,
     316,    60,   346,    61,    62,    63,   317,   345,    64,    65,
      66,    67,   348,    68,    69,    54,    55,    56,    57,    58,
      59,   288,   289,   350,   362,   353,   364,   113,   114,   115,
     116,   365,    60,   366,    61,    62,    63,   367,   370,    64,
      65,    66,    67,   371,    68,    69,     1,     2,   373,   374,
     377,   375,   379,   380,     3,     4,     5,   213,     6,     7,
       8,     9,    10,   390,   391,   397,    11,    12,    13,   401,
     395,   400,   402,   403,   404,    14,    15,   405,   410,   411,
     412,   413,   414,   416,    16,   418,    17,   415,   417,    18,
      82,   349,   302,   388,   296,   399,   378,   321
};

static const yytype_int16 yycheck[] =
{
       3,     4,    53,    53,   170,   185,   218,     9,    23,    11,
     293,   294,     4,    25,    23,   273,    23,    25,    45,    37,
      24,    25,   212,    59,    23,    70,   166,    70,    58,    70,
      87,    61,    34,   173,    45,     9,    70,    11,    10,    13,
      39,    68,    87,   326,    87,    70,    87,    83,    84,    38,
      53,    58,    70,    87,    61,    70,    68,    68,    70,    70,
      68,    70,    87,   321,    87,    68,    91,    92,    91,    71,
     121,    24,    25,   356,   124,    87,   126,    24,    25,   130,
      47,    24,    25,    40,   274,    89,    90,    91,    92,    24,
      25,    87,   304,    96,    97,    98,    99,   100,   278,   382,
      25,   104,   105,   106,    96,    97,    98,    99,   100,   112,
     113,   114,   115,   116,   372,   373,   306,   307,    87,   170,
     112,    24,    85,    86,   290,   291,   292,   293,   294,    80,
      81,    82,   322,    70,   392,    24,    89,    90,    91,    92,
      25,     0,    89,    90,    91,    92,    89,    90,    91,    92,
      87,     3,    24,    61,    89,    90,    91,    92,    24,    70,
     326,    24,    25,    87,    89,    90,    91,    92,   219,    87,
      78,    42,    43,    13,    70,    13,    87,    85,    86,    23,
      88,    16,    17,    87,    15,    87,    89,    90,    91,    92,
     356,    87,    23,    70,    70,    87,   199,   200,   201,    25,
      89,    90,    91,    92,    89,    90,    91,    92,   374,   389,
      87,    87,    25,    23,    91,    92,   382,    89,    90,    91,
      92,    70,   225,    89,    90,    91,    92,    70,    70,   395,
      61,    62,    63,    64,    65,    66,   149,   150,    87,   290,
     291,   292,   293,   294,    87,    87,    23,    78,    23,    80,
      81,    82,    23,    24,    85,    86,    87,    88,    23,    90,
      91,   221,   222,    89,    90,    91,    92,    70,    70,    70,
      89,    90,    91,    92,    23,   326,    89,    90,    91,    92,
      23,    23,    40,    87,    87,    87,    87,   290,   291,   292,
      61,    62,    63,    64,    65,    66,    23,    24,    87,    44,
      52,   351,    48,   353,    87,   356,    87,    78,    45,    80,
      81,    82,    24,    79,    85,    86,    87,    88,    25,    90,
      91,    25,   325,    87,    87,    87,   377,    41,    87,    15,
      87,   382,    88,   325,    61,    62,    63,    64,    65,    66,
      23,    24,    29,    30,    31,    32,    33,    34,    87,    45,
      45,    78,    87,    80,    81,    82,    24,    24,    85,    86,
      87,    88,    24,    90,    91,    24,    24,    24,    87,    23,
      52,   374,    23,    24,    38,    25,    25,    25,    61,    62,
      63,    64,    65,    66,    87,    87,    25,    87,    87,    87,
      87,    69,   395,    87,    87,    78,    25,    80,    81,    82,
       4,     9,    85,    86,    87,    88,    24,    90,    91,    24,
      61,    62,    63,    64,    65,    66,    23,    24,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    78,    23,    80,
      81,    82,    87,    23,    85,    86,    87,    88,     5,    90,
      91,    87,    87,    87,    87,    87,    87,    23,    67,    83,
      84,    87,    87,    24,    61,    62,    63,    64,    65,    66,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    58,
      87,    78,    85,    80,    81,    82,    87,    87,    85,    86,
      87,    88,    61,    90,    91,    61,    62,    63,    64,    65,
      66,    83,    84,    50,     8,    70,    39,    89,    90,    91,
      92,    24,    78,    24,    80,    81,    82,    51,    24,    85,
      86,    87,    88,    24,    90,    91,     6,     7,    87,     5,
      23,    77,    52,    72,    14,    15,    16,    68,    18,    19,
      20,    21,    22,    87,    23,    74,    26,    27,    28,    52,
      25,    24,    87,    25,    73,    35,    36,    52,    25,    75,
      52,    85,    25,    52,    44,    24,    46,    76,    85,    49,
      18,   302,   236,   375,   227,   395,   366,   272
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    14,    15,    16,    18,    19,    20,    21,
      22,    26,    27,    28,    35,    36,    44,    46,    49,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     107,   109,   110,   111,   117,   122,   123,   126,   128,   129,
     130,   131,   149,   150,   151,     9,    11,    34,    71,   106,
       9,    11,    13,    23,    61,    62,    63,    64,    65,    66,
      78,    80,    81,    82,    85,    86,    87,    88,    90,    91,
     119,   132,   133,   134,   132,    87,    10,    38,    40,    87,
      87,    47,    96,     0,     3,   152,    87,    87,    13,    13,
      87,    87,    87,   119,   130,   133,    23,    23,    23,    23,
      23,    85,    86,   120,    23,    23,    23,    37,    70,   133,
      70,    87,    25,    89,    90,    91,    92,    40,    87,    87,
      44,    52,    48,    23,    70,    23,    70,    87,    87,    45,
      25,   118,    24,    24,    24,   132,   133,    24,   132,   133,
      24,   132,   133,    24,   132,   133,    24,   132,   133,    25,
      25,    79,   133,   133,   133,    87,    91,    87,    87,   132,
     133,   133,   133,   133,    87,   135,   136,   138,    23,    39,
      41,   143,    87,   124,   125,   119,    88,    87,   113,   130,
      87,   130,    45,    45,    87,   119,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    24,    24,   120,   120,    25,
      25,    25,    70,    87,    70,    87,    70,    87,    70,    87,
      70,    87,    25,    68,    70,    87,   137,   143,    87,    23,
     119,   133,   134,   144,   145,    52,   143,    25,    38,    29,
      30,    31,    32,    33,    34,   116,    25,   112,    25,   127,
      87,    87,   118,    70,    87,    70,    87,    70,    87,    70,
      87,    70,    87,    70,    87,    70,    87,    70,    87,    70,
      87,    70,    87,   133,   133,   133,    87,    87,    87,    87,
      87,   136,    69,    87,    25,     4,   147,   127,   119,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    83,    84,
     146,   146,   146,    42,    43,   133,   124,     9,    23,    58,
      61,   114,   113,    24,    87,    24,    23,    23,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    24,    24,
      24,   135,    25,   137,   136,     5,    67,   148,    24,   118,
      59,    83,    84,    58,   119,   133,   134,   119,   133,   134,
     119,   133,   134,   144,   144,    87,    85,   115,    61,   112,
      50,   121,   127,    70,   136,   136,    45,    70,   137,   136,
     132,   144,     8,   142,    39,    24,    24,    51,   130,   130,
      24,    24,   144,    87,     5,    77,   139,    23,   114,    52,
      72,   137,    45,   137,   133,   134,   140,   141,   115,   119,
      87,    23,   144,    16,    17,    25,   118,    74,   137,   141,
      24,    52,    87,    25,    73,    52,    80,    81,    82,   108,
      25,    75,    52,    85,    25,    76,    52,    85,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   106,   107,   108,
     108,   108,   109,   110,   111,   112,   112,   113,   113,   114,
     114,   114,   115,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   120,   120,
     120,   120,   120,   121,   121,   122,   123,   124,   124,   125,
     126,   126,   127,   127,   128,   129,   129,   130,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   135,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   140,
     141,   141,   142,   142,   143,   143,   144,   144,   144,   144,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   148,   148,   149,   150,   151,
     152,   152
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     0,     1,     9,     1,
       1,     1,    27,     5,     8,     0,     3,     6,     3,     0,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     8,
      12,     0,     3,     1,     1,     1,     1,     3,     0,     1,
       1,     3,     3,     0,     4,     4,     5,     1,     3,     3,
       5,     9,     0,     3,     3,     5,     9,     9,     2,     1,
       3,     3,     4,     5,     3,     4,     5,     3,     4,     5,
       3,     4,     5,     3,     2,     1,     1,     1,     3,     6,
       6,     6,     3,     3,     3,     3,     3,     4,     5,     6,
       4,     5,     6,     4,     5,     6,     4,     5,     6,     4,
       5,     6,     4,     5,     6,     4,     5,     6,     4,     5,
       6,     4,     5,     6,     4,     5,     6,     3,     4,     1,
       3,     3,     2,     3,     5,     4,     1,     1,     3,     3,
       2,     5,     4,     1,     5,     7,     3,     5,     4,     6,
       6,     8,     2,     4,     0,     2,     2,     1,     2,     1,
       1,     3,     0,     3,     0,     2,     0,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       2,     1,     2,     0,     3,     0,     2,     7,     2,     4,
       0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 291 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2039 "yacc_sql.cpp"
    break;

  case 27: /* exit_stmt: EXIT  */
#line 325 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2048 "yacc_sql.cpp"
    break;

  case 28: /* help_stmt: HELP  */
#line 331 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2056 "yacc_sql.cpp"
    break;

  case 29: /* sync_stmt: SYNC  */
#line 336 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 30: /* begin_stmt: TRX_BEGIN  */
#line 342 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 31: /* commit_stmt: TRX_COMMIT  */
#line 348 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2080 "yacc_sql.cpp"
    break;

  case 32: /* rollback_stmt: TRX_ROLLBACK  */
#line 354 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 33: /* drop_table_stmt: DROP TABLE ID  */
#line 360 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 34: /* show_tables_stmt: SHOW TABLES  */
#line 367 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2106 "yacc_sql.cpp"
    break;

  case 35: /* desc_table_stmt: DESC ID  */
#line 373 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2116 "yacc_sql.cpp"
    break;

  case 36: /* index_type: %empty  */
#line 381 "yacc_sql.y"
  {
      (yyval.bools) = false;
  }
#line 2124 "yacc_sql.cpp"
    break;

  case 37: /* index_type: UNIQUE  */
#line 383 "yacc_sql.y"
           {
      (yyval.bools) = true;
  }
#line 2132 "yacc_sql.cpp"
    break;

  case 38: /* create_index_stmt: CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 389 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      for (const auto& pair : *(yyvsp[-1].relation_list)) {
         create_index.attribute_names.push_back(pair.first);
      }
      create_index.unique = (yyvsp[-7].bools);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      //free($2);
      delete((yyvsp[-1].relation_list));
    }
#line 2151 "yacc_sql.cpp"
    break;

  case 39: /* distance_type: L2_DISTANCE  */
#line 405 "yacc_sql.y"
               {
       (yyval.number)  = 1;
   }
#line 2159 "yacc_sql.cpp"
    break;

  case 40: /* distance_type: COSINE_DISTANCE  */
#line 408 "yacc_sql.y"
                  {
      (yyval.number)  =  2;
   }
#line 2167 "yacc_sql.cpp"
    break;

  case 41: /* distance_type: INNER_PRODUCT  */
#line 411 "yacc_sql.y"
                 {
      (yyval.number)  =  3;
   }
#line 2175 "yacc_sql.cpp"
    break;

  case 42: /* create_index_vector_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE TYPE EQ ID COMMA DISTANCE EQ distance_type COMMA LISTS EQ NUMBER COMMA PROBES EQ NUMBER RBRACE  */
#line 417 "yacc_sql.y"
  {
     (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VECTOR_INDEX);
     CreateVectorIndexSqlNode &create_index = (yyval.sql_node)->create_vector_index;
      create_index.index_name = (yyvsp[-23].string);
      create_index.relation_name = (yyvsp[-21].string);
      for (const auto& pair : *(yyvsp[-19].relation_list)) {
         create_index.attribute_names.push_back(pair.first);
      }
      create_index.lists = (yyvsp[-5].number);
      create_index.probes = (yyvsp[-1].number);
      create_index.distance_type = (yyvsp[-9].number);
  }
#line 2192 "yacc_sql.cpp"
    break;

  case 43: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 436 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2204 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 446 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2229 "yacc_sql.cpp"
    break;

  case 45: /* attr_def_list: %empty  */
#line 469 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 46: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 473 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2251 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type LBRACE number RBRACE not_null  */
#line 486 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if((yyval.attr_info)->type == AttrType::VECTORS){(yyval.attr_info)->set_vector_type_length((yyvsp[-2].number));}
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-5].string));
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type not_null  */
#line 496 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if((yyval.attr_info)->type == AttrType::TEXTS){
        (yyval.attr_info)->length = 65535;
      }else{
        (yyval.attr_info)->length = 4;
      }
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-2].string));
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 49: /* not_null: %empty  */
#line 511 "yacc_sql.y"
    {(yyval.number) = 0;}
#line 2288 "yacc_sql.cpp"
    break;

  case 50: /* not_null: NULL_T  */
#line 512 "yacc_sql.y"
             {(yyval.number) = 0;}
#line 2294 "yacc_sql.cpp"
    break;

  case 51: /* not_null: NOT NULL_T  */
#line 513 "yacc_sql.y"
                 {(yyval.number) = 1;}
#line 2300 "yacc_sql.cpp"
    break;

  case 52: /* number: NUMBER  */
#line 516 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2306 "yacc_sql.cpp"
    break;

  case 53: /* type: INT_T  */
#line 519 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2312 "yacc_sql.cpp"
    break;

  case 54: /* type: STRING_T  */
#line 520 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2318 "yacc_sql.cpp"
    break;

  case 55: /* type: FLOAT_T  */
#line 521 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2324 "yacc_sql.cpp"
    break;

  case 56: /* type: DATE_T  */
#line 522 "yacc_sql.y"
              { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2330 "yacc_sql.cpp"
    break;

  case 57: /* type: TEXT_T  */
#line 523 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2336 "yacc_sql.cpp"
    break;

  case 58: /* type: VECTOR_T  */
#line 524 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2342 "yacc_sql.cpp"
    break;

  case 59: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 528 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2359 "yacc_sql.cpp"
    break;

  case 60: /* insert_stmt: INSERT INTO ID LBRACE ID attr_name_list RBRACE VALUES LBRACE value value_list RBRACE  */
#line 541 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-9].string);

      std::vector<std::string> *p = (yyvsp[-6].attr_names);
      p->push_back((yyvsp[-7].string));

      (yyval.sql_node)->insertion.attr_names.swap(*p);
      std::reverse((yyval.sql_node)->insertion.attr_names.begin(), (yyval.sql_node)->insertion.attr_names.end());

      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-9].string));
    }
#line 2383 "yacc_sql.cpp"
    break;

  case 61: /* value_list: %empty  */
#line 564 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2391 "yacc_sql.cpp"
    break;

  case 62: /* value_list: COMMA value value_list  */
#line 567 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 63: /* value: NUMBER  */
#line 578 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2414 "yacc_sql.cpp"
    break;

  case 64: /* value: FLOAT  */
#line 582 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 586 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2434 "yacc_sql.cpp"
    break;

  case 66: /* value: NULL_T  */
#line 592 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 67: /* value: LEFT_BRACKET float_list RIGHT_BRACKET  */
#line 597 "yacc_sql.y"
    {
      (yyval.value) = new Value();
      (yyval.value)->set_vector(*(yyvsp[-1].float_list));
    }
#line 2452 "yacc_sql.cpp"
    break;

  case 68: /* float_list: %empty  */
#line 604 "yacc_sql.y"
    { (yyval.float_list) = nullptr;}
#line 2458 "yacc_sql.cpp"
    break;

  case 69: /* float_list: FLOAT  */
#line 606 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].floats));
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 70: /* float_list: NUMBER  */
#line 611 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].number));
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 71: /* float_list: NUMBER COMMA float_list  */
#line 616 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].number));
    }
#line 2489 "yacc_sql.cpp"
    break;

  case 72: /* float_list: FLOAT COMMA float_list  */
#line 625 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].floats));
    }
#line 2502 "yacc_sql.cpp"
    break;

  case 73: /* storage_format: %empty  */
#line 637 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 74: /* storage_format: STORAGE FORMAT EQ ID  */
#line 641 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 75: /* delete_stmt: DELETE FROM ID where  */
#line 648 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2532 "yacc_sql.cpp"
    break;

  case 76: /* update_stmt: UPDATE ID SET update_unite_list where  */
#line 660 "yacc_sql.y"
    {
      printf("解析update语句");
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.table_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_unites.swap(*(yyvsp[-1].update_unite_list));
      if( (yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      }
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 77: /* update_unite_list: update_unite  */
#line 672 "yacc_sql.y"
    {
      printf("解析update_unite_list为单个 unite list");
      (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      (yyval.update_unite_list)->push_back(*(yyvsp[0].update_unite));
    }
#line 2556 "yacc_sql.cpp"
    break;

  case 78: /* update_unite_list: update_unite COMMA update_unite_list  */
#line 678 "yacc_sql.y"
    {
      printf("解析不是空的 unite list");
      if((yyvsp[0].update_unite_list) != nullptr){
        (yyval.update_unite_list) = (yyvsp[0].update_unite_list);
      }
      else{
        (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      }
      (yyval.update_unite_list)->push_back(*(yyvsp[-2].update_unite));
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 79: /* update_unite: ID EQ expression  */
#line 691 "yacc_sql.y"
    {
      printf("解析update unite");
      (yyval.update_unite) = new UpdateUnite();
      (yyval.update_unite)->field_name = (yyvsp[-2].string);
      (yyval.update_unite)->expression = (yyvsp[0].expression);
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 80: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 699 "yacc_sql.y"
                                 {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      (yyval.sql_node)->create_view.view_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_view.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 81: /* create_view_stmt: CREATE VIEW ID LBRACE ID attr_name_list RBRACE AS select_stmt  */
#line 705 "yacc_sql.y"
                                                                    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      (yyval.sql_node)->create_view.view_name    = (yyvsp[-6].string);

      std::vector<std::string> *p = (yyvsp[-3].attr_names);
      p->push_back((yyvsp[-4].string));

      (yyval.sql_node)->create_view.attr_names.swap(*p);
      std::reverse((yyval.sql_node)->create_view.attr_names.begin(), (yyval.sql_node)->create_view.attr_names.end());
      (yyval.sql_node)->create_view.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-6].string));
    }
#line 2610 "yacc_sql.cpp"
    break;

  case 82: /* attr_name_list: %empty  */
#line 720 "yacc_sql.y"
    {
      (yyval.attr_names) = nullptr;
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 83: /* attr_name_list: COMMA ID attr_name_list  */
#line 724 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_names) != nullptr) {
        (yyval.attr_names) = (yyvsp[0].attr_names);
      } else {
        (yyval.attr_names) = new std::vector<std::string>;
      }
      (yyval.attr_names)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 84: /* drop_view_stmt: DROP VIEW ID  */
#line 735 "yacc_sql.y"
                {
      //do nothing
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 85: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 740 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 86: /* create_table_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 747 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        (yyval.sql_node)->create_table_select.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      (yyval.sql_node)->create_table_select.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse((yyval.sql_node)->create_table_select.attr_infos.begin(), (yyval.sql_node)->create_table_select.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].string) != nullptr) {
        (yyval.sql_node)->create_table_select.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      }
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 87: /* select_stmt: SELECT expression_list FROM rel_list where group_by having order_by limit_  */
#line 770 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }

      if ((yyvsp[-4].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-4].condition_list));
        delete (yyvsp[-4].condition_list);
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      if((yyvsp[-2].condition_list) != nullptr){
        (yyval.sql_node)->selection.having.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }
      (yyval.sql_node)->selection.join_conditions.swap(join_conditions);
      (yyval.sql_node)->selection.limit_count = (yyvsp[0].number);
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 88: /* calc_stmt: CALC expression_list  */
#line 807 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression  */
#line 816 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 90: /* expression_list: expression COMMA expression_list  */
#line 821 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '+' expression  */
#line 831 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2755 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '+' expression ID  */
#line 834 "yacc_sql.y"
                                  {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
      //expr->set_expr(token_name(sql_string, llocp));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '+' expression AS ID  */
#line 840 "yacc_sql.y"
                                     {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '-' expression  */
#line 845 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '-' expression ID  */
#line 848 "yacc_sql.y"
                                  {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2794 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression '-' expression AS ID  */
#line 853 "yacc_sql.y"
                                     {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '*' expression  */
#line 858 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2812 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression '*' expression ID  */
#line 861 "yacc_sql.y"
                                  {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression '*' expression AS ID  */
#line 866 "yacc_sql.y"
                                     {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2832 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '/' expression  */
#line 871 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression '/' expression ID  */
#line 874 "yacc_sql.y"
                                  {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 102: /* expression: expression '/' expression AS ID  */
#line 879 "yacc_sql.y"
                                     {
      ArithmeticExpr * expr = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(sql_string);
      (yyval.expression) = expr;
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 103: /* expression: LBRACE expression RBRACE  */
#line 884 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 104: /* expression: '-' expression  */
#line 888 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 105: /* expression: value  */
#line 891 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 106: /* expression: rel_attr  */
#line 896 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2898 "yacc_sql.cpp"
    break;

  case 107: /* expression: '*'  */
#line 902 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2906 "yacc_sql.cpp"
    break;

  case 108: /* expression: ID DOT '*'  */
#line 905 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2914 "yacc_sql.cpp"
    break;

  case 109: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 909 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2922 "yacc_sql.cpp"
    break;

  case 110: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 913 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 111: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 917 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2938 "yacc_sql.cpp"
    break;

  case 112: /* expression: SUM LBRACE RBRACE  */
#line 920 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2946 "yacc_sql.cpp"
    break;

  case 113: /* expression: MAX LBRACE RBRACE  */
#line 923 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2954 "yacc_sql.cpp"
    break;

  case 114: /* expression: MIN LBRACE RBRACE  */
#line 926 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2962 "yacc_sql.cpp"
    break;

  case 115: /* expression: AVG LBRACE RBRACE  */
#line 929 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2970 "yacc_sql.cpp"
    break;

  case 116: /* expression: COUNT LBRACE RBRACE  */
#line 932 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2978 "yacc_sql.cpp"
    break;

  case 117: /* expression: SUM LBRACE expression RBRACE  */
#line 935 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2986 "yacc_sql.cpp"
    break;

  case 118: /* expression: SUM LBRACE expression RBRACE ID  */
#line 938 "yacc_sql.y"
                                     {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("SUM", (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 2996 "yacc_sql.cpp"
    break;

  case 119: /* expression: SUM LBRACE expression RBRACE AS ID  */
#line 943 "yacc_sql.y"
                                        {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("SUM", (yyvsp[-3].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 120: /* expression: MAX LBRACE expression RBRACE  */
#line 948 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 121: /* expression: MAX LBRACE expression RBRACE ID  */
#line 951 "yacc_sql.y"
                                     {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MAX", (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3024 "yacc_sql.cpp"
    break;

  case 122: /* expression: MAX LBRACE expression RBRACE AS ID  */
#line 956 "yacc_sql.y"
                                        {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MAX", (yyvsp[-3].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 123: /* expression: MIN LBRACE expression RBRACE  */
#line 961 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 124: /* expression: MIN LBRACE expression RBRACE ID  */
#line 964 "yacc_sql.y"
                                     {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MIN", (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3052 "yacc_sql.cpp"
    break;

  case 125: /* expression: MIN LBRACE expression RBRACE AS ID  */
#line 969 "yacc_sql.y"
                                        {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("MIN", (yyvsp[-3].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 126: /* expression: AVG LBRACE expression RBRACE  */
#line 974 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 127: /* expression: AVG LBRACE expression RBRACE ID  */
#line 977 "yacc_sql.y"
                                     {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("AVG", (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3080 "yacc_sql.cpp"
    break;

  case 128: /* expression: AVG LBRACE expression RBRACE AS ID  */
#line 982 "yacc_sql.y"
                                        {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("AVG", (yyvsp[-3].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3090 "yacc_sql.cpp"
    break;

  case 129: /* expression: COUNT LBRACE expression RBRACE  */
#line 987 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 130: /* expression: COUNT LBRACE expression RBRACE ID  */
#line 990 "yacc_sql.y"
                                       {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("COUNT", (yyvsp[-2].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 131: /* expression: COUNT LBRACE expression RBRACE AS ID  */
#line 995 "yacc_sql.y"
                                          {
      UnboundAggregateExpr *expr = create_aggregate_expression_with_alias("COUNT", (yyvsp[-3].expression), (yyvsp[0].string));
      expr->set_expr(token_name(sql_string, &(yyloc)).c_str());
      (yyval.expression) = expr; 
    }
#line 3118 "yacc_sql.cpp"
    break;

  case 132: /* expression: SUM LBRACE expression_list RBRACE  */
#line 1000 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 3126 "yacc_sql.cpp"
    break;

  case 133: /* expression: SUM LBRACE expression_list RBRACE ID  */
#line 1003 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 3134 "yacc_sql.cpp"
    break;

  case 134: /* expression: SUM LBRACE expression_list RBRACE AS ID  */
#line 1006 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 135: /* expression: MAX LBRACE expression_list RBRACE  */
#line 1009 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 136: /* expression: MAX LBRACE expression_list RBRACE ID  */
#line 1012 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 137: /* expression: MAX LBRACE expression_list RBRACE AS ID  */
#line 1015 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 3166 "yacc_sql.cpp"
    break;

  case 138: /* expression: MIN LBRACE expression_list RBRACE  */
#line 1018 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 139: /* expression: MIN LBRACE expression_list RBRACE ID  */
#line 1021 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 3182 "yacc_sql.cpp"
    break;

  case 140: /* expression: MIN LBRACE expression_list RBRACE AS ID  */
#line 1024 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 3190 "yacc_sql.cpp"
    break;

  case 141: /* expression: AVG LBRACE expression_list RBRACE  */
#line 1027 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 3198 "yacc_sql.cpp"
    break;

  case 142: /* expression: AVG LBRACE expression_list RBRACE ID  */
#line 1030 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 3206 "yacc_sql.cpp"
    break;

  case 143: /* expression: AVG LBRACE expression_list RBRACE AS ID  */
#line 1033 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 3214 "yacc_sql.cpp"
    break;

  case 144: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 1036 "yacc_sql.y"
                                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 3222 "yacc_sql.cpp"
    break;

  case 145: /* expression: COUNT LBRACE expression_list RBRACE ID  */
#line 1039 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 146: /* expression: COUNT LBRACE expression_list RBRACE AS ID  */
#line 1042 "yacc_sql.y"
                                               {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3238 "yacc_sql.cpp"
    break;

  case 147: /* expression: LBRACE select_stmt RBRACE  */
#line 1045 "yacc_sql.y"
                                {
      printf("解析子查询");
      (yyval.expression) = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
    }
#line 3247 "yacc_sql.cpp"
    break;

  case 148: /* expression: LBRACE value value_list RBRACE  */
#line 1049 "yacc_sql.y"
                                    {
      if((yyvsp[-1].value_list) == nullptr){
        (yyvsp[-1].value_list) = new vector<Value>();
      }
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.expression) = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 149: /* rel_attr: ID  */
#line 1059 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3269 "yacc_sql.cpp"
    break;

  case 150: /* rel_attr: ID DOT ID  */
#line 1064 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3281 "yacc_sql.cpp"
    break;

  case 151: /* rel_attr: ID AS ID  */
#line 1071 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3293 "yacc_sql.cpp"
    break;

  case 152: /* rel_attr: '*' ID  */
#line 1078 "yacc_sql.y"
            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3304 "yacc_sql.cpp"
    break;

  case 153: /* rel_attr: '*' AS ID  */
#line 1084 "yacc_sql.y"
               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3315 "yacc_sql.cpp"
    break;

  case 154: /* rel_attr: ID DOT ID AS ID  */
#line 1090 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3329 "yacc_sql.cpp"
    break;

  case 155: /* rel_attr: ID DOT ID ID  */
#line 1099 "yacc_sql.y"
                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 156: /* relation: ID  */
#line 1111 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3351 "yacc_sql.cpp"
    break;

  case 157: /* rel_list: relation  */
#line 1116 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[0].string), (yyvsp[0].string)});
      free((yyvsp[0].string));
    }
#line 3361 "yacc_sql.cpp"
    break;

  case 158: /* rel_list: relation COMMA rel_list  */
#line 1121 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-2].string), (yyvsp[-2].string)});
      free((yyvsp[-2].string));
    }
#line 3376 "yacc_sql.cpp"
    break;

  case 159: /* rel_list: relation AS ID  */
#line 1131 "yacc_sql.y"
                    {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-2].string), (yyvsp[0].string)});
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3387 "yacc_sql.cpp"
    break;

  case 160: /* rel_list: relation ID  */
#line 1137 "yacc_sql.y"
                 {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-1].string), (yyvsp[0].string)});
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3398 "yacc_sql.cpp"
    break;

  case 161: /* rel_list: relation AS ID COMMA rel_list  */
#line 1143 "yacc_sql.y"
                                   {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-4].string), (yyvsp[-2].string)});
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 3413 "yacc_sql.cpp"
    break;

  case 162: /* rel_list: relation ID COMMA rel_list  */
#line 1153 "yacc_sql.y"
                                {
      if ((yyvsp[0].relation_list)!= nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-3].string), (yyvsp[-2].string)});
      free((yyvsp[-3].string));
      free((yyvsp[-2].string));
    }
#line 3428 "yacc_sql.cpp"
    break;

  case 163: /* rel_list: join_in  */
#line 1163 "yacc_sql.y"
             {
      if((yyval.relation_list) == nullptr){
        (yyval.relation_list) = (yyvsp[0].join_list);
      }else{
        //$$->insert($$->begin(), $1);
        (yyval.relation_list) = (yyvsp[0].join_list);
      }
    }
#line 3441 "yacc_sql.cpp"
    break;

  case 164: /* join_in_right_list: INNER JOIN relation ON condition_list  */
#line 1175 "yacc_sql.y"
                                        {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-2].string), (yyvsp[-2].string)});
  }
#line 3451 "yacc_sql.cpp"
    break;

  case 165: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list  */
#line 1180 "yacc_sql.y"
                                                {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-4].string), (yyvsp[-2].string)});
  }
#line 3461 "yacc_sql.cpp"
    break;

  case 166: /* join_in_right_list: INNER JOIN relation  */
#line 1185 "yacc_sql.y"
                         {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[0].string),(yyvsp[0].string)});
  }
#line 3472 "yacc_sql.cpp"
    break;

  case 167: /* join_in_right_list: INNER JOIN relation AS ID  */
#line 1191 "yacc_sql.y"
                               {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[-2].string),(yyvsp[0].string)});
  }
#line 3483 "yacc_sql.cpp"
    break;

  case 168: /* join_in_right_list: INNER JOIN relation join_in_right_list  */
#line 1197 "yacc_sql.y"
                                           {
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
      free((yyvsp[-1].string));
  }
#line 3499 "yacc_sql.cpp"
    break;

  case 169: /* join_in_right_list: INNER JOIN relation AS ID join_in_right_list  */
#line 1208 "yacc_sql.y"
                                                 {
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-1].string)});
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
  }
#line 3516 "yacc_sql.cpp"
    break;

  case 170: /* join_in_right_list: INNER JOIN relation ON condition_list join_in_right_list  */
#line 1220 "yacc_sql.y"
                                                            {
    join_conditions.push_back((yyvsp[-1].condition_list));
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-3].string)});
      free((yyvsp[-3].string));
  }
#line 3531 "yacc_sql.cpp"
    break;

  case 171: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list join_in_right_list  */
#line 1230 "yacc_sql.y"
                                                                  {
    join_conditions.push_back((yyvsp[-1].condition_list));
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::unordered_map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-5].string), (yyvsp[-3].string)});
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
  }
#line 3547 "yacc_sql.cpp"
    break;

  case 172: /* join_in: relation join_in_right_list  */
#line 1244 "yacc_sql.y"
                             {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
    free((yyvsp[-1].string));
  }
#line 3561 "yacc_sql.cpp"
    break;

  case 173: /* join_in: relation AS ID join_in_right_list  */
#line 1253 "yacc_sql.y"
                                     {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-1].string)});
    free((yyvsp[-3].string));
    free((yyvsp[-1].string));
  }
#line 3576 "yacc_sql.cpp"
    break;

  case 174: /* limit_: %empty  */
#line 1266 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3584 "yacc_sql.cpp"
    break;

  case 175: /* limit_: LIMIT number  */
#line 1269 "yacc_sql.y"
                  {
        (yyval.number) = (yyvsp[0].number);
    }
#line 3592 "yacc_sql.cpp"
    break;

  case 176: /* order_by_field: rel_attr DESC  */
#line 1274 "yacc_sql.y"
                  {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3603 "yacc_sql.cpp"
    break;

  case 177: /* order_by_field: rel_attr  */
#line 1280 "yacc_sql.y"
             {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3614 "yacc_sql.cpp"
    break;

  case 178: /* order_by_field: rel_attr ASC  */
#line 1285 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
      }
#line 3625 "yacc_sql.cpp"
    break;

  case 179: /* order_by_field: expression  */
#line 1291 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3633 "yacc_sql.cpp"
    break;

  case 180: /* order_by_field_list: order_by_field  */
#line 1296 "yacc_sql.y"
                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>> ;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
      //delete $1;
    }
#line 3643 "yacc_sql.cpp"
    break;

  case 181: /* order_by_field_list: order_by_field COMMA order_by_field_list  */
#line 1301 "yacc_sql.y"
                                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    }
#line 3653 "yacc_sql.cpp"
    break;

  case 182: /* order_by: %empty  */
#line 1308 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3661 "yacc_sql.cpp"
    break;

  case 183: /* order_by: ORDER BY order_by_field_list  */
#line 1312 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      }else{
        (yyval.expression_list) = nullptr;
      }
    }
#line 3673 "yacc_sql.cpp"
    break;

  case 184: /* where: %empty  */
#line 1322 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3681 "yacc_sql.cpp"
    break;

  case 185: /* where: WHERE condition_list  */
#line 1325 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3689 "yacc_sql.cpp"
    break;

  case 186: /* condition_list: %empty  */
#line 1331 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3697 "yacc_sql.cpp"
    break;

  case 187: /* condition_list: condition  */
#line 1334 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3707 "yacc_sql.cpp"
    break;

  case 188: /* condition_list: condition AND condition_list  */
#line 1339 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3717 "yacc_sql.cpp"
    break;

  case 189: /* condition_list: condition OR condition_list  */
#line 1344 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction_with_or = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3728 "yacc_sql.cpp"
    break;

  case 190: /* condition: rel_attr comp_op value  */
#line 1353 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 3744 "yacc_sql.cpp"
    break;

  case 191: /* condition: value comp_op value  */
#line 1365 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3760 "yacc_sql.cpp"
    break;

  case 192: /* condition: rel_attr comp_op rel_attr  */
#line 1377 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 3776 "yacc_sql.cpp"
    break;

  case 193: /* condition: value comp_op rel_attr  */
#line 1389 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 3792 "yacc_sql.cpp"
    break;

  case 194: /* condition: expression comp_op value  */
#line 1401 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3807 "yacc_sql.cpp"
    break;

  case 195: /* condition: value comp_op expression  */
#line 1412 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
    }
#line 3822 "yacc_sql.cpp"
    break;

  case 196: /* condition: expression comp_op rel_attr  */
#line 1423 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3837 "yacc_sql.cpp"
    break;

  case 197: /* condition: rel_attr comp_op expression  */
#line 1434 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3852 "yacc_sql.cpp"
    break;

  case 198: /* condition: expression comp_op expression  */
#line 1445 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3865 "yacc_sql.cpp"
    break;

  case 199: /* comp_op: EQ  */
#line 1456 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3871 "yacc_sql.cpp"
    break;

  case 200: /* comp_op: LT  */
#line 1457 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3877 "yacc_sql.cpp"
    break;

  case 201: /* comp_op: GT  */
#line 1458 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3883 "yacc_sql.cpp"
    break;

  case 202: /* comp_op: LE  */
#line 1459 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3889 "yacc_sql.cpp"
    break;

  case 203: /* comp_op: GE  */
#line 1460 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3895 "yacc_sql.cpp"
    break;

  case 204: /* comp_op: NE  */
#line 1461 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3901 "yacc_sql.cpp"
    break;

  case 205: /* comp_op: LIKE  */
#line 1462 "yacc_sql.y"
           { (yyval.comp) = LIKE_TO; }
#line 3907 "yacc_sql.cpp"
    break;

  case 206: /* comp_op: NOT LIKE  */
#line 1463 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_TO; }
#line 3913 "yacc_sql.cpp"
    break;

  case 207: /* comp_op: IS_  */
#line 1464 "yacc_sql.y"
          { (yyval.comp) = IS ;}
#line 3919 "yacc_sql.cpp"
    break;

  case 208: /* comp_op: IS_ NOT  */
#line 1465 "yacc_sql.y"
              { (yyval.comp) = IS_NOT ;}
#line 3925 "yacc_sql.cpp"
    break;

  case 209: /* comp_op: IN_T  */
#line 1466 "yacc_sql.y"
           { (yyval.comp) = IN ; }
#line 3931 "yacc_sql.cpp"
    break;

  case 210: /* comp_op: NOT IN_T  */
#line 1467 "yacc_sql.y"
               { (yyval.comp) = NOT_IN ; }
#line 3937 "yacc_sql.cpp"
    break;

  case 211: /* comp_op: EXISTS_T  */
#line 1468 "yacc_sql.y"
               { (yyval.comp) = EXISTS ; }
#line 3943 "yacc_sql.cpp"
    break;

  case 212: /* comp_op: NOT EXISTS_T  */
#line 1469 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXISTS ; }
#line 3949 "yacc_sql.cpp"
    break;

  case 213: /* group_by: %empty  */
#line 1474 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3957 "yacc_sql.cpp"
    break;

  case 214: /* group_by: GROUP BY expression_list  */
#line 1478 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3967 "yacc_sql.cpp"
    break;

  case 215: /* having: %empty  */
#line 1487 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3975 "yacc_sql.cpp"
    break;

  case 216: /* having: HAVING condition_list  */
#line 1491 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3985 "yacc_sql.cpp"
    break;

  case 217: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1500 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3999 "yacc_sql.cpp"
    break;

  case 218: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1513 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 4008 "yacc_sql.cpp"
    break;

  case 219: /* set_variable_stmt: SET ID EQ value  */
#line 1521 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 4020 "yacc_sql.cpp"
    break;


#line 4024 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1533 "yacc_sql.y"

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
