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
  YYSYMBOL_INDEX = 11,                     /* INDEX  */
  YYSYMBOL_CALC = 12,                      /* CALC  */
  YYSYMBOL_SELECT = 13,                    /* SELECT  */
  YYSYMBOL_DESC = 14,                      /* DESC  */
  YYSYMBOL_ASC = 15,                       /* ASC  */
  YYSYMBOL_SHOW = 16,                      /* SHOW  */
  YYSYMBOL_SYNC = 17,                      /* SYNC  */
  YYSYMBOL_INSERT = 18,                    /* INSERT  */
  YYSYMBOL_DELETE = 19,                    /* DELETE  */
  YYSYMBOL_UPDATE = 20,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 21,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 22,                    /* RBRACE  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 24,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 25,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 26,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 27,                     /* INT_T  */
  YYSYMBOL_STRING_T = 28,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 29,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 30,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_VECTOR_T = 32,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INTO = 36,                      /* INTO  */
  YYSYMBOL_VALUES = 37,                    /* VALUES  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_WHERE = 39,                     /* WHERE  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_SET = 42,                       /* SET  */
  YYSYMBOL_ON = 43,                        /* ON  */
  YYSYMBOL_LOAD = 44,                      /* LOAD  */
  YYSYMBOL_DATA = 45,                      /* DATA  */
  YYSYMBOL_INFILE = 46,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 47,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 48,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 49,                    /* FORMAT  */
  YYSYMBOL_EQ = 50,                        /* EQ  */
  YYSYMBOL_LT = 51,                        /* LT  */
  YYSYMBOL_GT = 52,                        /* GT  */
  YYSYMBOL_LE = 53,                        /* LE  */
  YYSYMBOL_GE = 54,                        /* GE  */
  YYSYMBOL_NE = 55,                        /* NE  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_LIKE = 57,                      /* LIKE  */
  YYSYMBOL_IS_ = 58,                       /* IS_  */
  YYSYMBOL_NULL_T = 59,                    /* NULL_T  */
  YYSYMBOL_MAX = 60,                       /* MAX  */
  YYSYMBOL_MIN = 61,                       /* MIN  */
  YYSYMBOL_AVG = 62,                       /* AVG  */
  YYSYMBOL_SUM = 63,                       /* SUM  */
  YYSYMBOL_COUNT = 64,                     /* COUNT  */
  YYSYMBOL_HAVING = 65,                    /* HAVING  */
  YYSYMBOL_INNER = 66,                     /* INNER  */
  YYSYMBOL_JOIN = 67,                      /* JOIN  */
  YYSYMBOL_AS = 68,                        /* AS  */
  YYSYMBOL_UNIQUE = 69,                    /* UNIQUE  */
  YYSYMBOL_WITH = 70,                      /* WITH  */
  YYSYMBOL_DISTANCE = 71,                  /* DISTANCE  */
  YYSYMBOL_TYPE = 72,                      /* TYPE  */
  YYSYMBOL_LISTS = 73,                     /* LISTS  */
  YYSYMBOL_PROBES = 74,                    /* PROBES  */
  YYSYMBOL_LIMIT = 75,                     /* LIMIT  */
  YYSYMBOL_LEFT_BRACKET = 76,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 77,             /* RIGHT_BRACKET  */
  YYSYMBOL_L2_DISTANCE = 78,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 79,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 80,             /* INNER_PRODUCT  */
  YYSYMBOL_IN_T = 81,                      /* IN_T  */
  YYSYMBOL_EXISTS_T = 82,                  /* EXISTS_T  */
  YYSYMBOL_NUMBER = 83,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 84,                     /* FLOAT  */
  YYSYMBOL_ID = 85,                        /* ID  */
  YYSYMBOL_SSS = 86,                       /* SSS  */
  YYSYMBOL_87_ = 87,                       /* '+'  */
  YYSYMBOL_88_ = 88,                       /* '-'  */
  YYSYMBOL_89_ = 89,                       /* '*'  */
  YYSYMBOL_90_ = 90,                       /* '/'  */
  YYSYMBOL_UMINUS = 91,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 92,                  /* $accept  */
  YYSYMBOL_commands = 93,                  /* commands  */
  YYSYMBOL_command_wrapper = 94,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 95,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 96,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 97,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 98,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 99,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 100,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 101,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 102,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 103,          /* desc_table_stmt  */
  YYSYMBOL_index_type = 104,               /* index_type  */
  YYSYMBOL_create_index_stmt = 105,        /* create_index_stmt  */
  YYSYMBOL_distance_type = 106,            /* distance_type  */
  YYSYMBOL_create_index_vector_stmt = 107, /* create_index_vector_stmt  */
  YYSYMBOL_drop_index_stmt = 108,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 109,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 110,            /* attr_def_list  */
  YYSYMBOL_attr_def = 111,                 /* attr_def  */
  YYSYMBOL_not_null = 112,                 /* not_null  */
  YYSYMBOL_number = 113,                   /* number  */
  YYSYMBOL_type = 114,                     /* type  */
  YYSYMBOL_insert_stmt = 115,              /* insert_stmt  */
  YYSYMBOL_value_list = 116,               /* value_list  */
  YYSYMBOL_value = 117,                    /* value  */
  YYSYMBOL_float_list = 118,               /* float_list  */
  YYSYMBOL_storage_format = 119,           /* storage_format  */
  YYSYMBOL_delete_stmt = 120,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 121,              /* update_stmt  */
  YYSYMBOL_update_unite_list = 122,        /* update_unite_list  */
  YYSYMBOL_update_unite = 123,             /* update_unite  */
  YYSYMBOL_create_table_select_stmt = 124, /* create_table_select_stmt  */
  YYSYMBOL_select_stmt = 125,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 126,                /* calc_stmt  */
  YYSYMBOL_expression_list = 127,          /* expression_list  */
  YYSYMBOL_expression = 128,               /* expression  */
  YYSYMBOL_rel_attr = 129,                 /* rel_attr  */
  YYSYMBOL_relation = 130,                 /* relation  */
  YYSYMBOL_rel_list = 131,                 /* rel_list  */
  YYSYMBOL_join_in_right_list = 132,       /* join_in_right_list  */
  YYSYMBOL_join_in = 133,                  /* join_in  */
  YYSYMBOL_limit_ = 134,                   /* limit_  */
  YYSYMBOL_order_by_field = 135,           /* order_by_field  */
  YYSYMBOL_order_by_field_list = 136,      /* order_by_field_list  */
  YYSYMBOL_order_by = 137,                 /* order_by  */
  YYSYMBOL_where = 138,                    /* where  */
  YYSYMBOL_condition_list = 139,           /* condition_list  */
  YYSYMBOL_condition = 140,                /* condition  */
  YYSYMBOL_comp_op = 141,                  /* comp_op  */
  YYSYMBOL_group_by = 142,                 /* group_by  */
  YYSYMBOL_having = 143,                   /* having  */
  YYSYMBOL_load_data_stmt = 144,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 145,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 146,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 147             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   547

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  393

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
       2,     2,    89,    87,     2,    88,     2,    90,     2,     2,
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
      85,    86,    91
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   282,   282,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   315,   321,   326,   332,   338,
     344,   350,   357,   363,   371,   373,   378,   395,   398,   401,
     406,   425,   435,   459,   462,   475,   485,   501,   502,   503,
     506,   509,   510,   511,   512,   513,   514,   517,   534,   537,
     548,   552,   556,   562,   566,   574,   575,   580,   585,   594,
     607,   610,   617,   629,   641,   647,   660,   669,   675,   698,
     735,   744,   749,   760,   763,   766,   769,   772,   775,   778,
     781,   784,   787,   790,   793,   796,   800,   803,   808,   814,
     817,   820,   824,   828,   832,   835,   838,   841,   844,   847,
     850,   853,   856,   859,   862,   865,   868,   871,   874,   877,
     880,   883,   886,   889,   892,   895,   898,   901,   904,   907,
     910,   913,   916,   919,   922,   925,   928,   931,   934,   937,
     941,   951,   956,   963,   970,   976,   982,   991,  1003,  1008,
    1013,  1023,  1029,  1035,  1045,  1055,  1067,  1072,  1077,  1083,
    1089,  1100,  1112,  1122,  1136,  1145,  1158,  1161,  1166,  1172,
    1177,  1183,  1188,  1193,  1200,  1203,  1214,  1217,  1223,  1226,
    1231,  1236,  1244,  1256,  1268,  1280,  1292,  1303,  1314,  1325,
    1336,  1348,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1366,  1369,  1379,  1382,  1391,
    1404,  1412,  1422,  1423
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
  "BY", "CREATE", "DROP", "ORDER", "TABLE", "TABLES", "INDEX", "CALC",
  "SELECT", "DESC", "ASC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "VECTOR_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ",
  "LT", "GT", "LE", "GE", "NE", "NOT", "LIKE", "IS_", "NULL_T", "MAX",
  "MIN", "AVG", "SUM", "COUNT", "HAVING", "INNER", "JOIN", "AS", "UNIQUE",
  "WITH", "DISTANCE", "TYPE", "LISTS", "PROBES", "LIMIT", "LEFT_BRACKET",
  "RIGHT_BRACKET", "L2_DISTANCE", "COSINE_DISTANCE", "INNER_PRODUCT",
  "IN_T", "EXISTS_T", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt", "index_type",
  "create_index_stmt", "distance_type", "create_index_vector_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "not_null", "number", "type", "insert_stmt", "value_list", "value",
  "float_list", "storage_format", "delete_stmt", "update_stmt",
  "update_unite_list", "update_unite", "create_table_select_stmt",
  "select_stmt", "calc_stmt", "expression_list", "expression", "rel_attr",
  "relation", "rel_list", "join_in_right_list", "join_in", "limit_",
  "order_by_field", "order_by_field_list", "order_by", "where",
  "condition_list", "condition", "comp_op", "group_by", "having",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-268)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     488,    17,   164,   404,   404,   -77,     9,  -268,    -7,   -14,
     -28,  -268,  -268,  -268,  -268,  -268,    28,    57,   488,    73,
      90,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,    32,   140,  -268,   167,   108,   127,   137,
    -268,   206,   212,   217,   224,   244,   125,   265,   267,   288,
    -268,  -268,   -25,  -268,   404,   -45,  -268,  -268,   116,  -268,
     257,  -268,  -268,   238,   246,   293,   286,   299,  -268,  -268,
    -268,  -268,   -15,   259,   262,  -268,   305,    42,   333,    38,
     218,   254,   298,   329,   373,   340,   341,   279,   404,   404,
     404,   -69,   280,  -268,   281,  -268,   404,   404,   404,   404,
     404,   282,   332,   331,   287,    88,   285,   290,   360,   336,
     337,   300,    88,   380,  -268,  -268,  -268,   381,    -9,  -268,
     382,    -5,  -268,   384,    44,  -268,   388,    48,  -268,   389,
      54,   125,   125,  -268,   147,   154,   161,   -40,  -268,  -268,
    -268,  -268,    72,   178,    78,    80,  -268,   126,   331,  -268,
     395,   404,  -268,   370,   331,   396,  -268,   385,   369,   399,
    -268,   338,   339,  -268,   403,  -268,    91,   139,   179,   184,
     198,   240,   242,   243,   256,   261,  -268,  -268,   404,   404,
     404,   342,  -268,   343,  -268,   344,  -268,   345,  -268,   346,
    -268,   282,   371,   354,   417,  -268,   437,    88,   -19,   203,
     -19,  -268,   230,   404,  -268,   287,   433,  -268,  -268,  -268,
    -268,  -268,  -268,   -12,   290,   421,   423,   424,  -268,   361,
    -268,   362,  -268,   363,  -268,   365,  -268,   375,  -268,   386,
    -268,   387,  -268,   390,  -268,   391,  -268,   392,  -268,    79,
      93,   101,  -268,  -268,  -268,  -268,  -268,  -268,   282,    -8,
     282,   449,   405,   403,  -268,  -268,  -268,  -268,  -268,  -268,
     -27,  -268,   413,  -268,  -268,   404,   404,   404,   404,   404,
      66,  -268,   393,   372,   414,  -268,  -268,   399,   426,   282,
     282,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,   -18,   282,  -268,  -268,   404,   404,
     471,   459,  -268,  -268,  -268,  -268,  -268,    66,  -268,  -268,
      66,  -268,  -268,    66,  -268,  -268,  -268,  -268,  -268,   463,
    -268,  -268,   442,   360,   464,   474,   404,   412,  -268,  -268,
    -268,  -268,   493,   428,  -268,     0,   460,  -268,   429,  -268,
     443,     8,   404,   372,  -268,  -268,   430,   490,  -268,   404,
    -268,    66,   204,   494,  -268,  -268,  -268,   444,   443,  -268,
    -268,   404,   468,  -268,  -268,   434,   497,   452,   475,   274,
    -268,  -268,  -268,   501,   453,   477,   445,   506,   457,   483,
     451,   514,  -268
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     212,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,    24,     4,     3,
      19,    20,    21,     0,     0,    35,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,    65,     0,     0,     0,
      60,    61,   141,    62,     0,    99,    97,    80,    81,    98,
       0,    33,    32,     0,     0,     0,     0,     0,   210,     1,
     213,     2,     0,     0,     0,    31,     0,    97,     0,     0,
       0,     0,     0,     0,     0,    67,    66,     0,     0,     0,
       0,     0,     0,    96,     0,   144,     0,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   139,    95,   105,     0,     0,   106,
       0,     0,   107,     0,     0,   104,     0,     0,   108,     0,
       0,    65,    65,    64,     0,     0,     0,   142,   100,   143,
     145,    82,    83,    86,    89,    92,   148,   149,   176,   155,
       0,   178,    72,     0,   176,    74,   211,     0,     0,    43,
      77,     0,     0,    41,    58,   140,   127,   112,   130,   115,
     133,   118,   124,   109,   136,   121,    68,    69,     0,     0,
       0,     0,   147,     0,    84,     0,    87,     0,    90,     0,
      93,     0,     0,     0,   152,   164,   205,     0,    97,     0,
      98,   177,   179,     0,    73,     0,     0,    51,    52,    53,
      54,    55,    56,    47,     0,     0,     0,     0,    59,     0,
     128,     0,   113,     0,   131,     0,   116,     0,   134,     0,
     119,     0,   125,     0,   110,     0,   137,     0,   122,     0,
       0,     0,   146,    85,    88,    91,    94,   150,     0,   151,
       0,     0,   207,    58,   191,   192,   193,   194,   195,   196,
       0,   197,   199,   201,   203,     0,     0,     0,   178,   178,
      76,    75,     0,     0,     0,    48,    46,    43,    70,     0,
       0,   129,   114,   132,   117,   135,   120,   126,   111,   138,
     123,   101,   102,   103,   158,     0,   165,   154,     0,   178,
     174,     0,   198,   202,   204,   200,    97,   187,    98,    97,
     190,    98,    97,   189,    98,   180,   181,   209,    50,     0,
      49,    44,     0,    42,     0,     0,   178,     0,   160,   153,
     206,   208,     0,   166,    57,    47,     0,    78,     0,    36,
     156,   159,     0,     0,    79,    45,     0,     0,   162,   178,
     161,   171,    98,   172,   175,   167,    71,     0,   157,   168,
     170,     0,     0,   163,   173,     0,     0,     0,     0,     0,
      37,    38,    39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -268,  -268,   519,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,   251,   315,
     195,   188,  -268,  -268,  -169,   -47,   158,  -268,  -268,  -268,
     327,  -268,  -268,   -46,  -268,    18,    -3,  -157,   289,  -160,
    -252,  -268,  -268,  -268,   172,  -268,  -137,  -267,  -268,   112,
    -268,  -268,  -268,  -268,  -268,  -268
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    46,    30,   383,    31,    32,    33,   225,   169,
     286,   329,   223,    34,   123,    66,    97,   333,    35,    36,
     164,   165,    37,    38,    39,    67,   209,    69,   157,   158,
     205,   159,   354,   363,   364,   343,   162,   211,   212,   275,
     262,   310,    40,    41,    42,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    68,    87,    88,   210,   228,   117,   306,    71,   283,
     101,   325,   326,   177,   106,   305,   147,   179,   106,    72,
     148,   206,    70,   104,    74,   336,    43,   214,   191,    73,
     312,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     105,   257,   341,   102,   284,   192,    89,   285,   202,    44,
     337,   359,   338,   118,   313,   314,   284,    75,   202,   285,
     125,   103,   273,   274,   -58,   122,   181,   106,   166,   350,
     183,   106,   170,    79,   202,   174,   185,   106,   107,   108,
     109,   110,   107,   108,   109,   110,    45,   128,   131,   134,
     137,   140,   368,    80,   311,   144,   145,   146,   358,   360,
     307,   301,    77,    68,   152,   153,   154,   155,   127,   130,
     133,   136,   139,    76,   208,   302,   373,    82,   318,   321,
     324,   210,   210,   303,   151,   107,   108,   109,   110,   334,
     335,   107,   108,   109,   110,   107,   108,   109,   110,   106,
     193,   107,   108,   109,   110,   339,   197,    50,   199,   201,
       4,    83,   210,   107,   108,   109,   110,   194,    49,   229,
     263,   109,   110,   198,    56,   200,   107,   108,   109,   110,
     188,    60,    61,    47,    63,    48,   230,   189,    84,   210,
     107,   108,   109,   110,   190,   249,   250,   251,   107,   108,
     109,   110,   202,    85,   203,   362,    50,    51,    52,    53,
      54,    55,   210,   107,   108,   109,   110,   231,    95,    96,
     280,   204,    86,    56,   362,    57,    58,    59,   369,   370,
      60,    61,    62,    63,   232,    64,    65,    90,   316,   319,
     322,   208,   208,    91,   107,   108,   109,   110,    92,    49,
     126,   107,   108,   109,   110,    93,   195,   233,   107,   108,
     109,   110,   235,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   208,   196,   234,    94,   237,   109,   110,   236,
     278,   279,   317,   320,   323,    49,   129,    50,    51,    52,
      53,    54,    55,   238,   273,   274,    98,   347,    99,   208,
     107,   108,   109,   110,    56,   111,    57,    58,    59,   186,
     187,    60,    61,    62,    63,    68,    64,    65,   239,   100,
     241,   243,   208,    50,    51,    52,    53,    54,    55,    49,
     132,   276,   277,   112,   245,   240,   340,   242,   244,   247,
      56,   113,    57,    58,    59,   114,   115,    60,    61,    62,
      63,   246,    64,    65,   119,   116,   248,   120,   121,   361,
      49,   135,   380,   381,   382,   124,   143,    50,    51,    52,
      53,    54,    55,   141,   142,   149,   150,   156,   361,   160,
     161,   167,   163,     4,    56,   168,    57,    58,    59,   171,
     172,    60,    61,    62,    63,   173,    64,    65,    50,    51,
      52,    53,    54,    55,    49,   138,   217,   218,   219,   220,
     221,   222,   175,   176,   178,    56,   180,    57,    58,    59,
     182,   184,    60,    61,    62,    63,   207,    64,    65,   215,
     213,   216,   224,   226,   227,    49,   122,   252,   253,   254,
     255,   256,    50,    51,    52,    53,    54,    55,   258,   259,
     260,   261,   282,   288,   289,   290,   291,   292,   293,    56,
     294,    57,    58,    59,   308,   328,    60,    61,    62,    63,
     295,    64,    65,    50,    51,    52,    53,    54,    55,   315,
     309,   296,   297,   330,   332,   298,   299,   300,   327,   342,
      56,   344,    57,    58,    59,   345,   348,    60,    61,    62,
      63,   346,    64,    65,     1,     2,   349,   351,   352,   357,
       3,     4,     5,   353,     6,     7,     8,     9,    10,   202,
     356,   367,    11,    12,    13,   366,   372,   371,   375,   376,
     377,    14,    15,   378,   384,   379,   385,   386,   387,   388,
      16,   389,    17,   390,   391,    18,   392,    78,   331,   287,
     355,   365,   281,   374,     0,     0,     0,   304
};

