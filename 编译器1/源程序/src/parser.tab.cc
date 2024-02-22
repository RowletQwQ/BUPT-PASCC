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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"

#include "log.h"
#include"parser.h"
using namespace pascals;
using namespace pascals::ast;
using std::string;
extern "C"			
{					
    void yyerror(const char *s);
    extern int yylex(void);
    extern int line_count;
    extern bool new_line_flag;
    extern int yyleng;
    extern int last_line_count;
}
extern std::string cur_line_info;
extern std::string last_line_info;
extern int lex_error_flag;
int semantic_error_flag = 0;
std::stack<TableSet*> table_set_queue;
int _ = (log_set_level(LOG_INFO), 0);
TableSet* top_table_set = new TableSet("main",nullptr);

int error_flag=0;
char location_pointer[256];
void location_pointer_refresh();

void yyerror(AST* real_ast,const char *msg);
void yyerror_var(AST* real_ast,int line);
void yynote(std::string msg,int line);
void semantic_error(AST* real_ast,std::string msg,int line,int row){
    semantic_error_flag=1;
    real_ast->set_root(nullptr); 
    if (row)
        fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", line,row,msg.c_str());
    else
        fprintf(stderr,"%d:\033[01;31m \terror\033[0m : %s\n", line,msg.c_str());
}



#line 113 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 5,                  /* PROCEDURE  */
  YYSYMBOL_TO = 6,                         /* TO  */
  YYSYMBOL_DOWNTO = 7,                     /* DOWNTO  */
  YYSYMBOL_ARRAY = 8,                      /* ARRAY  */
  YYSYMBOL_TYPE = 9,                       /* TYPE  */
  YYSYMBOL_CONST = 10,                     /* CONST  */
  YYSYMBOL_RECORD = 11,                    /* RECORD  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_THEN = 13,                      /* THEN  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_CASE = 15,                      /* CASE  */
  YYSYMBOL_OF = 16,                        /* OF  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_REPEAT = 20,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 21,                     /* UNTIL  */
  YYSYMBOL_BEGIN_ = 22,                    /* BEGIN_  */
  YYSYMBOL_END = 23,                       /* END  */
  YYSYMBOL_ADDOP = 24,                     /* ADDOP  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_PLUS = 26,                      /* PLUS  */
  YYSYMBOL_UMINUS = 27,                    /* UMINUS  */
  YYSYMBOL_CONSTASSIGNOP = 28,             /* CONSTASSIGNOP  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_CHAR = 30,                      /* CHAR  */
  YYSYMBOL_INT_NUM = 31,                   /* INT_NUM  */
  YYSYMBOL_REAL_NUM = 32,                  /* REAL_NUM  */
  YYSYMBOL_BASIC_TYPE = 33,                /* BASIC_TYPE  */
  YYSYMBOL_RELOP = 34,                     /* RELOP  */
  YYSYMBOL_MULOP = 35,                     /* MULOP  */
  YYSYMBOL_STRING_ = 36,                   /* STRING_  */
  YYSYMBOL_VAR = 37,                       /* VAR  */
  YYSYMBOL_SUBCATALOG = 38,                /* SUBCATALOG  */
  YYSYMBOL_ASSIGNOP = 39,                  /* ASSIGNOP  */
  YYSYMBOL_WRITE = 40,                     /* WRITE  */
  YYSYMBOL_WRITELN = 41,                   /* WRITELN  */
  YYSYMBOL_SEP = 42,                       /* SEP  */
  YYSYMBOL_READ = 43,                      /* READ  */
  YYSYMBOL_READLN = 44,                    /* READLN  */
  YYSYMBOL_TRUE = 45,                      /* TRUE  */
  YYSYMBOL_FALSE = 46,                     /* FALSE  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* '.'  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '='  */
  YYSYMBOL_53_ = 53,                       /* '['  */
  YYSYMBOL_54_ = 54,                       /* ']'  */
  YYSYMBOL_55_ = 55,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_program = 57,                   /* program  */
  YYSYMBOL_program_head = 58,              /* program_head  */
  YYSYMBOL_program_body = 59,              /* program_body  */
  YYSYMBOL_id_list = 60,                   /* id_list  */
  YYSYMBOL_const_declarations = 61,        /* const_declarations  */
  YYSYMBOL_const_declaration = 62,         /* const_declaration  */
  YYSYMBOL_const_variable = 63,            /* const_variable  */
  YYSYMBOL_num = 64,                       /* num  */
  YYSYMBOL_type_declarations = 65,         /* type_declarations  */
  YYSYMBOL_type_declaration = 66,          /* type_declaration  */
  YYSYMBOL_type = 67,                      /* type  */
  YYSYMBOL_record_body = 68,               /* record_body  */
  YYSYMBOL_standrad_type = 69,             /* standrad_type  */
  YYSYMBOL_periods = 70,                   /* periods  */
  YYSYMBOL_period = 71,                    /* period  */
  YYSYMBOL_var_declarations = 72,          /* var_declarations  */
  YYSYMBOL_var_declaration = 73,           /* var_declaration  */
  YYSYMBOL_subprogram_declarations = 74,   /* subprogram_declarations  */
  YYSYMBOL_subprogram_declaration = 75,    /* subprogram_declaration  */
  YYSYMBOL_subprogram_body = 76,           /* subprogram_body  */
  YYSYMBOL_subprogram_head = 77,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 78,          /* formal_parameter  */
  YYSYMBOL_parameter_lists = 79,           /* parameter_lists  */
  YYSYMBOL_parameter_list = 80,            /* parameter_list  */
  YYSYMBOL_var_parameter = 81,             /* var_parameter  */
  YYSYMBOL_value_parameter = 82,           /* value_parameter  */
  YYSYMBOL_compound_statement = 83,        /* compound_statement  */
  YYSYMBOL_statement_list = 84,            /* statement_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_variable_list = 86,             /* variable_list  */
  YYSYMBOL_variable = 87,                  /* variable  */
  YYSYMBOL_id_varparts = 88,               /* id_varparts  */
  YYSYMBOL_id_varpart = 89,                /* id_varpart  */
  YYSYMBOL_else_part = 90,                 /* else_part  */
  YYSYMBOL_case_body = 91,                 /* case_body  */
  YYSYMBOL_branch_list = 92,               /* branch_list  */
  YYSYMBOL_branch = 93,                    /* branch  */
  YYSYMBOL_const_list = 94,                /* const_list  */
  YYSYMBOL_updown = 95,                    /* updown  */
  YYSYMBOL_call_procedure_statement = 96,  /* call_procedure_statement  */
  YYSYMBOL_expression_list = 97,           /* expression_list  */
  YYSYMBOL_expression = 98,                /* expression  */
  YYSYMBOL_str_expression = 99,            /* str_expression  */
  YYSYMBOL_simple_expression = 100,        /* simple_expression  */
  YYSYMBOL_term = 101,                     /* term  */
  YYSYMBOL_factor = 102,                   /* factor  */
  YYSYMBOL_unsigned_const_variable = 103,  /* unsigned_const_variable  */
  YYSYMBOL_104_1 = 104,                    /* $@1  */
  YYSYMBOL_105_2 = 105,                    /* $@2  */
  YYSYMBOL_106_3 = 106,                    /* $@3  */
  YYSYMBOL_107_4 = 107,                    /* $@4  */
  YYSYMBOL_108_5 = 108,                    /* $@5  */
  YYSYMBOL_109_6 = 109,                    /* $@6  */
  YYSYMBOL_110_7 = 110,                    /* $@7  */
  YYSYMBOL_111_8 = 111,                    /* $@8  */
  YYSYMBOL_112_9 = 112,                    /* $@9  */
  YYSYMBOL_113_10 = 113,                   /* $@10  */
  YYSYMBOL_114_11 = 114,                   /* $@11  */
  YYSYMBOL_115_12 = 115,                   /* $@12  */
  YYSYMBOL_ID_or_type = 116,               /* ID_or_type  */
  YYSYMBOL_117_13 = 117                    /* $@13  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   659

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  190
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  325

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
      49,    50,     2,     2,    51,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    47,
       2,    52,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
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
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   103,   117,   126,   135,   146,   159,   169,   179,
     185,   194,   214,   234,   252,   270,   287,   297,   306,   315,
     324,   331,   341,   347,   354,   360,   369,   392,   415,   427,
     462,   480,   486,   493,   504,   523,   535,   547,   578,   584,
     606,   634,   660,   690,   720,   726,   739,   749,   761,   815,
     863,   871,   882,   895,   906,   916,   927,   942,   962,   971,
     979,   988,  1019,  1027,  1035,  1050,  1072,  1086,  1100,  1132,
    1138,  1150,  1162,  1169,  1176,  1190,  1203,  1210,  1220,  1230,
    1242,  1274,  1355,  1364,  1384,  1396,  1409,  1415,  1424,  1431,
    1441,  1457,  1467,  1478,  1493,  1503,  1510,  1518,  1550,  1573,
    1597,  1610,  1623,  1656,  1683,  1697,  1710,  1722,  1733,  1748,
    1758,  1781,  1802,  1822,  1850,  1877,  1887,  1926,  1936,  1947,
    1982,  1992,  2013,  2023,  2033,  2043,  2058,  2078,  2093,  2122,
    2163,  2204,  2246,  2254,  2262,  2284,  2283,  2295,  2294,  2306,
    2305,  2317,  2316,  2327,  2345,  2363,  2371,  2379,  2401,  2400,
    2412,  2411,  2423,  2422,  2434,  2433,  2444,  2462,  2480,  2488,
    2496,  2517,  2535,  2554,  2553,  2565,  2564,  2576,  2575,  2587,
    2586,  2597,  2598,  2602,  2613,  2624,  2635,  2670,  2678,  2707,
    2728,  2759,  2777,  2796,  2807,  2824,  2841,  2862,  2870,  2892,
    2891
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "FUNCTION",
  "PROCEDURE", "TO", "DOWNTO", "ARRAY", "TYPE", "CONST", "RECORD", "IF",
  "THEN", "ELSE", "CASE", "OF", "WHILE", "DO", "FOR", "REPEAT", "UNTIL",
  "BEGIN_", "END", "ADDOP", "NOT", "PLUS", "UMINUS", "CONSTASSIGNOP", "ID",
  "CHAR", "INT_NUM", "REAL_NUM", "BASIC_TYPE", "RELOP", "MULOP", "STRING_",
  "VAR", "SUBCATALOG", "ASSIGNOP", "WRITE", "WRITELN", "SEP", "READ",
  "READLN", "TRUE", "FALSE", "';'", "'.'", "'('", "')'", "','", "'='",
  "'['", "']'", "':'", "$accept", "program", "program_head",
  "program_body", "id_list", "const_declarations", "const_declaration",
  "const_variable", "num", "type_declarations", "type_declaration", "type",
  "record_body", "standrad_type", "periods", "period", "var_declarations",
  "var_declaration", "subprogram_declarations", "subprogram_declaration",
  "subprogram_body", "subprogram_head", "formal_parameter",
  "parameter_lists", "parameter_list", "var_parameter", "value_parameter",
  "compound_statement", "statement_list", "statement", "variable_list",
  "variable", "id_varparts", "id_varpart", "else_part", "case_body",
  "branch_list", "branch", "const_list", "updown",
  "call_procedure_statement", "expression_list", "expression",
  "str_expression", "simple_expression", "term", "factor",
  "unsigned_const_variable", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6",
  "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "ID_or_type", "$@13", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-197)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-99)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     107,  -197,    24,    32,    61,  -197,   171,  -197,    93,     7,
      69,  -197,    38,  -197,   478,    80,  -197,  -197,   158,   102,
    -197,   109,   181,   228,   257,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,   430,  -197,  -197,  -197,   335,  -197,   314,   123,
     176,  -197,  -197,   132,   167,  -197,  -197,  -197,  -197,   613,
    -197,  -197,   613,  -197,   505,    15,   172,  -197,  -197,    74,
    -197,  -197,  -197,   382,  -197,   198,    54,   160,   121,  -197,
    -197,  -197,  -197,  -197,   451,  -197,  -197,  -197,   613,   191,
     178,   173,  -197,  -197,   173,  -197,   315,  -197,  -197,  -197,
      28,  -197,  -197,   248,   190,   227,   472,   217,    61,  -197,
     613,  -197,  -197,   613,   237,   193,  -197,  -197,    90,  -197,
    -197,  -197,   103,  -197,  -197,   240,   240,  -197,  -197,  -197,
    -197,   235,    95,   246,   246,   163,   576,   197,   274,   426,
     155,   269,   284,   286,   289,  -197,    49,  -197,   105,  -197,
    -197,    69,  -197,  -197,  -197,   613,   613,   164,   173,  -197,
    -197,   173,  -197,  -197,  -197,  -197,    41,  -197,    -7,   288,
     309,  -197,   606,   606,   606,   312,  -197,  -197,  -197,  -197,
     209,  -197,  -197,   345,   336,   148,   328,  -197,  -197,   349,
    -197,   350,   338,  -197,    12,   516,   138,   576,   542,   346,
      40,  -197,   472,   122,  -197,   102,  -197,  -197,  -197,   326,
    -197,  -197,   240,   240,  -197,  -197,  -197,   355,   111,   224,
    -197,  -197,  -197,    18,  -197,  -197,   328,   328,   550,  -197,
     339,   472,   -10,   606,   606,   606,   584,   584,   606,   613,
     359,   236,   576,   106,   266,  -197,   356,   275,  -197,   280,
    -197,   291,   341,   295,  -197,  -197,   299,  -197,  -197,  -197,
    -197,   340,   369,  -197,  -197,  -197,  -197,  -197,  -197,   360,
      -7,  -197,  -197,   348,  -197,   301,  -197,   383,  -197,  -197,
     328,   328,   328,   270,   270,  -197,  -197,   373,   351,  -197,
     162,  -197,  -197,  -197,   272,  -197,  -197,   576,  -197,  -197,
     229,  -197,  -197,   367,  -197,   346,  -197,   576,  -197,  -197,
    -197,  -197,  -197,   472,  -197,  -197,   613,   613,   472,  -197,
    -197,   283,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,   391,   393,  -197,  -197
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   126,     0,     0,     9,   127,     0,     1,     0,     0,
      24,     5,     0,   129,     0,     0,   128,     2,     0,    38,
       8,     0,     0,     0,     0,    15,    19,    22,    23,   135,
      20,    21,     0,   139,   132,    17,     0,   130,     0,     0,
       0,    44,     4,     0,     0,    13,    18,    14,    16,     0,
     134,    12,     0,   144,     0,     0,    31,    34,   148,     0,
     152,   145,    28,     0,   131,     8,     0,     0,     0,     3,
       7,   136,   140,   137,     0,   141,   133,   174,     0,     0,
      32,     0,   147,    27,     0,   157,     0,   167,   171,   163,
       0,   172,   158,     0,     0,     0,    69,     0,     9,     6,
       0,   143,    11,     0,     0,     0,    36,    30,     0,   149,
     153,   150,     0,   154,   146,     0,     0,   160,    43,    41,
     162,     8,     0,    50,    50,     0,     0,     0,     0,     0,
      82,     0,    77,     0,    73,    63,     0,    60,     0,    62,
      45,    24,    46,   138,   142,     0,     0,     0,     0,   156,
      26,     0,   168,   164,   169,   165,     0,   159,     0,     0,
       0,   180,     0,     0,     0,    82,   123,   106,   124,   125,
       0,   122,   118,     0,   105,   104,   109,   115,   117,     0,
     182,     0,     0,   181,     0,     0,    81,     0,     0,     0,
       0,    58,    69,     0,   189,    38,    37,    35,   173,     0,
     151,   155,     0,     0,   161,    42,    40,     0,     0,     0,
      53,    54,    55,     0,    49,   121,   110,   111,     0,   178,
       0,    69,     0,     0,     0,     0,     0,     0,     0,    88,
       0,     0,     0,    99,     0,   101,     0,     0,    83,     0,
      76,     0,    82,     0,    78,    72,     0,    59,   188,   187,
      61,     0,     0,   175,   177,    29,   170,   166,    56,     0,
       0,    51,   179,     0,    80,     0,   120,    86,   108,   107,
     112,   113,   114,   102,   103,   116,    94,     0,    89,    91,
       0,   183,    66,   186,     0,    67,    97,     0,    85,   176,
       0,    74,    75,     0,    70,     0,    71,     0,    47,    57,
      52,    48,   119,    69,    64,    65,     0,     0,    69,    95,
      96,     0,   100,    84,    79,   190,    87,    90,    93,    92,
     185,     0,     0,   184,    68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -197,  -197,  -197,  -197,    -9,   303,  -197,    -8,   -14,   277,
    -197,   -36,  -197,  -196,  -197,   278,   225,   365,  -197,  -197,
    -197,  -197,   302,  -197,   165,  -197,   216,   -67,   300,  -187,
     238,   -92,  -197,  -197,  -197,  -197,  -197,   124,  -197,  -197,
    -197,  -160,  -114,  -197,    64,   -83,  -155,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -101,  -197
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     4,     9,   208,    10,    15,   104,   171,    19,
      39,    91,    79,    62,   105,   106,    41,    67,    68,    97,
     142,    98,   159,   209,   210,   211,   212,   135,   136,   137,
     243,   172,   186,   238,   304,   277,   278,   279,   280,   311,
     139,   234,   235,   174,   175,   176,   177,   178,    49,   100,
      52,   103,    81,   148,    84,   151,   116,   203,   115,   202,
      92,   251
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    99,    61,    22,   138,   247,    34,   215,    16,    46,
      48,   173,   179,   181,   152,   153,    77,   263,    35,   262,
     268,   157,    20,    83,    51,     5,   269,   239,   241,   117,
     207,    66,     7,   232,   267,    35,    55,   138,    35,    56,
      35,    71,   204,   282,    72,   109,    76,    66,   110,    55,
     114,    57,    56,     6,   119,    17,   220,   118,   265,   192,
      35,    57,    55,   299,    35,    56,   102,    20,    78,   242,
     205,     8,   191,   275,    57,    82,   150,   290,    18,   250,
     216,   217,    55,    88,   122,    56,    35,    57,    21,    35,
     245,   120,   143,    89,    13,   144,   192,   244,   244,   122,
     138,   256,   257,    55,   149,    44,    56,    57,     1,    90,
       2,    55,   200,   -33,    56,   201,   316,   284,   285,   121,
     206,   319,    14,   248,    88,    94,    95,    36,    57,   138,
      55,    35,    35,    56,   155,   324,    57,   196,   138,    40,
     270,   271,   272,    96,   193,   -80,    44,   162,   163,   164,
     156,   165,   166,    27,    28,    57,    42,   249,   167,    37,
     194,   -80,    44,   255,   161,   198,   259,   168,   169,   -98,
      63,   170,   223,   312,   224,   225,   -98,    64,   -98,    69,
     199,    55,   226,   315,    56,   298,   236,    38,   162,   163,
     164,   237,   165,   166,    27,    28,    70,   321,   180,   167,
     227,    65,   -98,   314,   185,    65,    57,    93,   168,   169,
     219,   138,   170,   307,   107,    35,   138,   308,    11,   123,
      12,   276,   162,   163,   164,   108,   165,   166,    27,    28,
     138,    43,    44,   167,   162,   163,   164,   283,   165,   166,
      27,    28,   168,   169,   146,   167,   170,   147,    55,   120,
      87,    56,   -39,   -39,   168,   169,   124,    45,   170,    27,
      28,   162,   163,   164,   140,   165,   166,    27,    28,    88,
     -39,   260,   167,    57,   261,   145,   289,   121,   309,   310,
     287,   168,   169,   313,   320,   170,    47,   154,    27,    28,
     273,   274,    35,    35,   223,   158,   224,   225,   276,   318,
     162,   163,   164,   182,   165,   166,    27,    28,   162,   163,
     164,   167,   165,   166,    27,    28,   286,   287,   187,   167,
     168,   169,    55,    55,   170,    56,    56,   253,   168,   169,
     291,   287,   170,   188,    55,   189,    53,    56,   190,   -10,
     -10,   292,   287,   213,   -10,   294,   295,    57,    57,   296,
     295,   302,   287,    58,   111,   254,   214,   -10,   221,    57,
     281,   218,   222,   228,    54,   229,    59,   112,   230,    60,
     113,   125,   -10,   -69,   126,   242,   127,   231,   128,   129,
     -69,    96,   -69,    85,    20,   288,   -25,   -25,   130,   266,
     293,    96,   297,    57,   323,   301,   305,   303,   306,   131,
     132,   141,   133,   134,   -25,   125,   -69,   -69,   126,   322,
     127,    86,   128,   129,   -69,    96,   -69,   264,   195,   -25,
     252,    80,   130,   258,   197,   300,   160,   183,   246,   184,
     317,    50,     0,   131,   132,     0,   133,   134,   125,     0,
     -69,   126,     0,   127,     0,   128,   129,   -69,    96,     0,
       0,     0,   101,     0,     0,   130,    23,    24,     0,    25,
      26,    27,    28,     0,     0,     0,   131,   132,     0,   133,
     134,     0,     0,   -69,     0,    30,    31,    23,    24,     0,
      25,    26,    27,    28,   125,     0,     0,   126,     0,   127,
       0,   128,   129,     0,    96,     0,    30,    31,     0,     0,
       0,   130,     0,     0,    23,    24,     0,    25,    26,    27,
      28,     0,   131,   132,     0,   133,   134,    29,     0,     0,
       0,     0,     0,    30,    31,     0,     0,     0,     0,     0,
      32,    23,    24,    33,    25,    26,    27,    28,     0,     0,
       0,   162,   163,   164,    73,   165,   166,    27,    28,     0,
      30,    31,   167,     0,     0,     0,     0,    74,     0,     0,
      75,   168,   169,     0,     0,   170,   233,   162,   163,   164,
       0,   165,   166,    27,    28,   162,   163,   164,   167,   165,
     166,    27,    28,     0,     0,     0,   167,   168,   169,     0,
       0,   170,   240,     0,     0,   168,   169,     0,     0,   170,
     264,   162,   163,   164,     0,   165,   166,    27,    28,   162,
     163,   164,   167,   165,   166,    27,    28,     0,     0,     0,
       0,   168,   169,     0,     0,   170,     0,     0,     0,   168,
     169,   162,     0,   170,     0,   165,   166,    27,    28,    23,
      24,     0,    25,    26,    27,    28,     0,     0,     0,     0,
       0,   168,   169,     0,     0,   170,     0,     0,    30,    31
};

static const yytype_int16 yycheck[] =
{
      14,    68,    38,    12,    96,   192,    14,   162,     1,    23,
      24,   125,   126,   127,   115,   116,     1,   213,    32,     1,
      30,   122,    29,    59,    32,     1,    36,   187,   188,     1,
      37,    40,     0,    21,   221,    49,     8,   129,    52,    11,
      54,    49,     1,   230,    52,    81,    54,    56,    84,     8,
      86,    33,    11,    29,    90,    48,   170,    29,   218,    47,
      74,    33,     8,   259,    78,    11,    74,    29,    53,    29,
      29,    10,    23,   228,    33,     1,   112,   237,     9,   193,
     163,   164,     8,    29,    93,    11,   100,    33,    50,   103,
      50,     1,   100,    39,     1,   103,    47,   189,   190,   108,
     192,   202,   203,     8,     1,    51,    11,    33,     1,    55,
       3,     8,   148,    23,    11,   151,   303,   231,   232,    29,
     156,   308,    29,     1,    29,     4,     5,    47,    33,   221,
       8,   145,   146,    11,    39,   322,    33,   145,   230,    37,
     223,   224,   225,    22,    39,    39,    51,    25,    26,    27,
      55,    29,    30,    31,    32,    33,    47,   193,    36,     1,
      55,    55,    51,   199,     1,     1,    55,    45,    46,    14,
      47,    49,    24,   287,    26,    27,    21,     1,    23,    47,
      16,     8,    34,   297,    11,   252,    48,    29,    25,    26,
      27,    53,    29,    30,    31,    32,    29,   311,     1,    36,
      52,    29,    47,   295,    49,    29,    33,    47,    45,    46,
       1,   303,    49,    51,    23,   229,   308,    55,    47,    29,
      49,   229,    25,    26,    27,    47,    29,    30,    31,    32,
     322,    50,    51,    36,    25,    26,    27,     1,    29,    30,
      31,    32,    45,    46,    51,    36,    49,    54,     8,     1,
      52,    11,     4,     5,    45,    46,    29,    29,    49,    31,
      32,    25,    26,    27,    47,    29,    30,    31,    32,    29,
      22,    47,    36,    33,    50,    38,     1,    29,     6,     7,
      51,    45,    46,    54,     1,    49,    29,    52,    31,    32,
     226,   227,   306,   307,    24,    49,    26,    27,   306,   307,
      25,    26,    27,    29,    29,    30,    31,    32,    25,    26,
      27,    36,    29,    30,    31,    32,    50,    51,    49,    36,
      45,    46,     8,     8,    49,    11,    11,     1,    45,    46,
      50,    51,    49,    49,     8,    49,     1,    11,    49,     4,
       5,    50,    51,    55,     9,    50,    51,    33,    33,    50,
      51,    50,    51,    39,    39,    29,    47,    22,    13,    33,
       1,    49,    26,    35,    29,    16,    52,    52,    18,    55,
      55,    12,    37,    14,    15,    29,    17,    39,    19,    20,
      21,    22,    23,     1,    29,    29,     4,     5,    29,    50,
      49,    22,    52,    33,     1,    47,    23,    14,    47,    40,
      41,    98,    43,    44,    22,    12,    47,    14,    15,    18,
      17,    29,    19,    20,    21,    22,    23,    50,   141,    37,
     195,    56,    29,   207,   146,   260,   124,     1,   190,   129,
     306,     1,    -1,    40,    41,    -1,    43,    44,    12,    -1,
      47,    15,    -1,    17,    -1,    19,    20,    21,    22,    -1,
      -1,    -1,     1,    -1,    -1,    29,    26,    27,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    40,    41,    -1,    43,
      44,    -1,    -1,    47,    -1,    45,    46,    26,    27,    -1,
      29,    30,    31,    32,    12,    -1,    -1,    15,    -1,    17,
      -1,    19,    20,    -1,    22,    -1,    45,    46,    -1,    -1,
      -1,    29,    -1,    -1,    26,    27,    -1,    29,    30,    31,
      32,    -1,    40,    41,    -1,    43,    44,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    26,    27,    55,    29,    30,    31,    32,    -1,    -1,
      -1,    25,    26,    27,    39,    29,    30,    31,    32,    -1,
      45,    46,    36,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    45,    46,    -1,    -1,    49,    50,    25,    26,    27,
      -1,    29,    30,    31,    32,    25,    26,    27,    36,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    45,    46,    -1,
      -1,    49,    50,    -1,    -1,    45,    46,    -1,    -1,    49,
      50,    25,    26,    27,    -1,    29,    30,    31,    32,    25,
      26,    27,    36,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    45,    46,    -1,    -1,    49,    -1,    -1,    -1,    45,
      46,    25,    -1,    49,    -1,    29,    30,    31,    32,    26,
      27,    -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
      -1,    45,    46,    -1,    -1,    49,    -1,    -1,    45,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    57,    58,     1,    29,     0,    10,    59,
      61,    47,    49,     1,    29,    62,     1,    48,     9,    65,
      29,    50,    60,    26,    27,    29,    30,    31,    32,    39,
      45,    46,    52,    55,    63,    64,    47,     1,    29,    66,
      37,    72,    47,    50,    51,    29,    64,    29,    64,   104,
       1,    63,   106,     1,    29,     8,    11,    33,    39,    52,
      55,    67,    69,    47,     1,    29,    60,    73,    74,    47,
      29,    63,    63,    39,    52,    55,    63,     1,    53,    68,
      73,   108,     1,    67,   110,     1,    29,    52,    29,    39,
      55,    67,   116,    47,     4,     5,    22,    75,    77,    83,
     105,     1,    63,   107,    63,    70,    71,    23,    47,    67,
      67,    39,    52,    55,    67,   114,   112,     1,    29,    67,
       1,    29,    60,    29,    29,    12,    15,    17,    19,    20,
      29,    40,    41,    43,    44,    83,    84,    85,    87,    96,
      47,    61,    76,    63,    63,    38,    51,    54,   109,     1,
      67,   111,   116,   116,    52,    39,    55,   116,    49,    78,
      78,     1,    25,    26,    27,    29,    30,    36,    45,    46,
      49,    64,    87,    98,    99,   100,   101,   102,   103,    98,
       1,    98,    29,     1,    84,    49,    88,    49,    49,    49,
      49,    23,    47,    39,    55,    65,    63,    71,     1,    16,
      67,    67,   115,   113,     1,    29,    67,    37,    60,    79,
      80,    81,    82,    55,    47,   102,   101,   101,    49,     1,
      98,    13,    26,    24,    26,    27,    34,    52,    35,    16,
      18,    39,    21,    50,    97,    98,    48,    53,    89,    97,
      50,    97,    29,    86,    87,    50,    86,    85,     1,    67,
      98,   117,    72,     1,    29,    67,   116,   116,    82,    55,
      47,    50,     1,    69,    50,    97,    50,    85,    30,    36,
     101,   101,   101,   100,   100,   102,    63,    91,    92,    93,
      94,     1,    85,     1,    98,    98,    50,    51,    29,     1,
      97,    50,    50,    49,    50,    51,    50,    52,    83,    69,
      80,    47,    50,    14,    90,    23,    47,    51,    55,     6,
       7,    95,    98,    54,    87,    98,    85,    93,    63,    85,
       1,    98,    18,     1,    85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    68,    68,    68,    69,    70,    70,    71,    72,    72,
      73,    73,    73,    73,    74,    74,    75,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    82,    83,    84,
      84,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      87,    87,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    92,    93,    94,    94,    95,    95,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,    99,   100,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   103,   103,   103,   103,    57,    58,    57,    61,
      65,    72,    62,    62,    62,   104,    62,   105,    62,   106,
      62,   107,    62,    62,    62,    66,    66,    66,   108,    66,
     109,    66,   110,    66,   111,    66,    66,    66,    73,    73,
      73,    73,    73,   112,    73,   113,    73,   114,    73,   115,
      73,   116,   116,    67,    67,    67,    89,    67,   102,    77,
      85,    85,    85,    85,    85,    85,    85,    85,    85,   117,
      85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     5,     3,     5,     3,     1,     0,
       3,     5,     3,     2,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     0,     3,     5,     3,     1,     6,
       3,     0,     1,     2,     1,     3,     1,     3,     0,     3,
       5,     3,     5,     3,     0,     3,     2,     4,     6,     4,
       0,     3,     3,     1,     1,     1,     2,     3,     3,     3,
       1,     3,     1,     1,     5,     5,     4,     4,     8,     0,
       4,     4,     3,     1,     4,     4,     3,     1,     1,     3,
       3,     2,     0,     2,     3,     2,     0,     2,     0,     1,
       3,     1,     3,     3,     1,     1,     1,     4,     1,     3,
       3,     1,     3,     3,     1,     1,     1,     3,     3,     1,
       2,     2,     3,     3,     3,     1,     3,     1,     1,     4,
       3,     2,     1,     1,     1,     1,     1,     2,     3,     2,
       2,     2,     2,     4,     3,     0,     4,     0,     6,     0,
       4,     0,     6,     5,     3,     2,     4,     3,     0,     4,
       0,     6,     0,     4,     0,     6,     5,     3,     2,     4,
       3,     5,     3,     0,     4,     0,     6,     0,     4,     0,
       6,     1,     1,     5,     2,     6,     2,     6,     2,     5,
       2,     2,     2,     4,     8,     6,     4,     3,     3,     0,
       5
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
        yyerror (real_ast, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, real_ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, pascals::ast::AST *real_ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (real_ast);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, pascals::ast::AST *real_ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, real_ast);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, pascals::ast::AST *real_ast)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], real_ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, real_ast); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, pascals::ast::AST *real_ast)
{
  YY_USE (yyvaluep);
  YY_USE (real_ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (pascals::ast::AST *real_ast)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: program_head program_body '.'  */
