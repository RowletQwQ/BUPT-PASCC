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
#line 1 "../../src/parser/yacc_pascal.y"

// 此处为相关头文件和函数，会添加在生成的代码中

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/log/log.hpp"
#include "ast/stmt.hpp"
#include "ast/stmt_test.hpp"
#include "yacc_pascal.hpp"
#include "lex_pascal.hpp"


RelExprStmt::RelExprType get_rel_expr_type(long long op) {
    if(op == 0){
        return RelExprStmt::RelExprType::Equal;
    } else if(op == 1){
        return RelExprStmt::RelExprType::NotEqual;
    } else if(op == 2){
        return RelExprStmt::RelExprType::Less;
    } else if(op == 3){
        return RelExprStmt::RelExprType::LessEqual;
    } else if(op == 4){
        return RelExprStmt::RelExprType::Greater;
    } else if(op == 5){
        return RelExprStmt::RelExprType::GreaterEqual;
    } else if(op == 6){
        return RelExprStmt::RelExprType::In;
    } else {
        return RelExprStmt::RelExprType::NULL_TYPE;
    }
}

AddExprStmt::AddExprType get_add_expr_type(long long op) {
    if(op == 0){
        return AddExprStmt::AddExprType::Plus;
    } else if(op == 1){
        return AddExprStmt::AddExprType::Minus;
    } else if(op == 2){
        return AddExprStmt::AddExprType::Or;
    } else {
        return AddExprStmt::AddExprType::NULL_TYPE;
    }
}

MulExprStmt::MulExprType get_mul_expr_type(long long op) {
    if(op == 0){
        return MulExprStmt::MulExprType::Mul;
    } else if(op == 1){
        return MulExprStmt::MulExprType::Div;
    } else if(op == 2){
        return MulExprStmt::MulExprType::Mod;
    } else if(op == 3){
        return MulExprStmt::MulExprType::And;
    } else if(op == 4){
        return MulExprStmt::MulExprType::AndThen;
    } else {
        return MulExprStmt::MulExprType::NULL_TYPE;
    }

}

std::unique_ptr<RelExprStmt> new_rel_expr_stmt(RelExprStmt::RelExprType type) {
    std::unique_ptr<RelExprStmt> rel_expr = std::make_unique<RelExprStmt>();
    rel_expr->type = type;
    if(type == RelExprStmt::RelExprType::NULL_TYPE){
        rel_expr->add_expr = nullptr;
    }
    return rel_expr;
}


std::unique_ptr<AddExprStmt> new_add_expr_stmt(AddExprStmt::AddExprType type) {
    std::unique_ptr<AddExprStmt> add_expr = std::make_unique<AddExprStmt>();
    add_expr->type = type;
    if(type == AddExprStmt::AddExprType::NULL_TYPE){
        add_expr->add_expr = nullptr;
    }
    return add_expr;
}


std::unique_ptr<MulExprStmt> new_mul_expr_stmt(MulExprStmt::MulExprType type) {
    std::unique_ptr<MulExprStmt> mul_expr = std::make_unique<MulExprStmt>();
    mul_expr->type = type;
    if(type == MulExprStmt::MulExprType::NULL_TYPE){
        mul_expr->mul_expr = nullptr;
    }
    return mul_expr;
}


std::unique_ptr<UnaryExprStmt> new_unary_expr_stmt(UnaryExprStmt::UnaryExprType type) {
    std::unique_ptr<UnaryExprStmt> unary_expr = std::make_unique<UnaryExprStmt>();
    unary_expr->type = type;
    return unary_expr;
}


std::unique_ptr<PrimaryExprStmt> new_primary_expr_stmt(PrimaryExprStmt::PrimaryExprType type) {
    std::unique_ptr<PrimaryExprStmt> primary_expr = std::make_unique<PrimaryExprStmt>();
    primary_expr->type = type;
    return primary_expr;
}

std::unique_ptr<ValueStmt> new_value_stmt(ValueStmt::ValueType type) {
    std::unique_ptr<ValueStmt> value = std::make_unique<ValueStmt>();
    value->type = type;
    return value;
}

NumberStmt * new_number_stmt(char char_val);
NumberStmt * new_number_stmt(double real_val);
NumberStmt * new_number_stmt(long long int_val);

void fill_number_stmt(std::unique_ptr<NumberStmt> & num_value, long long int_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->int_val = int_val;
}

void fill_number_stmt(std::unique_ptr<NumberStmt> & num_value, double real_val){
    num_value->is_signed = true;
    num_value->is_real = true;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->real_val = real_val;
}

void fill_number_stmt(std::unique_ptr<NumberStmt> & num_value, char char_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = true;
    num_value->is_unsigned = false;
    num_value->char_val = char_val;
}

void fill_number_stmt(NumberStmt* num_value, long long int_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->int_val = int_val;
}

void fill_number_stmt(NumberStmt* num_value, double real_val){
    num_value->is_signed = true;
    num_value->is_real = true;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->real_val = real_val;
}

void fill_number_stmt(NumberStmt* num_value, char char_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = true;
    num_value->is_unsigned = false;
    num_value->char_val = char_val;
}

std::unique_ptr<PrimaryExprStmt> bridge_primary_to_unary(std::unique_ptr<UnaryExprStmt> unary_expr){
    std::unique_ptr<PrimaryExprStmt> primary_expr = std::make_unique<PrimaryExprStmt>();
    primary_expr->type = PrimaryExprStmt::PrimaryExprType::Parentheses;
    primary_expr->expr = std::make_unique<ExprStmt>();
    primary_expr->expr->rel_expr = std::make_unique<RelExprStmt>();
    primary_expr->expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
    primary_expr->expr->rel_expr->add_expr = std::make_unique<AddExprStmt>();
    primary_expr->expr->rel_expr->add_expr->type = AddExprStmt::AddExprType::NULL_TYPE;
    primary_expr->expr->rel_expr->add_expr->mul_expr = std::make_unique<MulExprStmt>();
    primary_expr->expr->rel_expr->add_expr->mul_expr->type = MulExprStmt::MulExprType::NULL_TYPE;
    primary_expr->expr->rel_expr->add_expr->mul_expr->unary_expr = std::move(unary_expr);
    return primary_expr;
}


void syntax_error(const char *msg){
    printf("[SYNTAX ERROR] ");
    printf("%s\n", msg);
    exit(1);
}

// 相关所需的函数，可能包含一些错误处理函数
int yyerror(YYLTYPE *llocp, const char *code_str, ProgramStmt ** program, yyscan_t scanner, const char *msg)
{
    syntax_error(msg);
    return 0;
}

#line 265 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"

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

