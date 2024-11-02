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



#line 142 "yacc_sql.cpp"

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
  YYSYMBOL_SET = 40,                       /* SET  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_LOAD = 42,                      /* LOAD  */
  YYSYMBOL_DATA = 43,                      /* DATA  */
  YYSYMBOL_INFILE = 44,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 45,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 46,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 47,                    /* FORMAT  */
  YYSYMBOL_EQ = 48,                        /* EQ  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_GT = 50,                        /* GT  */
  YYSYMBOL_LE = 51,                        /* LE  */
  YYSYMBOL_GE = 52,                        /* GE  */
  YYSYMBOL_NE = 53,                        /* NE  */
  YYSYMBOL_NOT = 54,                       /* NOT  */
  YYSYMBOL_LIKE = 55,                      /* LIKE  */
  YYSYMBOL_IS_ = 56,                       /* IS_  */
  YYSYMBOL_NULL_T = 57,                    /* NULL_T  */
  YYSYMBOL_MAX = 58,                       /* MAX  */
  YYSYMBOL_MIN = 59,                       /* MIN  */
  YYSYMBOL_AVG = 60,                       /* AVG  */
  YYSYMBOL_SUM = 61,                       /* SUM  */
  YYSYMBOL_COUNT = 62,                     /* COUNT  */
  YYSYMBOL_HAVING = 63,                    /* HAVING  */
  YYSYMBOL_INNER = 64,                     /* INNER  */
  YYSYMBOL_JOIN = 65,                      /* JOIN  */
  YYSYMBOL_AS = 66,                        /* AS  */
  YYSYMBOL_UNIQUE = 67,                    /* UNIQUE  */
  YYSYMBOL_LEFT_BRACKET = 68,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 69,             /* RIGHT_BRACKET  */
  YYSYMBOL_L2_DISTANCE = 70,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 71,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 72,             /* INNER_PRODUCT  */
  YYSYMBOL_IN_T = 73,                      /* IN_T  */
  YYSYMBOL_EXISTS_T = 74,                  /* EXISTS_T  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 76,                     /* FLOAT  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_79_ = 79,                       /* '+'  */
  YYSYMBOL_80_ = 80,                       /* '-'  */
  YYSYMBOL_81_ = 81,                       /* '*'  */
  YYSYMBOL_82_ = 82,                       /* '/'  */
  YYSYMBOL_UMINUS = 83,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 84,                  /* $accept  */
  YYSYMBOL_commands = 85,                  /* commands  */
  YYSYMBOL_command_wrapper = 86,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 87,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 88,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 89,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 90,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 91,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 92,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 93,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 94,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 95,           /* desc_table_stmt  */
  YYSYMBOL_index_type = 96,                /* index_type  */
  YYSYMBOL_create_index_stmt = 97,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 98,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 99,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 100,            /* attr_def_list  */
  YYSYMBOL_attr_def = 101,                 /* attr_def  */
  YYSYMBOL_not_null = 102,                 /* not_null  */
  YYSYMBOL_number = 103,                   /* number  */
  YYSYMBOL_type = 104,                     /* type  */
  YYSYMBOL_insert_stmt = 105,              /* insert_stmt  */
  YYSYMBOL_value_list = 106,               /* value_list  */
  YYSYMBOL_value = 107,                    /* value  */
  YYSYMBOL_float_list = 108,               /* float_list  */
  YYSYMBOL_storage_format = 109,           /* storage_format  */
  YYSYMBOL_delete_stmt = 110,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 111,              /* update_stmt  */
  YYSYMBOL_update_unite_list = 112,        /* update_unite_list  */
  YYSYMBOL_update_unite = 113,             /* update_unite  */
  YYSYMBOL_create_table_select_stmt = 114, /* create_table_select_stmt  */
  YYSYMBOL_select_stmt = 115,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 116,                /* calc_stmt  */
  YYSYMBOL_expression_list = 117,          /* expression_list  */
  YYSYMBOL_expression = 118,               /* expression  */
  YYSYMBOL_rel_attr = 119,                 /* rel_attr  */
  YYSYMBOL_relation = 120,                 /* relation  */
  YYSYMBOL_rel_list = 121,                 /* rel_list  */
  YYSYMBOL_join_in_right_list = 122,       /* join_in_right_list  */
  YYSYMBOL_join_in = 123,                  /* join_in  */
  YYSYMBOL_order_by_field = 124,           /* order_by_field  */
  YYSYMBOL_order_by_field_list = 125,      /* order_by_field_list  */
  YYSYMBOL_order_by = 126,                 /* order_by  */
  YYSYMBOL_where = 127,                    /* where  */
  YYSYMBOL_condition_list = 128,           /* condition_list  */
  YYSYMBOL_condition = 129,                /* condition  */
  YYSYMBOL_comp_op = 130,                  /* comp_op  */
  YYSYMBOL_group_by = 131,                 /* group_by  */
  YYSYMBOL_having = 132,                   /* having  */
  YYSYMBOL_load_data_stmt = 133,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 134,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 135,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 136             /* opt_semicolon  */
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
#define YYLAST   479

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  309

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
       2,     2,    81,    79,     2,    80,     2,    82,     2,     2,
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
      75,    76,    77,    78,    83
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   248,   248,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   280,   286,   291,   297,   303,   309,
     315,   322,   328,   336,   338,   343,   361,   371,   395,   398,
     411,   421,   433,   434,   435,   438,   441,   442,   443,   444,
     445,   448,   465,   468,   479,   483,   487,   493,   497,   505,
     506,   511,   516,   525,   538,   541,   548,   560,   572,   578,
     591,   600,   606,   629,   665,   674,   679,   690,   693,   696,
     699,   702,   706,   709,   714,   720,   723,   727,   731,   735,
     738,   741,   744,   747,   750,   753,   756,   759,   762,   765,
     768,   771,   774,   777,   780,   784,   794,   799,   806,   813,
     825,   830,   835,   845,   851,   857,   867,   877,   889,   894,
     899,   905,   911,   922,   934,   944,   958,   967,   982,   988,
     993,  1000,  1003,  1008,  1015,  1018,  1029,  1032,  1038,  1041,
    1046,  1053,  1065,  1077,  1089,  1101,  1112,  1123,  1134,  1145,
    1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,
    1167,  1168,  1169,  1170,  1175,  1178,  1188,  1191,  1200,  1213,
    1221,  1231,  1232
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
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NOT", "LIKE", "IS_", "NULL_T", "MAX", "MIN", "AVG", "SUM",
  "COUNT", "HAVING", "INNER", "JOIN", "AS", "UNIQUE", "LEFT_BRACKET",
  "RIGHT_BRACKET", "L2_DISTANCE", "COSINE_DISTANCE", "INNER_PRODUCT",
  "IN_T", "EXISTS_T", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt", "index_type",
  "create_index_stmt", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "not_null", "number", "type", "insert_stmt",
  "value_list", "value", "float_list", "storage_format", "delete_stmt",
  "update_stmt", "update_unite_list", "update_unite",
  "create_table_select_stmt", "select_stmt", "calc_stmt",
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