#line 104 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // prgram -> program_head program_body '.'
	ProgramNode* node = new ProgramNode();
        node->append_child((yyvsp[-2].program_head_node));
        node->append_child((yyvsp[-1].program_body_node));

        if(!error_flag && !semantic_error_flag && !lex_error_flag){
            real_ast->set_root(node);
            real_ast->set_valid(true);
        }
        delete top_table_set;
    }
#line 1535 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 3: /* program_head: PROGRAM ID '(' id_list ')' ';'  */
#line 117 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                   {
        // program_head -> PROGRAM ID '(' id_list ')' ';'
    	if(error_flag)
	        break;
        (yyval.program_head_node) = new ProgramHeadNode();
        LeafNode* leaf_node = new LeafNode((yyvsp[-4].token_info).value);
        (yyval.program_head_node)->append_child(leaf_node);
        table_set_queue.push(top_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
    }
#line 1550 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 4: /* program_head: PROGRAM ID '(' ')' ';'  */
#line 126 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                {
        // program_head -> PROGRAM ID '('  ')' ';'
	    if(error_flag)
	        break;
        (yyval.program_head_node) = new ProgramHeadNode();
        LeafNode* leaf_node = new LeafNode((yyvsp[-3].token_info).value);
        (yyval.program_head_node)->append_child(leaf_node);
        table_set_queue.push(top_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
    }
#line 1565 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 5: /* program_head: PROGRAM ID ';'  */
#line 135 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                       {
        // program_head -> PROGRAM ID ';'
        if(error_flag)
            break;
        (yyval.program_head_node) = new ProgramHeadNode();
        LeafNode* leaf_node = new LeafNode((yyvsp[-1].token_info).value);
        (yyval.program_head_node)->append_child(leaf_node);
        table_set_queue.push(top_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
    }
#line 1580 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 6: /* program_body: const_declarations type_declarations var_declarations subprogram_declarations compound_statement  */
#line 147 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                               {
        // program_body -> const_declarations type_declarations var_declarations subprogram_declarations compound_statement
        if(error_flag)
            break;
        (yyval.program_body_node) = new ProgramBodyNode();
        (yyval.program_body_node)->append_child((yyvsp[-4].const_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-3].type_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-2].variable_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-1].subprogram_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1596 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 7: /* id_list: id_list ',' ID  */
#line 159 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                   { 
        // id_list -> id_list ',' ID
        (yyvsp[-2].id_list_node_info).list_ref->push_back(std::make_pair((yyvsp[0].token_info).value.get<string>(),(yyvsp[0].token_info).column_num));
        (yyval.id_list_node_info).list_ref = (yyvsp[-2].id_list_node_info).list_ref;
        (yyval.id_list_node_info).id_list_node = new IdListNode(IdListNode::GrammarType::MULTIPLE_ID);
        if(error_flag)
            break;
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.id_list_node_info).id_list_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        (yyval.id_list_node_info).id_list_node->append_child(leaf_node);
    }
#line 1612 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 8: /* id_list: ID  */
#line 169 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
           {
        // id_list -> ID
        (yyval.id_list_node_info).list_ref = new std::vector<std::pair<std::string,int>>();
        (yyval.id_list_node_info).list_ref->push_back(std::make_pair((yyvsp[0].token_info).value.get<string>(),(yyvsp[0].token_info).column_num));
        if(error_flag)
            break;
        (yyval.id_list_node_info).id_list_node = new IdListNode(IdListNode::GrammarType::SINGLE_ID);
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.id_list_node_info).id_list_node->append_child(leaf_node);
    }
#line 1627 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 9: /* const_declarations: %empty  */
#line 179 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                    {
        // const_declarations -> empty
        if(error_flag)
            break;
        (yyval.const_declarations_node) = new ConstDeclarationsNode();
    }
#line 1638 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 10: /* const_declarations: CONST const_declaration ';'  */
#line 186 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // const_declarations -> CONST const_declaration ';'
        if(error_flag)
            break;
        (yyval.const_declarations_node) = new ConstDeclarationsNode(); 
        (yyval.const_declarations_node)->append_child((yyvsp[-1].const_declaration_node));
    }
