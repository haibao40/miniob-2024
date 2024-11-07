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



#line 163 "yacc_sql.cpp"

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
  YYSYMBOL_VECTOR_T = 31,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_LOAD = 43,                      /* LOAD  */
  YYSYMBOL_DATA = 44,                      /* DATA  */
  YYSYMBOL_INFILE = 45,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 46,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 47,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 48,                    /* FORMAT  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_NOT = 55,                       /* NOT  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_IS_ = 57,                       /* IS_  */
  YYSYMBOL_NULL_T = 58,                    /* NULL_T  */
  YYSYMBOL_MAX = 59,                       /* MAX  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_AVG = 61,                       /* AVG  */
  YYSYMBOL_SUM = 62,                       /* SUM  */
  YYSYMBOL_COUNT = 63,                     /* COUNT  */
  YYSYMBOL_HAVING = 64,                    /* HAVING  */
  YYSYMBOL_INNER = 65,                     /* INNER  */
  YYSYMBOL_JOIN = 66,                      /* JOIN  */
  YYSYMBOL_AS = 67,                        /* AS  */
  YYSYMBOL_UNIQUE = 68,                    /* UNIQUE  */
  YYSYMBOL_LEFT_BRACKET = 69,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 70,             /* RIGHT_BRACKET  */
  YYSYMBOL_L2_DISTANCE = 71,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 72,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 73,             /* INNER_PRODUCT  */
  YYSYMBOL_IN_T = 74,                      /* IN_T  */
  YYSYMBOL_EXISTS_T = 75,                  /* EXISTS_T  */
  YYSYMBOL_NUMBER = 76,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 77,                     /* FLOAT  */
  YYSYMBOL_ID = 78,                        /* ID  */
  YYSYMBOL_SSS = 79,                       /* SSS  */
  YYSYMBOL_80_ = 80,                       /* '+'  */
  YYSYMBOL_81_ = 81,                       /* '-'  */
  YYSYMBOL_82_ = 82,                       /* '*'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_UMINUS = 84,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_commands = 86,                  /* commands  */
  YYSYMBOL_command_wrapper = 87,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 88,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 89,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 90,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 91,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 92,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 93,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 94,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 95,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 96,           /* desc_table_stmt  */
  YYSYMBOL_index_type = 97,                /* index_type  */
  YYSYMBOL_create_index_stmt = 98,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 99,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 100,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 101,            /* attr_def_list  */
  YYSYMBOL_attr_def = 102,                 /* attr_def  */
  YYSYMBOL_not_null = 103,                 /* not_null  */
  YYSYMBOL_number = 104,                   /* number  */
  YYSYMBOL_type = 105,                     /* type  */
  YYSYMBOL_insert_stmt = 106,              /* insert_stmt  */
  YYSYMBOL_value_list = 107,               /* value_list  */
  YYSYMBOL_value = 108,                    /* value  */
  YYSYMBOL_float_list = 109,               /* float_list  */
  YYSYMBOL_storage_format = 110,           /* storage_format  */
  YYSYMBOL_delete_stmt = 111,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 112,              /* update_stmt  */
  YYSYMBOL_update_unite_list = 113,        /* update_unite_list  */
  YYSYMBOL_update_unite = 114,             /* update_unite  */
  YYSYMBOL_create_table_select_stmt = 115, /* create_table_select_stmt  */
  YYSYMBOL_select_stmt = 116,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 117,                /* calc_stmt  */
  YYSYMBOL_expression_list = 118,          /* expression_list  */
  YYSYMBOL_expression = 119,               /* expression  */
  YYSYMBOL_rel_attr = 120,                 /* rel_attr  */
  YYSYMBOL_relation = 121,                 /* relation  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_join_in_right_list = 123,       /* join_in_right_list  */
  YYSYMBOL_join_in = 124,                  /* join_in  */
  YYSYMBOL_order_by_field = 125,           /* order_by_field  */
  YYSYMBOL_order_by_field_list = 126,      /* order_by_field_list  */
  YYSYMBOL_order_by = 127,                 /* order_by  */
  YYSYMBOL_where = 128,                    /* where  */
  YYSYMBOL_condition_list = 129,           /* condition_list  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_comp_op = 131,                  /* comp_op  */
  YYSYMBOL_group_by = 132,                 /* group_by  */
  YYSYMBOL_having = 133,                   /* having  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   516

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  361

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
       2,     2,    82,    80,     2,    81,     2,    83,     2,     2,
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
      75,    76,    77,    78,    79,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   270,   270,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   302,   308,   313,   319,   325,   331,
     337,   344,   350,   358,   360,   365,   383,   393,   417,   420,
     433,   443,   455,   456,   457,   460,   463,   464,   465,   466,
     467,   470,   487,   490,   501,   505,   509,   515,   519,   527,
     528,   533,   538,   547,   560,   563,   570,   582,   594,   600,
     613,   622,   628,   651,   687,   696,   701,   712,   715,   718,
     721,   724,   727,   730,   733,   736,   739,   742,   745,   748,
     752,   755,   760,   766,   769,   772,   776,   780,   784,   787,
     790,   793,   796,   799,   802,   805,   808,   811,   814,   817,
     820,   823,   826,   829,   832,   835,   838,   841,   844,   847,
     850,   853,   856,   859,   862,   865,   868,   871,   874,   877,
     880,   883,   886,   889,   893,   903,   908,   915,   922,   928,
     934,   943,   955,   960,   965,   975,   981,   987,   997,  1007,
    1019,  1024,  1029,  1035,  1041,  1052,  1064,  1074,  1088,  1097,
    1112,  1118,  1123,  1130,  1133,  1138,  1145,  1148,  1159,  1162,
    1168,  1171,  1176,  1181,  1189,  1201,  1213,  1225,  1237,  1248,
    1259,  1270,  1281,  1293,  1294,  1295,  1296,  1297,  1298,  1299,
    1300,  1301,  1302,  1303,  1304,  1305,  1306,  1311,  1314,  1324,
    1327,  1336,  1349,  1357,  1367,  1368
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
  "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "VECTOR_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NOT", "LIKE", "IS_", "NULL_T", "MAX", "MIN",
  "AVG", "SUM", "COUNT", "HAVING", "INNER", "JOIN", "AS", "UNIQUE",
  "LEFT_BRACKET", "RIGHT_BRACKET", "L2_DISTANCE", "COSINE_DISTANCE",
  "INNER_PRODUCT", "IN_T", "EXISTS_T", "NUMBER", "FLOAT", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "index_type", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "not_null", "number",
  "type", "insert_stmt", "value_list", "value", "float_list",
  "storage_format", "delete_stmt", "update_stmt", "update_unite_list",
  "update_unite", "create_table_select_stmt", "select_stmt", "calc_stmt",
  "expression_list", "expression", "rel_attr", "relation", "rel_list",
  "join_in_right_list", "join_in", "order_by_field", "order_by_field_list",
  "order_by", "where", "condition_list", "condition", "comp_op",
  "group_by", "having", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-265)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     410,    12,    40,   333,   333,   -49,    46,  -265,    24,    72,
       3,  -265,  -265,  -265,  -265,  -265,    52,    89,   410,   146,
     151,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,    85,  -265,   155,    90,    94,    98,  -265,   157,
     170,   187,   217,   227,    45,   244,   248,   266,  -265,  -265,
     -20,  -265,   333,   -42,  -265,  -265,   196,  -265,   255,  -265,
    -265,   229,   230,   269,   267,   277,  -265,  -265,  -265,  -265,
     -10,   249,  -265,   286,   164,   309,    44,   168,   212,   242,
     274,   304,   306,   315,   271,   333,   333,   333,   -54,   261,
    -265,   264,  -265,   333,   333,   333,   333,   333,   270,   308,
     311,   290,   126,   295,   300,   366,   342,   323,   126,   381,
    -265,  -265,  -265,   385,   -13,  -265,   386,    -7,  -265,   391,
      55,  -265,   396,    61,  -265,   397,    68,    45,    45,  -265,
     289,   307,   317,   -37,  -265,  -265,  -265,  -265,   -44,   175,
     -34,   -32,  -265,   -17,   311,  -265,   399,   333,  -265,   372,
     311,   402,  -265,   398,   330,   409,  -265,   353,  -265,   414,
    -265,   -14,    62,    67,    86,   118,   140,   142,   165,   219,
     239,  -265,  -265,   333,   333,   333,   360,  -265,   361,  -265,
     362,  -265,   363,  -265,   367,  -265,   270,   378,   368,   424,
    -265,   444,   126,   418,   408,   418,  -265,   154,   333,  -265,
     290,   440,  -265,  -265,  -265,  -265,  -265,   107,   300,   428,
     431,  -265,   376,  -265,   377,  -265,   388,  -265,   400,  -265,
     401,  -265,   403,  -265,   406,  -265,   407,  -265,   416,  -265,
     417,  -265,   117,   130,   179,  -265,  -265,  -265,  -265,  -265,
    -265,   270,   -11,   270,   471,   413,   414,  -265,  -265,  -265,
    -265,  -265,  -265,    57,  -265,   425,  -265,  -265,   333,   333,
     333,   333,   333,   134,  -265,   419,   411,   438,  -265,  -265,
     409,   439,   270,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,   -25,   270,  -265,  -265,
     333,   333,   490,   477,  -265,  -265,  -265,  -265,  -265,   134,
    -265,  -265,   134,  -265,  -265,   134,  -265,  -265,  -265,  -265,
    -265,   478,  -265,  -265,   453,   366,   480,   333,   426,  -265,
    -265,  -265,  -265,   498,  -265,  -265,     0,   456,  -265,  -265,
     441,   -22,   -51,  -265,   429,  -265,   333,  -265,   -15,   -42,
     221,   485,  -265,  -265,   441,   432,  -265,  -265,   -51,  -265,
    -265
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     204,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,    23,     4,     3,    18,
      19,    20,     0,    34,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,    59,     0,     0,     0,    54,    55,
     135,    56,     0,    93,    91,    74,    75,    92,     0,    32,
      31,     0,     0,     0,     0,     0,   202,     1,   205,     2,
       0,     0,    30,     0,    91,     0,     0,     0,     0,     0,
       0,     0,    61,    60,     0,     0,     0,     0,     0,     0,
      90,     0,   138,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     133,    89,    99,     0,     0,   100,     0,     0,   101,     0,
       0,    98,     0,     0,   102,     0,     0,    59,    59,    58,
       0,     0,     0,   136,    94,   137,   139,    76,    77,    80,
      83,    86,   142,   143,   168,   149,     0,   170,    66,     0,
     168,    68,   203,     0,     0,    38,    71,     0,    36,    52,
     134,   121,   106,   124,   109,   127,   112,   118,   103,   130,
     115,    62,    63,     0,     0,     0,     0,   141,     0,    78,
       0,    81,     0,    84,     0,    87,     0,     0,     0,   146,
     158,   197,     0,    91,     0,    92,   169,   171,     0,    67,
       0,     0,    46,    47,    48,    49,    50,    42,     0,     0,
       0,    53,     0,   122,     0,   107,     0,   125,     0,   110,
       0,   128,     0,   113,     0,   119,     0,   104,     0,   131,
       0,   116,     0,     0,     0,   140,    79,    82,    85,    88,
     144,     0,   145,     0,     0,   199,    52,   183,   184,   185,
     186,   187,   188,     0,   189,   191,   193,   195,     0,     0,
       0,   170,   170,    70,    69,     0,     0,     0,    43,    41,
      38,    64,     0,   123,   108,   126,   111,   129,   114,   120,
     105,   132,   117,    95,    96,    97,   152,     0,   159,   148,
       0,   170,   166,     0,   190,   194,   196,   192,    91,   179,
      92,    91,   182,    92,    91,   181,    92,   172,   173,   201,
      45,     0,    44,    39,     0,    37,     0,   170,     0,   154,
     147,   198,   200,     0,    73,    51,    42,     0,    72,    35,
     150,   153,   163,    40,     0,   156,   170,   155,   135,     0,
     161,   164,   167,    65,   151,     0,   160,   162,   163,   157,
     165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -265,  -265,   491,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,   231,   294,   177,  -265,
    -265,  -265,  -164,   -47,   114,  -265,  -265,  -265,   305,  -265,
    -265,   -43,  -265,     9,    -2,  -154,   263,  -174,  -234,  -265,
    -265,   158,  -265,  -128,  -264,  -265,    51,  -265,  -265,  -265,
    -265,  -265,  -265
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    44,    30,    31,    32,   219,   165,   279,   321,
     217,    33,   119,    64,    94,   325,    34,    35,   160,   161,
      36,    37,    38,    65,   204,    67,   153,   154,   200,   155,
     351,   352,   334,   158,   206,   207,   268,   255,   302,    39,
      40,    41,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    66,    66,   205,    85,   221,   196,   317,   318,   172,
     103,   114,   297,    68,    98,   174,   103,   327,   298,   355,
     346,    42,   250,   188,   143,   101,   201,   348,   144,    69,
     186,   349,   209,   192,   189,   194,   102,   332,   106,   107,
     197,   187,   328,   197,   193,    86,   195,    99,   197,    45,
     198,    46,    99,   222,   197,   277,    70,   115,   278,    71,
     100,   199,   329,   340,   223,   162,   121,   104,   105,   106,
     107,   169,   166,   104,   105,   106,   107,   176,   103,   299,
      43,    73,   354,   178,   103,   124,   127,   130,   133,   136,
     180,   103,   303,   140,   141,   142,   123,   126,   129,   132,
     135,    66,   148,   149,   150,   151,   345,   347,   326,    72,
     203,     4,   147,   304,   310,   313,   316,   205,   205,    47,
     359,    92,    93,   330,   104,   105,   106,   107,   276,   224,
      74,   305,   306,    75,   226,   104,   105,   106,   107,   293,
     225,   104,   105,   106,   107,   227,    77,   205,   104,   105,
     106,   107,   294,   228,    78,   256,    48,    49,    50,    51,
      52,    53,   277,    80,   229,   278,    81,    54,    82,    55,
      56,    57,    83,   205,    58,    59,    60,    61,    87,    62,
      63,   242,   243,   244,    48,   230,   -52,   118,   350,    47,
     122,    88,   205,   271,   272,    54,   231,   104,   105,   106,
     107,   295,    58,    59,   350,    61,   273,   232,    89,   234,
     104,   105,   106,   107,   104,   105,   106,   107,   233,   103,
     235,   308,   311,   314,   203,   203,    48,    49,    50,    51,
      52,    53,   236,    47,   125,   356,   357,    54,    90,    55,
      56,    57,   190,   237,    58,    59,    60,    61,    91,    62,
      63,   181,   182,   191,   203,   269,   270,   106,   107,   104,
     105,   106,   107,    47,   128,    95,   309,   312,   315,    96,
      48,    49,    50,    51,    52,    53,   104,   105,   106,   107,
     203,    54,   338,    55,    56,    57,   238,    97,    58,    59,
      60,    61,   108,    62,    63,    47,   131,   239,    66,   203,
      48,    49,    50,    51,    52,    53,   240,   109,   110,   331,
     111,    54,   183,    55,    56,    57,   112,   241,    58,    59,
      60,    61,   113,    62,    63,    47,   134,   116,   117,   137,
     184,   120,    48,    49,    50,    51,    52,    53,   138,   145,
     185,   139,   146,    54,   156,    55,    56,    57,   152,   157,
      58,    59,    60,    61,    47,    62,    63,   212,   213,   214,
     215,   216,    48,    49,    50,    51,    52,    53,   159,   104,
     105,   106,   107,    54,   163,    55,    56,    57,   164,     4,
      58,    59,    60,    61,   167,    62,    63,   104,   105,   106,
     107,    48,    49,    50,    51,    52,    53,   104,   105,   106,
     107,   168,    54,   170,    55,    56,    57,   171,   173,    58,
      59,    60,    61,   175,    62,    63,     1,     2,   177,   179,
     202,   208,     3,     4,     5,   210,     6,     7,     8,     9,
      10,   220,   218,   211,    11,    12,    13,   118,   245,   246,
     247,   248,    14,    15,   251,   249,   252,   253,   254,   275,
     281,    16,   282,    17,   283,   284,    18,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   285,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   300,   301,   286,   287,
     307,   288,   266,   267,   289,   290,   324,   320,   104,   105,
     106,   107,   266,   267,   291,   292,   322,   319,   333,   335,
     336,   337,   339,   342,   341,   344,   197,   353,   358,    76,
     143,   323,   280,   343,   296,   274,   360
};

static const yytype_int16 yycheck[] =
{
      47,     3,     4,   157,    47,   169,    23,   271,   272,    22,
      23,    21,    23,     4,    34,    22,    23,    42,   252,    34,
      42,     9,   196,    67,    78,    67,   154,    78,    82,    78,
      67,    82,   160,    67,    78,    67,    78,   301,    82,    83,
      65,    78,    67,    65,    78,    47,    78,    67,    65,     9,
      67,    11,    67,    67,    65,    55,    10,    67,    58,    35,
      62,    78,   296,   327,    78,   112,    22,    80,    81,    82,
      83,   118,   115,    80,    81,    82,    83,    22,    23,   253,
      68,    78,   346,    22,    23,    87,    88,    89,    90,    91,
      22,    23,   256,    95,    96,    97,    87,    88,    89,    90,
      91,   103,   104,   105,   106,   107,   340,   341,   282,    37,
     157,    13,   103,    56,   268,   269,   270,   271,   272,    21,
     354,    76,    77,   297,    80,    81,    82,    83,    21,    67,
      78,    74,    75,    44,    67,    80,    81,    82,    83,    22,
      78,    80,    81,    82,    83,    78,     0,   301,    80,    81,
      82,    83,    22,    67,     3,   202,    58,    59,    60,    61,
      62,    63,    55,    78,    78,    58,    11,    69,    78,    71,
      72,    73,    78,   327,    76,    77,    78,    79,    21,    81,
      82,   183,   184,   185,    58,    67,    22,    23,   342,    21,
      22,    21,   346,    39,    40,    69,    78,    80,    81,    82,
      83,    22,    76,    77,   358,    79,   208,    67,    21,    67,
      80,    81,    82,    83,    80,    81,    82,    83,    78,    23,
      78,   268,   269,   270,   271,   272,    58,    59,    60,    61,
      62,    63,    67,    21,    22,    14,    15,    69,    21,    71,
      72,    73,    67,    78,    76,    77,    78,    79,    21,    81,
      82,   137,   138,    78,   301,   204,   205,    82,    83,    80,
      81,    82,    83,    21,    22,    21,   268,   269,   270,    21,
      58,    59,    60,    61,    62,    63,    80,    81,    82,    83,
     327,    69,   325,    71,    72,    73,    67,    21,    76,    77,
      78,    79,    37,    81,    82,    21,    22,    78,   300,   346,
      58,    59,    60,    61,    62,    63,    67,    78,    78,   300,
      41,    69,    23,    71,    72,    73,    49,    78,    76,    77,
      78,    79,    45,    81,    82,    21,    22,    78,    42,    23,
      23,    22,    58,    59,    60,    61,    62,    63,    23,    78,
      23,    70,    78,    69,    36,    71,    72,    73,    78,    38,
      76,    77,    78,    79,    21,    81,    82,    27,    28,    29,
      30,    31,    58,    59,    60,    61,    62,    63,    78,    80,
      81,    82,    83,    69,    79,    71,    72,    73,    78,    13,
      76,    77,    78,    79,    42,    81,    82,    80,    81,    82,
      83,    58,    59,    60,    61,    62,    63,    80,    81,    82,
      83,    78,    69,    22,    71,    72,    73,    22,    22,    76,
      77,    78,    79,    22,    81,    82,     6,     7,    22,    22,
      21,    49,    12,    13,    14,    23,    16,    17,    18,    19,
      20,    78,    23,    35,    24,    25,    26,    23,    78,    78,
      78,    78,    32,    33,    66,    78,    78,    23,     4,     9,
      22,    41,    21,    43,    78,    78,    46,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    78,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     5,    64,    78,    78,
      55,    78,    74,    75,    78,    78,    47,    76,    80,    81,
      82,    83,    74,    75,    78,    78,    58,    78,     8,    22,
      22,    48,    22,     5,    78,    49,    65,    78,    23,    18,
      78,   280,   218,   336,   251,   210,   358
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    12,    13,    14,    16,    17,    18,    19,
      20,    24,    25,    26,    32,    33,    41,    43,    46,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      98,    99,   100,   106,   111,   112,   115,   116,   117,   134,
     135,   136,     9,    68,    97,     9,    11,    21,    58,    59,
      60,    61,    62,    63,    69,    71,    72,    73,    76,    77,
      78,    79,    81,    82,   108,   118,   119,   120,   118,    78,
      10,    35,    37,    78,    78,    44,    87,     0,     3,   137,
      78,    11,    78,    78,   108,   116,   119,    21,    21,    21,
      21,    21,    76,    77,   109,    21,    21,    21,    34,    67,
     119,    67,    78,    23,    80,    81,    82,    83,    37,    78,
      78,    41,    49,    45,    21,    67,    78,    42,    23,   107,
      22,    22,    22,   118,   119,    22,   118,   119,    22,   118,
     119,    22,   118,   119,    22,   118,   119,    23,    23,    70,
     119,   119,   119,    78,    82,    78,    78,   118,   119,   119,
     119,   119,    78,   121,   122,   124,    36,    38,   128,    78,
     113,   114,   108,    79,    78,   102,   116,    42,    78,   108,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,   109,   109,    23,    23,    23,    67,    78,    67,    78,
      67,    78,    67,    78,    67,    78,    23,    65,    67,    78,
     123,   128,    21,   108,   119,   120,   129,   130,    49,   128,
      23,    35,    27,    28,    29,    30,    31,   105,    23,   101,
      78,   107,    67,    78,    67,    78,    67,    78,    67,    78,
      67,    78,    67,    78,    67,    78,    67,    78,    67,    78,
      67,    78,   119,   119,   119,    78,    78,    78,    78,    78,
     122,    66,    78,    23,     4,   132,   108,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    74,    75,   131,   131,
     131,    39,    40,   119,   113,     9,    21,    55,    58,   103,
     102,    22,    21,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    22,    22,    22,   121,    23,   123,   122,
       5,    64,   133,   107,    56,    74,    75,    55,   108,   119,
     120,   108,   119,   120,   108,   119,   120,   129,   129,    78,
      76,   104,    58,   101,    47,   110,   122,    42,    67,   123,
     122,   118,   129,     8,   127,    22,    22,    48,   116,    22,
     129,    78,     5,   103,    49,   123,    42,   123,    78,    82,
     120,   125,   126,    78,   129,    34,    14,    15,    23,   123,
     126
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    97,    98,    99,   100,   101,   101,
     102,   102,   103,   103,   103,   104,   105,   105,   105,   105,
     105,   106,   107,   107,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   110,   110,   111,   112,   113,   113,
     114,   115,   115,   116,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   120,   120,   120,   120,   120,
     120,   120,   121,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   124,   124,
     125,   125,   125,   126,   126,   126,   127,   127,   128,   128,
     129,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   132,   132,   133,
     133,   134,   135,   136,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     0,     1,     9,     5,     8,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     8,     0,     3,     1,     1,     1,     1,     3,     0,
       1,     1,     3,     3,     0,     4,     4,     5,     1,     3,
       3,     5,     9,     8,     2,     1,     3,     3,     4,     5,
       3,     4,     5,     3,     4,     5,     3,     4,     5,     3,
       2,     1,     1,     1,     3,     6,     6,     6,     3,     3,
       3,     3,     3,     4,     5,     6,     4,     5,     6,     4,
       5,     6,     4,     5,     6,     4,     5,     6,     4,     5,
       6,     4,     5,     6,     4,     5,     6,     4,     5,     6,
       4,     5,     6,     3,     4,     1,     3,     3,     2,     3,
       5,     4,     1,     1,     3,     3,     2,     5,     4,     1,
       5,     7,     3,     5,     4,     6,     6,     8,     2,     4,
       2,     1,     2,     0,     1,     3,     0,     3,     0,     2,
       0,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     0,     3,     0,
       2,     7,     2,     4,     0,     1
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
#line 271 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1987 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 302 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1996 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 308 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 313 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 319 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 325 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 331 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 337 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 344 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 350 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 33: /* index_type: %empty  */
#line 358 "yacc_sql.y"
  {
      (yyval.bools) = false;
  }