#include "yacc_pascal.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_PROGRAM = 4,                    /* PROGRAM  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_RECORD = 6,                     /* RECORD  */
  YYSYMBOL_ARRAY = 7,                      /* ARRAY  */
  YYSYMBOL_OF = 8,                         /* OF  */
  YYSYMBOL_VAR = 9,                        /* VAR  */
  YYSYMBOL_FUNCTION = 10,                  /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 11,                 /* PROCEDURE  */
  YYSYMBOL_BEGIN_TOKEN = 12,               /* BEGIN_TOKEN  */
  YYSYMBOL_END = 13,                       /* END  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_CASE = 17,                      /* CASE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_REPEAT = 19,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 20,                     /* UNTIL  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_TO = 22,                        /* TO  */
  YYSYMBOL_DOWNTO = 23,                    /* DOWNTO  */
  YYSYMBOL_DO = 24,                        /* DO  */
  YYSYMBOL_READ = 25,                      /* READ  */
  YYSYMBOL_READLN = 26,                    /* READLN  */
  YYSYMBOL_WRITE = 27,                     /* WRITE  */
  YYSYMBOL_WRITELN = 28,                   /* WRITELN  */
  YYSYMBOL_CHAR_KW = 29,                   /* CHAR_KW  */
  YYSYMBOL_INTEGER_KW = 30,                /* INTEGER_KW  */
  YYSYMBOL_REAL_KW = 31,                   /* REAL_KW  */
  YYSYMBOL_BOOLEAN_KW = 32,                /* BOOLEAN_KW  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_DIV = 34,                       /* DIV  */
  YYSYMBOL_MOD = 35,                       /* MOD  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_NE = 38,                        /* NE  */
  YYSYMBOL_LE = 39,                        /* LE  */
  YYSYMBOL_GE = 40,                        /* GE  */
  YYSYMBOL_ASSIGNOP = 41,                  /* ASSIGNOP  */
  YYSYMBOL_IN = 42,                        /* IN  */
  YYSYMBOL_ORELSE = 43,                    /* ORELSE  */
  YYSYMBOL_ANDTHEN = 44,                   /* ANDTHEN  */
  YYSYMBOL_DOUBLE_DOT = 45,                /* DOUBLE_DOT  */
  YYSYMBOL_IDENTIFIER = 46,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER = 47,                   /* INTEGER  */
  YYSYMBOL_BOOLEAN = 48,                   /* BOOLEAN  */
  YYSYMBOL_REAL = 49,                      /* REAL  */
  YYSYMBOL_CHAR = 50,                      /* CHAR  */
  YYSYMBOL_STRING = 51,                    /* STRING  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_53_ = 53,                       /* '.'  */
  YYSYMBOL_54_ = 54,                       /* '('  */
  YYSYMBOL_55_ = 55,                       /* ')'  */
  YYSYMBOL_56_ = 56,                       /* ','  */
  YYSYMBOL_57_ = 57,                       /* '='  */
  YYSYMBOL_58_ = 58,                       /* '+'  */
  YYSYMBOL_59_ = 59,                       /* '-'  */
  YYSYMBOL_60_ = 60,                       /* ':'  */
  YYSYMBOL_61_ = 61,                       /* '['  */
  YYSYMBOL_62_ = 62,                       /* ']'  */
  YYSYMBOL_63_ = 63,                       /* '<'  */
  YYSYMBOL_64_ = 64,                       /* '>'  */
  YYSYMBOL_65_ = 65,                       /* '*'  */
  YYSYMBOL_66_ = 66,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_programstruct = 68,             /* programstruct  */
  YYSYMBOL_program_head = 69,              /* program_head  */
  YYSYMBOL_program_body = 70,              /* program_body  */
  YYSYMBOL_idlist = 71,                    /* idlist  */
  YYSYMBOL_const_declarations = 72,        /* const_declarations  */
  YYSYMBOL_const_declaration = 73,         /* const_declaration  */
  YYSYMBOL_const_value = 74,               /* const_value  */
  YYSYMBOL_var_declarations = 75,          /* var_declarations  */
  YYSYMBOL_var_declaration = 76,           /* var_declaration  */
  YYSYMBOL_type = 77,                      /* type  */
  YYSYMBOL_basic_type = 78,                /* basic_type  */
  YYSYMBOL_period_list = 79,               /* period_list  */
  YYSYMBOL_subprogram_declarations = 80,   /* subprogram_declarations  */
  YYSYMBOL_subprogram = 81,                /* subprogram  */
  YYSYMBOL_subprogram_head = 82,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 83,          /* formal_parameter  */
  YYSYMBOL_parameter_list = 84,            /* parameter_list  */
  YYSYMBOL_parameter = 85,                 /* parameter  */
  YYSYMBOL_var_parameter = 86,             /* var_parameter  */
  YYSYMBOL_value_parameter = 87,           /* value_parameter  */
  YYSYMBOL_subprogram_body = 88,           /* subprogram_body  */
  YYSYMBOL_compound_statement = 89,        /* compound_statement  */
  YYSYMBOL_statement_list = 90,            /* statement_list  */
  YYSYMBOL_statement = 91,                 /* statement  */
  YYSYMBOL_variable_list = 92,             /* variable_list  */
  YYSYMBOL_variable = 93,                  /* variable  */
  YYSYMBOL_id_varpart = 94,                /* id_varpart  */
  YYSYMBOL_id_random = 95,                 /* id_random  */
  YYSYMBOL_procedure_call = 96,            /* procedure_call  */
  YYSYMBOL_else_part = 97,                 /* else_part  */
  YYSYMBOL_expression_list = 98,           /* expression_list  */
  YYSYMBOL_expression = 99,                /* expression  */
  YYSYMBOL_simple_expression = 100,        /* simple_expression  */
  YYSYMBOL_term = 101,                     /* term  */
  YYSYMBOL_factor = 102,                   /* factor  */
  YYSYMBOL_addop = 103,                    /* addop  */
  YYSYMBOL_relop = 104,                    /* relop  */
  YYSYMBOL_mulop = 105                     /* mulop  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   386

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
      54,    55,    65,    58,    56,    59,    53,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    52,
      63,    57,    64,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   356,   356,   364,   374,   381,   387,   398,   423,   436,
     442,   448,   460,   464,   476,   488,   498,   515,   521,   527,
     533,   539,   545,   551,   568,   572,   577,   590,   605,   619,
     631,   640,   652,   664,   669,   674,   679,   693,   703,   721,
     725,   746,   763,   777,   800,   804,   820,   824,   830,   844,
     849,   862,   876,   894,   913,   924,   929,   940,   945,   956,
     973,   977,   987,  1000,  1007,  1012,  1027,  1048,  1065,  1077,
    1099,  1106,  1112,  1124,  1136,  1148,  1162,  1166,  1175,  1188,
    1198,  1205,  1221,  1228,  1241,  1256,  1260,  1266,  1279,  1283,
    1290,  1296,  1308,  1317,  1329,  1343,  1351,  1360,  1373,  1381,
    1390,  1403,  1416,  1429,  1442,  1455,  1468,  1481,  1495,  1508,
    1520,  1530,  1549,  1557,  1566,  1574,  1581,  1581,  1581,  1586,
    1586,  1586,  1586,  1586,  1586,  1586,  1591,  1591,  1591,  1591,
    1591,  1591
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
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "PROGRAM",
  "TYPE", "RECORD", "ARRAY", "OF", "VAR", "FUNCTION", "PROCEDURE",
  "BEGIN_TOKEN", "END", "IF", "THEN", "ELSE", "CASE", "WHILE", "REPEAT",
  "UNTIL", "FOR", "TO", "DOWNTO", "DO", "READ", "READLN", "WRITE",
  "WRITELN", "CHAR_KW", "INTEGER_KW", "REAL_KW", "BOOLEAN_KW", "NOT",
  "DIV", "MOD", "AND", "OR", "NE", "LE", "GE", "ASSIGNOP", "IN", "ORELSE",
  "ANDTHEN", "DOUBLE_DOT", "IDENTIFIER", "INTEGER", "BOOLEAN", "REAL",
  "CHAR", "STRING", "';'", "'.'", "'('", "')'", "','", "'='", "'+'", "'-'",
  "':'", "'['", "']'", "'<'", "'>'", "'*'", "'/'", "$accept",
  "programstruct", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type",
  "period_list", "subprogram_declarations", "subprogram",
  "subprogram_head", "formal_parameter", "parameter_list", "parameter",
  "var_parameter", "value_parameter", "subprogram_body",
  "compound_statement", "statement_list", "statement", "variable_list",
  "variable", "id_varpart", "id_random", "procedure_call", "else_part",
  "expression_list", "expression", "simple_expression", "term", "factor",
  "addop", "relop", "mulop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-89)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     109,   -33,   -22,    31,    -6,    13,  -119,   317,    32,    44,
      39,    52,   231,  -119,  -119,   129,    66,    87,  -119,  -119,
      34,  -119,  -119,    95,   214,   108,   107,    46,   115,   154,
    -119,  -119,  -119,  -119,   -38,   130,  -119,   124,   102,    33,
    -119,   141,   155,   298,   164,   172,  -119,  -119,  -119,  -119,
    -119,   214,  -119,   183,  -119,  -119,  -119,  -119,  -119,  -119,
      64,   181,   181,   195,    68,    68,   199,   192,   198,     9,
    -119,    -1,  -119,   216,  -119,  -119,   253,  -119,   211,   102,
      73,   215,  -119,  -119,   161,   134,  -119,  -119,  -119,  -119,
      68,   179,   201,  -119,   261,   299,   117,  -119,   256,   236,
      35,    40,   221,    68,    40,     6,  -119,   222,  -119,   334,
      68,   229,    20,  -119,   245,    80,  -119,    32,    84,   105,
    -119,  -119,  -119,   174,  -119,  -119,    40,   239,  -119,  -119,
    -119,  -119,  -119,  -119,   288,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,   220,   238,  -119,  -119,  -119,
    -119,  -119,  -119,   161,   288,    68,  -119,    16,   158,  -119,
    -119,   162,  -119,  -119,   167,    81,   233,    68,   195,  -119,
    -119,    14,   244,   246,   290,  -119,   174,    75,  -119,  -119,
     175,  -119,     7,  -119,   117,  -119,   -21,  -119,  -119,   281,
    -119,    92,  -119,    68,  -119,  -119,  -119,   243,  -119,  -119,
     262,   174,  -119,  -119,  -119,  -119,   288,  -119,    68,  -119,
    -119,  -119,  -119,   267,  -119,  -119,   284,  -119,   288,  -119
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     0,     5,     1,     0,     0,    14,
       0,     0,     0,    11,     9,     0,     0,     0,     2,    26,
       0,    39,     4,     0,     0,    13,    11,     0,     0,     0,
      10,    17,    20,    23,     0,     0,    15,     0,     0,     0,
      56,     0,     0,     0,     0,     0,     7,    18,    21,    19,
      22,     0,    32,     0,    36,    33,    34,    35,    27,    30,
       0,    44,    44,    56,     0,     0,     0,     0,     0,     0,
      64,     0,    57,     0,    63,    40,     0,    16,     0,     0,
       0,     0,    42,    75,     0,     0,   101,   107,   104,   108,
       0,     0,     0,   109,     0,    92,    95,    98,     0,     0,
       0,     0,    78,     0,     0,     0,    73,    74,    55,     0,
       0,    14,     0,    41,     0,     0,    28,     0,     0,     0,
      47,    49,    50,     0,    75,   112,     0,     0,   101,   104,
     113,   101,   104,   114,     0,   118,   120,   122,   124,   125,
     119,   116,   117,   121,   123,     0,     0,   128,   129,   130,
     131,   126,   127,     0,     0,     0,    72,     0,     0,    70,
      75,     0,    89,    62,     0,     0,    89,     0,    56,    58,
      61,     0,     0,     0,     0,    51,     0,     0,    45,    43,
       0,   110,     0,    75,    96,    75,    93,    99,    65,     0,
      68,     0,    69,     0,    83,    77,    80,     0,    53,    37,
       0,     0,    52,    48,   111,    87,     0,    66,     0,    75,
      71,    90,    79,     0,    31,    86,     0,    38,     0,    67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,  -119,    10,   241,  -119,   270,   210,  -119,
     251,  -118,  -119,  -119,  -119,  -119,   269,  -119,   147,  -119,
     225,  -119,   -25,  -119,  -106,  -119,   -43,  -119,  -119,  -119,
    -119,     3,   -63,   186,   188,   -78,  -119,  -119,  -119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    11,   118,    12,    17,    36,    21,    28,
      58,    59,   115,    29,    44,    45,    81,   119,   120,   121,
     122,   113,    70,    71,    72,   158,    93,   106,   107,    74,
     207,   161,   162,    95,    96,    97,   145,   146,   153
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    94,    98,   169,    46,   179,   125,   160,   205,    47,
     102,    48,   108,   130,   133,    40,   135,   102,    15,    -6,
     -85,    19,   -82,   206,     5,   -82,    43,   127,   182,    20,
      27,     6,   -24,    13,    13,    26,   156,   141,   142,    84,
     163,   160,   166,   -25,   -25,   -25,     7,   170,   188,    60,
     103,   109,    85,    86,    87,    88,    89,   159,   202,   -85,
      90,   -82,   -88,   104,    91,    92,    73,     8,   -88,    83,
     105,   -76,   -76,    84,    13,   187,    13,   105,    14,    14,
      14,   157,   117,   214,   117,    16,    85,    86,    87,    88,
      89,    73,   189,   209,    90,   -88,   -88,    -8,    91,    92,
     215,    84,    23,    52,   197,    18,    38,   164,   165,    53,
       1,    73,   219,     2,    85,    86,    87,    88,    89,    14,
      23,    14,    90,    24,    79,   -46,    91,    92,   -46,   180,
     211,    54,    55,    56,    57,   102,   173,   193,   157,    25,
      23,    30,   174,   195,   176,   216,   198,   -76,   210,   -76,
     -76,   147,   148,   149,    37,    40,   -76,   177,   -76,   -29,
     178,   150,   124,    73,    41,    42,    43,    39,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,    73,   -76,    49,   -76,    50,
     124,    51,   151,   152,    22,    23,   -76,    61,   126,   -76,
     -76,   -76,   -76,   -76,    84,   105,   -76,   -76,   -76,   -76,
     -76,    62,   124,    54,    55,    56,    57,    85,    86,    87,
      88,    89,    84,   190,   191,    90,    75,   192,   193,    91,
      92,   183,   194,   193,    76,    85,   128,    87,   129,    89,
     204,   193,    19,    90,    84,    80,   -75,    91,    92,   185,
      20,   -24,   -24,   -24,    78,    99,   100,    85,   131,    87,
     132,    89,   101,    84,   111,    90,    10,   110,   114,    91,
      92,    31,   -12,    32,    33,   -12,    85,    86,    87,    88,
      89,    84,    34,    35,    90,   123,   134,   155,    91,    92,
     154,   -54,   -81,   167,    85,    86,    87,    88,    89,   168,
     172,   199,    90,   200,   181,   196,    91,    92,   201,    63,
      43,   -60,    64,   208,   -60,   212,    65,   213,   218,    66,
      43,   -60,    64,    67,   217,    68,    65,   112,     9,    66,
      10,    77,   171,    67,   203,    68,   -12,   -12,   -12,   -12,
     116,    82,   186,   184,    69,   168,   135,   136,   137,   138,
     -60,   139,   175,     0,    69,     0,    43,   -60,    64,     0,
     -60,     0,    65,     0,     0,    66,   140,   141,   142,    67,
       0,    68,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,     0,     0,     0,     0,     0,   -60
};

static const yytype_int16 yycheck[] =
{
      43,    64,    65,   109,    29,   123,    84,     1,     1,    47,
       1,    49,    13,    91,    92,     1,    37,     1,     8,    52,
      13,     1,    13,    16,    46,    16,    12,    90,   134,     9,
      20,     0,    12,     1,     1,     1,     1,    58,    59,    33,
     103,     1,   105,    10,    11,    12,    52,   110,   154,    39,
      41,    52,    46,    47,    48,    49,    50,   100,   176,    52,
      54,    52,    56,    54,    58,    59,   109,    54,    62,     1,
      61,    55,    56,    33,     1,   153,     1,    61,    46,    46,
      46,    46,     9,   201,     9,    46,    46,    47,    48,    49,
      50,   134,   155,     1,    54,    55,    56,    53,    58,    59,
     206,    33,    56,     1,   167,    53,    60,   104,   105,     7,
       1,   154,   218,     4,    46,    47,    48,    49,    50,    46,
      56,    46,    54,    57,    60,    52,    58,    59,    55,   126,
     193,    29,    30,    31,    32,     1,    56,    56,    46,    52,
      56,    46,    62,    62,    60,   208,   171,    13,   191,    15,
      16,    34,    35,    36,    46,     1,    22,    52,    24,    52,
      55,    44,     1,   206,    10,    11,    12,    52,    34,    35,
      36,    37,    38,    39,    40,   218,    42,    47,    44,    49,
       1,    57,    65,    66,    55,    56,    52,    46,    54,    55,
      56,    57,    58,    59,    33,    61,    62,    63,    64,    65,
      66,    46,     1,    29,    30,    31,    32,    46,    47,    48,
      49,    50,    33,    55,    56,    54,    52,    55,    56,    58,
      59,     1,    55,    56,    52,    46,    47,    48,    49,    50,
      55,    56,     1,    54,    33,    54,    41,    58,    59,     1,
       9,    10,    11,    12,    61,    46,    54,    46,    47,    48,
      49,    50,    54,    33,     1,    54,     3,    41,    47,    58,
      59,    47,     9,    49,    50,    12,    46,    47,    48,    49,
      50,    33,    58,    59,    54,    60,    15,    41,    58,    59,
      24,    52,    61,    61,    46,    47,    48,    49,    50,     1,
      45,    47,    54,    47,    55,    62,    58,    59,     8,     1,
      12,    13,    14,    22,    16,    62,    18,    45,    24,    21,
      12,    13,    14,    25,    47,    27,    18,    76,     1,    21,
       3,    51,   112,    25,   177,    27,     9,    10,    11,    12,
      79,    62,   146,   145,    46,     1,    37,    38,    39,    40,
      52,    42,   117,    -1,    46,    -1,    12,    13,    14,    -1,
      52,    -1,    18,    -1,    -1,    21,    57,    58,    59,    25,
      -1,    27,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     4,    68,    69,    46,     0,    52,    54,     1,
       3,    70,    72,     1,    46,    71,    46,    73,    53,     1,
       9,    75,    55,    56,    57,    52,     1,    71,    76,    80,
      46,    47,    49,    50,    58,    59,    74,    46,    60,    52,
       1,    10,    11,    12,    81,    82,    89,    47,    49,    47,
      49,    57,     1,     7,    29,    30,    31,    32,    77,    78,
      71,    46,    46,     1,    14,    18,    21,    25,    27,    46,
      89,    90,    91,    93,    96,    52,    52,    74,    61,    60,
      54,    83,    83,     1,    33,    46,    47,    48,    49,    50,
      54,    58,    59,    93,    99,   100,   101,   102,    99,    46,
      54,    54,     1,    41,    54,    61,    94,    95,    13,    52,
      41,     1,    72,    88,    47,    79,    77,     9,    71,    84,
      85,    86,    87,    60,     1,   102,    54,    99,    47,    49,
     102,    47,    49,   102,    15,    37,    38,    39,    40,    42,
      57,    58,    59,    63,    64,   103,   104,    34,    35,    36,
      44,    65,    66,   105,    24,    41,     1,    46,    92,    93,
       1,    98,    99,    99,    98,    98,    99,    61,     1,    91,
      99,    75,    45,    56,    62,    87,    60,    52,    55,    78,
      98,    55,    91,     1,   101,     1,   100,   102,    91,    99,
      55,    56,    55,    56,    55,    62,    62,    99,    89,    47,
      47,     8,    78,    85,    55,     1,    16,    97,    22,     1,
      93,    99,    62,    45,    78,    91,    99,    47,    24,    91
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    75,    76,    76,    76,
      77,    77,    77,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    82,    82,    83,    83,    84,    84,    84,    85,
      85,    86,    87,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    92,    93,    93,    93,    94,    94,    94,    95,
      95,    95,    96,    96,    96,    97,    97,    97,    98,    98,
      98,    98,    99,    99,    99,   100,   100,   100,   101,   101,
     101,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   105
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     1,     5,     2,     1,     4,     1,     1,
       3,     1,     0,     3,     1,     3,     5,     1,     2,     2,
       1,     2,     2,     1,     0,     3,     1,     3,     5,     1,
       1,     6,     1,     1,     1,     1,     1,     3,     5,     0,
       3,     3,     3,     5,     0,     3,     0,     1,     3,     1,
       1,     2,     3,     3,     1,     3,     1,     1,     3,     1,
       0,     3,     3,     1,     1,     4,     5,     8,     4,     4,
       1,     3,     1,     2,     2,     1,     0,     3,     1,     4,
       3,     1,     1,     4,     1,     0,     2,     1,     0,     1,
       3,     1,     1,     3,     1,     1,     3,     1,     1,     3,
       1,     1,     2,     2,     1,     2,     2,     1,     1,     1,
       3,     4,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
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
        yyerror (&yylloc, code_str, program, scanner, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, Location, code_str, program, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * code_str, ProgramStmt ** program, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (code_str);
  YY_USE (program);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * code_str, ProgramStmt ** program, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, code_str, program, scanner);
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
                 int yyrule, const char * code_str, ProgramStmt ** program, void * scanner)
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
                       &(yylsp[(yyi + 1) - (yynrhs)]), code_str, program, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, code_str, program, scanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * code_str, ProgramStmt ** program, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (code_str);
  YY_USE (program);
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
yyparse (const char * code_str, ProgramStmt ** program, void * scanner)
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
  case 2: /* programstruct: program_head ';' program_body '.'  */