#line 1650 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 11: /* const_declaration: const_declaration ';' ID '=' const_variable  */
#line 195 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_declaration -> const_declaration ';' ID '=' const_variable
        if(error_flag)
            break;
        if (!(yyvsp[0].value_node_info).is_right)
            break;
        ConstSymbol *symbol = new ConstSymbol((yyvsp[-2].token_info).value.get<string>(),(yyvsp[0].value_node_info).value,(yyvsp[-2].token_info).line_num);

        if(!table_set_queue.top()->Insert<ConstSymbol>((yyvsp[-2].token_info).value.get<string>(),symbol)){
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"redefinition of '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
        } else{
            (yyval.const_declaration_node) = new ConstDeclarationNode(ConstDeclarationNode::GrammarType::DECLARATION,(yyvsp[0].value_node_info).type_ptr);
            (yyval.const_declaration_node)->append_child((yyvsp[-4].const_declaration_node));
            LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value);
            (yyval.const_declaration_node)->append_child(leaf_node);
            (yyval.const_declaration_node)->append_child((yyvsp[0].value_node_info).const_variable_node);
        }
    }
#line 1674 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 12: /* const_declaration: ID '=' const_variable  */
#line 215 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // const_declaration -> ID '=' const_variable
        if(error_flag)
            break;
        if (!(yyvsp[0].value_node_info).is_right)
            break;
        ConstSymbol *symbol = new ConstSymbol((yyvsp[-2].token_info).value.get<string>(),(yyvsp[0].value_node_info).value,(yyvsp[-2].token_info).line_num);

        if(!table_set_queue.top()->Insert<ConstSymbol>((yyvsp[-2].token_info).value.get<string>(),symbol)){
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"redefinition of '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
        } else {
            (yyval.const_declaration_node) = new ConstDeclarationNode(ConstDeclarationNode::GrammarType::VALUE,(yyvsp[0].value_node_info).type_ptr);
            LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value);
            (yyval.const_declaration_node)->append_child(leaf_node);
            (yyval.const_declaration_node)->append_child((yyvsp[0].value_node_info).const_variable_node);
        }
    }
#line 1697 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 13: /* const_variable: PLUS ID  */
#line 235 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // const_variable -> PLUS ID
        if(error_flag)
            break;
        ConstSymbol *symbol = table_set_queue.top()->SearchEntry<ConstSymbol>((yyvsp[0].token_info).value.get<string>());
        (yyval.value_node_info).type_ptr = TYPE_ERROR;
        if(!symbol){
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"'"+tn+"' undeclared or is not constant",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            (yyval.value_node_info).is_right = false;
        } else {
            /* You cannot use variables to assign values to constants */
            (yyval.value_node_info).value = symbol->value();
            (yyval.value_node_info).type_ptr = symbol->type();
            (yyval.value_node_info).const_variable_node = new LeafNode(ConstValue("+" + (yyvsp[0].token_info).value.get<string>()));     
        }
    }
#line 1719 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 14: /* const_variable: UMINUS ID  */
#line 253 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_variable -> UMINUS ID
        if(error_flag)
            break;
        ConstSymbol *symbol = table_set_queue.top()->SearchEntry<ConstSymbol>((yyvsp[0].token_info).value.get<string>());
        (yyval.value_node_info).type_ptr = TYPE_ERROR;
        if(!symbol){
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"'"+tn+"' undeclared or is not constant",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            (yyval.value_node_info).is_right = false;
        } else {
            /* You cannot use variables to assign values to constants */
            (yyval.value_node_info).type_ptr = symbol->type();
            (yyval.value_node_info).value = symbol->value();
            (yyval.value_node_info).const_variable_node = new LeafNode(ConstValue("-" + (yyvsp[0].token_info).value.get<string>()));
        }
    }
#line 1741 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 15: /* const_variable: ID  */
#line 271 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_variable -> ID
        if(error_flag)
            break;
        ConstSymbol *symbol = table_set_queue.top()->SearchEntry<ConstSymbol>((yyvsp[0].token_info).value.get<string>());
        (yyval.value_node_info).type_ptr = TYPE_ERROR;
        if(!symbol){
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"'"+tn+"' undeclared or is not constant",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            (yyval.value_node_info).is_right = false;
        } else {
            (yyval.value_node_info).type_ptr = symbol->type();
            (yyval.value_node_info).value = symbol->value();
        }
        (yyval.value_node_info).const_variable_node = new LeafNode((yyvsp[0].token_info).value);
    }
#line 1762 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 16: /* const_variable: UMINUS num  */
#line 288 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {  
        // const_variable -> UMINUS num
        (yyval.value_node_info).type_ptr = (yyvsp[0].value_node_info).type_ptr;
        (yyvsp[0].value_node_info).value.set_unimus();
        (yyval.value_node_info).value = (yyvsp[0].value_node_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode((yyvsp[0].value_node_info).value);
    }
#line 1776 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 17: /* const_variable: num  */
#line 298 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // const_variable -> num
        (yyval.value_node_info).type_ptr = (yyvsp[0].value_node_info).type_ptr;
        (yyval.value_node_info).value = (yyvsp[0].value_node_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode((yyvsp[0].value_node_info).value);
    }
#line 1789 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 18: /* const_variable: PLUS num  */
#line 307 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {  
        // const_variable -> PLUS num
        (yyval.value_node_info).type_ptr = (yyvsp[0].value_node_info).type_ptr;
        (yyval.value_node_info).value = (yyvsp[0].value_node_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode((yyvsp[0].value_node_info).value);
    }
#line 1802 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 19: /* const_variable: CHAR  */
#line 316 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_variable -> CHAR
        (yyval.value_node_info).type_ptr = TYPE_CHAR;
        (yyval.value_node_info).value = (yyvsp[0].token_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode((yyvsp[0].token_info).value);

    }
#line 1816 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 20: /* const_variable: TRUE  */
#line 325 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        (yyval.value_node_info).type_ptr = TYPE_BOOL;
        (yyval.value_node_info).value = (yyvsp[0].token_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode(ConstValue(true));
    }
#line 1828 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 21: /* const_variable: FALSE  */
#line 332 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        (yyval.value_node_info).type_ptr = TYPE_BOOL;
        (yyval.value_node_info).value = (yyvsp[0].token_info).value;
        if(error_flag)
            break; 
        (yyval.value_node_info).const_variable_node = new LeafNode(ConstValue(false));
    }
#line 1840 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 22: /* num: INT_NUM  */
#line 342 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // num -> INT_NUM
        (yyval.value_node_info).type_ptr = TYPE_INT;
        (yyval.value_node_info).value = (yyvsp[0].token_info).value;
    }
#line 1850 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 23: /* num: REAL_NUM  */
#line 348 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // num -> REAL_NUM
        (yyval.value_node_info).type_ptr = TYPE_REAL;
        (yyval.value_node_info).value = (yyvsp[0].token_info).value;
    }
#line 1860 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 24: /* type_declarations: %empty  */
#line 354 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type_declarations -> empty
        if(error_flag)
            break;
        (yyval.type_declarations_node) = new TypeDeclarationsNode();
    }
#line 1871 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 25: /* type_declarations: TYPE type_declaration ';'  */
#line 361 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type_declarations -> TYPE type_declaration ';'
        if(error_flag)
            break;
        (yyval.type_declarations_node) = new TypeDeclarationsNode();
        (yyval.type_declarations_node)->append_child((yyvsp[-1].type_declaration_node));
    }
#line 1883 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 26: /* type_declaration: type_declaration ';' ID '=' type  */
#line 370 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type_declaration -> type_declaration ';' ID '=' type
        if(error_flag)
            break;
        string tn = (yyvsp[-2].token_info).value.get<string>();
        bool err1 = (yyvsp[0].type_node_info).main_type == TypeAttr::BASIC && !table_set_queue.top()->Insert<BasicType>(tn,dynamic_cast<BasicType*>((yyvsp[0].type_node_info).type_ptr));
        bool err2 = (yyvsp[0].type_node_info).main_type == TypeAttr::ARRAY && !table_set_queue.top()->Insert<ArrayType>(tn,dynamic_cast<ArrayType*>((yyvsp[0].type_node_info).type_ptr));
        bool err3 = (yyvsp[0].type_node_info).record_info && !table_set_queue.top()->Insert<RecordType>(tn,dynamic_cast<RecordType*>((yyvsp[0].type_node_info).type_ptr));
        if(err1 || err2 || err3){
	    semantic_error(real_ast,"redefinition of '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
	}

        (yyval.type_declaration_node) = new TypeDeclarationNode(TypeDeclarationNode::GrammarType::MULTIPLE_DECL);
        (yyval.type_declaration_node)->append_child((yyvsp[-4].type_declaration_node));
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value);
        (yyval.type_declaration_node)->append_child(leaf_node);
        (yyval.type_declaration_node)->append_child((yyvsp[0].type_node_info).type_node);
        delete (yyvsp[0].type_node_info).record_info;
        if((yyvsp[0].type_node_info).bounds) {
            delete (yyvsp[0].type_node_info).bounds;
        }
    }
#line 1910 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 27: /* type_declaration: ID '=' type  */
#line 393 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type_declaration -> ID '=' type
        if(error_flag)
            break;
        string tn = (yyvsp[-2].token_info).value.get<string>();
        bool err1 = (yyvsp[0].type_node_info).main_type == TypeAttr::BASIC && !table_set_queue.top()->Insert<BasicType>(tn,dynamic_cast<BasicType*>((yyvsp[0].type_node_info).type_ptr));
        bool err2 = (yyvsp[0].type_node_info).main_type == TypeAttr::ARRAY && !table_set_queue.top()->Insert<ArrayType>(tn,dynamic_cast<ArrayType*>((yyvsp[0].type_node_info).type_ptr));
        bool err3 = (yyvsp[0].type_node_info).record_info && !table_set_queue.top()->Insert<RecordType>(tn,dynamic_cast<RecordType*>((yyvsp[0].type_node_info).type_ptr));
        if(err1 || err2 || err3){
	    semantic_error(real_ast,"redefinition of '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
	}

        (yyval.type_declaration_node) = new TypeDeclarationNode(TypeDeclarationNode::GrammarType::SINGLE_DECL);
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value);
        (yyval.type_declaration_node)->append_child(leaf_node);
        (yyval.type_declaration_node)->append_child((yyvsp[0].type_node_info).type_node);
        delete (yyvsp[0].type_node_info).record_info;
        if((yyvsp[0].type_node_info).bounds) {
            delete (yyvsp[0].type_node_info).bounds;
        }
    }
#line 1936 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 28: /* type: standrad_type  */
#line 416 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type -> standrad_type
        (yyval.type_node_info).main_type = (TypeAttr::MainType)0;
        (yyval.type_node_info).type_ptr = (yyvsp[0].standared_type_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.type_node_info).type_node = new TypeNode(TypeNode::GrammarType::BASIC_TYPE);
        (yyval.type_node_info).base_type_node = (yyval.type_node_info).type_node;
        (yyval.type_node_info).type_node->set_base_type_node((yyval.type_node_info).type_node);
        (yyval.type_node_info).type_node->append_child((yyvsp[0].standared_type_node_info).standard_type_node);
    }
#line 1952 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 29: /* type: ARRAY '[' periods ']' OF type  */
#line 428 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type -> ARRAY '[' periods ']' OF type
        (yyval.type_node_info).main_type = (TypeAttr::MainType)1;
        (yyval.type_node_info).base_type_node = (yyvsp[0].type_node_info).base_type_node;
        (yyval.type_node_info).bounds = (yyvsp[-3].periods_node_info).bounds;
        if ((yyvsp[-3].periods_node_info).bounds){
            auto merged_bounds = new std::vector<ArrayType::ArrayBound>();
            for (auto i : *((yyvsp[-3].periods_node_info).bounds)){
                merged_bounds->push_back(i);
            }
            auto basic_type = (yyvsp[0].type_node_info).type_ptr;
            if((yyvsp[0].type_node_info).type_ptr->template_type() == TypeTemplate::TYPE::ARRAY) {
                for (auto i : *((yyvsp[0].type_node_info).bounds)){
                    merged_bounds->push_back(i);
                    (yyval.type_node_info).bounds->push_back(i);
                }
                basic_type = (yyvsp[0].type_node_info).type_ptr->DynamicCast<ArrayType>()->base_type();
            }
            PtrCollect((yyvsp[0].type_node_info).type_ptr);
            (yyval.type_node_info).type_ptr = new ArrayType(basic_type, *merged_bounds);
            
            delete merged_bounds;
        }
        if(error_flag)
            break; 
        (yyval.type_node_info).type_node = new TypeNode(TypeNode::GrammarType::ARRAY);
        (yyval.type_node_info).type_node->set_base_type_node((yyvsp[0].type_node_info).base_type_node);
        (yyval.type_node_info).type_node->append_child((yyvsp[-3].periods_node_info).periods_node);
        (yyval.type_node_info).type_node->append_child((yyvsp[0].type_node_info).type_node);
        delete (yyvsp[0].type_node_info).bounds;
        if ((yyvsp[0].type_node_info).record_info){
            delete (yyvsp[0].type_node_info).record_info;
        }
    }
#line 1991 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 30: /* type: RECORD record_body END  */
#line 463 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // type -> RECORD record_body END
        (yyval.type_node_info).main_type = (TypeAttr::MainType)2;
        (yyval.type_node_info).record_info = (yyvsp[-1].record_node_info).record_info;
        if ((yyvsp[-1].record_node_info).record_info){
            (yyval.type_node_info).type_ptr = new RecordType(*((yyvsp[-1].record_node_info).record_info));
        } else{
             (yyval.type_node_info).type_ptr = new RecordType();
        }
        if(error_flag)
            break; 
        (yyval.type_node_info).type_node = new TypeNode(TypeNode::GrammarType::RECORD_TYPE);
        (yyval.type_node_info).base_type_node = (yyval.type_node_info).type_node;
        (yyval.type_node_info).type_node->append_child((yyvsp[-1].record_node_info).record_body_node);
        (yyval.type_node_info).type_node->set_base_type_node((yyval.type_node_info).type_node);
    }
#line 2012 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 31: /* record_body: %empty  */
#line 480 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // record_body -> empty
        (yyval.record_node_info).record_info = new std::unordered_map<std::string, TypeTemplate*>();
        if(error_flag)
            break;
        (yyval.record_node_info).record_body_node = new RecordBodyNode();
    }
#line 2024 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 32: /* record_body: var_declaration  */
#line 486 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                        {
	(yyval.record_node_info).record_info = (yyvsp[0].variable_declaration_node_info).record_info;
	if(error_flag)
	    break;
	(yyval.record_node_info).record_body_node = new RecordBodyNode();
	(yyval.record_node_info).record_body_node->append_child((yyvsp[0].variable_declaration_node_info).variable_declaration_node);
	delete (yyvsp[0].variable_declaration_node_info).pos_info;
    }
#line 2037 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 33: /* record_body: var_declaration ';'  */
#line 494 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // record_body -> var_declaration ';'
        (yyval.record_node_info).record_info = (yyvsp[-1].variable_declaration_node_info).record_info;
        if(error_flag)
            break;
        (yyval.record_node_info).record_body_node = new RecordBodyNode();
        (yyval.record_node_info).record_body_node->append_child((yyvsp[-1].variable_declaration_node_info).variable_declaration_node);
        delete (yyvsp[-1].variable_declaration_node_info).pos_info;
    }
#line 2051 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 34: /* standrad_type: BASIC_TYPE  */
#line 505 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // standrad_type -> BASIC_TYPE
        string typestr = (yyvsp[0].token_info).value.get<string>();
        if (typestr == "integer"){
            (yyval.standared_type_node_info).type_ptr = TYPE_INT;
        } else if(typestr == "real"){
            (yyval.standared_type_node_info).type_ptr = TYPE_REAL;
        } else if(typestr == "boolean"){
            (yyval.standared_type_node_info).type_ptr = TYPE_BOOL;
        } else{
            (yyval.standared_type_node_info).type_ptr = TYPE_CHAR;
        }
        if(error_flag)
            break;
        (yyval.standared_type_node_info).standard_type_node = new BasicTypeNode();
        (yyval.standared_type_node_info).standard_type_node->set_type(dynamic_cast<BasicType*>((yyval.standared_type_node_info).type_ptr));
    }
#line 2073 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 35: /* periods: periods ',' period  */
#line 524 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // periods -> periods ',' period
        (yyval.periods_node_info).bounds = (yyvsp[-2].periods_node_info).bounds;
        (yyval.periods_node_info).bounds->push_back(*((yyvsp[0].period_node_info).bound));
        if(error_flag)
            break;
        (yyval.periods_node_info).periods_node = new PeriodsNode();
        (yyval.periods_node_info).periods_node->append_child((yyvsp[-2].periods_node_info).periods_node);
        (yyval.periods_node_info).periods_node->append_child((yyvsp[0].period_node_info).period_node);
        delete (yyvsp[0].period_node_info).bound;
    }
#line 2089 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 36: /* periods: period  */
#line 536 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // periods -> period
        (yyval.periods_node_info).bounds = new std::vector<ArrayType::ArrayBound>();
        (yyval.periods_node_info).bounds->push_back(*((yyvsp[0].period_node_info).bound));
        if(error_flag)
            break;
        (yyval.periods_node_info).periods_node = new PeriodsNode();
        (yyval.periods_node_info).periods_node->append_child((yyvsp[0].period_node_info).period_node);
        delete (yyvsp[0].period_node_info).bound;
    }