#line 2072 "yacc_sql.cpp"
    break;

  case 34: /* index_type: UNIQUE  */
#line 360 "yacc_sql.y"
           {
      (yyval.bools) = true;
  }
#line 2080 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 366 "yacc_sql.y"
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
#line 2099 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 384 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2111 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 394 "yacc_sql.y"
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
#line 2136 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 417 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 421 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE not_null  */
#line 434 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if((yyval.attr_info)->type == AttrType::VECTORS){(yyval.attr_info)->set_vector_type_length((yyvsp[-2].number));}
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-5].string));
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type not_null  */
#line 444 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-2].string));
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 42: /* not_null: %empty  */
#line 455 "yacc_sql.y"
    {(yyval.number) = 0;}
#line 2191 "yacc_sql.cpp"
    break;

  case 43: /* not_null: NULL_T  */
#line 456 "yacc_sql.y"
             {(yyval.number) = 0;}
#line 2197 "yacc_sql.cpp"
    break;

  case 44: /* not_null: NOT NULL_T  */
#line 457 "yacc_sql.y"
                 {(yyval.number) = 1;}
#line 2203 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 460 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2209 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 463 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2215 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 464 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2221 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 465 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2227 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 466 "yacc_sql.y"
              { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2233 "yacc_sql.cpp"
    break;

  case 50: /* type: VECTOR_T  */
#line 467 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2239 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 471 "yacc_sql.y"
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
#line 2256 "yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 487 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2264 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 490 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 501 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 505 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2296 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 509 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2307 "yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 515 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2316 "yacc_sql.cpp"
    break;

  case 58: /* value: LEFT_BRACKET float_list RIGHT_BRACKET  */
#line 520 "yacc_sql.y"
    {
      (yyval.value) = new Value();
      (yyval.value)->set_vector(*(yyvsp[-1].float_list));
    }
#line 2325 "yacc_sql.cpp"
    break;

  case 59: /* float_list: %empty  */
#line 527 "yacc_sql.y"
    { (yyval.float_list) = nullptr;}
#line 2331 "yacc_sql.cpp"
    break;

  case 60: /* float_list: FLOAT  */
#line 529 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].floats));
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 61: /* float_list: NUMBER  */
#line 534 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].number));
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 62: /* float_list: NUMBER COMMA float_list  */
#line 539 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].number));
    }