static const yytype_int16 yycheck[] =
{
       3,     4,    49,    49,   161,   174,    21,   259,    85,    21,
      35,   278,   279,    22,    23,    23,    85,    22,    23,    10,
      89,   158,     4,    68,    38,    43,     9,   164,    68,    36,
      57,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      85,   201,   309,    68,    56,    85,    49,    59,    66,    32,
      68,    43,   304,    68,    81,    82,    56,    85,    66,    59,
      22,    64,    81,    82,    22,    23,    22,    23,   115,   336,
      22,    23,   118,     0,    66,   122,    22,    23,    87,    88,
      89,    90,    87,    88,    89,    90,    69,    90,    91,    92,
      93,    94,   359,     3,   263,    98,    99,   100,   350,   351,
     260,    22,    45,   106,   107,   108,   109,   110,    90,    91,
      92,    93,    94,    85,   161,    22,   368,    85,   275,   276,
     277,   278,   279,    22,   106,    87,    88,    89,    90,   289,
     290,    87,    88,    89,    90,    87,    88,    89,    90,    23,
      68,    87,    88,    89,    90,   305,    68,    59,    68,    23,
      13,    11,   309,    87,    88,    89,    90,    85,    21,    68,
     207,    89,    90,    85,    76,    85,    87,    88,    89,    90,
      23,    83,    84,     9,    86,    11,    85,    23,    11,   336,
      87,    88,    89,    90,    23,   188,   189,   190,    87,    88,
      89,    90,    66,    85,    68,   352,    59,    60,    61,    62,
      63,    64,   359,    87,    88,    89,    90,    68,    83,    84,
     213,    85,    85,    76,   371,    78,    79,    80,    14,    15,
      83,    84,    85,    86,    85,    88,    89,    21,   275,   276,
     277,   278,   279,    21,    87,    88,    89,    90,    21,    21,
      22,    87,    88,    89,    90,    21,    68,    68,    87,    88,
      89,    90,    68,    50,    51,    52,    53,    54,    55,    56,
      57,    58,   309,    85,    85,    21,    68,    89,    90,    85,
      40,    41,   275,   276,   277,    21,    22,    59,    60,    61,
      62,    63,    64,    85,    81,    82,    21,   333,    21,   336,
      87,    88,    89,    90,    76,    38,    78,    79,    80,   141,
     142,    83,    84,    85,    86,   308,    88,    89,    68,    21,
      68,    68,   359,    59,    60,    61,    62,    63,    64,    21,
      22,   209,   210,    85,    68,    85,   308,    85,    85,    68,
      76,    85,    78,    79,    80,    42,    50,    83,    84,    85,
      86,    85,    88,    89,    85,    46,    85,    85,    43,   352,
      21,    22,    78,    79,    80,    22,    77,    59,    60,    61,
      62,    63,    64,    23,    23,    85,    85,    85,   371,    37,
      39,    86,    85,    13,    76,    85,    78,    79,    80,    43,
      43,    83,    84,    85,    86,    85,    88,    89,    59,    60,
      61,    62,    63,    64,    21,    22,    27,    28,    29,    30,
      31,    32,    22,    22,    22,    76,    22,    78,    79,    80,
      22,    22,    83,    84,    85,    86,    21,    88,    89,    23,
      50,    36,    23,    85,    85,    21,    23,    85,    85,    85,
      85,    85,    59,    60,    61,    62,    63,    64,    67,    85,
      23,     4,     9,    22,    21,    21,    85,    85,    85,    76,
      85,    78,    79,    80,     5,    83,    83,    84,    85,    86,
      85,    88,    89,    59,    60,    61,    62,    63,    64,    56,
      65,    85,    85,    59,    48,    85,    85,    85,    85,     8,
      76,    22,    78,    79,    80,    22,    22,    83,    84,    85,
      86,    49,    88,    89,     6,     7,    22,    85,     5,    70,
      12,    13,    14,    75,    16,    17,    18,    19,    20,    66,
      50,    21,    24,    25,    26,    85,    72,    23,    50,    85,
      23,    33,    34,    71,    23,    50,    73,    50,    83,    23,
      42,    74,    44,    50,    83,    47,    22,    18,   287,   224,
     345,   353,   215,   371,    -1,    -1,    -1,   258
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    12,    13,    14,    16,    17,    18,    19,
      20,    24,    25,    26,    33,    34,    42,    44,    47,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     105,   107,   108,   109,   115,   120,   121,   124,   125,   126,
     144,   145,   146,     9,    32,    69,   104,     9,    11,    21,
      59,    60,    61,    62,    63,    64,    76,    78,    79,    80,
      83,    84,    85,    86,    88,    89,   117,   127,   128,   129,
     127,    85,    10,    36,    38,    85,    85,    45,    94,     0,
       3,   147,    85,    11,    11,    85,    85,   117,   125,   128,
      21,    21,    21,    21,    21,    83,    84,   118,    21,    21,
      21,    35,    68,   128,    68,    85,    23,    87,    88,    89,
      90,    38,    85,    85,    42,    50,    46,    21,    68,    85,
      85,    43,    23,   116,    22,    22,    22,   127,   128,    22,
     127,   128,    22,   127,   128,    22,   127,   128,    22,   127,
     128,    23,    23,    77,   128,   128,   128,    85,    89,    85,
      85,   127,   128,   128,   128,   128,    85,   130,   131,   133,
      37,    39,   138,    85,   122,   123,   117,    86,    85,   111,
     125,    43,    43,    85,   117,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,   118,   118,    23,    23,
      23,    68,    85,    68,    85,    68,    85,    68,    85,    68,
      85,    23,    66,    68,    85,   132,   138,    21,   117,   128,
     129,   139,   140,    50,   138,    23,    36,    27,    28,    29,
      30,    31,    32,   114,    23,   110,    85,    85,   116,    68,
      85,    68,    85,    68,    85,    68,    85,    68,    85,    68,
      85,    68,    85,    68,    85,    68,    85,    68,    85,   128,
     128,   128,    85,    85,    85,    85,    85,   131,    67,    85,
      23,     4,   142,   117,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    81,    82,   141,   141,   141,    40,    41,
     128,   122,     9,    21,    56,    59,   112,   111,    22,    21,
      21,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    22,    22,    22,   130,    23,   132,   131,     5,    65,
     143,   116,    57,    81,    82,    56,   117,   128,   129,   117,
     128,   129,   117,   128,   129,   139,   139,    85,    83,   113,
      59,   110,    48,   119,   131,   131,    43,    68,   132,   131,
     127,   139,     8,   137,    22,    22,    49,   125,    22,    22,
     139,    85,     5,    75,   134,   112,    50,    70,   132,    43,
     132,   128,   129,   135,   136,   113,    85,    21,   139,    14,
      15,    23,    72,   132,   136,    50,    85,    23,    71,    50,
      78,    79,    80,   106,    23,    73,    50,    83,    23,    74,
      50,    83,    22
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   104,   105,   106,   106,   106,
     107,   108,   109,   110,   110,   111,   111,   112,   112,   112,
     113,   114,   114,   114,   114,   114,   114,   115,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     119,   119,   120,   121,   122,   122,   123,   124,   124,   125,
     126,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   130,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   133,   134,   134,   135,   135,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   139,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   143,   143,   144,
     145,   146,   147,   147
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     0,     1,     9,     1,     1,     1,
      27,     5,     8,     0,     3,     6,     3,     0,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       1,     1,     1,     1,     3,     0,     1,     1,     3,     3,
       0,     4,     4,     5,     1,     3,     3,     5,     9,     9,
       2,     1,     3,     3,     4,     5,     3,     4,     5,     3,
       4,     5,     3,     4,     5,     3,     2,     1,     1,     1,
       3,     6,     6,     6,     3,     3,     3,     3,     3,     4,
       5,     6,     4,     5,     6,     4,     5,     6,     4,     5,
       6,     4,     5,     6,     4,     5,     6,     4,     5,     6,
       4,     5,     6,     4,     5,     6,     4,     5,     6,     3,
       4,     1,     3,     3,     2,     3,     5,     4,     1,     1,
       3,     3,     2,     5,     4,     1,     5,     7,     3,     5,
       4,     6,     6,     8,     2,     4,     0,     2,     2,     1,
       2,     1,     1,     3,     0,     3,     0,     2,     0,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     0,     3,     0,     2,     7,
       2,     4,     0,     1
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
#line 283 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 2019 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 315 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 321 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 326 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 332 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2052 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 338 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2060 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 344 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2068 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 350 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2078 "yacc_sql.cpp"
    break;

  case 32: /* show_tables_stmt: SHOW TABLES  */
#line 357 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2086 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 363 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2096 "yacc_sql.cpp"
    break;

  case 34: /* index_type: %empty  */
#line 371 "yacc_sql.y"
  {
      (yyval.bools) = false;
  }
#line 2104 "yacc_sql.cpp"
    break;

  case 35: /* index_type: UNIQUE  */
#line 373 "yacc_sql.y"
           {
      (yyval.bools) = true;
  }
#line 2112 "yacc_sql.cpp"
    break;

  case 36: /* create_index_stmt: CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 379 "yacc_sql.y"
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
#line 2131 "yacc_sql.cpp"
    break;

  case 37: /* distance_type: L2_DISTANCE  */
#line 395 "yacc_sql.y"
               {
       (yyval.number)  = 1;
   }
#line 2139 "yacc_sql.cpp"
    break;

  case 38: /* distance_type: COSINE_DISTANCE  */
#line 398 "yacc_sql.y"
                  {
      (yyval.number)  =  2;
   }
#line 2147 "yacc_sql.cpp"
    break;

  case 39: /* distance_type: INNER_PRODUCT  */
#line 401 "yacc_sql.y"
                 {
      (yyval.number)  =  3;
   }
#line 2155 "yacc_sql.cpp"
    break;

  case 40: /* create_index_vector_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE rel_list RBRACE WITH LBRACE TYPE EQ ID COMMA DISTANCE EQ distance_type COMMA LISTS EQ NUMBER COMMA PROBES EQ NUMBER RBRACE  */
#line 407 "yacc_sql.y"
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
#line 2172 "yacc_sql.cpp"
    break;

  case 41: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 426 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2184 "yacc_sql.cpp"
    break;

  case 42: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 436 "yacc_sql.y"
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
#line 2209 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: %empty  */
#line 459 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2217 "yacc_sql.cpp"
    break;

  case 44: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 463 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type LBRACE number RBRACE not_null  */
#line 476 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if((yyval.attr_info)->type == AttrType::VECTORS){(yyval.attr_info)->set_vector_type_length((yyvsp[-2].number));}
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-5].string));
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type not_null  */
#line 486 "yacc_sql.y"
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
#line 2262 "yacc_sql.cpp"
    break;

  case 47: /* not_null: %empty  */