#line 2104 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 37: /* period: const_variable SUBCATALOG const_variable  */
#line 548 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {     
        // period -> const_variable SUBCATALOG const_variable
        int arr_len=0;
        (yyval.period_node_info).bound = new ArrayType::ArrayBound();
        if ((yyvsp[-2].value_node_info).type_ptr == TYPE_INT&&(yyvsp[0].value_node_info).type_ptr == TYPE_INT){
            arr_len = ((yyvsp[0].value_node_info).value - (yyvsp[-2].value_node_info).value).get<int>();
            (yyval.period_node_info).bound-> type_ = TYPE_INT;
            (yyval.period_node_info).bound->lb_ = (yyvsp[-2].value_node_info).value.get<int>();
            (yyval.period_node_info).bound->ub_ = (yyvsp[0].value_node_info).value.get<int>();
        } else if((yyvsp[-2].value_node_info).type_ptr == TYPE_CHAR&&(yyvsp[0].value_node_info).type_ptr == TYPE_CHAR){
            arr_len = (int)((yyvsp[0].value_node_info).value - (yyvsp[-2].value_node_info).value).get<char>();
            (yyval.period_node_info).bound-> type_ = TYPE_CHAR;
            (yyval.period_node_info).bound->lb_ = int((yyvsp[-2].value_node_info).value.get<int>());
            (yyval.period_node_info).bound->ub_ = int((yyvsp[0].value_node_info).value.get<int>());
        } else {
            semantic_error(real_ast,"array bound should be integer or char",(yyvsp[-1].token_info).line_num,(yyvsp[-1].token_info).column_num);
        }
        if(arr_len < 0){
            arr_len = 0;
            semantic_error(real_ast,"array bound should be positive",(yyvsp[-1].token_info).line_num,(yyvsp[-1].token_info).column_num);
        }
        if(error_flag){
            break;
        }
        (yyval.period_node_info).period_node =new PeriodNode();
        (yyval.period_node_info).period_node->set_len(arr_len+1);
        (yyval.period_node_info).period_node->append_child((yyvsp[-2].value_node_info).const_variable_node);
        (yyval.period_node_info).period_node->append_child((yyvsp[0].value_node_info).const_variable_node);
    }
#line 2138 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 38: /* var_declarations: %empty  */
#line 578 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declarations -> empty
        if(error_flag)
            break;
        (yyval.variable_declarations_node) = new VariableDeclarationsNode();
    }
#line 2149 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 39: /* var_declarations: VAR var_declaration ';'  */
#line 585 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declarations -> VAR var_declaration ';'
        if(error_flag)
            break;
        for (auto i : *((yyvsp[-1].variable_declaration_node_info).record_info)){
            int line = (yyvsp[-1].variable_declaration_node_info).pos_info->find(i.first)->second.first;
            int row = (yyvsp[-1].variable_declaration_node_info).pos_info->find(i.first)->second.second;
            ObjectSymbol *obj = new ObjectSymbol(i.first, i.second,line);
            if(!table_set_queue.top()->Insert<ObjectSymbol>(i.first,obj)){
                semantic_error(real_ast,"redefinition of '"+ i.first +"'",line,row);
                yynote(i.first,table_set_queue.top()->SearchEntry<ObjectSymbol>(i.first)->decl_line());
            }
        }
        (yyval.variable_declarations_node) = new VariableDeclarationsNode();
        (yyval.variable_declarations_node)->append_child((yyvsp[-1].variable_declaration_node_info).variable_declaration_node);
        delete (yyvsp[-1].variable_declaration_node_info).pos_info;
        if ((yyvsp[-1].variable_declaration_node_info).record_info){
            delete (yyvsp[-1].variable_declaration_node_info).record_info;
        }
    }
#line 2174 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 40: /* var_declaration: var_declaration ';' id_list ':' type  */
#line 607 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declaration -> var_declaration ';' id_list ':' type
         if(error_flag)
            break;   
        (yyval.variable_declaration_node_info).record_info = (yyvsp[-4].variable_declaration_node_info).record_info;
        (yyval.variable_declaration_node_info).pos_info = (yyvsp[-4].variable_declaration_node_info).pos_info;
        for (auto i : *((yyvsp[-2].id_list_node_info).list_ref)){
            auto res = (yyval.variable_declaration_node_info).record_info->insert(make_pair(i.first, (yyvsp[0].type_node_info).type_ptr));
            (yyval.variable_declaration_node_info).pos_info->insert(make_pair(i.first,std::make_pair(line_count,i.second)));
            if (!res.second){
                semantic_error(real_ast,"redefinition of '"+ i.first +"'",line_count,i.second);
            }
        }
        (yyval.variable_declaration_node_info).variable_declaration_node = new VariableDeclarationNode(VariableDeclarationNode::GrammarType::MULTIPLE_DECL,VariableDeclarationNode::ListType::TYPE);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-4].variable_declaration_node_info).variable_declaration_node);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[0].type_node_info).type_node);
        delete (yyvsp[-2].id_list_node_info).list_ref;
        if((yyvsp[0].type_node_info).bounds) {
            delete (yyvsp[0].type_node_info).bounds;
        }
        if((yyvsp[0].type_node_info).record_info) {
            delete (yyvsp[0].type_node_info).record_info;
        }
        PtrCollect((yyvsp[0].type_node_info).type_ptr);

    }
#line 2206 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 41: /* var_declaration: id_list ':' type  */
#line 635 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declaration -> id_list ':' type
        if(error_flag)
           break;
        (yyval.variable_declaration_node_info).record_info = new std::unordered_map<std::string, TypeTemplate*>();
        (yyval.variable_declaration_node_info).pos_info = new std::unordered_map<std::string, std::pair<int,int>>();
        for (auto i : *((yyvsp[-2].id_list_node_info).list_ref)){
            auto res = (yyval.variable_declaration_node_info).record_info->insert(make_pair(i.first, (yyvsp[0].type_node_info).type_ptr));
            (yyval.variable_declaration_node_info).pos_info->insert(make_pair(i.first,std::make_pair(line_count,i.second)));
            if (!res.second){
                semantic_error(real_ast,"redefinition of '"+ i.first +"'",line_count,i.second);
            }
        }
        (yyval.variable_declaration_node_info).variable_declaration_node = new VariableDeclarationNode(VariableDeclarationNode::GrammarType::SINGLE_DECL,VariableDeclarationNode::ListType::TYPE);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[0].type_node_info).type_node);
        delete (yyvsp[-2].id_list_node_info).list_ref;
        if((yyvsp[0].type_node_info).bounds) {
            delete (yyvsp[0].type_node_info).bounds;
        }
        if((yyvsp[0].type_node_info).record_info) {
            delete (yyvsp[0].type_node_info).record_info;
        }
        PtrCollect((yyvsp[0].type_node_info).type_ptr);
    }
#line 2236 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 42: /* var_declaration: var_declaration ';' id_list ':' ID  */
#line 661 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declaration -> var_declaration ';' id_list ':' ID
        if(error_flag)
            break;
        (yyval.variable_declaration_node_info).record_info = (yyvsp[-4].variable_declaration_node_info).record_info;
        (yyval.variable_declaration_node_info).pos_info = (yyvsp[-4].variable_declaration_node_info).pos_info;
        TypeTemplate *tmp = table_set_queue.top()->SearchEntry<TypeTemplate>((yyvsp[0].token_info).value.get<string>());
        if(tmp == nullptr){
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"undefined type '"+tn+"'",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            break;
        } else {
            for (auto i : *((yyvsp[-2].id_list_node_info).list_ref)){
                auto res = (yyval.variable_declaration_node_info).record_info->insert(make_pair(i.first, tmp));
                (yyval.variable_declaration_node_info).pos_info->insert(make_pair(i.first,std::make_pair(line_count,i.second)));
                if (!res.second){
                    semantic_error(real_ast,"redefinition of '"+ i.first +"'",line_count,i.second);
                }
            }
        }
        if(error_flag)
            break;
        (yyval.variable_declaration_node_info).variable_declaration_node = new VariableDeclarationNode(VariableDeclarationNode::GrammarType::MULTIPLE_DECL,VariableDeclarationNode::ListType::ID);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-4].variable_declaration_node_info).variable_declaration_node);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child(leaf_node);
        delete (yyvsp[-2].id_list_node_info).list_ref;
    }
#line 2270 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 43: /* var_declaration: id_list ':' ID  */
#line 691 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // var_declaration -> id_list ':' ID
        if(error_flag)
                break;
        TypeTemplate *tmp = table_set_queue.top()->SearchEntry<TypeTemplate>((yyvsp[0].token_info).value.get<string>());
        if(tmp==nullptr){
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"undefined type '"+tn+"'",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            (yyval.variable_declaration_node_info).record_info = new std::unordered_map<std::string, TypeTemplate*>();
            (yyval.variable_declaration_node_info).pos_info = new std::unordered_map<std::string, std::pair<int,int>>();
            break;
        } else {
            (yyval.variable_declaration_node_info).record_info = new std::unordered_map<std::string, TypeTemplate*>();
            (yyval.variable_declaration_node_info).pos_info = new std::unordered_map<std::string, std::pair<int,int>>();
            for (auto i : *((yyvsp[-2].id_list_node_info).list_ref)){
                auto res = (yyval.variable_declaration_node_info).record_info->insert(make_pair(i.first, tmp));
                (yyval.variable_declaration_node_info).pos_info->insert(make_pair(i.first,std::make_pair(line_count,i.second)));
                if (!res.second){
                    semantic_error(real_ast,"redefinition of '"+ i.first +"'",line_count,i.second);
                }
            }
        }
        (yyval.variable_declaration_node_info).variable_declaration_node = new VariableDeclarationNode(VariableDeclarationNode::GrammarType::SINGLE_DECL,VariableDeclarationNode::ListType::ID);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.variable_declaration_node_info).variable_declaration_node->append_child(leaf_node);
        delete (yyvsp[-2].id_list_node_info).list_ref;
    }
#line 2303 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 44: /* subprogram_declarations: %empty  */
#line 720 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_declarations -> empty
        if(error_flag)
            break;
        (yyval.subprogram_declarations_node) = new SubprogramDeclarationsNode();
    }
#line 2314 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 45: /* subprogram_declarations: subprogram_declarations subprogram_declaration ';'  */
#line 727 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_declarations -> subprogram_declarations subprogram_declaration ';'
        if(error_flag)
            break;
        (yyval.subprogram_declarations_node) = new SubprogramDeclarationsNode();
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-2].subprogram_declarations_node));
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-1].subprogram_declaration_node));
        TableSet* top = table_set_queue.top();
        table_set_queue.pop();
        delete top;
    }
#line 2330 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 46: /* subprogram_declaration: subprogram_head subprogram_body  */
#line 740 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_declaration -> subprogram_head subprogram_body
        if(error_flag)
            break;
        (yyval.subprogram_declaration_node) = new SubprogramDeclarationNode();
        (yyval.subprogram_declaration_node)->append_child((yyvsp[-1].subprogram_head_node));
        (yyval.subprogram_declaration_node)->append_child((yyvsp[0].subprogram_body_node));
    }
#line 2343 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 47: /* subprogram_body: const_declarations type_declarations var_declarations compound_statement  */
#line 750 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_body -> const_declarations type_declarations var_declarations compound_statement
        if(error_flag)
            break;
        (yyval.subprogram_body_node) = new SubprogramBodyNode();
        (yyval.subprogram_body_node)->append_child((yyvsp[-3].const_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[-2].type_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[-1].variable_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 2358 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 48: /* subprogram_head: FUNCTION ID formal_parameter ':' standrad_type ';'  */
#line 762 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' standrad_type ';'
        FunctionSymbol* tmp ;
        if((yyvsp[-3].formal_parameter_node_info).parameters){
            tmp = new FunctionSymbol((yyvsp[-4].token_info).value.get<string>(), (yyvsp[-1].standared_type_node_info).type_ptr, (yyvsp[-4].token_info).line_num, *(yyvsp[-3].formal_parameter_node_info).parameters);
        } else {
            tmp = new FunctionSymbol((yyvsp[-4].token_info).value.get<string>(), (yyvsp[-1].standared_type_node_info).type_ptr, (yyvsp[-4].token_info).line_num);
        }
        if (!table_set_queue.top()->Insert<FunctionSymbol>((yyvsp[-4].token_info).value.get<string>(), tmp)){
            string tn = (yyvsp[-4].token_info).value.get<string>();
            semantic_error(real_ast,"redefinition of function '"+tn+"'",(yyvsp[-4].token_info).line_num,(yyvsp[-4].token_info).column_num);
            yynote((yyvsp[-4].token_info).value.get<string>(),table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-4].token_info).value.get<string>())->decl_line());
        } 

        TableSet* now_table_set = new TableSet((yyvsp[-4].token_info).value.get<string>(), table_set_queue.top());
        table_set_queue.push(now_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
        FunctionSymbol* tmp2 = new FunctionSymbol(*tmp);
        string tag = (yyvsp[-4].token_info).value.get<string>();
        table_set_queue.top()->Insert<FunctionSymbol>(tag, tmp2);
        ObjectSymbol* tmp3 = new ObjectSymbol("__"+tag+"__", (yyvsp[-1].standared_type_node_info).type_ptr, (yyvsp[-4].token_info).line_num);
        table_set_queue.top()->Insert<ObjectSymbol>("__"+tag+"__", tmp3);
        if ((yyvsp[-3].formal_parameter_node_info).parameters){
            int cnt = 0;
            for (auto i : *((yyvsp[-3].formal_parameter_node_info).parameters)){
                ObjectSymbol *tmp = new ObjectSymbol(i.first, i.second.first, (yyvsp[-4].token_info).line_num);
                if (i.second.second == FunctionSymbol::PARAM_MODE::REFERENCE){
                    tmp->set_ref(true);
                }
                if(!table_set_queue.top()->Insert<ObjectSymbol>(i.first, tmp)){
                    int line = (yyvsp[-3].formal_parameter_node_info).pos_info->at(cnt).first;
                    int row = (yyvsp[-3].formal_parameter_node_info).pos_info->at(cnt).second;
                    semantic_error(real_ast,"redefinition of '"+ i.first +"'",line,row);
                    yynote(i.first,table_set_queue.top()->SearchEntry<ObjectSymbol>(i.first)->decl_line());
                }
                cnt++;
            }
        }
        if(error_flag)
            break;
        (yyval.subprogram_head_node) = new SubprogramHeadNode(SubprogramHeadNode::GrammarType::FUNCTION);
        (yyval.subprogram_head_node)->set_id((yyvsp[-4].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-4].token_info).value);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-3].formal_parameter_node_info).formal_parameter_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].standared_type_node_info).standard_type_node);
        if((yyvsp[-3].formal_parameter_node_info).parameters){
            delete (yyvsp[-3].formal_parameter_node_info).parameters;
        }
        if((yyvsp[-3].formal_parameter_node_info).pos_info){
            delete (yyvsp[-3].formal_parameter_node_info).pos_info;
        }
    }
#line 2416 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 49: /* subprogram_head: PROCEDURE ID formal_parameter ';'  */
#line 816 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // subprogram_head -> PROCEDURE ID formal_parameter ';'
        if(error_flag)
            break;
        FunctionSymbol* tmp ;
        if((yyvsp[-1].formal_parameter_node_info).parameters){
            tmp = new FunctionSymbol((yyvsp[-2].token_info).value.get<string>(), nullptr, (yyvsp[-2].token_info).line_num, *(yyvsp[-1].formal_parameter_node_info).parameters);
        } else {
            tmp = new FunctionSymbol((yyvsp[-2].token_info).value.get<string>(), nullptr, (yyvsp[-2].token_info).line_num);
        }
        
        if (!table_set_queue.top()->Insert<FunctionSymbol>((yyvsp[-2].token_info).value.get<string>(), tmp)){
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"redefinition of procedure '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
            yynote((yyvsp[-2].token_info).value.get<string>(),table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-2].token_info).value.get<string>())->decl_line());
        } 

        TableSet* now_table_set = new TableSet((yyvsp[-2].token_info).value.get<string>(),table_set_queue.top());
        table_set_queue.push(now_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
        FunctionSymbol* tmp2 = new FunctionSymbol(*tmp);
        table_set_queue.top()->Insert<FunctionSymbol>((yyvsp[-2].token_info).value.get<string>(), tmp2);
        if ((yyvsp[-1].formal_parameter_node_info).parameters){
            int cnt = 0;
            for (auto i : *((yyvsp[-1].formal_parameter_node_info).parameters)){
                ObjectSymbol *tmp = new ObjectSymbol(i.first, i.second.first, (yyvsp[-2].token_info).line_num);
                if (i.second.second == FunctionSymbol::PARAM_MODE::REFERENCE){
                    tmp->set_ref(true);
                }
                if(!table_set_queue.top()->Insert<ObjectSymbol>(i.first, tmp)){
                    int line = (yyvsp[-1].formal_parameter_node_info).pos_info->at(cnt).first;
                    int row = (yyvsp[-1].formal_parameter_node_info).pos_info->at(cnt).second;
                    semantic_error(real_ast,"redefinition of '"+ i.first +"'",line,row);
                    yynote(i.first,table_set_queue.top()->SearchEntry<ObjectSymbol>(i.first)->decl_line());
                }
                cnt++;
            }
        }
        
        (yyval.subprogram_head_node) = new SubprogramHeadNode(SubprogramHeadNode::GrammarType::PROCEDURE);
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].formal_parameter_node_info).formal_parameter_node);
        delete (yyvsp[-1].formal_parameter_node_info).parameters;
        delete (yyvsp[-1].formal_parameter_node_info).pos_info;
    }
#line 2467 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 50: /* formal_parameter: %empty  */
#line 863 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // formal_parameter -> empty
        (yyval.formal_parameter_node_info).parameters = new std::vector<FunctionSymbol::Parameter>();
        (yyval.formal_parameter_node_info).pos_info = new std::vector<std::pair<int,int>>();
        if(error_flag)
            break;
        (yyval.formal_parameter_node_info).formal_parameter_node = new FormalParamNode();
    }
#line 2480 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 51: /* formal_parameter: '(' parameter_lists ')'  */
#line 872 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // formal_parameter -> '(' parameter_lists ')'
        (yyval.formal_parameter_node_info).parameters = (yyvsp[-1].parameter_lists_node_info).parameters;
        (yyval.formal_parameter_node_info).pos_info = (yyvsp[-1].parameter_lists_node_info).pos_info;
        if(error_flag)
            break;
        (yyval.formal_parameter_node_info).formal_parameter_node = new FormalParamNode();
        (yyval.formal_parameter_node_info).formal_parameter_node->append_child((yyvsp[-1].parameter_lists_node_info).param_lists_node);
    }