#line 2362 "yacc_sql.cpp"
    break;

  case 63: /* float_list: FLOAT COMMA float_list  */
#line 548 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].floats));
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 560 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2383 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 564 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2391 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 571 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET update_unite_list where  */
#line 583 "yacc_sql.y"
    {
      printf("解析update语句");
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.table_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_unites.swap(*(yyvsp[-1].update_unite_list));
      if( (yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      }
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 68: /* update_unite_list: update_unite  */
#line 595 "yacc_sql.y"
    {
      printf("解析update_unite_list为单个 unite list");
      (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      (yyval.update_unite_list)->push_back(*(yyvsp[0].update_unite));
    }
#line 2429 "yacc_sql.cpp"
    break;

  case 69: /* update_unite_list: update_unite COMMA update_unite_list  */
#line 601 "yacc_sql.y"
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
#line 2444 "yacc_sql.cpp"
    break;

  case 70: /* update_unite: ID EQ expression  */
#line 614 "yacc_sql.y"
    {
      printf("解析update unite");
      (yyval.update_unite) = new UpdateUnite();
      (yyval.update_unite)->field_name = (yyvsp[-2].string);
      (yyval.update_unite)->expression = (yyvsp[0].expression);
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 71: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 622 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 72: /* create_table_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 629 "yacc_sql.y"
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
#line 2491 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list FROM rel_list where group_by having order_by  */
#line 652 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if((yyvsp[-1].condition_list) != nullptr){
        (yyval.sql_node)->selection.having.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
      (yyval.sql_node)->selection.join_conditions.swap(join_conditions);
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 74: /* calc_stmt: CALC expression_list  */
#line 688 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: expression  */
#line 697 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2548 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: expression COMMA expression_list  */
#line 702 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 77: /* expression: expression '+' expression  */
#line 712 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2569 "yacc_sql.cpp"
    break;

  case 78: /* expression: expression '+' expression ID  */
#line 715 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2577 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '+' expression AS ID  */
#line 718 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::ADD, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2585 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '-' expression  */
#line 721 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '-' expression ID  */
#line 724 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '-' expression AS ID  */
#line 727 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::SUB, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2609 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '*' expression  */
#line 730 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '*' expression ID  */
#line 733 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2625 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '*' expression AS ID  */
#line 736 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::MUL, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2633 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '/' expression  */
#line 739 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2641 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression ID  */
#line 742 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-3].expression), (yyvsp[-1].expression), (yyvsp[0].string));
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '/' expression AS ID  */
#line 745 "yacc_sql.y"
                                     {
      (yyval.expression) = create_arithmetic_expression_with_alias(ArithmeticExpr::Type::DIV, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2657 "yacc_sql.cpp"
    break;

  case 89: /* expression: LBRACE expression RBRACE  */
#line 748 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2666 "yacc_sql.cpp"
    break;

  case 90: /* expression: '-' expression  */
#line 752 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2674 "yacc_sql.cpp"
    break;

  case 91: /* expression: value  */
#line 755 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 92: /* expression: rel_attr  */
#line 760 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 93: /* expression: '*'  */
#line 766 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 94: /* expression: ID DOT '*'  */
#line 769 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 95: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 773 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 96: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 777 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 97: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 781 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 98: /* expression: SUM LBRACE RBRACE  */
#line 784 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2743 "yacc_sql.cpp"
    break;

  case 99: /* expression: MAX LBRACE RBRACE  */
#line 787 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 100: /* expression: MIN LBRACE RBRACE  */
#line 790 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2759 "yacc_sql.cpp"
    break;

  case 101: /* expression: AVG LBRACE RBRACE  */
#line 793 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2767 "yacc_sql.cpp"
    break;

  case 102: /* expression: COUNT LBRACE RBRACE  */
#line 796 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 103: /* expression: SUM LBRACE expression RBRACE  */
#line 799 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 104: /* expression: SUM LBRACE expression RBRACE ID  */
#line 802 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 105: /* expression: SUM LBRACE expression RBRACE AS ID  */
#line 805 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2799 "yacc_sql.cpp"
    break;

  case 106: /* expression: MAX LBRACE expression RBRACE  */
#line 808 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2807 "yacc_sql.cpp"
    break;

  case 107: /* expression: MAX LBRACE expression RBRACE ID  */
#line 811 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2815 "yacc_sql.cpp"
    break;

  case 108: /* expression: MAX LBRACE expression RBRACE AS ID  */
#line 814 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2823 "yacc_sql.cpp"
    break;

  case 109: /* expression: MIN LBRACE expression RBRACE  */
#line 817 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 110: /* expression: MIN LBRACE expression RBRACE ID  */
#line 820 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 111: /* expression: MIN LBRACE expression RBRACE AS ID  */
#line 823 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 112: /* expression: AVG LBRACE expression RBRACE  */
#line 826 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 113: /* expression: AVG LBRACE expression RBRACE ID  */
#line 829 "yacc_sql.y"
                                     {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 114: /* expression: AVG LBRACE expression RBRACE AS ID  */
#line 832 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2871 "yacc_sql.cpp"
    break;

  case 115: /* expression: COUNT LBRACE expression RBRACE  */
#line 835 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 116: /* expression: COUNT LBRACE expression RBRACE ID  */
#line 838 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", (yyvsp[-2].expression), (yyvsp[0].string));
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 117: /* expression: COUNT LBRACE expression RBRACE AS ID  */
#line 841 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", (yyvsp[-3].expression), (yyvsp[0].string));
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 118: /* expression: SUM LBRACE expression_list RBRACE  */
#line 844 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2903 "yacc_sql.cpp"
    break;

  case 119: /* expression: SUM LBRACE expression_list RBRACE ID  */
#line 847 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 120: /* expression: SUM LBRACE expression_list RBRACE AS ID  */
#line 850 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("SUM", nullptr, (yyvsp[0].string));
    }
#line 2919 "yacc_sql.cpp"
    break;

  case 121: /* expression: MAX LBRACE expression_list RBRACE  */
#line 853 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2927 "yacc_sql.cpp"
    break;

  case 122: /* expression: MAX LBRACE expression_list RBRACE ID  */
#line 856 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 2935 "yacc_sql.cpp"
    break;

  case 123: /* expression: MAX LBRACE expression_list RBRACE AS ID  */
#line 859 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MAX", nullptr, (yyvsp[0].string));
    }
#line 2943 "yacc_sql.cpp"
    break;

  case 124: /* expression: MIN LBRACE expression_list RBRACE  */
#line 862 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2951 "yacc_sql.cpp"
    break;

  case 125: /* expression: MIN LBRACE expression_list RBRACE ID  */
#line 865 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 126: /* expression: MIN LBRACE expression_list RBRACE AS ID  */
#line 868 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("MIN", nullptr, (yyvsp[0].string));
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 127: /* expression: AVG LBRACE expression_list RBRACE  */
#line 871 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 128: /* expression: AVG LBRACE expression_list RBRACE ID  */
#line 874 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 2983 "yacc_sql.cpp"
    break;

  case 129: /* expression: AVG LBRACE expression_list RBRACE AS ID  */
#line 877 "yacc_sql.y"
                                             {
      (yyval.expression) = create_aggregate_expression_with_alias("AVG", nullptr, (yyvsp[0].string));
    }
#line 2991 "yacc_sql.cpp"
    break;

  case 130: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 880 "yacc_sql.y"
                                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2999 "yacc_sql.cpp"
    break;

  case 131: /* expression: COUNT LBRACE expression_list RBRACE ID  */
#line 883 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3007 "yacc_sql.cpp"
    break;

  case 132: /* expression: COUNT LBRACE expression_list RBRACE AS ID  */
#line 886 "yacc_sql.y"
                                               {
      (yyval.expression) = create_aggregate_expression_with_alias("COUNT", nullptr, (yyvsp[0].string));
    }
#line 3015 "yacc_sql.cpp"
    break;

  case 133: /* expression: LBRACE select_stmt RBRACE  */
#line 889 "yacc_sql.y"
                                {
      printf("解析子查询");
      (yyval.expression) = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
    }
#line 3024 "yacc_sql.cpp"
    break;

  case 134: /* expression: LBRACE value value_list RBRACE  */
#line 893 "yacc_sql.y"
                                    {
      if((yyvsp[-1].value_list) == nullptr){
        (yyvsp[-1].value_list) = new vector<Value>();
      }
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.expression) = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 3036 "yacc_sql.cpp"
    break;

  case 135: /* rel_attr: ID  */
#line 903 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 136: /* rel_attr: ID DOT ID  */
#line 908 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3058 "yacc_sql.cpp"
    break;

  case 137: /* rel_attr: ID AS ID  */
#line 915 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 138: /* rel_attr: '*' ID  */
#line 922 "yacc_sql.y"
            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 139: /* rel_attr: '*' AS ID  */
#line 928 "yacc_sql.y"
               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = "";  /* 这里是不合法的，为了方便适配测试用例返回failure，让它通过语法解析,匹配不到就会返回failure */
      (yyval.rel_attr)->alias          = "";
      free((yyvsp[0].string));
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 140: /* rel_attr: ID DOT ID AS ID  */
#line 934 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3106 "yacc_sql.cpp"
    break;

  case 141: /* rel_attr: ID DOT ID ID  */
#line 943 "yacc_sql.y"
                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3120 "yacc_sql.cpp"
    break;

  case 142: /* relation: ID  */
#line 955 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 143: /* rel_list: relation  */
#line 960 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[0].string), (yyvsp[0].string)});
      free((yyvsp[0].string));
    }
#line 3138 "yacc_sql.cpp"
    break;

  case 144: /* rel_list: relation COMMA rel_list  */
#line 965 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-2].string), (yyvsp[-2].string)});
      free((yyvsp[-2].string));
    }
#line 3153 "yacc_sql.cpp"
    break;

  case 145: /* rel_list: relation AS ID  */
#line 975 "yacc_sql.y"
                    {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-2].string), (yyvsp[0].string)});
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3164 "yacc_sql.cpp"
    break;

  case 146: /* rel_list: relation ID  */