#line 357 "../../src/parser/yacc_pascal.y"
    {
        ProgramStmt * program_struct = new ProgramStmt();
        program_struct->head = std::unique_ptr<ProgramHeadStmt>((yyvsp[-3].program_head));
        program_struct->body = std::unique_ptr<ProgramBodyStmt>((yyvsp[-1].program_body));
        LOG_DEBUG("DEBUG programstruct -> program_head ';' program_body '.'");
        *program = program_struct;
    }
#line 1956 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 3: /* programstruct: error  */
#line 364 "../../src/parser/yacc_pascal.y"
           {
        syntax_error("程序定义出错 请检查是否符合规范");
    }
#line 1964 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 4: /* program_head: PROGRAM IDENTIFIER '(' idlist ')'  */
#line 375 "../../src/parser/yacc_pascal.y"
    {
        (yyval.program_head) = new ProgramHeadStmt();
        (yyval.program_head)->id_list = *(yyvsp[-1].id_list);
        delete (yyvsp[-1].id_list);
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER '(' idlist ')'");
    }
#line 1975 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 5: /* program_head: PROGRAM IDENTIFIER  */
#line 382 "../../src/parser/yacc_pascal.y"
    {
        (yyval.program_head) = new ProgramHeadStmt();
        (yyval.program_head)->id_list.push_back(std::string((yyvsp[0].string)));
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER");
    }