#line 501 "yacc_sql.y"
    {(yyval.number) = 0;}
#line 2268 "yacc_sql.cpp"
    break;

  case 48: /* not_null: NULL_T  */
#line 502 "yacc_sql.y"
             {(yyval.number) = 0;}
#line 2274 "yacc_sql.cpp"
    break;

  case 49: /* not_null: NOT NULL_T  */
#line 503 "yacc_sql.y"
                 {(yyval.number) = 1;}
#line 2280 "yacc_sql.cpp"
    break;

  case 50: /* number: NUMBER  */
#line 506 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2286 "yacc_sql.cpp"
    break;

  case 51: /* type: INT_T  */
#line 509 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2292 "yacc_sql.cpp"
    break;

  case 52: /* type: STRING_T  */
#line 510 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2298 "yacc_sql.cpp"
    break;

  case 53: /* type: FLOAT_T  */
#line 511 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2304 "yacc_sql.cpp"
    break;

  case 54: /* type: DATE_T  */
#line 512 "yacc_sql.y"
              { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2310 "yacc_sql.cpp"
    break;

  case 55: /* type: TEXT_T  */
#line 513 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2316 "yacc_sql.cpp"
    break;

  case 56: /* type: VECTOR_T  */
#line 514 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2322 "yacc_sql.cpp"
    break;

  case 57: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 518 "yacc_sql.y"
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
#line 2339 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 534 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2347 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 537 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2361 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 548 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2370 "yacc_sql.cpp"
    break;

  case 61: /* value: FLOAT  */
#line 552 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 62: /* value: SSS  */
#line 556 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 63: /* value: NULL_T  */
#line 562 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 64: /* value: LEFT_BRACKET float_list RIGHT_BRACKET  */
#line 567 "yacc_sql.y"
    {
      (yyval.value) = new Value();
      (yyval.value)->set_vector(*(yyvsp[-1].float_list));
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 65: /* float_list: %empty  */
#line 574 "yacc_sql.y"
    { (yyval.float_list) = nullptr;}
#line 2414 "yacc_sql.cpp"
    break;

  case 66: /* float_list: FLOAT  */
#line 576 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].floats));
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 67: /* float_list: NUMBER  */
#line 581 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].number));
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 68: /* float_list: NUMBER COMMA float_list  */
#line 586 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].number));
    }
#line 2445 "yacc_sql.cpp"
    break;

  case 69: /* float_list: FLOAT COMMA float_list  */
#line 595 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].floats));
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 70: /* storage_format: %empty  */
#line 607 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 71: /* storage_format: STORAGE FORMAT EQ ID  */
#line 611 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 72: /* delete_stmt: DELETE FROM ID where  */
#line 618 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2488 "yacc_sql.cpp"
    break;

  case 73: /* update_stmt: UPDATE ID SET update_unite_list where  */
#line 630 "yacc_sql.y"
    {
      printf("解析update语句");
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.table_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_unites.swap(*(yyvsp[-1].update_unite_list));
      if( (yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      }
    }
#line 2502 "yacc_sql.cpp"
    break;

  case 74: /* update_unite_list: update_unite  */
#line 642 "yacc_sql.y"
    {
      printf("解析update_unite_list为单个 unite list");
      (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      (yyval.update_unite_list)->push_back(*(yyvsp[0].update_unite));
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 75: /* update_unite_list: update_unite COMMA update_unite_list  */
#line 648 "yacc_sql.y"
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
#line 2527 "yacc_sql.cpp"
    break;

  case 76: /* update_unite: ID EQ expression  */
#line 661 "yacc_sql.y"
    {
      printf("解析update unite");
      (yyval.update_unite) = new UpdateUnite();
      (yyval.update_unite)->field_name = (yyvsp[-2].string);
      (yyval.update_unite)->expression = (yyvsp[0].expression);
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 77: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 669 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 78: /* create_table_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 676 "yacc_sql.y"
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
#line 2574 "yacc_sql.cpp"
    break;

  case 79: /* select_stmt: SELECT expression_list FROM rel_list where group_by having order_by limit_  */
#line 699 "yacc_sql.y"
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
#line 2613 "yacc_sql.cpp"
    break;

  case 80: /* calc_stmt: CALC expression_list  */
#line 736 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 81: /* expression_list: expression  */
#line 745 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression COMMA expression_list  */
#line 750 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '+' expression  */
#line 760 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression ID  */
#line 763 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '+' expression AS ID  */
#line 766 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2669 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '-' expression  */
#line 769 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '-' expression ID  */
#line 772 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '-' expression AS ID  */
#line 775 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2693 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '*' expression  */
#line 778 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2701 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '*' expression ID  */
#line 781 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '*' expression AS ID  */
#line 784 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2717 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '/' expression  */
#line 787 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '/' expression ID  */
#line 790 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '/' expression AS ID  */
#line 793 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2741 "yacc_sql.cpp"
    break;

  case 95: /* expression: LBRACE expression RBRACE  */
#line 796 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2750 "yacc_sql.cpp"
    break;

  case 96: /* expression: '-' expression  */
#line 800 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 97: /* expression: value  */
#line 803 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2768 "yacc_sql.cpp"
    break;

  case 98: /* expression: rel_attr  */
#line 808 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2779 "yacc_sql.cpp"
    break;

  case 99: /* expression: '*'  */
#line 814 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2787 "yacc_sql.cpp"
    break;

  case 100: /* expression: ID DOT '*'  */
#line 817 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 101: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 821 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 102: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 825 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 103: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 829 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 104: /* expression: SUM LBRACE RBRACE  */
#line 832 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2827 "yacc_sql.cpp"
    break;

  case 105: /* expression: MAX LBRACE RBRACE  */
#line 835 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2835 "yacc_sql.cpp"
    break;

  case 106: /* expression: MIN LBRACE RBRACE  */
#line 838 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 107: /* expression: AVG LBRACE RBRACE  */
#line 841 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 108: /* expression: COUNT LBRACE RBRACE  */
#line 844 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 109: /* expression: SUM LBRACE expression RBRACE  */
#line 847 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 110: /* expression: SUM LBRACE expression RBRACE ID  */
#line 850 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2875 "yacc_sql.cpp"
    break;

  case 111: /* expression: SUM LBRACE expression RBRACE AS ID  */
#line 853 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2883 "yacc_sql.cpp"
    break;

  case 112: /* expression: MAX LBRACE expression RBRACE  */
#line 856 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2891 "yacc_sql.cpp"
    break;

  case 113: /* expression: MAX LBRACE expression RBRACE ID  */
#line 859 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 114: /* expression: MAX LBRACE expression RBRACE AS ID  */
#line 862 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 115: /* expression: MIN LBRACE expression RBRACE  */
#line 865 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 116: /* expression: MIN LBRACE expression RBRACE ID  */
#line 868 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 117: /* expression: MIN LBRACE expression RBRACE AS ID  */
#line 871 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 118: /* expression: AVG LBRACE expression RBRACE  */
#line 874 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 119: /* expression: AVG LBRACE expression RBRACE ID  */
#line 877 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 120: /* expression: AVG LBRACE expression RBRACE AS ID  */
#line 880 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 121: /* expression: COUNT LBRACE expression RBRACE  */
#line 883 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 122: /* expression: COUNT LBRACE expression RBRACE ID  */
#line 886 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 123: /* expression: COUNT LBRACE expression RBRACE AS ID  */
#line 889 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 124: /* expression: SUM LBRACE expression_list RBRACE  */
#line 892 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2987 "yacc_sql.cpp"
    break;

  case 125: /* expression: SUM LBRACE expression_list RBRACE ID  */
#line 895 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 2995 "yacc_sql.cpp"
    break;

  case 126: /* expression: SUM LBRACE expression_list RBRACE AS ID  */
#line 898 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 3003 "yacc_sql.cpp"
    break;

  case 127: /* expression: MAX LBRACE expression_list RBRACE  */
#line 901 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 128: /* expression: MAX LBRACE expression_list RBRACE ID  */
#line 904 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 129: /* expression: MAX LBRACE expression_list RBRACE AS ID  */
#line 907 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 3027 "yacc_sql.cpp"
    break;

  case 130: /* expression: MIN LBRACE expression_list RBRACE  */
#line 910 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 3035 "yacc_sql.cpp"
    break;

  case 131: /* expression: MIN LBRACE expression_list RBRACE ID  */
#line 913 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 3043 "yacc_sql.cpp"
    break;

  case 132: /* expression: MIN LBRACE expression_list RBRACE AS ID  */
#line 916 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 133: /* expression: AVG LBRACE expression_list RBRACE  */
#line 919 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 134: /* expression: AVG LBRACE expression_list RBRACE ID  */
#line 922 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 135: /* expression: AVG LBRACE expression_list RBRACE AS ID  */
#line 925 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 136: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 928 "yacc_sql.y"
                                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 3083 "yacc_sql.cpp"
    break;

  case 137: /* expression: COUNT LBRACE expression_list RBRACE ID  */
#line 931 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 138: /* expression: COUNT LBRACE expression_list RBRACE AS ID  */
#line 934 "yacc_sql.y"
                                               {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3099 "yacc_sql.cpp"
    break;

  case 139: /* expression: LBRACE select_stmt RBRACE  */
#line 937 "yacc_sql.y"
                                {
      printf("解析子查询");
      (yyval.expression) = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 140: /* expression: LBRACE value value_list RBRACE  */
#line 941 "yacc_sql.y"
                                    {
      if((yyvsp[-1].value_list) == nullptr){
        (yyvsp[-1].value_list) = new vector<Value>();
      }
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.expression) = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3120 "yacc_sql.cpp"
    break;

  case 141: /* rel_attr: ID  */
#line 951 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 142: /* rel_attr: ID DOT ID  */
#line 956 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 143: /* rel_attr: ID AS ID  */
#line 963 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 144: /* rel_attr: '*' ID  */
#line 970 "yacc_sql.y"
            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3165 "yacc_sql.cpp"
    break;

  case 145: /* rel_attr: '*' AS ID  */
#line 976 "yacc_sql.y"
               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3176 "yacc_sql.cpp"
    break;

  case 146: /* rel_attr: ID DOT ID AS ID  */
#line 982 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3190 "yacc_sql.cpp"
    break;

  case 147: /* rel_attr: ID DOT ID ID  */
#line 991 "yacc_sql.y"
                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3204 "yacc_sql.cpp"
    break;

  case 148: /* relation: ID  */
#line 1003 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3212 "yacc_sql.cpp"
    break;

  case 149: /* rel_list: relation  */
#line 1008 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[0].string), (yyvsp[0].string)});
      free((yyvsp[0].string));
    }
#line 3222 "yacc_sql.cpp"
    break;

  case 150: /* rel_list: relation COMMA rel_list  */
#line 1013 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-2].string), (yyvsp[-2].string)});
      free((yyvsp[-2].string));
    }
#line 3237 "yacc_sql.cpp"
    break;

  case 151: /* rel_list: relation AS ID  */
#line 1023 "yacc_sql.y"
                    {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-2].string), (yyvsp[0].string)});
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3248 "yacc_sql.cpp"
    break;

  case 152: /* rel_list: relation ID  */
#line 1029 "yacc_sql.y"
                 {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-1].string), (yyvsp[0].string)});
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 153: /* rel_list: relation AS ID COMMA rel_list  */
#line 1035 "yacc_sql.y"
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
#line 3274 "yacc_sql.cpp"
    break;

  case 154: /* rel_list: relation ID COMMA rel_list  */