#line 981 "yacc_sql.y"
                 {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-1].string), (yyvsp[0].string)});
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3175 "yacc_sql.cpp"
    break;

  case 147: /* rel_list: relation AS ID COMMA rel_list  */
#line 987 "yacc_sql.y"
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
#line 3190 "yacc_sql.cpp"
    break;

  case 148: /* rel_list: relation ID COMMA rel_list  */
#line 997 "yacc_sql.y"
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
#line 3205 "yacc_sql.cpp"
    break;

  case 149: /* rel_list: join_in  */
#line 1007 "yacc_sql.y"
             {
      if((yyval.relation_list) == nullptr){
        (yyval.relation_list) = (yyvsp[0].join_list);
      }else{
        //$$->insert($$->begin(), $1);
        (yyval.relation_list) = (yyvsp[0].join_list);
      }
    }
#line 3218 "yacc_sql.cpp"
    break;

  case 150: /* join_in_right_list: INNER JOIN relation ON condition_list  */
#line 1019 "yacc_sql.y"
                                        {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-2].string), (yyvsp[-2].string)});
  }
#line 3228 "yacc_sql.cpp"
    break;

  case 151: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list  */
#line 1024 "yacc_sql.y"
                                                {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-4].string), (yyvsp[-2].string)});
  }