#line 1985 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 6: /* program_head: error  */
#line 387 "../../src/parser/yacc_pascal.y"
           {
        syntax_error("程序头定义出错 请检查是否符合规范");
    }
#line 1993 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 7: /* program_body: const_declarations var_declarations subprogram_declarations compound_statement  */
#line 399 "../../src/parser/yacc_pascal.y"
    {
        ProgramBodyStmt* program_body = new ProgramBodyStmt();
        if((yyvsp[-3].const_decls) != nullptr) {program_body->const_decl = std::unique_ptr<ConstDeclStmt>((yyvsp[-3].const_decls));}
        if((yyvsp[-2].var_decls) != nullptr){
            for(auto var_decl : *(yyvsp[-2].var_decls)){
                program_body->var_decl.push_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete (yyvsp[-2].var_decls);
        }
        if((yyvsp[-1].func_decl_list) != nullptr){
            for(auto func_decl : *(yyvsp[-1].func_decl_list)){
                program_body->func_decl.push_back(std::unique_ptr<FuncDeclStmt>(func_decl));
            }
            delete (yyvsp[-1].func_decl_list);
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                program_body->comp_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        (yyval.program_body) = program_body;
        LOG_DEBUG("DEBUG program_body -> const_declarations var_declarations subprogram_declarations compound_statement");
    }
#line 2022 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 8: /* program_body: error  */
#line 423 "../../src/parser/yacc_pascal.y"
           {
        syntax_error("程序体定义出错 请检查是否符合规范");
    }
#line 2030 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 9: /* idlist: IDENTIFIER  */
#line 437 "../../src/parser/yacc_pascal.y"
    {
        (yyval.id_list) = new std::vector<std::string>();
        (yyval.id_list)->push_back(std::string((yyvsp[0].string)));
        LOG_DEBUG("DEBUG idlist -> IDENTIFIER");
    }
#line 2040 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 10: /* idlist: idlist ',' IDENTIFIER  */
#line 443 "../../src/parser/yacc_pascal.y"
    {
        (yyvsp[-2].id_list)->push_back(std::string((yyvsp[0].string)));
        (yyval.id_list) = (yyvsp[-2].id_list);
        LOG_DEBUG("DEBUG idlist -> idlist ',' IDENTIFIER");
    }
#line 2050 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 11: /* idlist: error  */
#line 448 "../../src/parser/yacc_pascal.y"
           {
        syntax_error("标识符定义错误 请检查是否符合规范");
    }
#line 2058 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 12: /* const_declarations: %empty  */
#line 460 "../../src/parser/yacc_pascal.y"
    {
        (yyval.const_decls) = nullptr;
        LOG_DEBUG("DEBUG const_declarations -> empty");
    }
#line 2067 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 13: /* const_declarations: CONST const_declaration ';'  */
#line 465 "../../src/parser/yacc_pascal.y"
    {
        ConstDeclStmt * const_decls = new ConstDeclStmt();
        for(auto kv_pair : *(yyvsp[-1].kv_pair_list)){
            const_decls->pairs.push_back(*kv_pair);
            delete kv_pair;
        }
        // 疑似内存泄漏
        delete (yyvsp[-1].kv_pair_list);
        (yyval.const_decls) = const_decls;
        LOG_DEBUG("DEBUG const_declarations -> CONST const_declaration ';' const_declarations");
    }
#line 2083 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 14: /* const_declarations: error  */
#line 477 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("常量定义出错 请检查是否符合规范");
    }
#line 2091 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 15: /* const_declaration: IDENTIFIER '=' const_value  */
#line 489 "../../src/parser/yacc_pascal.y"
    {
        std::vector<std::pair<std::string, NumberStmt> *> * const_decls = new std::vector<std::pair<std::string, NumberStmt> *>();
        std::pair<std::string, NumberStmt> * kv_pair = new std::pair<std::string, NumberStmt>((yyvsp[-2].string), *(yyvsp[0].num_value));
        const_decls->push_back(kv_pair);
        delete (yyvsp[-2].string);
        delete (yyvsp[0].num_value);
        // 疑似内存泄漏
        (yyval.kv_pair_list) = const_decls;
    }
#line 2105 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 16: /* const_declaration: const_declaration ';' IDENTIFIER '=' const_value  */
#line 499 "../../src/parser/yacc_pascal.y"
    {
        (yyvsp[-4].kv_pair_list)->push_back(new std::pair<std::string, NumberStmt>((yyvsp[-2].string), *(yyvsp[0].num_value)));
        delete (yyvsp[-2].string);
        delete (yyvsp[0].num_value);
        (yyval.kv_pair_list) = (yyvsp[-4].kv_pair_list); // 不需要删除
    }
#line 2116 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 17: /* const_value: INTEGER  */
#line 516 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, (yyvsp[0].number));
        (yyval.num_value) = num_value;
    }