#line 2494 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 52: /* parameter_lists: parameter_lists ';' parameter_list  */
#line 883 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // parameter_lists -> parameter_lists ';' parameter_list
        (yyval.parameter_lists_node_info).parameters = (yyvsp[-2].parameter_lists_node_info).parameters;
        (yyval.parameter_lists_node_info).pos_info = (yyvsp[-2].parameter_lists_node_info).pos_info;
        (yyval.parameter_lists_node_info).parameters->insert((yyval.parameter_lists_node_info).parameters->end(), (yyvsp[0].parameter_list_node_info).parameters->begin(), (yyvsp[0].parameter_list_node_info).parameters->end());
        (yyval.parameter_lists_node_info).pos_info->insert((yyval.parameter_lists_node_info).pos_info->end(),(yyvsp[0].parameter_list_node_info).pos_info->begin(), (yyvsp[0].parameter_list_node_info).pos_info->end());
        if(error_flag)
            break;
        (yyval.parameter_lists_node_info).param_lists_node = new ParamListsNode(ParamListsNode::GrammarType::MULTIPLE_PARAM_LIST);
        (yyval.parameter_lists_node_info).param_lists_node->append_child((yyvsp[-2].parameter_lists_node_info).param_lists_node);
        (yyval.parameter_lists_node_info).param_lists_node->append_child((yyvsp[0].parameter_list_node_info).param_list_node);
    }
#line 2511 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 53: /* parameter_lists: parameter_list  */
#line 896 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {  
        // parameter_lists -> parameter_list
        (yyval.parameter_lists_node_info).parameters = (yyvsp[0].parameter_list_node_info).parameters;
        (yyval.parameter_lists_node_info).pos_info = (yyvsp[0].parameter_list_node_info).pos_info;
        if(error_flag)
            break;
        (yyval.parameter_lists_node_info).param_lists_node = new ParamListsNode(ParamListsNode::GrammarType::SINGLE_PARAM_LIST);
        (yyval.parameter_lists_node_info).param_lists_node->append_child((yyvsp[0].parameter_list_node_info).param_list_node);
    }
#line 2525 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 54: /* parameter_list: var_parameter  */
#line 907 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // parameter_list -> var_parameter
        (yyval.parameter_list_node_info).parameters = (yyvsp[0].var_parameter_node_info).parameters;
        (yyval.parameter_list_node_info).pos_info = (yyvsp[0].var_parameter_node_info).pos_info;
        if(error_flag)
            break;
        (yyval.parameter_list_node_info).param_list_node = new ParamListNode();
        (yyval.parameter_list_node_info).param_list_node->append_child((yyvsp[0].var_parameter_node_info).var_parameter_node);
    }
#line 2539 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 55: /* parameter_list: value_parameter  */
#line 917 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // parameter_list -> value_parameter
        (yyval.parameter_list_node_info).parameters = (yyvsp[0].value_parameter_node_info).parameters;
        (yyval.parameter_list_node_info).pos_info = (yyvsp[0].value_parameter_node_info).pos_info;
        if(error_flag)
            break;
        (yyval.parameter_list_node_info).param_list_node = new ParamListNode();
        (yyval.parameter_list_node_info).param_list_node->append_child((yyvsp[0].value_parameter_node_info).value_parameter_node);
    }
#line 2553 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 56: /* var_parameter: VAR value_parameter  */
#line 928 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // var_parameter -> VAR value_parameter
        int para_len = (yyvsp[0].value_parameter_node_info).parameters->size();
        for (int i = 0; i < para_len; i++){
            (yyvsp[0].value_parameter_node_info).parameters->at(i).second.second = FunctionSymbol::PARAM_MODE::REFERENCE;
        }
        (yyval.var_parameter_node_info).parameters = (yyvsp[0].value_parameter_node_info).parameters;
        (yyval.var_parameter_node_info).pos_info = (yyvsp[0].value_parameter_node_info).pos_info;
        if(error_flag)
            break;
        (yyval.var_parameter_node_info).var_parameter_node = new VarParamNode();
        (yyval.var_parameter_node_info).var_parameter_node->append_child((yyvsp[0].value_parameter_node_info).value_parameter_node);
    }
#line 2571 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 57: /* value_parameter: id_list ':' standrad_type  */
#line 943 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // value_parameter -> id_list ':' standrad_type
        (yyval.value_parameter_node_info).parameters = new std::vector<FunctionSymbol::Parameter>();
        (yyval.value_parameter_node_info).pos_info = new std::vector<std::pair<int,int>>();
        FunctionSymbol::ParamType tmp((yyvsp[0].standared_type_node_info).type_ptr,FunctionSymbol::PARAM_MODE::VALUE);
        for (auto i : *((yyvsp[-2].id_list_node_info).list_ref)){
            FunctionSymbol::Parameter tmp_pair(i.first,tmp);
            (yyval.value_parameter_node_info).parameters->push_back(tmp_pair);
            (yyval.value_parameter_node_info).pos_info->push_back(std::make_pair(line_count,i.second));
        }
        
        if(error_flag)
            break;
        (yyval.value_parameter_node_info).value_parameter_node = new ValueParamNode();
        (yyval.value_parameter_node_info).value_parameter_node->append_child((yyvsp[-2].id_list_node_info).id_list_node);
        (yyval.value_parameter_node_info).value_parameter_node->append_child((yyvsp[0].standared_type_node_info).standard_type_node);
        delete (yyvsp[-2].id_list_node_info).list_ref;
    }
#line 2594 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 58: /* compound_statement: BEGIN_ statement_list END  */
#line 963 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // compound_statement -> BEGIN_ statement_list END
        if(error_flag)
            break;
        (yyval.compound_statement_node) = new CompoundStatementNode();
        (yyval.compound_statement_node)->append_child((yyvsp[-1].statement_list_node));
    }
#line 2606 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 59: /* statement_list: statement_list ';' statement  */
#line 972 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement_list -> statement_list ';' statement
        if(error_flag)
            break;
        (yyval.statement_list_node) = new StatementListNode();
        (yyval.statement_list_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 2619 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 60: /* statement_list: statement  */
#line 980 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement_list -> statement
        if(error_flag)
            break;
        (yyval.statement_list_node) = new StatementListNode();
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 2631 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 61: /* statement: variable ASSIGNOP expression  */
#line 989 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        //statement -> variable ASSIGNOP expression
        if(error_flag)
            break;
        bool var_flag = ((yyvsp[-2].variable_node_info).type_ptr==TYPE_REAL && (yyvsp[0].expression_node_info).type_ptr==TYPE_INT) || is_same((yyvsp[-2].variable_node_info).type_ptr,(yyvsp[0].expression_node_info).type_ptr);
        bool str_flag = ((yyvsp[-2].variable_node_info).type_ptr != TYPE_ERROR &&
        		 (yyvsp[-2].variable_node_info).type_ptr->StringLike() &&
        		 (yyvsp[0].expression_node_info).type_ptr==TYPE_STRINGLIKE);
        if(!var_flag && !str_flag){
            string tn1 = type_name((yyvsp[-2].variable_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].expression_node_info).type_ptr);
            semantic_error(real_ast,"incompatible type assigning '"+tn1+"' from '"+tn2+"'",line_count,0);
            break;
        }
        std::string func_name = table_set_queue.top()->tag();

        if(func_name == *(yyvsp[-2].variable_node_info).name){
            (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::FUNC_ASSIGN_OP_EXP);
        }else{
            (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::VAR_ASSIGN_OP_EXP);
            if (!(yyvsp[-2].variable_node_info).is_lvalue){
                semantic_error(real_ast,"lvalue required as left operand of assignment",(yyvsp[-1].token_info).line_num,(yyvsp[-1].token_info).column_num);
            }
        }
        if(error_flag)
            break;
        (yyval.statement_node)->append_child((yyvsp[-2].variable_node_info).variable_node);
        (yyval.statement_node)->append_child((yyvsp[0].expression_node_info).expression_node);
        delete (yyvsp[-2].variable_node_info).name;
    }
#line 2666 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 62: /* statement: call_procedure_statement  */
#line 1020 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> call_procedure_statement
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::PROCEDURE_CALL);
        (yyval.statement_node)->append_child((yyvsp[0].procedure_call_node));
    }
#line 2678 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 63: /* statement: compound_statement  */
#line 1028 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> compound_statement
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::COMPOUND_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 2690 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 64: /* statement: IF expression THEN statement else_part  */
#line 1036 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // statement -> IF expression THEN statement else_part
        if(error_flag)
            break;
        //类型检查
        if(!is_same((yyvsp[-3].expression_node_info).type_ptr,TYPE_BOOL)){
            string tn = type_name((yyvsp[-3].expression_node_info).type_ptr);
            semantic_error(real_ast,"IF quantity cannot be '"+tn+"'",line_count,0);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::IF_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-3].expression_node_info).expression_node);
        (yyval.statement_node)->append_child((yyvsp[-1].statement_node));
        (yyval.statement_node)->append_child((yyvsp[0].else_node));
    }
#line 2709 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 65: /* statement: CASE expression OF case_body END  */
#line 1051 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> CASE expression OF case_body END
        if(error_flag)
            break;
        //类型检查
        bool valid = (yyvsp[-3].expression_node_info).type_ptr == TYPE_INT || (yyvsp[-3].expression_node_info).type_ptr == TYPE_BOOL || (yyvsp[-3].expression_node_info).type_ptr == TYPE_CHAR;
        if(!valid){
            string tn = type_name((yyvsp[-3].expression_node_info).type_ptr);
            semantic_error(real_ast,"CASE quantity cannot be '"+tn+"'",line_count,0);
        }
        if(!is_same((yyvsp[-1].case_body_node_info).type_ptr,TYPE_ERROR)){
            if(!is_same((yyvsp[-3].expression_node_info).type_ptr,(yyvsp[-1].case_body_node_info).type_ptr)){
            	string tn = type_name((yyvsp[-3].expression_node_info).type_ptr);
            	string tn2 = type_name((yyvsp[-1].case_body_node_info).type_ptr);
                semantic_error(real_ast,"CASE label cannot reduce from '"+tn2+"' to '"+tn+"'",line_count,0);
            }
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::CASE_STATEMET);
        (yyval.statement_node)->append_child((yyvsp[-3].expression_node_info).expression_node);
        (yyval.statement_node)->append_child((yyvsp[-1].case_body_node_info).case_body_node);
    }
#line 2735 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 66: /* statement: WHILE expression DO statement  */
#line 1073 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> WHILE expression DO statement
        if(error_flag)
            break;
        if(!is_same((yyvsp[-2].expression_node_info).type_ptr,TYPE_BOOL)){
            string tn = type_name((yyvsp[-2].expression_node_info).type_ptr);
            semantic_error(real_ast,"WHILE quantity cannot be '"+tn+"'",line_count,0);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::WHILE_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-2].expression_node_info).expression_node);
        (yyval.statement_node)->append_child((yyvsp[0].statement_node));

    }
#line 2753 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 67: /* statement: REPEAT statement_list UNTIL expression  */
#line 1087 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> REPEAT statement_list UNTIL expression
        if(error_flag)
            break;
        //类型检查
        if(!is_same((yyvsp[0].expression_node_info).type_ptr,TYPE_BOOL)){
            string tn = type_name((yyvsp[0].expression_node_info).type_ptr);
            semantic_error(real_ast,"REPEAT quantity cannot be '"+tn+"'",line_count,0);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::REPEAT_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.statement_node)->append_child((yyvsp[0].expression_node_info).expression_node);
    }
#line 2771 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 68: /* statement: FOR ID ASSIGNOP expression updown expression DO statement  */
#line 1101 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> FOR ID ASSIGNOP expression updown expression DO statement
        if(error_flag)
            break;
        //类型检查
        ObjectSymbol *tmp = table_set_queue.top()->SearchEntry<ObjectSymbol>((yyvsp[-6].token_info).value.get<string>());
        if(tmp==nullptr){
            string tn = (yyvsp[-6].token_info).value.get<string>();
            semantic_error(real_ast,"'"+tn+"' undeclared",(yyvsp[-6].token_info).line_num,(yyvsp[-6].token_info).column_num);
            break;
        }
        if((!is_basic(tmp->type()))||(!is_same(tmp->type(),(yyvsp[-4].expression_node_info).type_ptr))){
            string tn1 = type_name(tmp->type());
            string tn2 = type_name((yyvsp[-4].expression_node_info).type_ptr);
            semantic_error(real_ast,"incompatible type assigning '"+tn1+"' from '"+tn2+"'",line_count,0);
        }

        if((!is_same((yyvsp[-4].expression_node_info).type_ptr,(yyvsp[-2].expression_node_info).type_ptr))||(is_same((yyvsp[-4].expression_node_info).type_ptr,TYPE_REAL))){
            string tn1 = type_name((yyvsp[-4].expression_node_info).type_ptr);
            string tn2 = type_name((yyvsp[-2].expression_node_info).type_ptr);
            semantic_error(real_ast,"invalid updown type from '"+tn1+"' to '"+tn2+"'",line_count,0);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::FOR_STATEMENT);
        LeafNode *id_node = new LeafNode((yyvsp[-6].token_info).value);
        (yyval.statement_node)->append_child(id_node);
        (yyval.statement_node)->append_child((yyvsp[-4].expression_node_info).expression_node);
        (yyval.statement_node)->append_child((yyvsp[-3].updown_node));
        (yyval.statement_node)->append_child((yyvsp[-2].expression_node_info).expression_node);
        (yyval.statement_node)->append_child((yyvsp[0].statement_node));
    }
#line 2806 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 69: /* statement: %empty  */
#line 1132 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> empty
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::EPSILON);
    }
#line 2817 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 70: /* statement: READ '(' variable_list ')'  */
#line 1139 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> READ '(' variable_list ')'
        if(error_flag)
            break;
        if(!(yyvsp[-1].variable_list_node_info).variable_list_node->set_types((yyvsp[-1].variable_list_node_info).type_ptr_list)){
            semantic_error(real_ast,"basic type is expected in READ",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
        }  
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::READ_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-1].variable_list_node_info).variable_list_node);
        delete (yyvsp[-1].variable_list_node_info).type_ptr_list;
    }
#line 2833 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 71: /* statement: READLN '(' variable_list ')'  */
#line 1151 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> READLN '(' variable_list ')'
        if(error_flag)
            break;
        if(!(yyvsp[-1].variable_list_node_info).variable_list_node->set_types((yyvsp[-1].variable_list_node_info).type_ptr_list)){
            semantic_error(real_ast,"basic type is expected in READLN",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::READLN_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-1].variable_list_node_info).variable_list_node);
        delete (yyvsp[-1].variable_list_node_info).type_ptr_list;
    }
#line 2849 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 72: /* statement: READLN '(' ')'  */
#line 1163 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> READLN '('  ')'
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::READLN_STATEMENT);
    }
#line 2860 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 73: /* statement: READLN  */
#line 1170 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> READLN
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::READLN_STATEMENT);
    }
#line 2871 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 74: /* statement: WRITE '(' expression_list ')'  */
#line 1177 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> WRITE '(' expression_list ')'
        if(error_flag)
            break;
        if(!(yyvsp[-1].expression_list_node_info).expression_list_node->set_types((yyvsp[-1].expression_list_node_info).type_ptr_list)){
            semantic_error(real_ast,"basic type is expected in WRITE",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
        }
        
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::WRITE_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-1].expression_list_node_info).expression_list_node);
        delete (yyvsp[-1].expression_list_node_info).type_ptr_list;
        delete (yyvsp[-1].expression_list_node_info).is_lvalue_list;
    }
#line 2889 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 75: /* statement: WRITELN '(' expression_list ')'  */
#line 1191 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> WRITELN'(' expression_list ')'
        if(error_flag)
            break;
        if(!(yyvsp[-1].expression_list_node_info).expression_list_node->set_types((yyvsp[-1].expression_list_node_info).type_ptr_list)){
            semantic_error(real_ast,"basic type is expected in WRITELN",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
        }
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::WRITELN_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[-1].expression_list_node_info).expression_list_node);
        delete (yyvsp[-1].expression_list_node_info).type_ptr_list;
        delete (yyvsp[-1].expression_list_node_info).is_lvalue_list;
    }
#line 2906 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 76: /* statement: WRITELN '(' ')'  */
#line 1204 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> WRITELN '(' ')'
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::WRITELN_STATEMENT);
    }
#line 2917 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 77: /* statement: WRITELN  */
#line 1211 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // statement -> WRITELN
        if(error_flag)
            break;
        (yyval.statement_node) = new StatementNode(StatementNode::GrammarType::WRITELN_STATEMENT);
    }
#line 2928 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 78: /* variable_list: variable  */
#line 1221 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    { 
        // variable_list -> variable
        (yyval.variable_list_node_info).type_ptr_list = new std::vector<TypeTemplate*>();
        (yyval.variable_list_node_info).type_ptr_list->push_back((yyvsp[0].variable_node_info).type_ptr);
        if(error_flag)
            break;
        (yyval.variable_list_node_info).variable_list_node = new VariableListNode(VariableListNode::GrammarType::VARIABLE);
        (yyval.variable_list_node_info).variable_list_node->append_child((yyvsp[0].variable_node_info).variable_node);
        if((yyvsp[0].variable_node_info).name) delete (yyvsp[0].variable_node_info).name;
    }
#line 2943 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 79: /* variable_list: variable_list ',' variable  */
#line 1230 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                  {
        // variable_list -> variable_list ',' variable
        (yyval.variable_list_node_info).type_ptr_list = (yyvsp[-2].variable_list_node_info).type_ptr_list;
        (yyval.variable_list_node_info).type_ptr_list->push_back((yyvsp[0].variable_node_info).type_ptr);
        if(error_flag)
            break;
        (yyval.variable_list_node_info).variable_list_node = new VariableListNode(VariableListNode::GrammarType::VARIABLE_LIST_VARIABLE);
        (yyval.variable_list_node_info).variable_list_node->append_child((yyvsp[-2].variable_list_node_info).variable_list_node);
        (yyval.variable_list_node_info).variable_list_node->append_child((yyvsp[0].variable_node_info).variable_node);
        if((yyvsp[0].variable_node_info).name) delete (yyvsp[0].variable_node_info).name;
    }
