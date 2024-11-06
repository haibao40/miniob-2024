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

std::vector<std::vector<ConditionSqlNode>*>  join_conditions;



#line 144 "yacc_sql.cpp"

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
#define YYLAST   496

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  310

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
       0,   251,   251,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   283,   289,   294,   300,   306,   312,
     318,   325,   331,   339,   341,   346,   364,   374,   398,   401,
     414,   424,   440,   441,   442,   445,   448,   449,   450,   451,
     452,   453,   456,   473,   476,   487,   491,   495,   501,   505,
     513,   514,   519,   524,   533,   546,   549,   556,   568,   580,
     586,   599,   608,   614,   637,   673,   682,   687,   698,   701,
     704,   707,   710,   714,   717,   722,   728,   731,   735,   739,
     743,   746,   749,   752,   755,   758,   761,   764,   767,   770,
     773,   776,   779,   782,   785,   788,   792,   802,   807,   814,
     821,   833,   838,   843,   853,   859,   865,   875,   885,   897,
     902,   907,   913,   919,   930,   942,   952,   966,   975,   990,
     996,  1001,  1008,  1011,  1016,  1023,  1026,  1037,  1040,  1046,
    1049,  1054,  1061,  1073,  1085,  1097,  1109,  1120,  1131,  1142,
    1153,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,
    1174,  1175,  1176,  1177,  1178,  1183,  1186,  1196,  1199,  1208,
    1221,  1229,  1239,  1240
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
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
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