#line 1045 "yacc_sql.y"
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
#line 3289 "yacc_sql.cpp"
    break;

  case 155: /* rel_list: join_in  */
#line 1055 "yacc_sql.y"
             {
      if((yyval.relation_list) == nullptr){
        (yyval.relation_list) = (yyvsp[0].join_list);
      }else{
        //$$->insert($$->begin(), $1);
        (yyval.relation_list) = (yyvsp[0].join_list);
      }
    }
#line 3302 "yacc_sql.cpp"
    break;

  case 156: /* join_in_right_list: INNER JOIN relation ON condition_list  */
#line 1067 "yacc_sql.y"
                                        {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-2].string), (yyvsp[-2].string)});
  }
#line 3312 "yacc_sql.cpp"
    break;

  case 157: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list  */
#line 1072 "yacc_sql.y"
                                                {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-4].string), (yyvsp[-2].string)});
  }
#line 3322 "yacc_sql.cpp"
    break;

  case 158: /* join_in_right_list: INNER JOIN relation  */
#line 1077 "yacc_sql.y"
                         {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[0].string),(yyvsp[0].string)});
  }
#line 3333 "yacc_sql.cpp"
    break;

  case 159: /* join_in_right_list: INNER JOIN relation AS ID  */
#line 1083 "yacc_sql.y"
                               {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[-2].string),(yyvsp[0].string)});
  }