#line 3238 "yacc_sql.cpp"
    break;

  case 152: /* join_in_right_list: INNER JOIN relation  */
#line 1029 "yacc_sql.y"
                         {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[0].string),(yyvsp[0].string)});
  }
#line 3249 "yacc_sql.cpp"
    break;

  case 153: /* join_in_right_list: INNER JOIN relation AS ID  */
#line 1035 "yacc_sql.y"
                               {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[-2].string),(yyvsp[0].string)});
  }
#line 3260 "yacc_sql.cpp"
    break;

  case 154: /* join_in_right_list: INNER JOIN relation join_in_right_list  */
#line 1041 "yacc_sql.y"
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
#line 3276 "yacc_sql.cpp"
    break;

  case 155: /* join_in_right_list: INNER JOIN relation AS ID join_in_right_list  */
#line 1052 "yacc_sql.y"
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
#line 3293 "yacc_sql.cpp"
    break;

  case 156: /* join_in_right_list: INNER JOIN relation ON condition_list join_in_right_list  */
#line 1064 "yacc_sql.y"
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
#line 3308 "yacc_sql.cpp"
    break;

  case 157: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list join_in_right_list  */
#line 1074 "yacc_sql.y"
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
#line 3324 "yacc_sql.cpp"
    break;

  case 158: /* join_in: relation join_in_right_list  */