#define YYPACT_NINF (-233)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     397,    -6,    13,   312,   312,   -45,    26,  -233,     6,    16,
     -27,  -233,  -233,  -233,  -233,  -233,   -19,    17,   397,    71,
      80,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,    33,  -233,   128,    75,    76,    99,  -233,   120,
     133,   144,   151,   152,   -28,   162,   167,   168,  -233,  -233,
     -11,  -233,   312,  -233,  -233,  -233,   145,  -233,   112,  -233,
    -233,    89,   113,   165,   160,   166,  -233,  -233,  -233,  -233,
     -14,   143,  -233,   182,    34,   206,    15,   141,   208,   233,
     260,   285,   209,   219,   177,   312,   312,   312,   170,   171,
    -233,   312,   312,   312,   312,   312,   174,   216,   215,   179,
      72,   180,   198,   244,   218,   200,    72,   265,  -233,  -233,
    -233,   274,    -4,  -233,   275,   115,  -233,   276,   159,  -233,
     277,   192,  -233,   278,   326,   -28,   -28,  -233,   155,   181,
     316,   236,  -233,  -233,    -2,    -2,  -233,  -233,  -233,   -15,
     215,  -233,   291,   312,  -233,   267,   215,   293,  -233,   288,
      -1,   301,  -233,   248,  -233,   303,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,   312,
     312,   312,   250,   174,   264,   257,   327,  -233,   347,    72,
     405,   395,   405,  -233,   313,   312,  -233,   179,   345,  -233,
    -233,  -233,  -233,  -233,   -12,   198,   336,   338,  -233,    42,
      46,    51,  -233,  -233,   174,   -10,   174,   359,   304,   303,
    -233,  -233,  -233,  -233,  -233,  -233,   -30,  -233,   314,  -233,
    -233,   312,   312,   312,   312,    64,  -233,   298,   302,   319,
    -233,  -233,   301,   332,   174,  -233,  -233,  -233,   -31,   174,
    -233,  -233,   312,   312,   371,   363,  -233,  -233,  -233,  -233,
    -233,    64,  -233,  -233,    64,  -233,  -233,    64,  -233,  -233,
    -233,  -233,   364,  -233,  -233,   334,   244,   369,   312,   317,
    -233,  -233,  -233,  -233,   394,  -233,  -233,   -23,   352,  -233,
    -233,   337,   -24,   325,  -233,   335,  -233,   312,  -233,    90,
     396,  -233,  -233,   337,  -233,  -233,   325,  -233,  -233
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     171,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,    23,     4,     3,    18,
      19,    20,     0,    34,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,    59,     0,     0,     0,    54,    55,
     106,    56,     0,    85,    83,    74,    75,    84,     0,    32,
      31,     0,     0,     0,     0,     0,   169,     1,   172,     2,
       0,     0,    30,     0,    83,     0,     0,     0,     0,     0,
       0,     0,    61,    60,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,     0,     0,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,    81,
      90,     0,     0,    91,     0,     0,    92,     0,     0,    89,
       0,     0,    93,     0,     0,    59,    59,    58,     0,     0,
       0,   107,   108,    76,    77,    78,    79,    80,   110,   111,
     136,   117,     0,   138,    66,     0,   136,    68,   170,     0,
       0,    38,    71,     0,    36,    52,   105,   100,    95,   101,
      96,   102,    97,    99,    94,   103,    98,    62,    63,     0,
       0,     0,     0,     0,     0,     0,   114,   126,   164,     0,
      83,     0,    84,   137,   139,     0,    67,     0,     0,    46,
      47,    48,    49,    50,    42,     0,     0,     0,    53,     0,
       0,     0,   109,   112,     0,   113,     0,     0,   166,    52,
     150,   151,   152,   153,   154,   155,     0,   156,   158,   160,
     162,     0,     0,     0,   138,    70,    69,     0,     0,     0,
      43,    41,    38,    64,     0,    86,    87,    88,   120,     0,
     127,   116,     0,   138,   134,     0,   157,   161,   163,   159,
      83,   146,    84,    83,   149,    84,    83,   148,    84,   140,
     168,    45,     0,    44,    39,     0,    37,     0,   138,     0,
     122,   115,   165,   167,     0,    73,    51,    42,     0,    72,
      35,   118,   121,   131,    40,     0,   124,   138,   123,   129,
     132,   135,    65,   119,   128,   130,   131,   125,   133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -233,  -233,   400,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,   178,   220,   137,  -233,
    -233,  -233,  -153,   -47,   -17,  -233,  -233,  -233,   229,  -233,
    -233,   -43,  -233,    -3,    12,  -142,   213,  -177,  -210,  -233,
    -233,   122,  -233,  -136,  -232,  -233,   -57,  -233,  -233,  -233,
    -233,  -233,  -233
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    44,    30,    31,    32,   206,   161,   241,   272,
     204,    33,   117,    64,    94,   276,    34,    35,   156,   157,
      36,    37,    38,    65,   191,    67,   149,   150,   187,   151,
     300,   301,   285,   154,   193,   194,   231,   218,   254,    39,
      40,    41,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    68,   269,    42,    85,   250,   213,   112,   183,   238,
     278,   192,   208,   249,   188,    66,    66,   297,   168,   101,
     196,   283,    45,    98,    46,   256,   199,   200,   201,   202,
     203,   239,    69,   184,   240,   279,    70,   119,   280,   251,
     184,    71,   239,   257,   258,   240,   291,    92,    93,   184,
      73,   185,   113,    72,   184,    99,   -52,   116,    74,    86,
      75,    43,   186,   158,   245,   303,   255,   277,   246,   165,
     162,    77,   281,   247,   100,   102,   103,   104,   105,   104,
     105,   296,   298,    78,   121,   124,   127,   130,   133,   262,
     265,   268,   192,   307,   102,   103,   104,   105,   143,   122,
     125,   128,   131,   134,   304,   305,   190,   138,   139,   140,
      80,   192,     4,    66,   144,   145,   146,   147,   177,   178,
      47,   102,   103,   104,   105,   102,   103,   104,   105,    48,
     102,   103,   104,   105,   232,   233,   192,   170,   101,    81,
      54,    87,   219,   102,   103,   104,   105,    58,    59,   106,
      61,   299,    82,    83,    88,   192,    48,    49,    50,    51,
      52,    53,    47,   120,   299,    89,   107,    54,   101,    55,
      56,    57,    90,    91,    58,    59,    60,    61,   179,    62,
      63,   172,   101,    95,   260,   263,   266,   190,    96,    97,
     108,   209,   210,   211,   102,   103,   104,   105,    48,    49,
      50,    51,    52,    53,   180,   109,   190,   235,   110,    54,
     111,    55,    56,    57,   174,   101,    58,    59,    60,    61,
     114,    62,    63,   115,   102,   103,   104,   105,   118,    47,
     123,   190,   135,   289,   102,   103,   104,   105,   102,   103,
     104,   105,   136,   261,   264,   267,   137,   141,   142,   282,
     190,   148,   152,   153,    47,   126,   155,     4,   159,   163,
     102,   103,   104,   105,    66,    48,    49,    50,    51,    52,
      53,   102,   103,   104,   105,   160,    54,   164,    55,    56,
      57,    47,   129,    58,    59,    60,    61,   166,    62,    63,
      48,    49,    50,    51,    52,    53,   167,   169,   171,   173,
     175,    54,   182,    55,    56,    57,    47,   132,    58,    59,
      60,    61,   189,    62,    63,   195,   197,    48,    49,    50,
      51,    52,    53,   198,   205,   207,   116,   212,    54,   214,
      55,    56,    57,    47,   215,    58,    59,    60,    61,   181,
      62,    63,    48,    49,    50,    51,    52,    53,   176,   101,
     216,   217,   234,    54,   237,    55,    56,    57,   243,   244,
      58,    59,    60,    61,   252,    62,    63,   253,   259,    48,
      49,    50,    51,    52,    53,   270,   273,   271,   275,   284,
      54,   288,    55,    56,    57,   286,   287,    58,    59,    60,
      61,   290,    62,    63,   292,   102,   103,   104,   105,   293,
     295,   184,    60,     1,     2,   102,   103,   104,   105,     3,
       4,     5,   302,     6,     7,     8,     9,    10,    76,   306,
     274,    11,    12,    13,   294,   242,   236,   248,   308,    14,
      15,     0,     0,     0,     0,     0,     0,    16,     0,    17,
       0,     0,    18,   220,   221,   222,   223,   224,   225,   226,
     227,   228,     0,   220,   221,   222,   223,   224,   225,   226,
     227,   228,     0,     0,     0,     0,     0,     0,   229,   230,
       0,     0,     0,     0,   102,   103,   104,   105,   229,   230
};