#line 3344 "yacc_sql.cpp"
    break;

  case 160: /* join_in_right_list: INNER JOIN relation join_in_right_list  */
#line 1089 "yacc_sql.y"
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
#line 3360 "yacc_sql.cpp"
    break;

  case 161: /* join_in_right_list: INNER JOIN relation AS ID join_in_right_list  */
#line 1100 "yacc_sql.y"
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
#line 3377 "yacc_sql.cpp"
    break;

  case 162: /* join_in_right_list: INNER JOIN relation ON condition_list join_in_right_list  */
#line 1112 "yacc_sql.y"
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
#line 3392 "yacc_sql.cpp"
    break;

  case 163: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list join_in_right_list  */
#line 1122 "yacc_sql.y"
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
#line 3408 "yacc_sql.cpp"
    break;

  case 164: /* join_in: relation join_in_right_list  */
#line 1136 "yacc_sql.y"
                             {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
    free((yyvsp[-1].string));
  }
#line 3422 "yacc_sql.cpp"
    break;

  case 165: /* join_in: relation AS ID join_in_right_list  */
#line 1145 "yacc_sql.y"
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
#line 3437 "yacc_sql.cpp"
    break;

  case 166: /* limit_: %empty  */
#line 1158 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 3445 "yacc_sql.cpp"
    break;

  case 167: /* limit_: LIMIT number  */