#line 1088 "yacc_sql.y"
                             {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
    free((yyvsp[-1].string));
  }
#line 3338 "yacc_sql.cpp"
    break;

  case 159: /* join_in: relation AS ID join_in_right_list  */
#line 1097 "yacc_sql.y"
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
#line 3353 "yacc_sql.cpp"
    break;

  case 160: /* order_by_field: rel_attr DESC  */
#line 1112 "yacc_sql.y"
                  {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3364 "yacc_sql.cpp"
    break;

  case 161: /* order_by_field: rel_attr  */
#line 1118 "yacc_sql.y"
             {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3375 "yacc_sql.cpp"
    break;

  case 162: /* order_by_field: rel_attr ASC  */
#line 1123 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3386 "yacc_sql.cpp"
    break;

  case 163: /* order_by_field_list: %empty  */
#line 1130 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3394 "yacc_sql.cpp"
    break;

  case 164: /* order_by_field_list: order_by_field  */
#line 1133 "yacc_sql.y"
                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>> ;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
      //delete $1;
    }
#line 3404 "yacc_sql.cpp"
    break;

  case 165: /* order_by_field_list: order_by_field COMMA order_by_field_list  */
#line 1138 "yacc_sql.y"
                                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    }
#line 3414 "yacc_sql.cpp"
    break;

  case 166: /* order_by: %empty  */