#line 2126 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 18: /* const_value: '+' INTEGER  */
#line 522 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, (yyvsp[0].number));
        (yyval.num_value) = num_value;
    }
#line 2136 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 19: /* const_value: '-' INTEGER  */
#line 528 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, ((yyvsp[0].number)) * -1);
        (yyval.num_value) = num_value;
    }
#line 2146 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 20: /* const_value: REAL  */
#line 534 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, (yyvsp[0].real));
        (yyval.num_value) = num_value;
    }
#line 2156 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 21: /* const_value: '+' REAL  */
#line 540 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, (yyvsp[0].real));
        (yyval.num_value) = num_value;
    }
#line 2166 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 22: /* const_value: '-' REAL  */
#line 546 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, ((yyvsp[0].real)) * -1);
        (yyval.num_value) = num_value;
    }
#line 2176 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 23: /* const_value: CHAR  */
#line 552 "../../src/parser/yacc_pascal.y"
    {
        NumberStmt * num_value = new NumberStmt();
        fill_number_stmt(num_value, (yyvsp[0].charactor));
        (yyval.num_value) = num_value;
    }
#line 2186 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 24: /* var_declarations: %empty  */
#line 568 "../../src/parser/yacc_pascal.y"
    {
        (yyval.var_decls) = nullptr;
        LOG_DEBUG("DEBUG var_declarations -> empty");
    }
#line 2195 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 25: /* var_declarations: VAR var_declaration ';'  */
#line 573 "../../src/parser/yacc_pascal.y"
    {
        (yyval.var_decls) = (yyvsp[-1].var_decls);
        LOG_DEBUG("DEBUG var_declarations -> VAR var_declaration ';'");
    }
#line 2204 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 26: /* var_declarations: error  */
#line 578 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
#line 2212 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 27: /* var_declaration: idlist ':' type  */
#line 591 "../../src/parser/yacc_pascal.y"
    {
        std::vector<VarDeclStmt *> * var_decls = new std::vector<VarDeclStmt *>();
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
        // deal with type
        var_decl->basic_type = (yyvsp[0].var_decl)->basic_type;
        var_decl->data_type = (yyvsp[0].var_decl)->data_type;
        var_decl->array_range = std::move((yyvsp[0].var_decl)->array_range);
        delete (yyvsp[-2].id_list);
        delete (yyvsp[0].var_decl);
        var_decls->push_back(var_decl);
        (yyval.var_decls) = var_decls;
        LOG_DEBUG("DEBUG var_declaration -> idlist ':' type");
    }
#line 2231 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 28: /* var_declaration: var_declaration ';' idlist ':' type  */
#line 606 "../../src/parser/yacc_pascal.y"
    {
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
        // deal with type
        var_decl->basic_type = (yyvsp[0].var_decl)->basic_type;
        var_decl->data_type = (yyvsp[0].var_decl)->data_type;
        var_decl->array_range = std::move((yyvsp[0].var_decl)->array_range);
        delete (yyvsp[-2].id_list);
        delete (yyvsp[0].var_decl);
        (yyvsp[-4].var_decls)->push_back(var_decl);
        (yyval.var_decls) = (yyvsp[-4].var_decls);
        LOG_DEBUG("DEBUG var_declaration -> var_declaration ';' idlist ':' type");
    }
#line 2249 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 29: /* var_declaration: error  */
#line 620 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
#line 2257 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 30: /* type: basic_type  */
#line 632 "../../src/parser/yacc_pascal.y"
    {
        VarDeclStmt * type_stmt = new VarDeclStmt();
        // TODO 处理type_size
        type_stmt->data_type = DataType::BasicType;
        type_stmt->basic_type = (yyvsp[0].basic_type);
        (yyval.var_decl) = type_stmt;
        LOG_DEBUG("DEBUG type -> basic_type");
    }
#line 2270 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 31: /* type: ARRAY '[' period_list ']' OF basic_type  */
#line 641 "../../src/parser/yacc_pascal.y"
    {
        VarDeclStmt * type_stmt = new VarDeclStmt();
        type_stmt->data_type = DataType::ArrayType;
        type_stmt->basic_type = (yyvsp[0].basic_type);
        for(auto period : *(yyvsp[-3].period_list)){
            type_stmt->array_range.push_back(std::unique_ptr<PeriodStmt>(period));
        }
        delete (yyvsp[-3].period_list);
        (yyval.var_decl) = type_stmt;
        LOG_DEBUG("DEBUG type -> ARRAY '[' period_list ']' OF basic_type");
    }
#line 2286 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 32: /* type: error  */
#line 653 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("类型定义出错 请检查是否符合规范");
    }
#line 2294 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 33: /* basic_type: INTEGER_KW  */
#line 665 "../../src/parser/yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::INT;
            LOG_DEBUG("DEBUG basic_type -> INTEGER_KW");
        }
#line 2303 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 34: /* basic_type: REAL_KW  */
#line 670 "../../src/parser/yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::REAL;
            LOG_DEBUG("DEBUG basic_type -> REAL_KW");
        }
#line 2312 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 35: /* basic_type: BOOLEAN_KW  */
#line 675 "../../src/parser/yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::BOOLEAN;
            LOG_DEBUG("DEBUG basic_type -> BOOLEAN_KW");
        }
#line 2321 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 36: /* basic_type: CHAR_KW  */
#line 680 "../../src/parser/yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::CHAR;
            LOG_DEBUG("DEBUG basic_type -> CHAR_KW");
        }
#line 2330 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 37: /* period_list: INTEGER DOUBLE_DOT INTEGER  */
#line 694 "../../src/parser/yacc_pascal.y"
        {
            (yyval.period_list) = new std::vector<PeriodStmt *>();
            PeriodStmt * period = new PeriodStmt();
            period->begin = (yyvsp[-2].number);
            period->end = (yyvsp[0].number);
            (yyval.period_list)->push_back(period);
            // debug
            LOG_DEBUG("DEBUG period_list -> INTEGER '..' INTEGER");
        }
#line 2344 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 38: /* period_list: period_list ',' INTEGER DOUBLE_DOT INTEGER  */
#line 704 "../../src/parser/yacc_pascal.y"
        {
            PeriodStmt * period = new PeriodStmt();
            period->begin = (yyvsp[-2].number);
            period->end = (yyvsp[0].number);
            (yyvsp[-4].period_list)->push_back(period);
            (yyval.period_list) = (yyvsp[-4].period_list);
            // debug
            LOG_DEBUG("DEBUG period_list -> period_list ',' INTEGER '..' INTEGER");
        }