#define YYPACT_NINF (-234)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     413,    -6,    24,   327,   327,   -48,    29,  -234,    11,    21,
     -17,  -234,  -234,  -234,  -234,  -234,     5,    30,   413,   105,
      96,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,    35,  -234,   108,    43,    50,    99,  -234,    86,
     114,   128,   129,   132,   -62,   133,   135,   144,  -234,  -234,
     -23,  -234,   327,  -234,  -234,  -234,   146,  -234,   136,  -234,
    -234,    68,    88,   126,   124,   137,  -234,  -234,  -234,  -234,
     -13,   106,  -234,   147,   100,   161,   119,   196,   221,   249,
     274,   302,   167,   168,   139,   327,   327,   327,   138,   142,
    -234,   327,   327,   327,   327,   327,   152,   177,   176,   153,
     -45,   140,   155,   212,   193,   162,   -45,   219,  -234,  -234,
    -234,   222,    -4,  -234,   226,    14,  -234,   227,    44,  -234,
     230,    49,  -234,   231,   115,   -62,   -62,  -234,   156,   331,
     335,   194,  -234,  -234,    51,    51,  -234,  -234,  -234,   -14,
     176,  -234,   239,   327,  -234,   213,   176,   240,  -234,   228,
     452,   253,  -234,   207,  -234,   263,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,   327,
     327,   327,   209,   152,   223,   210,   268,  -234,   297,   -45,
     421,   411,   421,  -234,   264,   327,  -234,   153,   296,  -234,
    -234,  -234,  -234,  -234,  -234,   -10,   155,   284,   292,  -234,
     123,   130,   141,  -234,  -234,   152,   -16,   152,   309,   251,
     263,  -234,  -234,  -234,  -234,  -234,  -234,   -33,  -234,   261,
    -234,  -234,   327,   327,   327,   327,   -25,  -234,   241,   262,
     259,  -234,  -234,   253,   282,   152,  -234,  -234,  -234,   -15,
     152,  -234,  -234,   327,   327,   332,   317,  -234,  -234,  -234,
    -234,  -234,   -25,  -234,  -234,   -25,  -234,  -234,   -25,  -234,
    -234,  -234,  -234,   319,  -234,  -234,   294,   212,   322,   327,
     271,  -234,  -234,  -234,  -234,   352,  -234,  -234,   -29,   310,
    -234,  -234,   301,   -22,   289,  -234,   290,  -234,   327,  -234,
     125,   346,  -234,  -234,   301,  -234,  -234,   289,  -234,  -234
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     172,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,    23,     4,     3,    18,
      19,    20,     0,    34,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,    60,     0,     0,     0,    55,    56,
     107,    57,     0,    86,    84,    75,    76,    85,     0,    32,
      31,     0,     0,     0,     0,     0,   170,     1,   173,     2,
       0,     0,    30,     0,    84,     0,     0,     0,     0,     0,
       0,     0,    62,    61,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,    82,
      91,     0,     0,    92,     0,     0,    93,     0,     0,    90,
       0,     0,    94,     0,     0,    60,    60,    59,     0,     0,
       0,   108,   109,    77,    78,    79,    80,    81,   111,   112,
     137,   118,     0,   139,    67,     0,   137,    69,   171,     0,
       0,    38,    72,     0,    36,    53,   106,   101,    96,   102,
      97,   103,    98,   100,    95,   104,    99,    63,    64,     0,
       0,     0,     0,     0,     0,     0,   115,   127,   165,     0,
      84,     0,    85,   138,   140,     0,    68,     0,     0,    46,
      47,    48,    49,    50,    51,    42,     0,     0,     0,    54,
       0,     0,     0,   110,   113,     0,   114,     0,     0,   167,
      53,   151,   152,   153,   154,   155,   156,     0,   157,   159,
     161,   163,     0,     0,     0,   139,    71,    70,     0,     0,
       0,    43,    41,    38,    65,     0,    87,    88,    89,   121,
       0,   128,   117,     0,   139,   135,     0,   158,   162,   164,
     160,    84,   147,    85,    84,   150,    85,    84,   149,    85,
     141,   169,    45,     0,    44,    39,     0,    37,     0,   139,
       0,   123,   116,   166,   168,     0,    74,    52,    42,     0,
      73,    35,   119,   122,   132,    40,     0,   125,   139,   124,
     130,   133,   136,    66,   120,   129,   131,   132,   126,   134
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -234,  -234,   354,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,   127,   170,    89,  -234,
    -234,  -234,  -140,   -47,     8,  -234,  -234,  -234,   185,  -234,
    -234,   -43,  -234,    -3,    13,  -143,   178,  -177,  -211,  -234,
    -234,    84,  -234,  -128,  -233,  -234,   -44,  -234,  -234,  -234,
    -234,  -234,  -234
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    44,    30,    31,    32,   207,   161,   242,   273,
     205,    33,   117,    64,    94,   277,    34,    35,   156,   157,
      36,    37,    38,    65,   191,    67,   149,   150,   187,   151,
     301,   302,   286,   154,   193,   194,   232,   219,   255,    39,
      40,    41,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    68,   270,    42,    85,   251,   214,   250,   112,   183,
     192,   239,    98,    48,    92,    93,    66,    66,   168,   101,
     298,   284,   188,   257,    54,   209,   240,   279,   196,   241,
      69,    58,    59,    45,    61,    46,   170,   101,   281,    70,
     252,   258,   259,   184,    99,   240,   292,    71,   241,   184,
     184,   184,   280,   185,   113,   102,   103,   104,   105,    72,
      86,    73,    43,   158,   186,   304,   172,   101,   278,   165,
     162,   174,   101,   282,    75,   100,   102,   103,   104,   105,
     256,   297,   299,    74,   121,   124,   127,   130,   133,   263,
     266,   269,   192,   308,   102,   103,   104,   105,   143,    78,
     122,   125,   128,   131,   134,    77,   190,    87,   138,   139,
     140,   192,     4,    80,    66,   144,   145,   146,   147,    81,
      47,    82,   -53,   116,   102,   103,   104,   105,    83,   102,
     103,   104,   105,   104,   105,    88,   192,   176,   101,   305,
     306,   119,   220,   177,   178,   246,   107,   233,   234,    89,
      90,   300,   247,    91,    95,   192,    96,    48,    49,    50,
      51,    52,    53,   248,   300,    97,   108,   109,    54,   101,
      55,    56,    57,   110,   106,    58,    59,    60,    61,   179,
      62,    63,   111,   118,   114,   261,   264,   267,   190,   115,
     135,   136,   210,   211,   212,   102,   103,   104,   105,   102,
     103,   104,   105,   102,   103,   104,   105,   190,   236,   137,
     102,   103,   104,   105,   152,   153,   141,    47,   120,   159,
     142,   102,   103,   104,   105,     4,   102,   103,   104,   105,
     148,   155,   190,   160,   290,   163,   102,   103,   104,   105,
     164,   166,    47,   123,   167,   262,   265,   268,   169,   171,
     283,   190,   173,   175,    48,    49,    50,    51,    52,    53,
     189,   182,   195,   197,   198,    54,    66,    55,    56,    57,
      47,   126,    58,    59,    60,    61,   206,    62,    63,    48,
      49,    50,    51,    52,    53,   208,   116,   213,   216,   215,
      54,   217,    55,    56,    57,    47,   129,    58,    59,    60,
      61,   218,    62,    63,   235,   238,   244,    48,    49,    50,
      51,    52,    53,   245,   253,   254,   260,   274,    54,   271,
      55,    56,    57,    47,   132,    58,    59,    60,    61,   276,
      62,    63,    48,    49,    50,    51,    52,    53,   272,   287,
     285,   288,   289,    54,   291,    55,    56,    57,    47,   293,
      58,    59,    60,    61,   180,    62,    63,   294,   181,   296,
      48,    49,    50,    51,    52,    53,   184,    60,   303,   307,
     275,    54,    76,    55,    56,    57,   243,   295,    58,    59,
      60,    61,   237,    62,    63,    48,    49,    50,    51,    52,
      53,   309,     0,   249,     0,     0,    54,     0,    55,    56,
      57,     0,     0,    58,    59,    60,    61,     0,    62,    63,
       0,   102,   103,   104,   105,   102,   103,   104,   105,     1,
       2,     0,     0,     0,     0,     3,     4,     5,     0,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
       0,     0,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,     0,     0,    16,     0,    17,     0,     0,    18,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   199,
     200,   201,   202,   203,   204,   230,   231,     0,     0,     0,
       0,   102,   103,   104,   105,   230,   231
};