#line 1145 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3422 "yacc_sql.cpp"
    break;

  case 167: /* order_by: ORDER BY order_by_field_list  */
#line 1149 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      }else{
        (yyval.expression_list) = nullptr;
      }
    }
#line 3434 "yacc_sql.cpp"
    break;

  case 168: /* where: %empty  */
#line 1159 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3442 "yacc_sql.cpp"
    break;

  case 169: /* where: WHERE condition_list  */
#line 1162 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3450 "yacc_sql.cpp"
    break;

  case 170: /* condition_list: %empty  */
#line 1168 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3458 "yacc_sql.cpp"
    break;

  case 171: /* condition_list: condition  */
#line 1171 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3468 "yacc_sql.cpp"
    break;

  case 172: /* condition_list: condition AND condition_list  */
#line 1176 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3478 "yacc_sql.cpp"
    break;

  case 173: /* condition_list: condition OR condition_list  */
#line 1181 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->conjunction_with_or = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3489 "yacc_sql.cpp"
    break;

  case 174: /* condition: rel_attr comp_op value  */
#line 1190 "yacc_sql.y"
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
#line 3505 "yacc_sql.cpp"
    break;

  case 175: /* condition: value comp_op value  */
#line 1202 "yacc_sql.y"
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
#line 3521 "yacc_sql.cpp"
    break;

  case 176: /* condition: rel_attr comp_op rel_attr  */