static const yytype_int16 yycheck[] =
{
      47,     4,   234,     9,    47,   215,   183,    21,    23,    21,
      41,   153,   165,    23,   150,     3,     4,    41,    22,    23,
     156,   253,     9,    34,    11,    55,    27,    28,    29,    30,
      31,    54,    77,    64,    57,    66,    10,    22,   248,   216,
      64,    35,    54,    73,    74,    57,   278,    75,    76,    64,
      77,    66,    66,    37,    64,    66,    22,    23,    77,    47,
      43,    67,    77,   110,    22,   297,   219,   244,    22,   116,
     113,     0,   249,    22,    62,    79,    80,    81,    82,    81,
      82,   291,   292,     3,    87,    88,    89,    90,    91,   231,
     232,   233,   234,   303,    79,    80,    81,    82,   101,    87,
      88,    89,    90,    91,    14,    15,   153,    95,    96,    97,
      77,   253,    13,   101,   102,   103,   104,   105,   135,   136,
      21,    79,    80,    81,    82,    79,    80,    81,    82,    57,
      79,    80,    81,    82,   191,   192,   278,    22,    23,    11,
      68,    21,   189,    79,    80,    81,    82,    75,    76,    37,
      78,   293,    77,    77,    21,   297,    57,    58,    59,    60,
      61,    62,    21,    22,   306,    21,    77,    68,    23,    70,
      71,    72,    21,    21,    75,    76,    77,    78,    23,    80,
      81,    22,    23,    21,   231,   232,   233,   234,    21,    21,
      77,   179,   180,   181,    79,    80,    81,    82,    57,    58,
      59,    60,    61,    62,    23,    40,   253,   195,    48,    68,
      44,    70,    71,    72,    22,    23,    75,    76,    77,    78,
      77,    80,    81,    41,    79,    80,    81,    82,    22,    21,
      22,   278,    23,   276,    79,    80,    81,    82,    79,    80,
      81,    82,    23,   231,   232,   233,    69,    77,    77,   252,
     297,    77,    36,    38,    21,    22,    77,    13,    78,    41,
      79,    80,    81,    82,   252,    57,    58,    59,    60,    61,
      62,    79,    80,    81,    82,    77,    68,    77,    70,    71,
      72,    21,    22,    75,    76,    77,    78,    22,    80,    81,
      57,    58,    59,    60,    61,    62,    22,    22,    22,    22,
      22,    68,    66,    70,    71,    72,    21,    22,    75,    76,
      77,    78,    21,    80,    81,    48,    23,    57,    58,    59,
      60,    61,    62,    35,    23,    77,    23,    77,    68,    65,
      70,    71,    72,    21,    77,    75,    76,    77,    78,    23,
      80,    81,    57,    58,    59,    60,    61,    62,    22,    23,
      23,     4,    39,    68,     9,    70,    71,    72,    22,    21,
      75,    76,    77,    78,     5,    80,    81,    63,    54,    57,
      58,    59,    60,    61,    62,    77,    57,    75,    46,     8,
      68,    47,    70,    71,    72,    22,    22,    75,    76,    77,
      78,    22,    80,    81,    77,    79,    80,    81,    82,     5,
      48,    64,    77,     6,     7,    79,    80,    81,    82,    12,
      13,    14,    77,    16,    17,    18,    19,    20,    18,    23,
     242,    24,    25,    26,   287,   205,   197,   214,   306,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,
      -1,    -1,    45,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    79,    80,    81,    82,    73,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    12,    13,    14,    16,    17,    18,    19,
      20,    24,    25,    26,    32,    33,    40,    42,    45,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      97,    98,    99,   105,   110,   111,   114,   115,   116,   133,
     134,   135,     9,    67,    96,     9,    11,    21,    57,    58,
      59,    60,    61,    62,    68,    70,    71,    72,    75,    76,
      77,    78,    80,    81,   107,   117,   118,   119,   117,    77,
      10,    35,    37,    77,    77,    43,    86,     0,     3,   136,
      77,    11,    77,    77,   107,   115,   118,    21,    21,    21,
      21,    21,    75,    76,   108,    21,    21,    21,    34,    66,
     118,    23,    79,    80,    81,    82,    37,    77,    77,    40,
      48,    44,    21,    66,    77,    41,    23,   106,    22,    22,
      22,   117,   118,    22,   117,   118,    22,   117,   118,    22,
     117,   118,    22,   117,   118,    23,    23,    69,   118,   118,
     118,    77,    77,   117,   118,   118,   118,   118,    77,   120,
     121,   123,    36,    38,   127,    77,   112,   113,   107,    78,
      77,   101,   115,    41,    77,   107,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,   108,   108,    23,
      23,    23,    66,    23,    64,    66,    77,   122,   127,    21,
     107,   118,   119,   128,   129,    48,   127,    23,    35,    27,
      28,    29,    30,    31,   104,    23,   100,    77,   106,   118,
     118,   118,    77,   121,    65,    77,    23,     4,   131,   107,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    73,
      74,   130,   130,   130,    39,   118,   112,     9,    21,    54,
      57,   102,   101,    22,    21,    22,    22,    22,   120,    23,
     122,   121,     5,    63,   132,   106,    55,    73,    74,    54,
     107,   118,   119,   107,   118,   119,   107,   118,   119,   128,
      77,    75,   103,    57,   100,    46,   109,   121,    41,    66,
     122,   121,   117,   128,     8,   126,    22,    22,    47,   115,
      22,   128,    77,     5,   102,    48,   122,    41,   122,   119,
     124,   125,    77,   128,    14,    15,    23,   122,   125
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    96,    97,    98,    99,   100,   100,
     101,   101,   102,   102,   102,   103,   104,   104,   104,   104,
     104,   105,   106,   106,   107,   107,   107,   107,   107,   108,
     108,   108,   108,   108,   109,   109,   110,   111,   112,   112,
     113,   114,   114,   115,   116,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     120,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   133,   134,
     135,   136,   136
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
       3,     5,     9,     8,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     1,     6,     6,     6,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     4,     1,     3,     3,     5,
       1,     1,     3,     3,     2,     5,     4,     1,     5,     7,
       3,     5,     4,     6,     6,     8,     2,     4,     2,     1,
       2,     0,     1,     3,     0,     3,     0,     2,     0,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     2,     1,     2,     0,     3,     0,     2,     7,     2,
       4,     0,     1
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
#line 249 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1930 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 280 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1939 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 291 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1955 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 297 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1963 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 309 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1979 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 322 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1997 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 328 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 33: /* index_type: %empty  */
#line 336 "yacc_sql.y"
  {
      (yyval.bools) = false;
  }
#line 2015 "yacc_sql.cpp"
    break;

  case 34: /* index_type: UNIQUE  */
#line 338 "yacc_sql.y"
           {
      (yyval.bools) = true;
  }
#line 2023 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE index_type INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 344 "yacc_sql.y"
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
#line 2042 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 362 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 372 "yacc_sql.y"
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
#line 2079 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 395 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 399 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2101 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE not_null  */
#line 412 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if((yyval.attr_info)->type == AttrType::VECTORS){(yyval.attr_info)->set_vector_type_length((yyvsp[-2].number));}
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-5].string));
    }