static const yytype_int16 yycheck[] =
{
      47,     4,   235,     9,    47,   216,   183,    23,    21,    23,
     153,    21,    35,    58,    76,    77,     3,     4,    22,    23,
      42,   254,   150,    56,    69,   165,    55,    42,   156,    58,
      78,    76,    77,     9,    79,    11,    22,    23,   249,    10,
     217,    74,    75,    65,    67,    55,   279,    36,    58,    65,
      65,    65,    67,    67,    67,    80,    81,    82,    83,    38,
      47,    78,    68,   110,    78,   298,    22,    23,   245,   116,
     113,    22,    23,   250,    44,    62,    80,    81,    82,    83,
     220,   292,   293,    78,    87,    88,    89,    90,    91,   232,
     233,   234,   235,   304,    80,    81,    82,    83,   101,     3,
      87,    88,    89,    90,    91,     0,   153,    21,    95,    96,
      97,   254,    13,    78,   101,   102,   103,   104,   105,    11,
      21,    78,    22,    23,    80,    81,    82,    83,    78,    80,
      81,    82,    83,    82,    83,    21,   279,    22,    23,    14,
      15,    22,   189,   135,   136,    22,    78,   191,   192,    21,
      21,   294,    22,    21,    21,   298,    21,    58,    59,    60,
      61,    62,    63,    22,   307,    21,    78,    41,    69,    23,
      71,    72,    73,    49,    38,    76,    77,    78,    79,    23,
      81,    82,    45,    22,    78,   232,   233,   234,   235,    42,
      23,    23,   179,   180,   181,    80,    81,    82,    83,    80,
      81,    82,    83,    80,    81,    82,    83,   254,   195,    70,
      80,    81,    82,    83,    37,    39,    78,    21,    22,    79,
      78,    80,    81,    82,    83,    13,    80,    81,    82,    83,
      78,    78,   279,    78,   277,    42,    80,    81,    82,    83,
      78,    22,    21,    22,    22,   232,   233,   234,    22,    22,
     253,   298,    22,    22,    58,    59,    60,    61,    62,    63,
      21,    67,    49,    23,    36,    69,   253,    71,    72,    73,
      21,    22,    76,    77,    78,    79,    23,    81,    82,    58,
      59,    60,    61,    62,    63,    78,    23,    78,    78,    66,
      69,    23,    71,    72,    73,    21,    22,    76,    77,    78,
      79,     4,    81,    82,    40,     9,    22,    58,    59,    60,
      61,    62,    63,    21,     5,    64,    55,    58,    69,    78,
      71,    72,    73,    21,    22,    76,    77,    78,    79,    47,
      81,    82,    58,    59,    60,    61,    62,    63,    76,    22,
       8,    22,    48,    69,    22,    71,    72,    73,    21,    78,
      76,    77,    78,    79,    23,    81,    82,     5,    23,    49,
      58,    59,    60,    61,    62,    63,    65,    78,    78,    23,
     243,    69,    18,    71,    72,    73,   206,   288,    76,    77,
      78,    79,   197,    81,    82,    58,    59,    60,    61,    62,
      63,   307,    -1,   215,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    76,    77,    78,    79,    -1,    81,    82,
      -1,    80,    81,    82,    83,    80,    81,    82,    83,     6,
       7,    -1,    -1,    -1,    -1,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    46,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    27,
      28,    29,    30,    31,    32,    74,    75,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    74,    75
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    12,    13,    14,    16,    17,    18,    19,
      20,    24,    25,    26,    33,    34,    41,    43,    46,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      98,    99,   100,   106,   111,   112,   115,   116,   117,   134,
     135,   136,     9,    68,    97,     9,    11,    21,    58,    59,
      60,    61,    62,    63,    69,    71,    72,    73,    76,    77,
      78,    79,    81,    82,   108,   118,   119,   120,   118,    78,
      10,    36,    38,    78,    78,    44,    87,     0,     3,   137,
      78,    11,    78,    78,   108,   116,   119,    21,    21,    21,
      21,    21,    76,    77,   109,    21,    21,    21,    35,    67,
     119,    23,    80,    81,    82,    83,    38,    78,    78,    41,
      49,    45,    21,    67,    78,    42,    23,   107,    22,    22,
      22,   118,   119,    22,   118,   119,    22,   118,   119,    22,
     118,   119,    22,   118,   119,    23,    23,    70,   119,   119,
     119,    78,    78,   118,   119,   119,   119,   119,    78,   121,
     122,   124,    37,    39,   128,    78,   113,   114,   108,    79,
      78,   102,   116,    42,    78,   108,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,   109,   109,    23,
      23,    23,    67,    23,    65,    67,    78,   123,   128,    21,
     108,   119,   120,   129,   130,    49,   128,    23,    36,    27,
      28,    29,    30,    31,    32,   105,    23,   101,    78,   107,
     119,   119,   119,    78,   122,    66,    78,    23,     4,   132,
     108,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      74,    75,   131,   131,   131,    40,   119,   113,     9,    21,
      55,    58,   103,   102,    22,    21,    22,    22,    22,   121,
      23,   123,   122,     5,    64,   133,   107,    56,    74,    75,
      55,   108,   119,   120,   108,   119,   120,   108,   119,   120,
     129,    78,    76,   104,    58,   101,    47,   110,   122,    42,
      67,   123,   122,   118,   129,     8,   127,    22,    22,    48,
     116,    22,   129,    78,     5,   103,    49,   123,    42,   123,
     120,   125,   126,    78,   129,    14,    15,    23,   123,   126
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    97,    98,    99,   100,   101,   101,
     102,   102,   103,   103,   103,   104,   105,   105,   105,   105,
     105,   105,   106,   107,   107,   108,   108,   108,   108,   108,
     109,   109,   109,   109,   109,   110,   110,   111,   112,   113,
     113,   114,   115,   115,   116,   117,   118,   118,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   120,   120,
     120,   121,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   126,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   134,
     135,   136,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     0,     1,     9,     5,     8,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     1,     1,     1,     3,
       0,     1,     1,     3,     3,     0,     4,     4,     5,     1,
       3,     3,     5,     9,     8,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     6,     6,     6,
       3,     3,     3,     3,     3,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     4,     1,     3,     3,
       5,     1,     1,     3,     3,     2,     5,     4,     1,     5,
       7,     3,     5,     4,     6,     6,     8,     2,     4,     2,
       1,     2,     0,     1,     3,     0,     3,     0,     2,     0,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
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
#line 252 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1937 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 283 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1946 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 289 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1954 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 294 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 306 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1978 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1986 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 318 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1996 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 325 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 331 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 33: /* index_type: %empty  */
#line 339 "yacc_sql.y"
  {
      (yyval.bools) = false;
  }
#line 2022 "yacc_sql.cpp"
    break;

  case 34: /* index_type: UNIQUE  */
#line 341 "yacc_sql.y"
           {
      (yyval.bools) = true;
  }
#line 2030 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 347 "yacc_sql.y"
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
#line 2049 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 365 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2061 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 375 "yacc_sql.y"
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
#line 2086 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 398 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2094 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 402 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE not_null  */
#line 415 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if((yyval.attr_info)->type == AttrType::VECTORS){(yyval.attr_info)->set_vector_type_length((yyvsp[-2].number));}
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-5].string));
    }