#line 1161 "yacc_sql.y"
                  {
        (yyval.number) = (yyvsp[0].number);
    }
#line 3453 "yacc_sql.cpp"
    break;

  case 168: /* order_by_field: rel_attr DESC  */
#line 1166 "yacc_sql.y"
                  {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3464 "yacc_sql.cpp"
    break;

  case 169: /* order_by_field: rel_attr  */
#line 1172 "yacc_sql.y"
             {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3475 "yacc_sql.cpp"
    break;

  case 170: /* order_by_field: rel_attr ASC  */
#line 1177 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
      }
#line 3486 "yacc_sql.cpp"
    break;

  case 171: /* order_by_field: expression  */
#line 1183 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3494 "yacc_sql.cpp"
    break;

  case 172: /* order_by_field_list: order_by_field  */
#line 1188 "yacc_sql.y"
                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>> ;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
      //delete $1;
    }
#line 3504 "yacc_sql.cpp"
    break;

  case 173: /* order_by_field_list: order_by_field COMMA order_by_field_list  */
#line 1193 "yacc_sql.y"
                                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    }
#line 3514 "yacc_sql.cpp"
    break;

  case 174: /* order_by: %empty  */
#line 1200 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3522 "yacc_sql.cpp"
    break;

  case 175: /* order_by: ORDER BY order_by_field_list  */