#line 2115 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type not_null  */
#line 422 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyvsp[0].number) == 1 ? (yyval.attr_info)->not_null = true : (yyval.attr_info)->not_null = false;
      free((yyvsp[-2].string));
    }
#line 2128 "yacc_sql.cpp"
    break;

  case 42: /* not_null: %empty  */
#line 433 "yacc_sql.y"
    {(yyval.number) = 0;}
#line 2134 "yacc_sql.cpp"
    break;

  case 43: /* not_null: NULL_T  */
#line 434 "yacc_sql.y"
             {(yyval.number) = 0;}
#line 2140 "yacc_sql.cpp"
    break;

  case 44: /* not_null: NOT NULL_T  */
#line 435 "yacc_sql.y"
                 {(yyval.number) = 1;}
#line 2146 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 438 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2152 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 441 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2158 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 442 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2164 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 443 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2170 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 444 "yacc_sql.y"
              { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2176 "yacc_sql.cpp"
    break;

  case 50: /* type: VECTOR_T  */
#line 445 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2182 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 449 "yacc_sql.y"
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
#line 2199 "yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 465 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2207 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 468 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2221 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 479 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 483 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 487 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2250 "yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 493 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2259 "yacc_sql.cpp"
    break;

  case 58: /* value: LEFT_BRACKET float_list RIGHT_BRACKET  */
#line 498 "yacc_sql.y"
    {
      (yyval.value) = new Value();
      (yyval.value)->set_vector(*(yyvsp[-1].float_list));
    }
#line 2268 "yacc_sql.cpp"
    break;

  case 59: /* float_list: %empty  */
#line 505 "yacc_sql.y"
    { (yyval.float_list) = nullptr;}
#line 2274 "yacc_sql.cpp"
    break;

  case 60: /* float_list: FLOAT  */
#line 507 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].floats));
    }