#line 2122 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type not_null  */
#line 425 "yacc_sql.y"
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
#line 2139 "yacc_sql.cpp"
    break;

  case 42: /* not_null: %empty  */
#line 440 "yacc_sql.y"
    {(yyval.number) = 0;}
#line 2145 "yacc_sql.cpp"
    break;

  case 43: /* not_null: NULL_T  */
#line 441 "yacc_sql.y"
             {(yyval.number) = 0;}
#line 2151 "yacc_sql.cpp"
    break;

  case 44: /* not_null: NOT NULL_T  */
#line 442 "yacc_sql.y"
                 {(yyval.number) = 1;}
#line 2157 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 445 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2163 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 448 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2169 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 449 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2175 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 450 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2181 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 451 "yacc_sql.y"
              { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2187 "yacc_sql.cpp"
    break;

  case 50: /* type: TEXT_T  */
#line 452 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2193 "yacc_sql.cpp"
    break;

  case 51: /* type: VECTOR_T  */
#line 453 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2199 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 457 "yacc_sql.y"
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
#line 2216 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 473 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2224 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 476 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2238 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 487 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 491 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2256 "yacc_sql.cpp"
    break;

  case 57: /* value: SSS  */
#line 495 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2267 "yacc_sql.cpp"
    break;

  case 58: /* value: NULL_T  */
#line 501 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2276 "yacc_sql.cpp"
    break;

  case 59: /* value: LEFT_BRACKET float_list RIGHT_BRACKET  */
#line 506 "yacc_sql.y"
    {
      (yyval.value) = new Value();
      (yyval.value)->set_vector(*(yyvsp[-1].float_list));
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 60: /* float_list: %empty  */
#line 513 "yacc_sql.y"
    { (yyval.float_list) = nullptr;}
#line 2291 "yacc_sql.cpp"
    break;

  case 61: /* float_list: FLOAT  */
#line 515 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].floats));
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 62: /* float_list: NUMBER  */
#line 520 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].number));
    }
#line 2309 "yacc_sql.cpp"
    break;

  case 63: /* float_list: NUMBER COMMA float_list  */
#line 525 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].number));
    }