#line 2358 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 39: /* subprogram_declarations: %empty  */
#line 721 "../../src/parser/yacc_pascal.y"
        {
            (yyval.func_decl_list) = nullptr;
            LOG_DEBUG("DEBUG subprogram_declarations -> empty");
        }
#line 2367 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 40: /* subprogram_declarations: subprogram_declarations subprogram ';'  */
#line 726 "../../src/parser/yacc_pascal.y"
        {
            if((yyvsp[-2].func_decl_list) == nullptr){
                std::vector<FuncDeclStmt *> * func_decl_list = new std::vector<FuncDeclStmt *>();
                func_decl_list->push_back((yyvsp[-1].func_decl));    
                (yyval.func_decl_list) = func_decl_list;
            }else{
                (yyvsp[-2].func_decl_list)->push_back((yyvsp[-1].func_decl));
                (yyval.func_decl_list) = (yyvsp[-2].func_decl_list);
            }
            LOG_DEBUG("DEBUG subprogram_declarations -> subprogram_declarations subprogram ';'");
        }
#line 2383 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 41: /* subprogram: subprogram_head ';' subprogram_body  */
#line 747 "../../src/parser/yacc_pascal.y"
        {
            FuncDeclStmt * subprogram = new FuncDeclStmt();
            subprogram->header = std::unique_ptr<FuncHeadDeclStmt>((yyvsp[-2].func_head));
            subprogram->body = std::unique_ptr<FuncBodyDeclStmt>((yyvsp[0].func_body));
            (yyval.func_decl) = subprogram;
            LOG_DEBUG("DEBUG subprogram -> subprogram_head ';' subprogram_body");
        }
#line 2395 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 42: /* subprogram_head: PROCEDURE IDENTIFIER formal_parameter  */
#line 764 "../../src/parser/yacc_pascal.y"
        {
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string((yyvsp[-1].string));
            sub_head->ret_type = BasicType::VOID;
            if((yyvsp[0].var_decls) != nullptr){
                for(auto formal_parameter : *(yyvsp[0].var_decls)){
                    sub_head->args.push_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete (yyvsp[0].var_decls);
            }
            (yyval.func_head) = sub_head;
            LOG_DEBUG("DEBUG subprogram_head -> PROGRAM IDENTIFIER formal_parameter");
        }
#line 2413 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 43: /* subprogram_head: FUNCTION IDENTIFIER formal_parameter ':' basic_type  */
#line 778 "../../src/parser/yacc_pascal.y"
        {
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string((yyvsp[-3].string));
            sub_head->ret_type = (yyvsp[0].basic_type);
            if((yyvsp[-2].var_decls) != nullptr){
                for(auto formal_parameter : *(yyvsp[-2].var_decls)){
                    sub_head->args.push_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete (yyvsp[-2].var_decls);
            }
            (yyval.func_head) = sub_head;
            LOG_DEBUG("DEBUG subprogram_head -> FUNCTION IDENTIFIER formal_parameter ':' basic_type");
        }
#line 2431 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 44: /* formal_parameter: %empty  */
#line 800 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decls) = nullptr;
            LOG_DEBUG("DEBUG formal_parameter -> empty");
        }
#line 2440 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 45: /* formal_parameter: '(' parameter_list ')'  */
#line 805 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decls) = (yyvsp[-1].var_decls);
            LOG_DEBUG("DEBUG formal_parameter -> '(' parameter_list ')'");
        }
#line 2449 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 46: /* parameter_list: %empty  */
#line 820 "../../src/parser/yacc_pascal.y"
    {
        (yyval.var_decls) = nullptr;
        LOG_DEBUG("DEBUG parameter_list -> empty");
    }
#line 2458 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 47: /* parameter_list: parameter  */
#line 825 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decls) = new std::vector<VarDeclStmt *>();
            (yyval.var_decls)->push_back((yyvsp[0].var_decl));
            LOG_DEBUG("DEBUG parameter_list -> parameter");
        }
#line 2468 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 48: /* parameter_list: parameter_list ';' parameter  */
#line 831 "../../src/parser/yacc_pascal.y"
        {
            (yyvsp[-2].var_decls)->push_back((yyvsp[0].var_decl));
            (yyval.var_decls) = (yyvsp[-2].var_decls);
            LOG_DEBUG("DEBUG parameter_list -> parameter_list ';' parameter");
        }
#line 2478 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 49: /* parameter: var_parameter  */
#line 845 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            LOG_DEBUG("DEBUG parameter -> var_parameter");
        }
#line 2487 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 50: /* parameter: value_parameter  */
#line 850 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            LOG_DEBUG("DEBUG parameter -> value_parameter");
        }
#line 2496 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 51: /* var_parameter: VAR value_parameter  */
#line 863 "../../src/parser/yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            LOG_DEBUG("DEBUG var_parameter -> VAR value_parameter");
        }
#line 2505 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 52: /* value_parameter: idlist ':' basic_type  */
#line 877 "../../src/parser/yacc_pascal.y"
        {
            VarDeclStmt* var_decl = new VarDeclStmt();
            var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
            var_decl->data_type = DataType::BasicType;
            var_decl-> basic_type = (yyvsp[0].basic_type);
            // 疑似内存泄漏
            delete (yyvsp[-2].id_list);
            (yyval.var_decl) = var_decl;
            LOG_DEBUG("DEBUG value_parameter -> idlist ':' basic_type");
        }
#line 2520 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 53: /* subprogram_body: const_declarations var_declarations compound_statement  */
#line 895 "../../src/parser/yacc_pascal.y"
    {
        FuncBodyDeclStmt * func_body = new FuncBodyDeclStmt();
        if((yyvsp[-2].const_decls) != nullptr) func_body->const_decl = std::unique_ptr<ConstDeclStmt>((yyvsp[-2].const_decls));
        if((yyvsp[-1].var_decls) != nullptr){
            for(auto var_decl : *(yyvsp[-1].var_decls)){
                func_body->var_decl.push_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete (yyvsp[-1].var_decls);
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                func_body->comp_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        (yyval.func_body) = func_body;
        LOG_DEBUG("DEBUG subprogram_body -> const_declarations var_declarations compound_statement");
    }
#line 2543 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 54: /* subprogram_body: error  */
#line 914 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("子函数体定义出错 请检查是否符合规范");
    }
#line 2551 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 55: /* compound_statement: BEGIN_TOKEN statement_list END  */
#line 925 "../../src/parser/yacc_pascal.y"
    {
        (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        LOG_DEBUG("DEBUG compound_statement -> BEGIN_TOKEN statement_list END");
    }
#line 2560 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 56: /* compound_statement: error  */
#line 930 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("复合语句定义出错 请检查是否符合规范");
    }
#line 2568 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 57: /* statement_list: statement  */
#line 941 "../../src/parser/yacc_pascal.y"
    {
        (yyval.stmt_list) = (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement_list -> statement");
    }
#line 2577 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 58: /* statement_list: statement_list ';' statement  */
#line 946 "../../src/parser/yacc_pascal.y"
    {
        // copy the vector
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                (yyvsp[-2].stmt_list)->push_back(stmt);
            }
        }
        (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        LOG_DEBUG("DEBUG statement_list -> statement_list ';' statement");
    }
#line 2592 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 59: /* statement_list: error  */
#line 957 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("语句定义出错 请检查是否符合规范");
    }
#line 2600 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 60: /* statement: %empty  */
#line 973 "../../src/parser/yacc_pascal.y"
    {
        (yyval.stmt_list) = nullptr;
        LOG_DEBUG("DEBUG statement -> empty");
    }
#line 2609 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 61: /* statement: variable ASSIGNOP expression  */
#line 978 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::unique_ptr<LValStmt>((yyvsp[-2].lval));
        assign_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[0].expr));
        stmt_list->push_back(assign_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> variable ASSIGNOP expression");
    }
#line 2623 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 62: /* statement: IDENTIFIER ASSIGNOP expression  */
#line 988 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::make_unique<LValStmt>();
        assign_stmt->lval->id = std::string((yyvsp[-2].string));
        // how to deal with array_index
        // assign_stmt->lval->array_index = std::vector<std::unique_ptr<ExprStmt>>();
        assign_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[0].expr));
        stmt_list->push_back(assign_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> IDENTIFIER ASSIGNOP expression");
    }
#line 2640 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 63: /* statement: procedure_call  */
#line 1001 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        stmt_list->push_back((yyvsp[0].func_call_stmt));
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> procedure_call");
    }