#line 2283 "yacc_sql.cpp"
    break;

  case 61: /* float_list: NUMBER  */
#line 512 "yacc_sql.y"
    {
      (yyval.float_list) = new std::vector<float>;
      (yyval.float_list)->push_back((yyvsp[0].number));
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 62: /* float_list: NUMBER COMMA float_list  */
#line 517 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].number));
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 63: /* float_list: FLOAT COMMA float_list  */
#line 526 "yacc_sql.y"
    {
      if ((yyvsp[0].float_list) != nullptr) {
        (yyval.float_list) = (yyvsp[0].float_list);
      } else {
        (yyval.float_list) = new std::vector<float>;
      }
      (yyval.float_list)->insert((yyval.float_list)->begin(), (yyvsp[-2].floats));
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 538 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 542 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2334 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 549 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET update_unite_list where  */
#line 561 "yacc_sql.y"
    {
      printf("解析update语句");
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.table_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_unites.swap(*(yyvsp[-1].update_unite_list));
      if( (yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      }
    }
#line 2362 "yacc_sql.cpp"
    break;

  case 68: /* update_unite_list: update_unite  */
#line 573 "yacc_sql.y"
    {
      printf("解析update_unite_list为单个 unite list");
      (yyval.update_unite_list) = new std::vector<UpdateUnite>;
      (yyval.update_unite_list)->push_back(*(yyvsp[0].update_unite));
    }
#line 2372 "yacc_sql.cpp"
    break;

  case 69: /* update_unite_list: update_unite COMMA update_unite_list  */
#line 579 "yacc_sql.y"
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
#line 2387 "yacc_sql.cpp"
    break;

  case 70: /* update_unite: ID EQ expression  */
#line 592 "yacc_sql.y"
    {
      printf("解析update unite");
      (yyval.update_unite) = new UpdateUnite();
      (yyval.update_unite)->field_name = (yyvsp[-2].string);
      (yyval.update_unite)->expression = (yyvsp[0].expression);
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 71: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 600 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
      (yyval.sql_node)->create_table_select.table_name    = (yyvsp[-2].string);
      (yyval.sql_node)->create_table_select.sql_node      = (yyvsp[0].sql_node); 
      free((yyvsp[-2].string));
    }
#line 2409 "yacc_sql.cpp"
    break;

  case 72: /* create_table_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format select_stmt  */
#line 607 "yacc_sql.y"
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
#line 2434 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list FROM rel_list where group_by having order_by  */
#line 630 "yacc_sql.y"
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
#line 2472 "yacc_sql.cpp"
    break;

  case 74: /* calc_stmt: CALC expression_list  */
#line 666 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: expression  */
#line 675 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: expression COMMA expression_list  */
#line 680 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 77: /* expression: expression '+' expression  */
#line 690 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 78: /* expression: expression '-' expression  */
#line 693 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '*' expression  */
#line 696 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '/' expression  */
#line 699 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 81: /* expression: LBRACE expression RBRACE  */
#line 702 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 82: /* expression: '-' expression  */
#line 706 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 83: /* expression: value  */
#line 709 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 84: /* expression: rel_attr  */
#line 714 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name, node->alias);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 85: /* expression: '*'  */
#line 720 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 86: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 724 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 87: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 728 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 88: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 732 "yacc_sql.y"
    {
      (yyval.expression) = create_vector_function_expression(VectorFunctionExpr::VECTOR_FUNCTION::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2606 "yacc_sql.cpp"
    break;

  case 89: /* expression: SUM LBRACE RBRACE  */
#line 735 "yacc_sql.y"
                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2614 "yacc_sql.cpp"
    break;

  case 90: /* expression: MAX LBRACE RBRACE  */
#line 738 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 91: /* expression: MIN LBRACE RBRACE  */
#line 741 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 92: /* expression: AVG LBRACE RBRACE  */
#line 744 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 93: /* expression: COUNT LBRACE RBRACE  */
#line 747 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 94: /* expression: SUM LBRACE expression RBRACE  */
#line 750 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("SUM", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 95: /* expression: MAX LBRACE expression RBRACE  */
#line 753 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MAX", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 96: /* expression: MIN LBRACE expression RBRACE  */
#line 756 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("MIN", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 97: /* expression: AVG LBRACE expression RBRACE  */
#line 759 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("AVG", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 98: /* expression: COUNT LBRACE expression RBRACE  */
#line 762 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("COUNT", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 99: /* expression: SUM LBRACE expression_list RBRACE  */
#line 765 "yacc_sql.y"
                                        {
      (yyval.expression) = create_aggregate_expression("SUM", nullptr, sql_string, &(yyloc));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 100: /* expression: MAX LBRACE expression_list RBRACE  */
#line 768 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MAX", nullptr, sql_string, &(yyloc));
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 101: /* expression: MIN LBRACE expression_list RBRACE  */
#line 771 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("MIN", nullptr, sql_string, &(yyloc));
    }
#line 2710 "yacc_sql.cpp"
    break;

  case 102: /* expression: AVG LBRACE expression_list RBRACE  */
#line 774 "yacc_sql.y"
                                       {
      (yyval.expression) = create_aggregate_expression("AVG", nullptr, sql_string, &(yyloc));
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 103: /* expression: COUNT LBRACE expression_list RBRACE  */
#line 777 "yacc_sql.y"
                                         {
      (yyval.expression) = create_aggregate_expression("COUNT", nullptr, sql_string, &(yyloc));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 104: /* expression: LBRACE select_stmt RBRACE  */
#line 780 "yacc_sql.y"
                                {
      printf("解析子查询");
      (yyval.expression) = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 105: /* expression: LBRACE value value_list RBRACE  */
#line 784 "yacc_sql.y"
                                    {
      if((yyvsp[-1].value_list) == nullptr){
        (yyvsp[-1].value_list) = new vector<Value>();
      }
      (yyvsp[-1].value_list)->push_back(*(yyvsp[-2].value));
      (yyval.expression) = new ValueListExpr(*(yyvsp[-1].value_list));
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 106: /* rel_attr: ID  */
#line 794 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2757 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID DOT ID  */
#line 799 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 108: /* rel_attr: ID AS ID  */
#line 806 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 109: /* rel_attr: ID DOT ID AS ID  */
#line 813 "yacc_sql.y"
                     {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias          = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 110: /* relation: ID  */
#line 825 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 111: /* rel_list: relation  */
#line 830 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[0].string), (yyvsp[0].string)});
      free((yyvsp[0].string));
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 112: /* rel_list: relation COMMA rel_list  */
#line 835 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::map<std::string, std::string>();
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-2].string), (yyvsp[-2].string)});
      free((yyvsp[-2].string));
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 113: /* rel_list: relation AS ID  */
#line 845 "yacc_sql.y"
                    {
      (yyval.relation_list) = new std::map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-2].string), (yyvsp[0].string)});
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 114: /* rel_list: relation ID  */
#line 851 "yacc_sql.y"
                 {
      (yyval.relation_list) = new std::map<std::string, std::string>();
      (yyval.relation_list)->insert({(yyvsp[-1].string), (yyvsp[0].string)});
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 115: /* rel_list: relation AS ID COMMA rel_list  */
#line 857 "yacc_sql.y"
                                   {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::map<std::string, std::string>();
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-4].string), (yyvsp[-2].string)});
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 116: /* rel_list: relation ID COMMA rel_list  */
#line 867 "yacc_sql.y"
                                {
      if ((yyvsp[0].relation_list)!= nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::map<std::string, std::string>();
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), {(yyvsp[-3].string), (yyvsp[-2].string)});
      free((yyvsp[-3].string));
      free((yyvsp[-2].string));
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 117: /* rel_list: join_in  */
#line 877 "yacc_sql.y"
             {
      if((yyval.relation_list) == nullptr){
        (yyval.relation_list) = (yyvsp[0].join_list);
      }else{
        //$$->insert($$->begin(), $1);
        (yyval.relation_list) = (yyvsp[0].join_list);
      }
    }
#line 2893 "yacc_sql.cpp"
    break;

  case 118: /* join_in_right_list: INNER JOIN relation ON condition_list  */
#line 889 "yacc_sql.y"
                                        {
    (yyval.join_list) = new std::map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-2].string), (yyvsp[-2].string)});
  }