#line 2322 "yacc_sql.cpp"
    break;

  case 64: /* float_list: FLOAT COMMA float_list  */
#line 534 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].floats));
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: %empty  */
#line 546 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2343 "yacc_sql.cpp"
    break;

  case 66: /* storage_format: STORAGE FORMAT EQ ID  */
#line 550 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 67: /* delete_stmt: DELETE FROM ID where  */
#line 557 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2365 "yacc_sql.cpp"
    break;

  case 68: /* update_stmt: UPDATE ID SET update_unite_list where  */
#line 569 "yacc_sql.y"
    {
      printf("解析update语句");
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.table_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_unites.swap(*(yyvsp[-1].update_unite_list));
      if( (yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      }
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 69: /* update_unite_list: update_unite  */
#line 581 "yacc_sql.y"
    {
      printf("解析update_unite_list为单个 unite list");
      (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      (yyval.update_unite_list)->push_back(*(yyvsp[0].update_unite));
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 70: /* update_unite_list: update_unite COMMA update_unite_list  */
#line 587 "yacc_sql.y"
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
#line 2404 "yacc_sql.cpp"
    break;

  case 71: /* update_unite: ID EQ expression  */
#line 600 "yacc_sql.y"
    {
      printf("解析update unite");
      (yyval.update_unite) = new UpdateUnite();
      (yyval.update_unite)->field_name = (yyvsp[-2].string);
      (yyval.update_unite)->expression = (yyvsp[0].expression);
    }
#line 2415 "yacc_sql.cpp"
    break;

  case 72: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 608 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2426 "yacc_sql.cpp"
    break;

  case 73: /* create_table_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 615 "yacc_sql.y"
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
#line 2451 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list FROM rel_list where group_by having order_by  */
#line 638 "yacc_sql.y"
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
#line 2489 "yacc_sql.cpp"
    break;

  case 75: /* calc_stmt: CALC expression_list  */
#line 674 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: expression  */
#line 683 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2508 "yacc_sql.cpp"
    break;

  case 77: /* expression_list: expression COMMA expression_list  */
#line 688 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 78: /* expression: expression '+' expression  */
#line 698 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '-' expression  */
#line 701 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '*' expression  */
#line 704 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '/' expression  */
#line 707 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 82: /* expression: LBRACE expression RBRACE  */
#line 710 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2562 "yacc_sql.cpp"
    break;

  case 83: /* expression: '-' expression  */
#line 714 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2570 "yacc_sql.cpp"
    break;

  case 84: /* expression: value  */
#line 717 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 85: /* expression: rel_attr  */
#line 722 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2591 "yacc_sql.cpp"
    break;

  case 86: /* expression: '*'  */
#line 728 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 87: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 732 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 88: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 736 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 89: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 740 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 90: /* expression: SUM LBRACE RBRACE  */
#line 743 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 91: /* expression: MAX LBRACE RBRACE  */
#line 746 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 92: /* expression: MIN LBRACE RBRACE  */
#line 749 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2647 "yacc_sql.cpp"
    break;

  case 93: /* expression: AVG LBRACE RBRACE  */
#line 752 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 94: /* expression: COUNT LBRACE RBRACE  */
#line 755 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 95: /* expression: SUM LBRACE expression RBRACE  */
#line 758 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 96: /* expression: MAX LBRACE expression RBRACE  */
#line 761 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 97: /* expression: MIN LBRACE expression RBRACE  */
#line 764 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 98: /* expression: AVG LBRACE expression RBRACE  */
#line 767 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 99: /* expression: COUNT LBRACE expression RBRACE  */
#line 770 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 100: /* expression: SUM LBRACE expression_list RBRACE  */
#line 773 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 101: /* expression: MAX LBRACE expression_list RBRACE  */
#line 776 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2719 "yacc_sql.cpp"
    break;

  case 102: /* expression: MIN LBRACE expression_list RBRACE  */
#line 779 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 103: /* expression: AVG LBRACE expression_list RBRACE  */
#line 782 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 104: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 785 "yacc_sql.y"
                                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2743 "yacc_sql.cpp"
    break;

  case 105: /* expression: LBRACE select_stmt RBRACE  */
#line 788 "yacc_sql.y"
                                {
      printf("解析子查询");
      (yyval.expression) = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 106: /* expression: LBRACE value value_list RBRACE  */
#line 792 "yacc_sql.y"
                                    {
      if((yyvsp[-1].value_list) == nullptr){
        (yyvsp[-1].value_list) = new vector<Value>();
      }
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.expression) = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 2764 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID  */
#line 802 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 108: /* rel_attr: ID DOT ID  */
#line 807 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 109: /* rel_attr: ID AS ID  */
#line 814 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 110: /* rel_attr: ID DOT ID AS ID  */
#line 821 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2812 "yacc_sql.cpp"
    break;

  case 111: /* relation: ID  */
#line 833 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2820 "yacc_sql.cpp"
    break;

  case 112: /* rel_list: relation  */
#line 838 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[0].string), (yyvsp[0].string)});
      free((yyvsp[0].string));
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 113: /* rel_list: relation COMMA rel_list  */
#line 843 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-2].string), (yyvsp[-2].string)});
      free((yyvsp[-2].string));
    }
#line 2845 "yacc_sql.cpp"
    break;

  case 114: /* rel_list: relation AS ID  */
#line 853 "yacc_sql.y"
                    {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-2].string), (yyvsp[0].string)});
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 115: /* rel_list: relation ID  */
#line 859 "yacc_sql.y"
                 {
      (yyval.relation_list) = new std::unordered_map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-1].string), (yyvsp[0].string)});
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 116: /* rel_list: relation AS ID COMMA rel_list  */
#line 865 "yacc_sql.y"
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
#line 2882 "yacc_sql.cpp"
    break;

  case 117: /* rel_list: relation ID COMMA rel_list  */