#line 2651 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 64: /* statement: compound_statement  */
#line 1008 "../../src/parser/yacc_pascal.y"
    {
        (yyval.stmt_list) = (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement -> compound_statement");
    }
#line 2660 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 65: /* statement: WHILE expression DO statement  */
#line 1013 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WhileStmt * while_stmt = new WhileStmt();
        while_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[-2].expr));
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                while_stmt->stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        stmt_list->push_back(while_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> WHILE expression DO statement");
    }
#line 2679 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 66: /* statement: IF expression THEN statement else_part  */
#line 1028 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[-3].expr));
        if((yyvsp[-1].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[-1].stmt_list)){
                if_stmt->true_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                if_stmt->false_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        delete (yyvsp[-1].stmt_list);
        delete (yyvsp[0].stmt_list);
        stmt_list->push_back(if_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement else_part");
    }
#line 2704 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 67: /* statement: FOR IDENTIFIER ASSIGNOP expression TO expression DO statement  */
#line 1049 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ForStmt * for_stmt = new ForStmt();
        for_stmt->id = std::string((yyvsp[-6].string));
        for_stmt->begin = std::unique_ptr<ExprStmt>((yyvsp[-4].expr));
        for_stmt->end = std::unique_ptr<ExprStmt>((yyvsp[-2].expr));
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                for_stmt->stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        stmt_list->push_back(for_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> FOR IDENTIFIER ASSIGNOP expression TO expression DO statement");
    }
#line 2725 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 68: /* statement: READ '(' variable_list ')'  */
#line 1066 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ReadFuncStmt * read_stmt = new ReadFuncStmt();
        for(auto lval : *(yyvsp[-1].lval_list)){
            read_stmt->lval.push_back(std::unique_ptr<LValStmt>(lval));
        }
        delete (yyvsp[-1].lval_list);
        stmt_list->push_back(read_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> READ '(' variable_list ')'");
    }
#line 2741 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 69: /* statement: WRITE '(' expression_list ')'  */
#line 1078 "../../src/parser/yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WriteFuncStmt * write_stmt = new WriteFuncStmt();
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                write_stmt->expr.push_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[-1].expr_list);
        }
        stmt_list->push_back(write_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> WRITE '(' expression_list ')'");
    }
#line 2759 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 70: /* variable_list: variable  */
#line 1100 "../../src/parser/yacc_pascal.y"
    {
        std::vector<LValStmt *> * lval_list = new std::vector<LValStmt *>();
        lval_list->push_back((yyvsp[0].lval));
        (yyval.lval_list) = lval_list;
        LOG_DEBUG("DEBUG variable_list -> variable");
    }
#line 2770 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 71: /* variable_list: variable_list ',' variable  */
#line 1107 "../../src/parser/yacc_pascal.y"
    {
        (yyvsp[-2].lval_list)->push_back((yyvsp[0].lval));
        (yyval.lval_list) = (yyvsp[-2].lval_list);
        LOG_DEBUG("DEBUG variable_list -> variable_list ',' variable");
    }
#line 2780 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 72: /* variable_list: error  */
#line 1113 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
#line 2788 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 73: /* variable: IDENTIFIER id_varpart  */
#line 1125 "../../src/parser/yacc_pascal.y"
    {
        (yyval.lval) = new LValStmt();
        (yyval.lval)->id = std::string((yyvsp[-1].string));
        if((yyvsp[0].expr_list) != nullptr){
            for(auto expr : *(yyvsp[0].expr_list)){
                (yyval.lval)->array_index.push_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[0].expr_list);
        }
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_varpart");
    }
#line 2804 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 74: /* variable: IDENTIFIER id_random  */
#line 1137 "../../src/parser/yacc_pascal.y"
    {
        (yyval.lval) = new LValStmt();
        (yyval.lval)->id = std::string((yyvsp[-1].string));
        if((yyvsp[0].expr_list) != nullptr){
            for(auto expr : *(yyvsp[0].expr_list)){
                (yyval.lval)->array_index.push_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[0].expr_list);
        }
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_random");
    }
#line 2820 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 75: /* variable: error  */
#line 1149 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
#line 2828 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 76: /* id_varpart: %empty  */
#line 1162 "../../src/parser/yacc_pascal.y"
    {
        (yyval.expr_list) = nullptr;
        LOG_DEBUG("DEBUG id_varpart -> empty");
    }
#line 2837 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 77: /* id_varpart: '[' expression_list ']'  */
#line 1167 "../../src/parser/yacc_pascal.y"
    {
        if((yyvsp[-1].expr_list) != nullptr){
            (yyval.expr_list) = (yyvsp[-1].expr_list);    
        }else{
            syntax_error("数组下标定义出错 请检查是否符合规范");
        }
        LOG_DEBUG("DEBUG id_varpart -> '[' expression_list ']'");
    }
#line 2850 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 78: /* id_varpart: error  */
#line 1176 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("数组下标定义出错 请检查是否符合规范");
    }
#line 2858 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 79: /* id_random: id_random '[' expression ']'  */
#line 1189 "../../src/parser/yacc_pascal.y"
    {
        if((yyvsp[-3].expr_list) != nullptr){
            (yyvsp[-3].expr_list)->push_back((yyvsp[-1].expr));
            (yyval.expr_list) = (yyvsp[-3].expr_list);
        }else{
            syntax_error("随机存取数组定义出错 请检查是否符合规范");
        }
        LOG_DEBUG("DEBUG id_random -> id_random '[' expression ']'");
    }
#line 2872 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 80: /* id_random: '[' expression ']'  */
#line 1199 "../../src/parser/yacc_pascal.y"
    {
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->push_back((yyvsp[-1].expr));
        (yyval.expr_list) = expr_list;
        LOG_DEBUG("DEBUG id_random -> '[' expression ']'");
    }
#line 2883 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 81: /* id_random: error  */
#line 1206 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("随机存取数组定义出错 请检查是否符合规范");
    }
#line 2891 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 82: /* procedure_call: IDENTIFIER  */
#line 1222 "../../src/parser/yacc_pascal.y"
    {
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string((yyvsp[0].string));
        (yyval.func_call_stmt) = proc_call;
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER");
    }
#line 2902 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 83: /* procedure_call: IDENTIFIER '(' expression_list ')'  */
#line 1229 "../../src/parser/yacc_pascal.y"
    {
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string((yyvsp[-3].string));
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                proc_call->args.push_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[-1].expr_list);
        }
        (yyval.func_call_stmt) = proc_call;
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER '(' expression_list ')'");
    }
#line 2919 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 84: /* procedure_call: error  */
#line 1242 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("过程调用定义出错 请检查是否符合规范");
    }
#line 2927 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 85: /* else_part: %empty  */
#line 1256 "../../src/parser/yacc_pascal.y"
    {
        (yyval.stmt_list) = nullptr;
        LOG_DEBUG("DEBUG else_part -> empty");
    }
#line 2936 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 86: /* else_part: ELSE statement  */
#line 1261 "../../src/parser/yacc_pascal.y"
    {
        // 强行取第一个
        (yyval.stmt_list) = (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG else_part -> ELSE statement");
    }
#line 2946 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 87: /* else_part: error  */
#line 1267 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("else 语法定义出错 请检查是否符合规范");
    }
#line 2954 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 88: /* expression_list: %empty  */
#line 1279 "../../src/parser/yacc_pascal.y"
                  {
        (yyval.expr_list) = nullptr;
        LOG_DEBUG("DEBUG expression_list -> empty");
    }
#line 2963 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 89: /* expression_list: expression  */
#line 1284 "../../src/parser/yacc_pascal.y"
    {
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->push_back((yyvsp[0].expr));
        (yyval.expr_list) = expr_list;
        LOG_DEBUG("DEBUG expression_list -> expression");
    }
#line 2974 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 90: /* expression_list: expression_list ',' expression  */
#line 1291 "../../src/parser/yacc_pascal.y"
    {
        (yyvsp[-2].expr_list)->push_back((yyvsp[0].expr));
        (yyval.expr_list) = (yyvsp[-2].expr_list);
        LOG_DEBUG("DEBUG expression_list -> expression_list ',' expression");
    }