#line 2903 "yacc_sql.cpp"
    break;

  case 119: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list  */
#line 894 "yacc_sql.y"
                                                {
    (yyval.join_list) = new std::map<std::string, std::string>();
    join_conditions.push_back((yyvsp[0].condition_list));
    (yyval.join_list)->insert({(yyvsp[-4].string), (yyvsp[-2].string)});
  }
#line 2913 "yacc_sql.cpp"
    break;

  case 120: /* join_in_right_list: INNER JOIN relation  */
#line 899 "yacc_sql.y"
                         {
    (yyval.join_list) = new std::map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[0].string),(yyvsp[0].string)});
  }
#line 2924 "yacc_sql.cpp"
    break;

  case 121: /* join_in_right_list: INNER JOIN relation AS ID  */
#line 905 "yacc_sql.y"
                               {
    (yyval.join_list) = new std::map<std::string, std::string>();
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    (yyval.join_list)->insert({(yyvsp[-2].string),(yyvsp[0].string)});
  }
#line 2935 "yacc_sql.cpp"
    break;

  case 122: /* join_in_right_list: INNER JOIN relation join_in_right_list  */
#line 911 "yacc_sql.y"
                                           {
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
      free((yyvsp[-1].string));
  }
#line 2951 "yacc_sql.cpp"
    break;

  case 123: /* join_in_right_list: INNER JOIN relation AS ID join_in_right_list  */