#line 2959 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 80: /* variable: ID '(' ')'  */
#line 1243 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // variable -> ID '('')'
        if (error_flag) break;
        FunctionSymbol *tmp = table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-2].token_info).value.get<string>());
        (yyval.variable_node_info).type_ptr = TYPE_ERROR;
        (yyval.variable_node_info).is_lvalue = false;
        if(tmp == nullptr){
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"undefined function '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
            break;
        }
        if(tmp->type() != nullptr && tmp->symbol_type() == ObjectSymbol::SYMBOL_TYPE::FUNCTION){
            if(!tmp->AssertParams()){
                string tn = (yyvsp[-2].token_info).value.get<string>();
                string param = tmp->ParamName();
	        semantic_error(real_ast,"too few arguments to function '"+tn+"' (expected '("+param+")')",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
                break;
            }
            (yyval.variable_node_info).type_ptr = tmp->type();
            (yyval.variable_node_info).name = new std::string((yyvsp[-2].token_info).value.get<string>());
            real_ast->libs()->Call(*((yyval.variable_node_info).name));
            string name = (yyvsp[-2].token_info).value.get<string>()+"()";
            (yyval.variable_node_info).variable_node = new VariableNode();
            LeafNode *id_node = new LeafNode(name);
            (yyval.variable_node_info).variable_node->append_child(id_node);
        } else {
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"undefined function '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
        }
         
    }
#line 2995 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 81: /* variable: ID id_varparts  */
#line 1275 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // variable -> ID id_varparts
        if(error_flag)
            break;
        ObjectSymbol *tmp = table_set_queue.top()->SearchEntry<ObjectSymbol>((yyvsp[-1].token_info).value.get<string>());
        string name = (yyvsp[-1].token_info).value.get<string>();
        (yyval.variable_node_info).name = new std::string((yyvsp[-1].token_info).value.get<string>());
        (yyval.variable_node_info).type_ptr = TYPE_ERROR;
        if(tmp == nullptr) {
            semantic_error(real_ast,"'"+name+ "' undeclared",(yyvsp[-1].token_info).line_num,(yyvsp[-1].token_info).column_num);
            break;
        } else {
            //类型检查
            (yyval.variable_node_info).is_lvalue = true;
            if (ObjectSymbol::SYMBOL_TYPE::CONST == tmp->symbol_type()){
                tmp = dynamic_cast<ConstSymbol*>(tmp);
                (yyval.variable_node_info).is_lvalue = false;
            } else if(ObjectSymbol::SYMBOL_TYPE::FUNCTION == tmp->symbol_type()){
                //函数调用 类型检查
                if (name!=table_set_queue.top()->tag()){
                    if(!dynamic_cast<FunctionSymbol*>(tmp)->AssertParams()){
                        string param = dynamic_cast<FunctionSymbol*>(tmp)->ParamName();
                        semantic_error(real_ast,"too few arguments to function '"+name+"' (expected '("+param+")')",line_count,0);
                    }else{
                    	name += "()";
                    }
                }else{
                    name="__"+name+"__";
                }
                (yyval.variable_node_info).is_lvalue = false;
                real_ast->libs()->Call(tmp->name());
            } else {
                if (tmp->type()->template_type() == TypeTemplate::TYPE::ARRAY && !error_flag){
                    std::vector<ArrayType::ArrayBound> bounds = dynamic_cast<ArrayType*>(tmp->type())->bounds();
                    (yyvsp[0].id_varparts_node_info).id_varparts_node->set_lb(bounds);
                }
            }
            (yyval.variable_node_info).type_ptr = (yyvsp[0].id_varparts_node_info).AccessCheck(tmp->type());
            if((yyval.variable_node_info).type_ptr==nullptr){
                string tn1 = type_name(tmp->type());
                if(tmp->symbol_type() == ObjectSymbol::SYMBOL_TYPE::FUNCTION ||
                   tmp->symbol_type() == ObjectSymbol::SYMBOL_TYPE::CONST ||
                   tmp->type() == TYPE_ERROR ||
                   tmp->type()->template_type() == TypeTemplate::TYPE::BASIC){
                    if((yyvsp[0].id_varparts_node_info).var_parts != nullptr && (yyvsp[0].id_varparts_node_info).var_parts->size() != 0){
                    	semantic_error(real_ast,"requested value is nither array nor record (have '"+tn1+"')",line_count,0);
                    }
                }else{
                    string tn2;
                    std::vector<VarParts>* vp = (yyvsp[0].id_varparts_node_info).var_parts;
                    if(vp == nullptr) tn2 += "error";
                    else{
                        for(int i=0;i<vp->size();i++){
                            if((*vp)[i].flag == 0){
                                tn2 += "[" + type_name(*((*vp)[i].subscript)) + "]";
                            }else{
                            	tn2 += (*vp)[i].name;
                            }
			    if(i != vp->size() - 1) tn2 += ",";
		        }
                    }
                    semantic_error(real_ast,"invalid request from '"+tn1+"' with '"+tn2+"'",line_count,0);
                }
            }
            if(tmp->is_ref()){
                name = "*("+name+")";
            }
        }

        (yyval.variable_node_info).variable_node = new VariableNode();
        LeafNode *id_node = new LeafNode(name);
        (yyval.variable_node_info).variable_node->append_child(id_node);
        (yyval.variable_node_info).variable_node->append_child((yyvsp[0].id_varparts_node_info).id_varparts_node);
        for (auto i : *((yyvsp[0].id_varparts_node_info).var_parts)){
            delete i.subscript;
        }
        delete (yyvsp[0].id_varparts_node_info).var_parts;
    }
#line 3078 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 82: /* id_varparts: %empty  */
#line 1355 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // id_varparts -> empty.
        if(error_flag)
            break;
        (yyval.id_varparts_node_info).var_parts = new std::vector<VarParts>();
        if(error_flag)
            break;
        (yyval.id_varparts_node_info).id_varparts_node = new IDVarPartsNode();
    }
#line 3092 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 83: /* id_varparts: id_varparts id_varpart  */
#line 1365 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // id_varparts -> id_varparts id_varpart.
        if(error_flag)
            break;
        if((yyvsp[-1].id_varparts_node_info).var_parts){
            (yyval.id_varparts_node_info).var_parts = (yyvsp[-1].id_varparts_node_info).var_parts;
        } else {
            (yyval.id_varparts_node_info).var_parts = new std::vector<VarParts>();
        }
        
        (yyval.id_varparts_node_info).var_parts->push_back(*((yyvsp[0].id_varpart_node_info).var_part));

        (yyval.id_varparts_node_info).id_varparts_node = new IDVarPartsNode();
        (yyval.id_varparts_node_info).id_varparts_node->append_child((yyvsp[-1].id_varparts_node_info).id_varparts_node);
        (yyval.id_varparts_node_info).id_varparts_node->append_child((yyvsp[0].id_varpart_node_info).id_varpart_node);
        delete (yyvsp[0].id_varpart_node_info).var_part;
    }
#line 3114 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 84: /* id_varpart: '[' expression_list ']'  */
#line 1385 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // id_varpart -> [expression_list].
        (yyval.id_varpart_node_info).var_part= new VarParts();
        (yyval.id_varpart_node_info).var_part->flag = 0;//数组
        (yyval.id_varpart_node_info).var_part->subscript = (yyvsp[-1].expression_list_node_info).type_ptr_list;
        if(error_flag)
            break;
        (yyval.id_varpart_node_info).id_varpart_node = new IDVarPartNode(IDVarPartNode::GrammarType::EXP_LIST);
        (yyval.id_varpart_node_info).id_varpart_node->append_child((yyvsp[-1].expression_list_node_info).expression_list_node);
        delete (yyvsp[-1].expression_list_node_info).is_lvalue_list;
    }
#line 3130 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 85: /* id_varpart: '.' ID  */
#line 1397 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // id_varpart -> .id.
        (yyval.id_varpart_node_info).var_part= new VarParts();
        (yyval.id_varpart_node_info).var_part->flag = 1;//结构体
        (yyval.id_varpart_node_info).var_part->name = (yyvsp[0].token_info).value.get<string>();
        if(error_flag)
            break;
        (yyval.id_varpart_node_info).id_varpart_node = new IDVarPartNode(IDVarPartNode::GrammarType::_ID);
        LeafNode *id_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.id_varpart_node_info).id_varpart_node->append_child(id_node);
    }
#line 3146 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 86: /* else_part: %empty  */
#line 1409 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // else_part -> empty.
        if(error_flag)
            break;
        (yyval.else_node) = new ElseNode(ElseNode::GrammarType::EPSILON);
    }
#line 3157 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 87: /* else_part: ELSE statement  */
#line 1416 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // else_part -> ELSE statement.
        if(error_flag)
            break;
        (yyval.else_node) = new ElseNode(ElseNode::GrammarType::ELSE_STATEMENT);
        (yyval.else_node)->append_child((yyvsp[0].statement_node));
    }
#line 3169 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 88: /* case_body: %empty  */
#line 1424 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // case_body -> empty.
        (yyval.case_body_node_info).type_ptr= TYPE_ERROR;
        if(error_flag)
            break;
        (yyval.case_body_node_info).case_body_node = new CaseBodyNode();
    }
#line 3181 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 89: /* case_body: branch_list  */
#line 1432 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // case_body -> branch_list.
        (yyval.case_body_node_info).type_ptr = (yyvsp[0].branch_list_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.case_body_node_info).case_body_node = new CaseBodyNode();
        (yyval.case_body_node_info).case_body_node->append_child((yyvsp[0].branch_list_node_info).branch_list_node);
    }
#line 3194 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 90: /* branch_list: branch_list ';' branch  */
#line 1442 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // branch_list -> branch_list branch.
        if(error_flag)
            break;        
        if((yyvsp[-2].branch_list_node_info).type_ptr!=(yyvsp[0].branch_node_info).type_ptr){
            string tn1 = type_name((yyvsp[-2].branch_list_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].branch_node_info).type_ptr);
            semantic_error(real_ast,"branch type conflict between '"+tn1+"' and '"+tn2+"'",line_count,0);
        }
        (yyval.branch_list_node_info).type_ptr = (yyvsp[-2].branch_list_node_info).type_ptr;

        (yyval.branch_list_node_info).branch_list_node = new BranchListNode();
        (yyval.branch_list_node_info).branch_list_node->append_child((yyvsp[-2].branch_list_node_info).branch_list_node);
        (yyval.branch_list_node_info).branch_list_node->append_child((yyvsp[0].branch_node_info).branch_node);
    }
#line 3214 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 91: /* branch_list: branch  */
#line 1458 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // branch_list -> branch.
        (yyval.branch_list_node_info).type_ptr = (yyvsp[0].branch_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.branch_list_node_info).branch_list_node = new BranchListNode();
        (yyval.branch_list_node_info).branch_list_node->append_child((yyvsp[0].branch_node_info).branch_node);
    }
#line 3227 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 92: /* branch: const_list ':' statement  */
#line 1468 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // branch -> const_list : statement.
        (yyval.branch_node_info).type_ptr = (yyvsp[-2].const_list_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.branch_node_info).branch_node = new BranchNode();
        (yyval.branch_node_info).branch_node->append_child((yyvsp[-2].const_list_node_info).const_list_node);
        (yyval.branch_node_info).branch_node->append_child((yyvsp[0].statement_node));
    }
#line 3241 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 93: /* const_list: const_list ',' const_variable  */
#line 1479 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_list -> const_list , const_variable.
        if((yyvsp[-2].const_list_node_info).type_ptr != (yyvsp[0].value_node_info).type_ptr) {
           string tn1 = type_name((yyvsp[-2].const_list_node_info).type_ptr);
           string tn2 = type_name((yyvsp[0].value_node_info).type_ptr);
           semantic_error(real_ast,"constlist type conflict between '"+tn1+"' and '"+tn2+"'",line_count,0);
        }
        (yyval.const_list_node_info).type_ptr = (yyvsp[-2].const_list_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.const_list_node_info).const_list_node = new ConstListNode();
        (yyval.const_list_node_info).const_list_node->append_child((yyvsp[-2].const_list_node_info).const_list_node);
        (yyval.const_list_node_info).const_list_node->append_child((yyvsp[0].value_node_info).const_variable_node);
    }
#line 3260 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 94: /* const_list: const_variable  */
#line 1494 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // const_list -> const_variable.
        (yyval.const_list_node_info).type_ptr = (yyvsp[0].value_node_info).type_ptr;
        if(error_flag)
            break;
        (yyval.const_list_node_info).const_list_node = new ConstListNode();
        (yyval.const_list_node_info).const_list_node->append_child((yyvsp[0].value_node_info).const_variable_node);
    }
#line 3273 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 95: /* updown: TO  */
#line 1504 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // updown -> TO.
        if(error_flag)
            break;
        (yyval.updown_node) = new UpdownNode(true);
    }
#line 3284 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 96: /* updown: DOWNTO  */
#line 1511 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // updown -> DOWNTO.
        if(error_flag)
            break;
        (yyval.updown_node) = new UpdownNode(false);
    }
#line 3295 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 97: /* call_procedure_statement: ID '(' expression_list ')'  */
#line 1519 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // call_procedure_statement -> id (expression_list).
        FunctionSymbol *tmp = table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-3].token_info).value.get<string>());
        if(tmp == nullptr) {
            string tn = (yyvsp[-3].token_info).value.get<string>();
            semantic_error(real_ast,"undefined procedure '"+tn+"'",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
            break;
        }
        if(!tmp || !tmp->AssertParams(*((yyvsp[-1].expression_list_node_info).type_ptr_list),*((yyvsp[-1].expression_list_node_info).is_lvalue_list))){
            string tn = (yyvsp[-3].token_info).value.get<string>();
            string param = tmp->ParamName();
            string input = type_name(*((yyvsp[-1].expression_list_node_info).type_ptr_list));
            semantic_error(real_ast,"invalid arguments '("+input+")' to procedure '"+tn+"' (expected '("+param+")')",line_count,0);
        }
        if(error_flag)
            break;
        (yyval.procedure_call_node) = new ProcedureCallNode(ProcedureCallNode::GrammarType::ID_EXP_LIST);
        LeafNode *id_node = new LeafNode((yyvsp[-3].token_info).value);
        (yyval.procedure_call_node)->append_child(id_node);
        (yyval.procedure_call_node)->append_child((yyvsp[-1].expression_list_node_info).expression_list_node);
        auto ref_vec = tmp->ParamRefVec();
        auto ref_stack = new std::stack<bool>();
        for (auto i : ref_vec){
            ref_stack->push(i);
        }
        (yyvsp[-1].expression_list_node_info).expression_list_node->DynamicCast<ExpressionListNode>()->set_ref(ref_stack);
        delete ref_stack;
        real_ast->libs()->Call(tmp->name());
        delete (yyvsp[-1].expression_list_node_info).is_lvalue_list;
        delete (yyvsp[-1].expression_list_node_info).type_ptr_list;
    }
#line 3331 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 98: /* call_procedure_statement: ID  */
#line 1551 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // call_procedure_statement -> id.
        FunctionSymbol *tmp = table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[0].token_info).value.get<string>());
        if(tmp == nullptr) {
            string tn = (yyvsp[0].token_info).value.get<string>();
            semantic_error(real_ast,"undefined procedure '"+tn+"'",(yyvsp[0].token_info).line_num,(yyvsp[0].token_info).column_num);
            break;
        } else {
            //函数调用 类型检查
            if(!dynamic_cast<FunctionSymbol*>(tmp)->AssertParams()){
                string tn = (yyvsp[0].token_info).value.get<string>();
                string param = dynamic_cast<FunctionSymbol*>(tmp)->ParamName();
	        semantic_error(real_ast,"too few arguments to procedure '"+tn+"' (expected '("+param+")')",line_count,0);
            }
        }
        if(error_flag)
            break;
        (yyval.procedure_call_node) = new ProcedureCallNode(ProcedureCallNode::GrammarType::ID);
        LeafNode *id_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.procedure_call_node)->append_child(id_node);
        real_ast->libs()->Call(tmp->name());
    }
#line 3358 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 99: /* call_procedure_statement: ID '(' ')'  */
#line 1574 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // call_procedure_statement -> id().
        FunctionSymbol *tmp = table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-2].token_info).value.get<string>());
        if(tmp == nullptr) {
            string tn = (yyvsp[-2].token_info).value.get<string>();
            semantic_error(real_ast,"undefined procedure '"+tn+"'",(yyvsp[-2].token_info).line_num,(yyvsp[-2].token_info).column_num);
            break;
        } else {
            //函数调用 类型检查
            if(!dynamic_cast<FunctionSymbol*>(tmp)->AssertParams()){
                string tn = (yyvsp[-2].token_info).value.get<string>();
                string param = dynamic_cast<FunctionSymbol*>(tmp)->ParamName();
	        semantic_error(real_ast,"too many arguments to procedure '"+tn+"' (expected '("+param+")')",(yyvsp[-2].token_info).line_num,0);
            }
        }
        if(error_flag)
            break;
        (yyval.procedure_call_node) = new ProcedureCallNode(ProcedureCallNode::GrammarType::ID);
        LeafNode *id_node = new LeafNode((yyvsp[-2].token_info).value);
        (yyval.procedure_call_node)->append_child(id_node);
        real_ast->libs()->Call(tmp->name());
    }