#line 2984 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 91: /* expression_list: error  */
#line 1297 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
#line 2992 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 92: /* expression: simple_expression  */
#line 1309 "../../src/parser/yacc_pascal.y"
    {
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>((yyvsp[0].add_expr));
        (yyval.expr) = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression");
    }
#line 3005 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 93: /* expression: simple_expression relop simple_expression  */
#line 1318 "../../src/parser/yacc_pascal.y"
    {
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->type = get_rel_expr_type((yyvsp[-1].number));
        expr->rel_expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        expr->rel_expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>((yyvsp[-2].add_expr));
        expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>((yyvsp[0].add_expr));
        (yyval.expr) = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression relop simple_expression");
    }
#line 3021 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 94: /* expression: error  */
#line 1330 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
#line 3029 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 95: /* simple_expression: term  */
#line 1344 "../../src/parser/yacc_pascal.y"
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = AddExprStmt::AddExprType::NULL_TYPE;
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>((yyvsp[0].mul_expr));
        (yyval.add_expr) = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> term");
    }
#line 3041 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 96: /* simple_expression: simple_expression addop term  */
#line 1352 "../../src/parser/yacc_pascal.y"
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = get_add_expr_type((yyvsp[-1].number));
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>((yyvsp[0].mul_expr));
        add_expr->add_expr = std::unique_ptr<AddExprStmt>((yyvsp[-2].add_expr));
        (yyval.add_expr) = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> simple_expression %lld term\n", (yyvsp[-1].number));
    }
#line 3054 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 97: /* simple_expression: error  */
#line 1361 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
#line 3062 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 98: /* term: factor  */
#line 1374 "../../src/parser/yacc_pascal.y"
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprStmt::MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr));
        (yyval.mul_expr) = mul_expr;
        LOG_DEBUG("DEBUG term -> factor");
    }
#line 3074 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 99: /* term: term mulop factor  */
#line 1382 "../../src/parser/yacc_pascal.y"
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = get_mul_expr_type((yyvsp[-1].number));
        mul_expr->mul_expr = std::unique_ptr<MulExprStmt>((yyvsp[-2].mul_expr));
        mul_expr->unary_expr = std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr));
        (yyval.mul_expr) = mul_expr;
        LOG_DEBUG("DEBUG term -> term mulop factor");
    }
#line 3087 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 100: /* term: error  */
#line 1391 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
#line 3095 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 101: /* factor: INTEGER  */
#line 1404 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].number));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> INTEGER");
    }
#line 3112 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 102: /* factor: '+' INTEGER  */
#line 1417 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].number));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '+' INTEGER");
    }
#line 3129 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 103: /* factor: '-' INTEGER  */
#line 1430 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,((yyvsp[0].number))*-1);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' INTEGER");
    }
#line 3146 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 104: /* factor: REAL  */
#line 1443 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].real));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> REAL");
    }
#line 3163 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 105: /* factor: '+' REAL  */
#line 1456 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].real));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '+' REAL");
    }
#line 3180 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 106: /* factor: '-' REAL  */
#line 1469 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,((yyvsp[0].real))*-1);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' REAL");
    }
#line 3197 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 107: /* factor: BOOLEAN  */
#line 1482 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        long long int val = (yyvsp[0].boolean) == true ? 1 : 0;
        fill_number_stmt(unary_expr->primary_expr->value->number,val);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> BOOLEAN");
    }
#line 3215 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 108: /* factor: CHAR  */
#line 1496 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].charactor));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> CHAR");
    }
#line 3232 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 109: /* factor: variable  */
#line 1509 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::LVal;
        unary_expr->primary_expr->value->lval = std::unique_ptr<LValStmt>((yyvsp[0].lval));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> variable");
    }
#line 3248 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 110: /* factor: '(' expression ')'  */
#line 1521 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Parentheses;
        unary_expr->primary_expr->expr = std::unique_ptr<ExprStmt>((yyvsp[-1].expr));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '(' expression ')'");
    }
#line 3262 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 111: /* factor: IDENTIFIER '(' expression_list ')'  */
#line 1531 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::FuncCall;
        unary_expr->primary_expr->value->func_call = std::make_unique<FuncCallStmt>();
        unary_expr->primary_expr->value->func_call->id = std::string((yyvsp[-3].string));
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                unary_expr->primary_expr->value->func_call->args.push_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[-1].expr_list);
        }
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> IDENTIFIER '(' expression_list ')'");
    }
#line 3285 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 112: /* factor: NOT factor  */
#line 1550 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::Not;
        unary_expr->primary_expr = bridge_primary_to_unary(std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr)));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> NOT factor");
    }
#line 3297 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 113: /* factor: '+' factor  */
#line 1558 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type = (yyvsp[0].unary_expr)->type;
        unary_expr->primary_expr = std::move((yyvsp[0].unary_expr)->primary_expr);
        delete (yyvsp[0].unary_expr);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '+' factor");
    }
#line 3310 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 114: /* factor: '-' factor  */
#line 1567 "../../src/parser/yacc_pascal.y"
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = bridge_primary_to_unary(std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr)));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' factor");
    }
#line 3322 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 115: /* factor: error  */
#line 1575 "../../src/parser/yacc_pascal.y"
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
#line 3330 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 116: /* addop: '+'  */
#line 1581 "../../src/parser/yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3336 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 117: /* addop: '-'  */
#line 1581 "../../src/parser/yacc_pascal.y"
                              { (yyval.number) = 1; }
#line 3342 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 118: /* addop: OR  */
#line 1581 "../../src/parser/yacc_pascal.y"
                                               { (yyval.number) = 2; }
#line 3348 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 119: /* relop: '='  */
#line 1586 "../../src/parser/yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3354 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 120: /* relop: NE  */
#line 1586 "../../src/parser/yacc_pascal.y"
                             { (yyval.number) = 1; }
#line 3360 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 121: /* relop: '<'  */
#line 1586 "../../src/parser/yacc_pascal.y"
                                               { (yyval.number) = 2; }
#line 3366 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 122: /* relop: LE  */
#line 1586 "../../src/parser/yacc_pascal.y"
                                                                { (yyval.number) = 3; }
#line 3372 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 123: /* relop: '>'  */
#line 1586 "../../src/parser/yacc_pascal.y"
                                                                                  { (yyval.number) = 4; }
#line 3378 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 124: /* relop: GE  */
#line 1586 "../../src/parser/yacc_pascal.y"
                                                                                                   { (yyval.number) = 5; }
#line 3384 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 125: /* relop: IN  */
#line 1586 "../../src/parser/yacc_pascal.y"
                                                                                                                    { (yyval.number) = 6; }
#line 3390 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 126: /* mulop: '*'  */
#line 1591 "../../src/parser/yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3396 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 127: /* mulop: '/'  */
#line 1591 "../../src/parser/yacc_pascal.y"
                              { (yyval.number) = 1; }
#line 3402 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 128: /* mulop: DIV  */
#line 1591 "../../src/parser/yacc_pascal.y"
                                                { (yyval.number) = 1; }
#line 3408 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 129: /* mulop: MOD  */
#line 1591 "../../src/parser/yacc_pascal.y"
                                                                  { (yyval.number) = 2; }
#line 3414 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 130: /* mulop: AND  */
#line 1591 "../../src/parser/yacc_pascal.y"
                                                                                    { (yyval.number) = 3; }
#line 3420 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;

  case 131: /* mulop: ANDTHEN  */
#line 1591 "../../src/parser/yacc_pascal.y"
                                                                                                          { (yyval.number) = 4; }
#line 3426 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"
    break;


#line 3430 "/mnt/e/BUPT-PASCC/test/bison_test/build/yacc_pascal.cpp"

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
        yyerror (&yylloc, code_str, program, scanner, yymsgp);
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
                      yytoken, &yylval, &yylloc, code_str, program, scanner);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, code_str, program, scanner);
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
  yyerror (&yylloc, code_str, program, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, code_str, program, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, code_str, program, scanner);
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

#line 1594 "../../src/parser/yacc_pascal.y"

// 此处书写相关函数，会添加在生成的代码中
extern void scan_string(const char *str, yyscan_t scanner);

int code_parse(const char * code_str, ProgramStmt ** program) {
    yyscan_t scanner;
    yylex_init(&scanner);
    scan_string(code_str, scanner);

    int ret = yyparse(code_str,program, scanner);

    yylex_destroy(scanner);
    return ret;
}