#line 922 "yacc_sql.y"
                                                 {
    std::vector<ConditionSqlNode>* temp = new std::vector<ConditionSqlNode>();
    join_conditions.push_back(temp);
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-1].string)});
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
  }
#line 2968 "yacc_sql.cpp"
    break;

  case 124: /* join_in_right_list: INNER JOIN relation ON condition_list join_in_right_list  */
#line 934 "yacc_sql.y"
                                                            {
    join_conditions.push_back((yyvsp[-1].condition_list));
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-3].string)});
      free((yyvsp[-3].string));
  }
#line 2983 "yacc_sql.cpp"
    break;

  case 125: /* join_in_right_list: INNER JOIN relation AS ID ON condition_list join_in_right_list  */
#line 944 "yacc_sql.y"
                                                                  {
    join_conditions.push_back((yyvsp[-1].condition_list));
    if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new std::map<std::string, std::string>();
      }
      (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-5].string), (yyvsp[-3].string)});
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
  }
#line 2999 "yacc_sql.cpp"
    break;

  case 126: /* join_in: relation join_in_right_list  */
#line 958 "yacc_sql.y"
                             {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-1].string), (yyvsp[-1].string)});
    free((yyvsp[-1].string));
  }
#line 3013 "yacc_sql.cpp"
    break;

  case 127: /* join_in: relation AS ID join_in_right_list  */
#line 967 "yacc_sql.y"
                                     {
    if ((yyvsp[0].join_list) != nullptr) {
      (yyval.join_list) = (yyvsp[0].join_list);
    } else{
      (yyval.join_list) = new std::map<std::string, std::string>();
    }
    (yyval.join_list)->insert((yyval.join_list)->begin(), {(yyvsp[-3].string), (yyvsp[-1].string)});
    free((yyvsp[-3].string));
    free((yyvsp[-1].string));
  }
#line 3028 "yacc_sql.cpp"
    break;

  case 128: /* order_by_field: rel_attr DESC  */