#line 3385 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 100: /* expression_list: expression_list ',' expression  */
#line 1598 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression_list -> expression_list ',' expression
        (yyval.expression_list_node_info).type_ptr_list = (yyvsp[-2].expression_list_node_info).type_ptr_list;
        (yyval.expression_list_node_info).type_ptr_list->push_back((yyvsp[0].expression_node_info).type_ptr);
        (yyval.expression_list_node_info).is_lvalue_list = (yyvsp[-2].expression_list_node_info).is_lvalue_list;
        (yyval.expression_list_node_info).is_lvalue_list->push_back((yyvsp[0].expression_node_info).is_lvalue);
        if(error_flag)
            break;
        (yyval.expression_list_node_info).expression_list_node = new ExpressionListNode((ExpressionListNode::GrammarType)1);
        (yyval.expression_list_node_info).expression_list_node->append_child((yyvsp[-2].expression_list_node_info).expression_list_node);
        (yyval.expression_list_node_info).expression_list_node->append_child((yyvsp[0].expression_node_info).expression_node);
    }
#line 3402 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 101: /* expression_list: expression  */
#line 1611 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression_list -> expression
        (yyval.expression_list_node_info).type_ptr_list = new std::vector<TypeTemplate*>();
        (yyval.expression_list_node_info).type_ptr_list->push_back((yyvsp[0].expression_node_info).type_ptr);
        (yyval.expression_list_node_info).is_lvalue_list = new std::vector<bool>();
        (yyval.expression_list_node_info).is_lvalue_list->push_back((yyvsp[0].expression_node_info).is_lvalue);
        if(error_flag)
            break;
        (yyval.expression_list_node_info).expression_list_node = new ExpressionListNode((ExpressionListNode::GrammarType)0);
        (yyval.expression_list_node_info).expression_list_node->append_child((yyvsp[0].expression_node_info).expression_node);
    }
#line 3418 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 102: /* expression: simple_expression RELOP simple_expression  */
#line 1624 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression -> simple_expression RELOP simple_expression.
        if(error_flag)
            break;
        // 类型检查
        //从这里开始进行运算检查
        if((!is_basic((yyvsp[-2].simple_expression_node_info).type_ptr))||(!is_basic((yyvsp[0].simple_expression_node_info).type_ptr))){
            string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].simple_expression_node_info).type_ptr);
            string tn3 = (yyvsp[-1].token_info).value.get<string>();
            semantic_error(real_ast,"invalid operands to binary "+tn3+" (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[-2].simple_expression_node_info).type_ptr, (BasicType*)(yyvsp[0].simple_expression_node_info).type_ptr, (yyvsp[-1].token_info).value.get<string>());
        if(result==TYPE_ERROR){
            string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
	    string tn2 = type_name((yyvsp[0].simple_expression_node_info).type_ptr);
	    string tn3 = (yyvsp[-1].token_info).value.get<string>();
	    semantic_error(real_ast,"invalid operands to binary "+tn3+" (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.expression_node_info).is_lvalue = false;
        (yyval.expression_node_info).type_ptr = result;
        
        std::string relop = (yyvsp[-1].token_info).value.get<string>();
        if((yyvsp[-1].token_info).value.get<string>() == "<>") {
            relop = "!=";
        }
        (yyval.expression_node_info).expression_node = new ExpressionNode();
        (yyval.expression_node_info).expression_node->append_child((yyvsp[-2].simple_expression_node_info).simple_expression_node);
        LeafNode *relop_node = new LeafNode(ConstValue(relop));
        (yyval.expression_node_info).expression_node->append_child(relop_node);
        (yyval.expression_node_info).expression_node->append_child((yyvsp[0].simple_expression_node_info).simple_expression_node);
    }
#line 3455 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 103: /* expression: simple_expression '=' simple_expression  */
#line 1657 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression -> simple_expression '=' simple_expression.
        // 类型检查
        if((!is_basic((yyvsp[-2].simple_expression_node_info).type_ptr))||(!is_basic((yyvsp[0].simple_expression_node_info).type_ptr))){
           string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
           string tn2 = type_name((yyvsp[0].simple_expression_node_info).type_ptr);
           semantic_error(real_ast,"invalid operands to binary = (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[-2].simple_expression_node_info).type_ptr, (BasicType*)(yyvsp[0].simple_expression_node_info).type_ptr, "=");
        
        if(result==TYPE_ERROR){
           string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
           string tn2 = type_name((yyvsp[0].simple_expression_node_info).type_ptr);
           semantic_error(real_ast,"invalid operands to binary = (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.expression_node_info).is_lvalue = false;
        (yyval.expression_node_info).type_ptr = result;

        if(error_flag)
            break;
        (yyval.expression_node_info).expression_node = new ExpressionNode();
        (yyval.expression_node_info).expression_node->append_child((yyvsp[-2].simple_expression_node_info).simple_expression_node);
        LeafNode *relop_node = new LeafNode(ConstValue("=="));
        (yyval.expression_node_info).expression_node->append_child(relop_node);
        (yyval.expression_node_info).expression_node->append_child((yyvsp[0].simple_expression_node_info).simple_expression_node);
    }
#line 3486 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 104: /* expression: simple_expression  */
#line 1684 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression -> simple_expression.
        (yyval.expression_node_info).type_ptr = (yyvsp[0].simple_expression_node_info).type_ptr;
        (yyval.expression_node_info).is_lvalue = (yyvsp[0].simple_expression_node_info).is_lvalue;
        if(error_flag)
            break;
        if((yyval.expression_node_info).type_ptr && (yyval.expression_node_info).type_ptr->template_type() == TypeTemplate::TYPE::ARRAY) {
            (yyval.expression_node_info).expression_node = new ExpressionNode(ExpressionNode::TargetType::VAR_ARRAY);
        } else {
            (yyval.expression_node_info).expression_node = new ExpressionNode();
        }
        
        (yyval.expression_node_info).expression_node->append_child((yyvsp[0].simple_expression_node_info).simple_expression_node);
    }
#line 3505 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 105: /* expression: str_expression  */
#line 1698 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // expression -> str_expression.
        (yyval.expression_node_info).type_ptr = (yyvsp[0].str_expression_node_info).type_ptr;
        (yyval.expression_node_info).length = (yyvsp[0].str_expression_node_info).length;
        (yyval.expression_node_info).is_lvalue = false;
        if(error_flag)
            break;
        (yyval.expression_node_info).expression_node = new ExpressionNode(ExpressionNode::TargetType::CONST_STRING);
        (yyval.expression_node_info).expression_node->append_child((yyvsp[0].str_expression_node_info).str_expression_node);
    }
#line 3520 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 106: /* str_expression: STRING_  */
#line 1710 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
            {
        // str_expression -> string.
        if(error_flag)
            break;
        (yyval.str_expression_node_info).type_ptr = TYPE_STRINGLIKE;
        (yyval.str_expression_node_info).length = (yyvsp[0].token_info).value.get<string>().length();
        (yyval.str_expression_node_info).is_lvalue = false;
        if(error_flag)
            break;
        (yyval.str_expression_node_info).str_expression_node = new StrExpressionNode();
        LeafNode *string_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.str_expression_node_info).str_expression_node->append_child(string_node);
    }
#line 3538 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 107: /* str_expression: str_expression PLUS STRING_  */
#line 1722 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                    {
        // str_expression -> str_expression + string.
        (yyval.str_expression_node_info).type_ptr = TYPE_STRINGLIKE;
        (yyval.str_expression_node_info).length = (yyvsp[-2].str_expression_node_info).length + (yyvsp[0].token_info).value.get<string>().length();
        (yyval.str_expression_node_info).is_lvalue = false;
        if(error_flag)
	    break;
        (yyval.str_expression_node_info).str_expression_node = new StrExpressionNode();
        (yyval.str_expression_node_info).str_expression_node->append_child((yyvsp[-2].str_expression_node_info).str_expression_node);
        LeafNode *string_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.str_expression_node_info).str_expression_node->append_child(string_node);
    }
#line 3555 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 108: /* str_expression: str_expression PLUS CHAR  */
#line 1733 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
                                  {
        // str_expression -> str_expression + char.
        (yyval.str_expression_node_info).type_ptr = TYPE_STRINGLIKE;
        (yyval.str_expression_node_info).length = (yyvsp[-2].str_expression_node_info).length + 1;
        char c = (yyvsp[0].token_info).value.get<char>();
        (yyvsp[0].token_info).value.set(std::string(1, c));
        (yyval.str_expression_node_info).is_lvalue = false;
        if(error_flag)
            break;
        (yyval.str_expression_node_info).str_expression_node = new StrExpressionNode();
        (yyval.str_expression_node_info).str_expression_node->append_child((yyvsp[-2].str_expression_node_info).str_expression_node);
        LeafNode *string_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.str_expression_node_info).str_expression_node->append_child(string_node);
    }
#line 3574 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 109: /* simple_expression: term  */
#line 1749 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // simple_expression -> term.
        (yyval.simple_expression_node_info).type_ptr = (yyvsp[0].term_node_info).type_ptr;
        (yyval.simple_expression_node_info).is_lvalue = (yyvsp[0].term_node_info).is_lvalue;
        if(error_flag)
            break;
        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3588 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 110: /* simple_expression: PLUS term  */
#line 1759 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // simple_expression -> + term.
        //类型检查
        if(!is_basic((yyvsp[0].term_node_info).type_ptr)){
            semantic_error(real_ast,"wrong type argument to unary plus",line_count,0);
        }

        auto result=compute((BasicType*)(yyvsp[0].term_node_info).type_ptr, "+");
        
        if(result==TYPE_ERROR){
            semantic_error(real_ast,"wrong type argument to unary plus",line_count,0);
        }
        (yyval.simple_expression_node_info).is_lvalue = false;
        (yyval.simple_expression_node_info).type_ptr = result;

        if(error_flag)
            break;
        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        LeafNode *plus_node = new LeafNode(ConstValue("+"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(plus_node);
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3615 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 111: /* simple_expression: UMINUS term  */
#line 1782 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // simple_expression -> - term.
        //类型检查
        if(!is_basic((yyvsp[0].term_node_info).type_ptr)){
            semantic_error(real_ast,"wrong type argument to unary minus",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[0].term_node_info).type_ptr, "-");
        
        if(result==TYPE_ERROR){
            semantic_error(real_ast,"wrong type argument to unary minus",line_count,0);
        }
        (yyval.simple_expression_node_info).is_lvalue = false;
        (yyval.simple_expression_node_info).type_ptr = result;
        if(error_flag)
            break;
        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        LeafNode *minus_node = new LeafNode(ConstValue("-"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(minus_node);
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3640 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 112: /* simple_expression: simple_expression ADDOP term  */
#line 1803 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // simple_expression -> simple_expression or term.、
        //类型检查
        if((yyvsp[-2].simple_expression_node_info).type_ptr!=(yyvsp[0].term_node_info).type_ptr){
            string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].term_node_info).type_ptr);
            semantic_error(real_ast,"invalid operands to binary or (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.simple_expression_node_info).is_lvalue = false;
        (yyval.simple_expression_node_info).type_ptr = (yyvsp[-2].simple_expression_node_info).type_ptr;

        if(error_flag)
            break;
        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[-2].simple_expression_node_info).simple_expression_node);
        LeafNode *addop_node = new LeafNode(ConstValue("||"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(addop_node);
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3664 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 113: /* simple_expression: simple_expression PLUS term  */
#line 1823 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    { 
        // 类型检查
        // simple_expression -> simple_expression + term.
        (yyval.simple_expression_node_info).is_lvalue = false;
        if(error_flag)
            break;
        if((!is_basic((yyvsp[-2].simple_expression_node_info).type_ptr))||(!is_basic((yyvsp[0].term_node_info).type_ptr))){
           string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
           string tn2 = type_name((yyvsp[0].term_node_info).type_ptr);
           semantic_error(real_ast,"invalid operands to binary + (have '"+tn1+"' and '"+tn2+"')",line_count,0);
           (yyval.simple_expression_node_info).type_ptr = (yyvsp[-2].simple_expression_node_info).type_ptr;
        }
        else{
            auto result=compute((BasicType*)(yyvsp[-2].simple_expression_node_info).type_ptr, (BasicType*)(yyvsp[0].term_node_info).type_ptr,"+");
            if(result==TYPE_ERROR){
                 string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
                 string tn2 = type_name((yyvsp[0].term_node_info).type_ptr);
                 semantic_error(real_ast,"invalid operands to binary + (have '"+tn1+"' and '"+tn2+"')",line_count,0);
            }
            (yyval.simple_expression_node_info).type_ptr = result;
        }
        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[-2].simple_expression_node_info).simple_expression_node);
        LeafNode *plus_node = new LeafNode(ConstValue("+"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(plus_node);
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3696 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 114: /* simple_expression: simple_expression UMINUS term  */
#line 1851 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        (yyval.simple_expression_node_info).is_lvalue = false;
        if(error_flag)
            break;
        // 类型检查
        // simple_expression -> simple_expression - term.
        if((!is_basic((yyvsp[-2].simple_expression_node_info).type_ptr))||(!is_basic((yyvsp[0].term_node_info).type_ptr))){
            string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].term_node_info).type_ptr);
            semantic_error(real_ast,"invalid operands to binary - (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[-2].simple_expression_node_info).type_ptr, (BasicType*)(yyvsp[0].term_node_info).type_ptr,"-");
        if(result==TYPE_ERROR){
            string tn1 = type_name((yyvsp[-2].simple_expression_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].term_node_info).type_ptr);
            semantic_error(real_ast,"invalid operands to binary - (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.simple_expression_node_info).type_ptr = result;

        (yyval.simple_expression_node_info).simple_expression_node = new SimpleExpressionNode();
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[-2].simple_expression_node_info).simple_expression_node);
        LeafNode *minus_node = new LeafNode(ConstValue("-"));
        (yyval.simple_expression_node_info).simple_expression_node->append_child(minus_node);
        (yyval.simple_expression_node_info).simple_expression_node->append_child((yyvsp[0].term_node_info).term_node);
    }
#line 3726 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 115: /* term: factor  */
#line 1878 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // term -> factor.
        (yyval.term_node_info).type_ptr = (yyvsp[0].factor_node_info).type_ptr;
        (yyval.term_node_info).is_lvalue = (yyvsp[0].factor_node_info).is_lvalue;
        if(error_flag)
            break;
        (yyval.term_node_info).term_node = new TermNode();
        (yyval.term_node_info).term_node->append_child((yyvsp[0].factor_node_info).factor_node);
    }
#line 3740 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 116: /* term: term MULOP factor  */
#line 1888 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {  
        // term -> term mulop factor.
        // 类型检查
        if((!is_basic((yyvsp[-2].term_node_info).type_ptr))||(!is_basic((yyvsp[0].factor_node_info).type_ptr))){
            string tn1 = type_name((yyvsp[-2].term_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].factor_node_info).type_ptr);
            string tn3 = (yyvsp[-1].token_info).value.get<string>();
            semantic_error(real_ast,"invalid operands to binary "+tn3+" (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[-2].term_node_info).type_ptr, (BasicType*)(yyvsp[0].factor_node_info).type_ptr,(yyvsp[-1].token_info).value.get<string>());
        if(result==TYPE_ERROR){
            string tn1 = type_name((yyvsp[-2].term_node_info).type_ptr);
            string tn2 = type_name((yyvsp[0].factor_node_info).type_ptr);
            string tn3 = (yyvsp[-1].token_info).value.get<string>();
            semantic_error(real_ast,"invalid operands to binary "+tn3+" (have '"+tn1+"' and '"+tn2+"')",line_count,0);
        }
        (yyval.term_node_info).is_lvalue = false;
        (yyval.term_node_info).type_ptr = result;
        
        std::string mulop = (yyvsp[-1].token_info).value.get<string>();
        if(mulop == "/" && !error_flag){
            (yyvsp[-2].term_node_info).term_node->set_op_div(true);
        } else if(mulop == "div"){
            mulop = "/";
        } else if (mulop == "mod"){
            mulop = "%";
        } else if (mulop == "and"){
            mulop = "&&";
        }
        if(error_flag)
            break;
        (yyval.term_node_info).term_node = new TermNode();
        (yyval.term_node_info).term_node->append_child((yyvsp[-2].term_node_info).term_node);
        LeafNode *mulop_node = new LeafNode(ConstValue(mulop));
        (yyval.term_node_info).term_node->append_child(mulop_node);
        (yyval.term_node_info).term_node->append_child((yyvsp[0].factor_node_info).factor_node);
    }
#line 3782 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 117: /* factor: unsigned_const_variable  */
#line 1927 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // factor -> unsigned_const_variable.
        (yyval.factor_node_info).type_ptr = (yyvsp[0].unsigned_constant_var_node_info).type_ptr;
        (yyval.factor_node_info).is_lvalue = false;
        if(error_flag)
            break;
        (yyval.factor_node_info).factor_node = new FactorNode(FactorNode::GrammarType::UCONST_VAR);
        (yyval.factor_node_info).factor_node->append_child((yyvsp[0].unsigned_constant_var_node_info).unsigned_constant_var_node);
    }
#line 3796 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 118: /* factor: variable  */
#line 1937 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // factor -> variable.
        (yyval.factor_node_info).type_ptr = (yyvsp[0].variable_node_info).type_ptr;
        (yyval.factor_node_info).is_lvalue = (yyvsp[0].variable_node_info).is_lvalue;
        if(error_flag)
            break;
        (yyval.factor_node_info).factor_node = new FactorNode(FactorNode::GrammarType::VARIABLE);
        (yyval.factor_node_info).factor_node->append_child((yyvsp[0].variable_node_info).variable_node);
        if((yyvsp[0].variable_node_info).name) delete (yyvsp[0].variable_node_info).name;
    }