#line 875 "yacc_sql.y"
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
#line 2897 "yacc_sql.cpp"
    break;

  case 118: /* rel_list: join_in  */
#line 885 "yacc_sql.y"
             {
      if((yyval.relation_list) == nullptr){
        (yyval.relation_list) = (yyvsp[0].join_list);
      }else{
        //$$->insert($$->begin(), $1);
        (yyval.relation_list) = (yyvsp[0].join_list);
      }
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 119: /* join_in_right_list: INNER JOIN relation ON condition_list  */
#line 897 "yacc_sql.y"
                                        {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-2].string), (yyvsp[-2].string)});
  }
#line 2920 "yacc_sql.cpp"
    break;

  case 120: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list  */
#line 902 "yacc_sql.y"
                                                {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-4].string), (yyvsp[-2].string)});
  }
#line 2930 "yacc_sql.cpp"
    break;

  case 121: /* join_in_right_list: INNER JOIN relation  */
#line 907 "yacc_sql.y"
                         {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[0].string),(yyvsp[0].string)});
  }
#line 2941 "yacc_sql.cpp"
    break;

  case 122: /* join_in_right_list: INNER JOIN relation AS ID  */
#line 913 "yacc_sql.y"
                               {
    (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[-2].string),(yyvsp[0].string)});
  }