#line 982 "yacc_sql.y"
                  {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,false);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 129: /* order_by_field: rel_attr  */
#line 988 "yacc_sql.y"
             {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 3050 "yacc_sql.cpp"
    break;

  case 130: /* order_by_field: rel_attr ASC  */
#line 993 "yacc_sql.y"
                    {
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.expression) = new UnboundORderedFieldExpr(node->relation_name, node->attribute_name,true);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].rel_attr);
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 131: /* order_by_field_list: %empty  */
#line 1000 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 132: /* order_by_field_list: order_by_field  */
#line 1003 "yacc_sql.y"
                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>> ;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
      //delete $1;
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 133: /* order_by_field_list: order_by_field COMMA order_by_field_list  */
#line 1008 "yacc_sql.y"
                                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      //delete $1; 我也不知道为啥，有这个和上一个delect 会报错
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 134: /* order_by: %empty  */
#line 1015 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3097 "yacc_sql.cpp"
    break;

  case 135: /* order_by: ORDER BY order_by_field_list  */
#line 1019 "yacc_sql.y"
    {
      if((yyvsp[0].expression_list) != nullptr){
        (yyval.expression_list) = (yyvsp[0].expression_list);
      }else{
        (yyval.expression_list) = nullptr;
      }
    }
#line 3109 "yacc_sql.cpp"
    break;

  case 136: /* where: %empty  */
#line 1029 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 137: /* where: WHERE condition_list  */
#line 1032 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 138: /* condition_list: %empty  */
#line 1038 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3133 "yacc_sql.cpp"
    break;

  case 139: /* condition_list: condition  */
#line 1041 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3143 "yacc_sql.cpp"
    break;

  case 140: /* condition_list: condition AND condition_list  */
#line 1046 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3153 "yacc_sql.cpp"
    break;

  case 141: /* condition: rel_attr comp_op value  */
#line 1054 "yacc_sql.y"
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
#line 3169 "yacc_sql.cpp"
    break;

  case 142: /* condition: value comp_op value  */
#line 1066 "yacc_sql.y"
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
#line 3185 "yacc_sql.cpp"
    break;

  case 143: /* condition: rel_attr comp_op rel_attr  */
#line 1078 "yacc_sql.y"
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
#line 3201 "yacc_sql.cpp"
    break;

  case 144: /* condition: value comp_op rel_attr  */
#line 1090 "yacc_sql.y"
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
#line 3217 "yacc_sql.cpp"
    break;

  case 145: /* condition: expression comp_op value  */
#line 1102 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 3232 "yacc_sql.cpp"
    break;

  case 146: /* condition: value comp_op expression  */
#line 1113 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
    }
#line 3247 "yacc_sql.cpp"
    break;

  case 147: /* condition: expression comp_op rel_attr  */
#line 1124 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 3262 "yacc_sql.cpp"
    break;

  case 148: /* condition: rel_attr comp_op expression  */
#line 1135 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
    }
#line 3277 "yacc_sql.cpp"
    break;

  case 149: /* condition: expression comp_op expression  */
#line 1146 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_expr = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_is_expr = 1;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3290 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: EQ  */
#line 1157 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3296 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: LT  */
#line 1158 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3302 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: GT  */
#line 1159 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3308 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: LE  */
#line 1160 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3314 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: GE  */
#line 1161 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3320 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: NE  */
#line 1162 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3326 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: LIKE  */
#line 1163 "yacc_sql.y"
           { (yyval.comp) = LIKE_TO; }
#line 3332 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: NOT LIKE  */
#line 1164 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_TO; }
#line 3338 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: IS_  */
#line 1165 "yacc_sql.y"
          { (yyval.comp) = IS ;}
#line 3344 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: IS_ NOT  */
#line 1166 "yacc_sql.y"
              { (yyval.comp) = IS_NOT ;}
#line 3350 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: IN_T  */
#line 1167 "yacc_sql.y"
           { (yyval.comp) = IN ; }
#line 3356 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: NOT IN_T  */
#line 1168 "yacc_sql.y"
               { (yyval.comp) = NOT_IN ; }
#line 3362 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: EXISTS_T  */
#line 1169 "yacc_sql.y"
               { (yyval.comp) = EXISTS ; }
#line 3368 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: NOT EXISTS_T  */
#line 1170 "yacc_sql.y"
                   { (yyval.comp) = NOT_EXISTS ; }
#line 3374 "yacc_sql.cpp"
    break;

  case 164: /* group_by: %empty  */
#line 1175 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3382 "yacc_sql.cpp"
    break;

  case 165: /* group_by: GROUP BY expression_list  */
#line 1179 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 3392 "yacc_sql.cpp"
    break;

  case 166: /* having: %empty  */
#line 1188 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3400 "yacc_sql.cpp"
    break;

  case 167: /* having: HAVING condition_list  */
#line 1192 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3410 "yacc_sql.cpp"
    break;

  case 168: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1201 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3424 "yacc_sql.cpp"
    break;

  case 169: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1214 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3433 "yacc_sql.cpp"
    break;

  case 170: /* set_variable_stmt: SET ID EQ value  */
#line 1222 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3445 "yacc_sql.cpp"
    break;


#line 3449 "yacc_sql.cpp"

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

#line 1234 "yacc_sql.y"

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