#line 3811 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 119: /* factor: ID '(' expression_list ')'  */
#line 1948 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        if(error_flag)
            break;
        (yyval.factor_node_info).is_lvalue = false;
        FunctionSymbol *tmp = table_set_queue.top()->SearchEntry<FunctionSymbol>((yyvsp[-3].token_info).value.get<string>());
        if(tmp == nullptr) {
            semantic_error(real_ast,"undefined function '" + (yyvsp[-3].token_info).value.get<string>() + "'",(yyvsp[-3].token_info).line_num,(yyvsp[-3].token_info).column_num);
            break;
        }else if(!tmp->AssertParams(*((yyvsp[-1].expression_list_node_info).type_ptr_list),*((yyvsp[-1].expression_list_node_info).is_lvalue_list))){
            string tn = (yyvsp[-3].token_info).value.get<string>();
            string param = tmp->ParamName();
            string input = type_name(*((yyvsp[-1].expression_list_node_info).type_ptr_list));
            semantic_error(real_ast,"invalid arguments '("+input+")' to function '"+tn+"' (expected '("+param+")')",line_count,0);
            break;
        }
        //if(error_flag)
        //   break;
        (yyval.factor_node_info).type_ptr = tmp->type();
        (yyval.factor_node_info).factor_node = new FactorNode(FactorNode::GrammarType::ID_EXP_LIST);
        LeafNode *id_node = new LeafNode((yyvsp[-3].token_info).value);
        (yyval.factor_node_info).factor_node->append_child(id_node);
        (yyval.factor_node_info).factor_node->append_child((yyvsp[-1].expression_list_node_info).expression_list_node);
        auto ref_vec = tmp->ParamRefVec();
        auto ref_stack = new std::stack<bool>();
        for (auto i : ref_vec){
            ref_stack->push(i);
        }
        (yyvsp[-1].expression_list_node_info).expression_list_node->DynamicCast<ExpressionListNode>()->set_ref(ref_stack);
        delete ref_stack;
        real_ast->libs()->Call(tmp->name());
        delete (yyvsp[-1].expression_list_node_info).type_ptr_list;
        delete (yyvsp[-1].expression_list_node_info).is_lvalue_list;

    }
#line 3850 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 120: /* factor: '(' expression ')'  */
#line 1983 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // factor -> (expression).
        (yyval.factor_node_info).type_ptr = (yyvsp[-1].expression_node_info).type_ptr;
        (yyval.factor_node_info).is_lvalue = false;
        if(error_flag)
            break;
        (yyval.factor_node_info).factor_node = new FactorNode(FactorNode::GrammarType::EXP);
        (yyval.factor_node_info).factor_node->append_child((yyvsp[-1].expression_node_info).expression_node);
    }
#line 3864 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 121: /* factor: NOT factor  */
#line 1993 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        if(!is_basic((yyvsp[0].factor_node_info).type_ptr)){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
        }
        auto result=compute((BasicType*)(yyvsp[0].factor_node_info).type_ptr, "not");
        
        if(result==TYPE_ERROR){
            semantic_error(real_ast,"wrong type argument to unary not",line_count,0);
        }
        (yyval.factor_node_info).is_lvalue = false;
        (yyval.factor_node_info).type_ptr = result;

        if(error_flag)
            break;
        (yyval.factor_node_info).factor_node = new FactorNode(FactorNode::GrammarType::NOT);
        (yyval.factor_node_info).factor_node->append_child((yyvsp[0].factor_node_info).factor_node);
    }
#line 3888 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 122: /* unsigned_const_variable: num  */
#line 2014 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // unsigned_const_variable -> num
        (yyval.unsigned_constant_var_node_info).type_ptr = (yyvsp[0].value_node_info).type_ptr;
        if(error_flag)
            break;
        LeafNode *num_node = new LeafNode((yyvsp[0].value_node_info).value);
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node = new UnsignConstVarNode();
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node->append_child(num_node);
    }
#line 3902 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 123: /* unsigned_const_variable: CHAR  */
#line 2024 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // unsigned_const_variable -> 'LETTER'
        (yyval.unsigned_constant_var_node_info).type_ptr = TYPE_CHAR;
        if(error_flag)
            break;
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node = new UnsignConstVarNode();
        LeafNode *char_node = new LeafNode((yyvsp[0].token_info).value);
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node->append_child(char_node);
    }
#line 3916 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 124: /* unsigned_const_variable: TRUE  */
#line 2034 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        // unsigned_const_variable -> true
        (yyval.unsigned_constant_var_node_info).type_ptr = TYPE_BOOL;
        if(error_flag)
            break;
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node = new UnsignConstVarNode();
        LeafNode *true_node = new LeafNode(ConstValue(true));
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node->append_child(true_node);
    }
#line 3930 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 125: /* unsigned_const_variable: FALSE  */
#line 2044 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {   
        // unsigned_const_variable -> false
        (yyval.unsigned_constant_var_node_info).type_ptr = TYPE_BOOL;
        if(error_flag)
            break;
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node = new UnsignConstVarNode();
        LeafNode *false_node = new LeafNode(ConstValue(false));
        (yyval.unsigned_constant_var_node_info).unsigned_constant_var_node->append_child(false_node);
    }
#line 3944 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 126: /* program: error  */
#line 2059 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        yyerror(real_ast,"unrecoverable errors occurred");
        while (new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        while (yychar!= YYEOF){
            yychar = yylex();
        }        
    }
#line 3964 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 127: /* program_head: PROGRAM error  */
#line 2079 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 3982 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 128: /* program: program_head program_body error  */
#line 2094 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        table_set_queue.push(top_table_set);
        real_ast->libs()->Preset(table_set_queue.top()->symbols());
        ProgramNode* node = new ProgramNode();
	node->append_child((yyvsp[-2].program_head_node));
	node->append_child((yyvsp[-1].program_body_node));
	real_ast->set_root(node);
	delete top_table_set;

        int length=cur_line_info.size();
        if(length==0){
            length = last_line_info.size();
            char msg[]="expected '.' at the end of the program";
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }else{        
            yyerror(real_ast,"expected '.' at the end of the program");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4012 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 129: /* const_declarations: CONST error  */
#line 2123 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        if(yychar==TYPE || yychar==BEGIN_ || yychar==VAR || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar=='=')
                yyerror(real_ast,"expected identifier before '='");
            else
                yyerror(real_ast,"unrecoverable errors occurred in const_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }    
        while (yychar!=TYPE && yychar!= VAR && yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
            yychar = yylex();
        }
    }
#line 4056 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 130: /* type_declarations: TYPE error  */
#line 2164 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        if(yychar==BEGIN_ || yychar==VAR || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{     
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar=='=')
                yyerror(real_ast,"expected identifier before '='");
            else
                yyerror(real_ast,"unrecoverable errors occurred in type_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }
        while (yychar!= VAR && yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
            yychar = yylex();
        }
    }
#line 4100 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 131: /* var_declarations: VAR error  */
#line 2205 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        if( yychar==BEGIN_ || yychar==FUNCTION || yychar== PROCEDURE){
            char msg[] = "expcted ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            break;
        }
        else if(yychar==ID){      
            char msg[] = "expected ';'";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            location_pointer_refresh();
            new_line_flag=false;
            if(yychar==':')
                yyerror(real_ast,"expected identifier before ':'");
            else
                yyerror(real_ast,"unrecoverable errors occurred in var_declarations");
            while (new_line_flag==false && yychar!= YYEOF){
                yychar = yylex();
            }
            if(new_line_flag){
                fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
                fprintf(stderr,"\t| %s",location_pointer);
            }
        }
        while (yychar!= YYEOF && yychar != FUNCTION && yychar!=PROCEDURE && yychar!=BEGIN_){
           yychar = yylex();
        }
        
    }
#line 4145 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 132: /* const_declaration: ID const_variable  */
#line 2247 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before const value");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4156 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 133: /* const_declaration: const_declaration ';' ID const_variable  */
#line 2255 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before const value");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4167 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 134: /* const_declaration: ID '=' error  */
#line 2263 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected const value before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4191 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 135: /* $@1: %empty  */
#line 2284 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
#line 4200 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 136: /* const_declaration: ID ASSIGNOP $@1 const_variable  */
#line 2289 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4209 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 137: /* $@2: %empty  */
#line 2295 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
#line 4218 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 138: /* const_declaration: const_declaration ';' ID ASSIGNOP $@2 const_variable  */
#line 2300 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4227 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 139: /* $@3: %empty  */
#line 2306 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
#line 4236 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 140: /* const_declaration: ID ':' $@3 const_variable  */
#line 2311 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4245 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 141: /* $@4: %empty  */
#line 2317 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
#line 4254 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 142: /* const_declaration: const_declaration ';' ID ':' $@4 const_variable  */
#line 2322 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4263 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 143: /* const_declaration: const_declaration ';' ID '=' error  */
#line 2328 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected const value before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4284 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 144: /* const_declaration: const_declaration ';' error  */
#line 2346 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar=='=')
            yyerror(real_ast,"expected identifier before '='");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4305 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 145: /* type_declaration: ID type  */
#line 2364 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4316 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 146: /* type_declaration: type_declaration ';' ID type  */
#line 2372 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected '=' before type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4327 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 147: /* type_declaration: ID '=' error  */
#line 2380 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4351 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 148: /* $@5: %empty  */
#line 2401 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
#line 4360 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 149: /* type_declaration: ID ASSIGNOP $@5 type  */
#line 2406 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4369 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 150: /* $@6: %empty  */
#line 2412 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':=')");
        location_pointer_refresh();
    }
#line 4378 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 151: /* type_declaration: type_declaration ';' ID ASSIGNOP $@6 type  */
#line 2417 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4387 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 152: /* $@7: %empty  */
#line 2423 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
#line 4396 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 153: /* type_declaration: ID ':' $@7 type  */
#line 2428 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4405 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 154: /* $@8: %empty  */
#line 2434 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected '=' (have ':')");
        location_pointer_refresh();
    }
#line 4414 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 155: /* type_declaration: type_declaration ';' ID ':' $@8 type  */
#line 2439 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4423 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 156: /* type_declaration: type_declaration ';' ID '=' error  */
#line 2445 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4444 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 157: /* type_declaration: type_declaration ';' error  */
#line 2463 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar=='=')
            yyerror(real_ast,"expected identifier before '='");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4465 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 158: /* var_declaration: id_list ID_or_type  */
#line 2481 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected ':' before identifier or type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4476 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 159: /* var_declaration: var_declaration ';' id_list ID_or_type  */
#line 2489 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        yyerror(real_ast,"expected ':' before identifier or type");
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4487 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 160: /* var_declaration: id_list ':' error  */
#line 2497 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4511 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 161: /* var_declaration: var_declaration ';' id_list ':' error  */
#line 2518 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected type identifier before ';'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4532 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 162: /* var_declaration: var_declaration ';' error  */
#line 2536 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==':')
            yyerror(real_ast,"expected identifier before ':'");
        else
            yyerror(real_ast,"Syntax error");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';')
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        else
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4553 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 163: /* $@9: %empty  */
#line 2554 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected ':' (have ':=')");
        location_pointer_refresh();
    }
#line 4562 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 164: /* var_declaration: id_list ASSIGNOP $@9 ID_or_type  */
#line 2559 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4571 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 165: /* $@10: %empty  */
#line 2565 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected ':' (have ':=')");
        location_pointer_refresh();
    }
#line 4580 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 166: /* var_declaration: var_declaration ';' id_list ASSIGNOP $@10 ID_or_type  */
#line 2570 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4589 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 167: /* $@11: %empty  */
#line 2576 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected ':' (have '=')");
        location_pointer_refresh();
    }
#line 4598 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 168: /* var_declaration: ID '=' $@11 ID_or_type  */
#line 2581 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4607 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 169: /* $@12: %empty  */
#line 2587 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected ':' (have '=')");
        location_pointer_refresh();
    }
#line 4616 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 170: /* var_declaration: var_declaration ';' ID '=' $@12 ID_or_type  */
#line 2592 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4625 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 173: /* type: ARRAY '[' periods ']' error  */
#line 2603 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"expected 'of' before type.");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4639 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 174: /* type: ARRAY error  */
#line 2614 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"Invaild periods.");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4653 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 175: /* type: ARRAY '[' periods ']' OF error  */
#line 2625 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        location_pointer_refresh();
        yyerror(real_ast,"unknown error!");
        while(yychar!=';' && !new_line_flag)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4667 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 176: /* id_varpart: '[' error  */
#line 2636 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';'){
            yyerror(real_ast,"expected ']' before ';'");
        }else if(yychar == ASSIGNOP){
            yyerror(real_ast,"expected ']' before ':='");
        }else
            yyerror(real_ast,"invalid expression");
        int left_num = 1;   // 括号匹配
        while (yychar!=';' && yychar!=ASSIGNOP && new_line_flag==false && yychar!= YYEOF ){
            if(yychar=='[') left_num++;
            if(yychar==']'&& left_num == 1) break; 
            yychar = yylex();
        }
        if(yychar==']'){
            yychar=yylex();
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==ASSIGNOP){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4705 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 177: /* type: ARRAY '[' periods ']' OF ID  */
#line 2671 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"unsupported definition of array using customized type");
        location_pointer_refresh();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4716 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 178: /* factor: '(' error  */
#line 2679 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected ')' before ';'");
        else
            yyerror(real_ast,"invalid expression");
        int left_num = 1;   // 括号匹配
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF ){
            if(yychar=='(') left_num++;
            if(yychar==')'&& left_num == 1) break; 
            yychar = yylex();
        }
        if(yychar==')'){
            yychar=yylex();
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4748 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 179: /* subprogram_head: FUNCTION ID formal_parameter ':' error  */
#line 2708 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        location_pointer_refresh();
        if(yychar==ARRAY||yychar==RECORD||yychar==ID)
        {
            yyerror(real_ast,"return type of function should be integer, real, boolean or char");
        }
        while(yychar!=';'&&!new_line_flag)
            yychar=yylex();
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            yychar=yylex();
        }
    }
#line 4768 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 180: /* statement: IF error  */
#line 2729 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        location_pointer_refresh();
        while(yychar!=THEN && !new_line_flag&&yychar!=';')
            yychar=yylex();
        if(yychar==THEN){
            yyerror(real_ast,"invalid expression");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
            yychar=yylex();
        }
        else if(yychar==';'){
            char msg[] = "'THEN' might be missing";
            int length = last_line_info.size();
            fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
            memset(location_pointer,' ',length);
            memcpy(location_pointer+length,"^\n\0",3);
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else{
            yyerror(real_ast,"Syntax error");
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        while(yychar!=';'&&yychar!=END)
            yychar=yylex();
    }
#line 4801 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 181: /* statement: REPEAT error  */
#line 2760 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        new_line_flag=false;
        if(yychar=='='||yychar==RELOP||yychar==END)
            yyerror(real_ast,"'UNTIL' might be missing");
        else
            yyerror(real_ast,"Syntax error");
        location_pointer_refresh();
        while(yychar!=';'&&!new_line_flag && yychar!=END)
            yychar=yylex();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4818 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 182: /* statement: WHILE error  */
#line 2778 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
{
    new_line_flag=false;
    location_pointer_refresh();
    char msg[] = "'do' might be missing";
    int length = last_line_info.size();
    if(yychar==ID)
        fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,msg);   
    else{
        fprintf(stderr,"%d,%d:\033[01;31m \terror\033[0m : %s\n", last_line_count,length,"Syntax error");   
    }
    while(yychar!=';'&&!new_line_flag && yychar!=END)
        yychar=yylex();
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
    fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
    fprintf(stderr,"\t| %s",location_pointer);
}
#line 4840 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 183: /* statement: WHILE expression DO error  */
#line 2797 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&&!new_line_flag && yychar!=END)
        yychar=yylex();
    fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
    fprintf(stderr,"\t| %s",location_pointer);
}
#line 4854 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 184: /* statement: FOR ID ASSIGNOP expression updown expression DO error  */
#line 2808 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
}
#line 4874 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 185: /* statement: FOR ID ASSIGNOP expression updown error  */
#line 2825 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
{
    new_line_flag=false;
    yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
}
#line 4894 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 186: /* statement: FOR ID ASSIGNOP error  */
#line 2842 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
{
    new_line_flag=false;
    if(yychar==INT_NUM)
        yyerror(real_ast,"'to' or 'downto' might be missing");
    else
        yyerror(real_ast,"Syntax error");
    location_pointer_refresh();
    while(yychar!=';'&& yychar!=END)
        yychar=yylex();
    if(new_line_flag){
        fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
    else if(yychar==';'){
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
}
#line 4917 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 187: /* statement: variable ASSIGNOP type  */
#line 2863 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"type identifier not allowed");
        location_pointer_refresh();
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4928 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 188: /* statement: variable ASSIGNOP error  */
#line 2871 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        location_pointer_refresh();
        new_line_flag=false;
        if(yychar==';')
            yyerror(real_ast,"expected expression before ';'");
        else
            yyerror(real_ast,"invalid expression");
        while (yychar!=';' && new_line_flag==false && yychar!= YYEOF){
            yychar = yylex();
        }
        if(yychar==';'){
            fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
        else if(new_line_flag){
            fprintf(stderr,"%d:\t| %s\n",last_line_count,last_line_info.c_str());
            fprintf(stderr,"\t| %s",location_pointer);
        }
    }
#line 4952 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 189: /* $@13: %empty  */
#line 2892 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        yyerror(real_ast,"expected ':=' (have ':' and '=')");
        location_pointer_refresh();
    }
#line 4961 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;

  case 190: /* statement: variable ':' $@13 '=' expression  */
#line 2896 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"
    {
        fprintf(stderr,"%d:\t| %s\n",line_count,cur_line_info.c_str());
        fprintf(stderr,"\t| %s",location_pointer);
    }
#line 4970 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"
    break;


#line 4974 "D:/Coding/CProject/PASCC/cmake-build-release/../src/parser.tab.cc"

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
      yyerror (real_ast, YY_("syntax error"));
    }

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
                      yytoken, &yylval, real_ast);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, real_ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (real_ast, YY_("memory exhausted"));
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
                  yytoken, &yylval, real_ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, real_ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2902 "D:/Coding/CProject/PASCC/cmake-build-release/../scripts/parser.y"

 

void yyerror(ast::AST* real_ast,const char *msg){
    if(yydebug || strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void yynote(std::string msg ,int line){
    fprintf(stderr,"%d:\033[01;32m \tnote\033[0m : previous definition of \"%s\" was here\n", line, msg.c_str());
}

void yyerror_var(AST* real_ast,int line){
    fprintf(stderr,"%d:\033[01;31m \terror\033[0m : %s\n", line, "redifinition of variable");
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void location_pointer_refresh(){
    int length = cur_line_info.size()-yyleng;
    if(length<0)
        length=0;
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
}
int yywrap(){
    return 1;
}