#line 1214 "yacc_sql.y"
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
#line 3537 "yacc_sql.cpp"
    break;

  case 177: /* condition: value comp_op rel_attr  */
#line 1226 "yacc_sql.y"
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
#line 3553 "yacc_sql.cpp"
    break;

  case 178: /* condition: expression comp_op value  */
#line 1238 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3568 "yacc_sql.cpp"
    break;

  case 179: /* condition: value comp_op expression  */
#line 1249 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
    }
#line 3583 "yacc_sql.cpp"
    break;

  case 180: /* condition: expression comp_op rel_attr  */
#line 1260 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3598 "yacc_sql.cpp"
    break;

  case 181: /* condition: rel_attr comp_op expression  */
#line 1271 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3613 "yacc_sql.cpp"
    break;

  case 182: /* condition: expression comp_op expression  */
#line 1282 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3626 "yacc_sql.cpp"
    break;

  case 183: /* comp_op: EQ  */
#line 1293 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3632 "yacc_sql.cpp"
    break;

  case 184: /* comp_op: LT  */
#line 1294 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3638 "yacc_sql.cpp"
    break;

  case 185: /* comp_op: GT  */
#line 1295 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3644 "yacc_sql.cpp"
    break;

  case 186: /* comp_op: LE  */
#line 1296 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3650 "yacc_sql.cpp"
    break;

  case 187: /* comp_op: GE  */
#line 1297 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3656 "yacc_sql.cpp"
    break;

  case 188: /* comp_op: NE  */
#line 1298 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3662 "yacc_sql.cpp"
    break;

  case 189: /* comp_op: LIKE  */
#line 1299 "yacc_sql.y"
           { (yyval.comp) = LIKE_TO; }
#line 3668 "yacc_sql.cpp"
    break;

  case 190: /* comp_op: NOT LIKE  */
#line 1300 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_TO; }
#line 3674 "yacc_sql.cpp"
    break;

  case 191: /* comp_op: IS_  */
#line 1301 "yacc_sql.y"
          { (yyval.comp) = IS ;}
#line 3680 "yacc_sql.cpp"
    break;

  case 192: /* comp_op: IS_ NOT  */
#line 1302 "yacc_sql.y"
              { (yyval.comp) = IS_NOT ;}
#line 3686 "yacc_sql.cpp"
    break;

  case 193: /* comp_op: IN_T  */
#line 1303 "yacc_sql.y"
           { (yyval.comp) = IN ; }
#line 3692 "yacc_sql.cpp"
    break;

  case 194: /* comp_op: NOT IN_T  */
#line 1304 "yacc_sql.y"
               { (yyval.comp) = NOT_IN ; }
#line 3698 "yacc_sql.cpp"
    break;

  case 195: /* comp_op: EXISTS_T  */
#line 1305 "yacc_sql.y"
               { (yyval.comp) = EXISTS ; }
#line 3704 "yacc_sql.cpp"
    break;

  case 196: /* comp_op: NOT EXISTS_T  */
#line 1306 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXISTS ; }
#line 3710 "yacc_sql.cpp"
    break;

  case 197: /* group_by: %empty  */
#line 1311 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3718 "yacc_sql.cpp"
    break;

  case 198: /* group_by: GROUP BY expression_list  */
#line 1315 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3728 "yacc_sql.cpp"
    break;

  case 199: /* having: %empty  */
#line 1324 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3736 "yacc_sql.cpp"
    break;

  case 200: /* having: HAVING condition_list  */
#line 1328 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3746 "yacc_sql.cpp"
    break;

  case 201: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1337 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3760 "yacc_sql.cpp"
    break;

  case 202: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1350 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3769 "yacc_sql.cpp"
    break;

  case 203: /* set_variable_stmt: SET ID EQ value  */
#line 1358 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3781 "yacc_sql.cpp"
    break;


#line 3785 "yacc_sql.cpp"

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

#line 1370 "yacc_sql.y"

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