#line 2952 "yacc_sql.cpp"
    break;

  case 123: /* join_in_right_list: INNER JOIN relation join_in_right_list  */
#line 919 "yacc_sql.y"
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
#line 2968 "yacc_sql.cpp"
    break;

  case 124: /* join_in_right_list: INNER JOIN relation AS ID join_in_right_list  */
#line 930 "yacc_sql.y"
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
#line 2985 "yacc_sql.cpp"
    break;

  case 125: /* join_in_right_list: INNER JOIN relation ON condition_list join_in_right_list  */
#line 942 "yacc_sql.y"
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
#line 3000 "yacc_sql.cpp"
    break;

  case 126: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list join_in_right_list  */
#line 952 "yacc_sql.y"
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
#line 3016 "yacc_sql.cpp"
    break;

  case 127: /* join_in: relation join_in_right_list  */
#line 966 "yacc_sql.y"
                             {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::unordered_map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
    free((yyvsp[-1].string));
  }
#line 3030 "yacc_sql.cpp"
    break;

  case 128: /* join_in: relation AS ID join_in_right_list  */
#line 975 "yacc_sql.y"
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
#line 3045 "yacc_sql.cpp"
    break;

  case 129: /* order_by_field: rel_attr DESC  */
#line 990 "yacc_sql.y"
                  {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3056 "yacc_sql.cpp"
    break;

  case 130: /* order_by_field: rel_attr  */
#line 996 "yacc_sql.y"
             {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 131: /* order_by_field: rel_attr ASC  */
#line 1001 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3078 "yacc_sql.cpp"
    break;

  case 132: /* order_by_field_list: %empty  */
#line 1008 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3086 "yacc_sql.cpp"
    break;

  case 133: /* order_by_field_list: order_by_field  */
#line 1011 "yacc_sql.y"
                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>> ;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
      //delete $1;
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 134: /* order_by_field_list: order_by_field COMMA order_by_field_list  */
#line 1016 "yacc_sql.y"
                                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    }
#line 3106 "yacc_sql.cpp"
    break;

  case 135: /* order_by: %empty  */
#line 1023 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 136: /* order_by: ORDER BY order_by_field_list  */
#line 1027 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      }else{
        (yyval.expression_list) = nullptr;
      }
    }