#line 1204 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      }else{
        (yyval.expression_list) = nullptr;
      }
    }
#line 3534 "yacc_sql.cpp"
    break;

  case 176: /* where: %empty  */
#line 1214 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3542 "yacc_sql.cpp"
    break;

  case 177: /* where: WHERE condition_list  */
#line 1217 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3550 "yacc_sql.cpp"
    break;

  case 178: /* condition_list: %empty  */
#line 1223 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3558 "yacc_sql.cpp"
    break;

  case 179: /* condition_list: condition  */
#line 1226 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3568 "yacc_sql.cpp"
    break;

  case 180: /* condition_list: condition AND condition_list  */
#line 1231 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3578 "yacc_sql.cpp"
    break;

  case 181: /* condition_list: condition OR condition_list  */
#line 1236 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction_with_or = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3589 "yacc_sql.cpp"
    break;

  case 182: /* condition: rel_attr comp_op value  */
#line 1245 "yacc_sql.y"
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
#line 3605 "yacc_sql.cpp"
    break;

  case 183: /* condition: value comp_op value  */
#line 1257 "yacc_sql.y"
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
#line 3621 "yacc_sql.cpp"
    break;

  case 184: /* condition: rel_attr comp_op rel_attr  */
#line 1269 "yacc_sql.y"
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
#line 3637 "yacc_sql.cpp"
    break;

  case 185: /* condition: value comp_op rel_attr  */