#line 3126 "yacc_sql.cpp"
    break;

  case 137: /* where: %empty  */
#line 1037 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3134 "yacc_sql.cpp"
    break;

  case 138: /* where: WHERE condition_list  */
#line 1040 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 139: /* condition_list: %empty  */
#line 1046 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3150 "yacc_sql.cpp"
    break;

  case 140: /* condition_list: condition  */
#line 1049 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3160 "yacc_sql.cpp"
    break;

  case 141: /* condition_list: condition AND condition_list  */
#line 1054 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3170 "yacc_sql.cpp"
    break;

  case 142: /* condition: rel_attr comp_op value  */
#line 1062 "yacc_sql.y"
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
#line 3186 "yacc_sql.cpp"
    break;

  case 143: /* condition: value comp_op value  */
#line 1074 "yacc_sql.y"
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
#line 3202 "yacc_sql.cpp"
    break;

  case 144: /* condition: rel_attr comp_op rel_attr  */
#line 1086 "yacc_sql.y"
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
#line 3218 "yacc_sql.cpp"
    break;

  case 145: /* condition: value comp_op rel_attr  */
#line 1098 "yacc_sql.y"
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
#line 3234 "yacc_sql.cpp"
    break;

  case 146: /* condition: expression comp_op value  */
#line 1110 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3249 "yacc_sql.cpp"
    break;

  case 147: /* condition: value comp_op expression  */
#line 1121 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
    }
#line 3264 "yacc_sql.cpp"
    break;

  case 148: /* condition: expression comp_op rel_attr  */
#line 1132 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3279 "yacc_sql.cpp"
    break;

  case 149: /* condition: rel_attr comp_op expression  */
#line 1143 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3294 "yacc_sql.cpp"
    break;

  case 150: /* condition: expression comp_op expression  */
#line 1154 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3307 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: EQ  */
#line 1165 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3313 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: LT  */
#line 1166 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3319 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: GT  */
#line 1167 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3325 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: LE  */
#line 1168 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3331 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: GE  */
#line 1169 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3337 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: NE  */
#line 1170 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3343 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: LIKE  */
#line 1171 "yacc_sql.y"
           { (yyval.comp) = LIKE_TO; }
#line 3349 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: NOT LIKE  */
#line 1172 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_TO; }
#line 3355 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: IS_  */
#line 1173 "yacc_sql.y"
          { (yyval.comp) = IS ;}
#line 3361 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: IS_ NOT  */
#line 1174 "yacc_sql.y"
              { (yyval.comp) = IS_NOT ;}
#line 3367 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: IN_T  */
#line 1175 "yacc_sql.y"
           { (yyval.comp) = IN ; }
#line 3373 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NOT IN_T  */
#line 1176 "yacc_sql.y"
               { (yyval.comp) = NOT_IN ; }
#line 3379 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: EXISTS_T  */
#line 1177 "yacc_sql.y"
               { (yyval.comp) = EXISTS ; }
#line 3385 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: NOT EXISTS_T  */
#line 1178 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXISTS ; }
#line 3391 "yacc_sql.cpp"
    break;

  case 165: /* group_by: %empty  */
#line 1183 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3399 "yacc_sql.cpp"
    break;

  case 166: /* group_by: GROUP BY expression_list  */
#line 1187 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3409 "yacc_sql.cpp"
    break;

  case 167: /* having: %empty  */
#line 1196 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3417 "yacc_sql.cpp"
    break;

  case 168: /* having: HAVING condition_list  */
#line 1200 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3427 "yacc_sql.cpp"
    break;

  case 169: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1209 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3441 "yacc_sql.cpp"
    break;

  case 170: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1222 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3450 "yacc_sql.cpp"
    break;

  case 171: /* set_variable_stmt: SET ID EQ value  */
#line 1230 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3462 "yacc_sql.cpp"
    break;


#line 3466 "yacc_sql.cpp"

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

#line 1242 "yacc_sql.y"

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