#line 1281 "yacc_sql.y"
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
#line 3653 "yacc_sql.cpp"
    break;

  case 186: /* condition: expression comp_op value  */
#line 1293 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3668 "yacc_sql.cpp"
    break;

  case 187: /* condition: value comp_op expression  */
#line 1304 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
    }
#line 3683 "yacc_sql.cpp"
    break;

  case 188: /* condition: expression comp_op rel_attr  */
#line 1315 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3698 "yacc_sql.cpp"
    break;

  case 189: /* condition: rel_attr comp_op expression  */
#line 1326 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3713 "yacc_sql.cpp"
    break;

  case 190: /* condition: expression comp_op expression  */
#line 1337 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3726 "yacc_sql.cpp"
    break;

  case 191: /* comp_op: EQ  */
#line 1348 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3732 "yacc_sql.cpp"
    break;

  case 192: /* comp_op: LT  */
#line 1349 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3738 "yacc_sql.cpp"
    break;

  case 193: /* comp_op: GT  */
#line 1350 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3744 "yacc_sql.cpp"
    break;

  case 194: /* comp_op: LE  */
#line 1351 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3750 "yacc_sql.cpp"
    break;

  case 195: /* comp_op: GE  */
#line 1352 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3756 "yacc_sql.cpp"
    break;

  case 196: /* comp_op: NE  */
#line 1353 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3762 "yacc_sql.cpp"
    break;

  case 197: /* comp_op: LIKE  */
#line 1354 "yacc_sql.y"
           { (yyval.comp) = LIKE_TO; }
#line 3768 "yacc_sql.cpp"
    break;

  case 198: /* comp_op: NOT LIKE  */
#line 1355 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_TO; }
#line 3774 "yacc_sql.cpp"
    break;

  case 199: /* comp_op: IS_  */
#line 1356 "yacc_sql.y"
          { (yyval.comp) = IS ;}
#line 3780 "yacc_sql.cpp"
    break;

  case 200: /* comp_op: IS_ NOT  */
#line 1357 "yacc_sql.y"
              { (yyval.comp) = IS_NOT ;}
#line 3786 "yacc_sql.cpp"
    break;

  case 201: /* comp_op: IN_T  */
#line 1358 "yacc_sql.y"
           { (yyval.comp) = IN ; }
#line 3792 "yacc_sql.cpp"
    break;

  case 202: /* comp_op: NOT IN_T  */
#line 1359 "yacc_sql.y"
               { (yyval.comp) = NOT_IN ; }
#line 3798 "yacc_sql.cpp"
    break;

  case 203: /* comp_op: EXISTS_T  */
#line 1360 "yacc_sql.y"
               { (yyval.comp) = EXISTS ; }
#line 3804 "yacc_sql.cpp"
    break;

  case 204: /* comp_op: NOT EXISTS_T  */
#line 1361 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXISTS ; }
#line 3810 "yacc_sql.cpp"
    break;

  case 205: /* group_by: %empty  */
#line 1366 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3818 "yacc_sql.cpp"
    break;

  case 206: /* group_by: GROUP BY expression_list  */
#line 1370 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3828 "yacc_sql.cpp"
    break;

  case 207: /* having: %empty  */
#line 1379 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3836 "yacc_sql.cpp"
    break;

  case 208: /* having: HAVING condition_list  */
#line 1383 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3846 "yacc_sql.cpp"
    break;

  case 209: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1392 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3860 "yacc_sql.cpp"
    break;

  case 210: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1405 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3869 "yacc_sql.cpp"
    break;

  case 211: /* set_variable_stmt: SET ID EQ value  */
#line 1413 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3881 "yacc_sql.cpp"
    break;


#line 3885 "yacc_sql.cpp"

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

#line 1425 "yacc_sql.y"

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
