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
#line 1 "yacc_pascal.y"

// 此处为相关头文件和函数，会添加在生成的代码中

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "common/log/log.hpp"
#include "common/setting/settings.hpp"
#include "ast/stmt.hpp"
#include "ast/stmt_test.hpp"
#include "yacc_pascal.hpp"
#include "lex_pascal.hpp"

bool hadError = false; // 错误标志

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

// std::unique_ptr<RelExprStmt> new_rel_expr_stmt(RelExprStmt::RelExprType type) {
//     std::unique_ptr<RelExprStmt> rel_expr = std::make_unique<RelExprStmt>();
//     rel_expr->type = type;
//     if(type == RelExprStmt::RelExprType::NULL_TYPE){
//         rel_expr->add_expr = nullptr;
//     }
//     return rel_expr;
// }


// std::unique_ptr<AddExprStmt> new_add_expr_stmt(AddExprStmt::AddExprType type) {
//     std::unique_ptr<AddExprStmt> add_expr = std::make_unique<AddExprStmt>();
//     add_expr->type = type;
//     if(type == AddExprStmt::AddExprType::NULL_TYPE){
//         add_expr->add_expr = nullptr;
//     }
//     return add_expr;
// }


// std::unique_ptr<MulExprStmt> new_mul_expr_stmt(MulExprStmt::MulExprType type) {
//     std::unique_ptr<MulExprStmt> mul_expr = std::make_unique<MulExprStmt>();
//     mul_expr->type = type;
//     if(type == MulExprStmt::MulExprType::NULL_TYPE){
//         mul_expr->mul_expr = nullptr;
//     }
//     return mul_expr;
// }


// std::unique_ptr<UnaryExprStmt> new_unary_expr_stmt(UnaryExprStmt::UnaryExprType type) {
//     std::unique_ptr<UnaryExprStmt> unary_expr = std::make_unique<UnaryExprStmt>();
//     unary_expr->type = type;
//     return unary_expr;
// }


// std::unique_ptr<PrimaryExprStmt> new_primary_expr_stmt(PrimaryExprStmt::PrimaryExprType type) {
//     std::unique_ptr<PrimaryExprStmt> primary_expr = std::make_unique<PrimaryExprStmt>();
//     primary_expr->type = type;
//     return primary_expr;
// }

// std::unique_ptr<ValueStmt> new_value_stmt(ValueStmt::ValueType type) {
//     std::unique_ptr<ValueStmt> value = std::make_unique<ValueStmt>();
//     value->type = type;
//     return value;
// }

NumberStmt * new_number_stmt(char char_val);
NumberStmt * new_number_stmt(double real_val);
NumberStmt * new_number_stmt(long long int_val);

void fill_number_stmt(std::unique_ptr<NumberStmt> &num_value, long long int_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->int_val = int_val;
}

void fill_number_stmt(std::unique_ptr<NumberStmt> &num_value, double real_val){
    num_value->is_signed = true;
    num_value->is_real = true;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->real_val = real_val;
}

void fill_number_stmt(std::unique_ptr<NumberStmt> &num_value, char char_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = true;
    num_value->is_unsigned = false;
    num_value->char_val = char_val;
    LOG_DEBUG("DEBUG fill_number_stmt -> char_val: %c", char_val);
}

void fill_number_stmt(NumberStmt* num_value, long long int_val){
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->int_val = int_val;
    LOG_DEBUG("DEBUG fill_number_stmt -> int_val: %lld", int_val);
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

// std::unique_ptr<PrimaryExprStmt> bridge_primary_to_unary(std::unique_ptr<UnaryExprStmt> unary_expr){
//     std::unique_ptr<PrimaryExprStmt> primary_expr = std::make_unique<PrimaryExprStmt>();
//     primary_expr->type = PrimaryExprStmt::PrimaryExprType::Parentheses;
//     primary_expr->expr = std::make_unique<ExprStmt>();
//     primary_expr->expr->rel_expr = std::make_unique<RelExprStmt>();
//     primary_expr->expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
//     primary_expr->expr->rel_expr->add_expr = std::make_unique<AddExprStmt>();
//     primary_expr->expr->rel_expr->add_expr->type = AddExprStmt::AddExprType::NULL_TYPE;
//     primary_expr->expr->rel_expr->add_expr->mul_expr = std::make_unique<MulExprStmt>();
//     primary_expr->expr->rel_expr->add_expr->mul_expr->type = MulExprStmt::MulExprType::NULL_TYPE;
//     primary_expr->expr->rel_expr->add_expr->mul_expr->unary_expr = std::move(unary_expr);
//     return primary_expr;
// }


void syntax_error(YYLTYPE *llocp, const char *msg){
    LOG_ERROR("[Syntax Error] at line %d, column %d: %s", llocp->first_line, llocp->first_column, msg);
    exit(1);
}

enum class CurrentRule {
    ProgramStruct,
    ProgramHead,
    ProgramBody,
    IdList,
    ConstDeclarations,
    ConstDeclaration,
    ConstValue,
    VarDeclarations,
    VarDeclaration,
    Type,
    BasicType,
    PeriodList,
    SubprogramDeclarations,
    Subprogram,
    SubprogramHead,
    FormalParameter,
    ParameterList,
    Parameter,
    VarParameter,
    ValueParameter,
    SubprogramBody,
    CompoundStatement,
    StatementList,
    Statement,
    ProcedureCall,
    VariableList,
    Variable,
    IdVarpart,
    ExpressionList,
    ArrayIndexExpression,
    BracketExpressionList,
    Expression,
    SimpleExpression,
    Term,
    Factor,
};
static CurrentRule current_rule = CurrentRule::ProgramStruct;

void resetErrorFlag() {
        hadError = false; // 重置错误标志，为下一次解析准备
    }
int yyerror(YYLTYPE *llocp, const char *code_str, ProgramStmt ** program, yyscan_t scanner, const char *msg);


#line 307 "yacc_pascal.cpp"

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
  YYSYMBOL_BRACE_PAIR = 46,                /* BRACE_PAIR  */
  YYSYMBOL_BREAK = 47,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 48,                  /* CONTINUE  */
  YYSYMBOL_IDENTIFIER = 49,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER = 50,                   /* INTEGER  */
  YYSYMBOL_BOOLEAN = 51,                   /* BOOLEAN  */
  YYSYMBOL_REAL = 52,                      /* REAL  */
  YYSYMBOL_CHAR = 53,                      /* CHAR  */
  YYSYMBOL_STRING = 54,                    /* STRING  */
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* '.'  */
  YYSYMBOL_57_ = 57,                       /* '('  */
  YYSYMBOL_58_ = 58,                       /* ')'  */
  YYSYMBOL_59_ = 59,                       /* ','  */
  YYSYMBOL_60_ = 60,                       /* '='  */
  YYSYMBOL_61_ = 61,                       /* '+'  */
  YYSYMBOL_62_ = 62,                       /* '-'  */
  YYSYMBOL_63_ = 63,                       /* ':'  */
  YYSYMBOL_64_ = 64,                       /* '['  */
  YYSYMBOL_65_ = 65,                       /* ']'  */
  YYSYMBOL_66_ = 66,                       /* '<'  */
  YYSYMBOL_67_ = 67,                       /* '>'  */
  YYSYMBOL_68_ = 68,                       /* '*'  */
  YYSYMBOL_69_ = 69,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_programstruct = 71,             /* programstruct  */
  YYSYMBOL_program_head = 72,              /* program_head  */
  YYSYMBOL_program_body = 73,              /* program_body  */
  YYSYMBOL_idlist = 74,                    /* idlist  */
  YYSYMBOL_const_declarations = 75,        /* const_declarations  */
  YYSYMBOL_const_declaration = 76,         /* const_declaration  */
  YYSYMBOL_const_value = 77,               /* const_value  */
  YYSYMBOL_var_declarations = 78,          /* var_declarations  */
  YYSYMBOL_var_declaration = 79,           /* var_declaration  */
  YYSYMBOL_type = 80,                      /* type  */
  YYSYMBOL_basic_type = 81,                /* basic_type  */
  YYSYMBOL_period_list = 82,               /* period_list  */
  YYSYMBOL_subprogram_declarations = 83,   /* subprogram_declarations  */
  YYSYMBOL_subprogram = 84,                /* subprogram  */
  YYSYMBOL_subprogram_head = 85,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 86,          /* formal_parameter  */
  YYSYMBOL_parameter_list = 87,            /* parameter_list  */
  YYSYMBOL_parameter = 88,                 /* parameter  */
  YYSYMBOL_var_parameter = 89,             /* var_parameter  */
  YYSYMBOL_value_parameter = 90,           /* value_parameter  */
  YYSYMBOL_subprogram_body = 91,           /* subprogram_body  */
  YYSYMBOL_compound_statement = 92,        /* compound_statement  */
  YYSYMBOL_statement_list = 93,            /* statement_list  */
  YYSYMBOL_statement = 94,                 /* statement  */
  YYSYMBOL_variable_list = 95,             /* variable_list  */
  YYSYMBOL_variable = 96,                  /* variable  */
  YYSYMBOL_id_varpart = 97,                /* id_varpart  */
  YYSYMBOL_array_index_expression = 98,    /* array_index_expression  */
  YYSYMBOL_procedure_call = 99,            /* procedure_call  */
  YYSYMBOL_expression_list = 100,          /* expression_list  */
  YYSYMBOL_expression = 101,               /* expression  */
  YYSYMBOL_simple_expression = 102,        /* simple_expression  */
  YYSYMBOL_term = 103,                     /* term  */
  YYSYMBOL_factor = 104,                   /* factor  */
  YYSYMBOL_addop = 105,                    /* addop  */
  YYSYMBOL_relop = 106,                    /* relop  */
  YYSYMBOL_mulop = 107                     /* mulop  */
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
      57,    58,    68,    61,    59,    62,    56,    69,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    55,
      66,    60,    67,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   424,   424,   441,   450,   474,   510,   518,   535,   540,
     575,   584,   601,   609,   617,   625,   636,   647,   658,   667,
     687,   691,   713,   729,   751,   761,   781,   786,   791,   796,
     810,   820,   838,   842,   864,   882,   898,   923,   927,   944,
     948,   954,   968,   974,   988,  1002,  1021,  1049,  1070,  1075,
    1108,  1112,  1135,  1142,  1147,  1162,  1177,  1198,  1216,  1228,
    1242,  1250,  1267,  1275,  1289,  1325,  1329,  1339,  1360,  1368,
    1386,  1395,  1444,  1448,  1456,  1471,  1483,  1504,  1515,  1535,
    1546,  1566,  1606,  1649,  1664,  1678,  1691,  1702,  1723,  1731,
    1737,  1748,  1748,  1748,  1753,  1753,  1753,  1753,  1753,  1753,
    1753,  1758,  1758,  1758,  1758,  1758,  1758
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "CONST", "PROGRAM", "TYPE",
  "RECORD", "ARRAY", "OF", "VAR", "FUNCTION", "PROCEDURE", "BEGIN_TOKEN",
  "END", "IF", "THEN", "ELSE", "CASE", "WHILE", "REPEAT", "UNTIL", "FOR",
  "TO", "DOWNTO", "DO", "READ", "READLN", "WRITE", "WRITELN", "CHAR_KW",
  "INTEGER_KW", "REAL_KW", "BOOLEAN_KW", "NOT", "DIV", "MOD", "AND", "OR",
  "NE", "LE", "GE", "ASSIGNOP", "IN", "ORELSE", "ANDTHEN", "DOUBLE_DOT",
  "BRACE_PAIR", "BREAK", "CONTINUE", "IDENTIFIER", "INTEGER", "BOOLEAN",
  "REAL", "CHAR", "STRING", "';'", "'.'", "'('", "')'", "','", "'='",
  "'+'", "'-'", "':'", "'['", "']'", "'<'", "'>'", "'*'", "'/'", "$accept",
  "programstruct", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type",
  "period_list", "subprogram_declarations", "subprogram",
  "subprogram_head", "formal_parameter", "parameter_list", "parameter",
  "var_parameter", "value_parameter", "subprogram_body",
  "compound_statement", "statement_list", "statement", "variable_list",
  "variable", "id_varpart", "array_index_expression", "procedure_call",
  "expression_list", "expression", "simple_expression", "term", "factor",
  "addop", "relop", "mulop", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-66)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      20,    12,    65,    42,    62,  -109,    76,    79,    80,    81,
     126,  -109,    14,    98,   104,  -109,    79,  -109,  -109,   116,
      93,   118,   -43,   113,   101,  -109,  -109,  -109,  -109,  -109,
      43,    57,  -109,   109,   178,    79,   125,   132,    73,   127,
     128,  -109,  -109,  -109,  -109,  -109,    93,    89,  -109,  -109,
    -109,  -109,  -109,  -109,   -17,   129,   129,    99,    99,   139,
     130,   135,  -109,  -109,   -24,  -109,    -5,  -109,   160,  -109,
    -109,    76,  -109,   152,   178,     2,   140,  -109,    99,   -42,
    -109,  -109,  -109,  -109,    99,    99,    99,  -109,    -8,     7,
      70,  -109,    -3,   170,   157,    99,    99,    99,  -109,  -109,
      73,    99,   126,  -109,   167,   -47,  -109,    79,     8,    22,
    -109,  -109,  -109,   165,  -109,    99,    50,  -109,  -109,    73,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,    99,  -109,  -109,
    -109,    99,  -109,  -109,  -109,  -109,  -109,  -109,    99,    73,
      99,   149,    24,  -109,    67,   138,    75,   -10,   133,  -109,
     138,   202,   166,   168,   207,  -109,   165,     2,  -109,  -109,
      82,  -109,   201,     7,    70,  -109,  -109,   -13,  -109,   157,
    -109,    99,  -109,  -109,    99,  -109,  -109,   174,   165,  -109,
    -109,  -109,    73,    99,  -109,   138,  -109,   124,   171,  -109,
    -109,    36,    99,  -109,  -109,    73,  -109,  -109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      20,     6,     0,     0,     0,     2,     0,    32,     3,     0,
       0,     9,     0,     0,     0,     7,    12,    15,    18,    19,
       0,     0,    10,     0,     0,    21,     0,     0,    50,     0,
       0,     5,    13,    16,    14,    17,     0,     0,    29,    26,
      27,    28,    22,    24,     0,    37,    37,     0,     0,     0,
       0,     0,    60,    61,    70,    53,     0,    48,     0,    52,
      33,     8,    11,     0,     0,    39,     0,    35,     0,    65,
      81,    83,    82,    84,     0,     0,     0,    85,     0,    75,
      77,    79,     0,     0,     0,    72,    72,    72,    64,    47,
      50,     0,    20,    34,     0,     0,    23,     0,     0,     0,
      40,    42,    43,     0,    88,    72,     0,    89,    90,    50,
      95,    97,    99,   100,    94,    96,    98,     0,    93,    91,
      92,     0,   103,   104,   105,   106,   101,   102,     0,    50,
       0,    65,     0,    62,     0,    73,     0,     0,    73,    49,
      51,     0,     0,     0,     0,    44,     0,     0,    38,    36,
       0,    86,    55,    76,    78,    80,    54,     0,    58,     0,
      59,     0,    71,    66,     0,    46,    30,     0,     0,    45,
      41,    87,    50,     0,    63,    74,    67,     0,     0,    25,
      56,     0,     0,    68,    31,    50,    69,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,  -109,     3,   151,  -109,   177,   122,  -109,
     146,  -108,  -109,  -109,  -109,  -109,   169,  -109,    69,  -109,
     120,  -109,   -21,  -109,   -96,  -109,   -38,  -109,    37,  -109,
      27,   -56,   103,    97,   -72,  -109,  -109,  -109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     9,   108,    10,    14,    32,    17,    23,
      52,    53,   105,    24,    39,    40,    76,   109,   110,   111,
     112,   103,    65,    66,    67,   142,    87,    98,   186,    69,
     144,   145,    89,    90,    91,   131,   127,   138
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    88,    92,    41,   149,   159,   114,   119,    99,   183,
      12,   107,   153,   117,   118,   115,    19,   -65,   154,    22,
      34,   139,    97,   162,     1,   120,   121,   122,   116,   123,
     120,   121,   122,    96,   123,   120,   121,   122,    54,   123,
      97,   148,    19,   166,   128,   150,    74,   124,   179,   171,
     100,    11,   124,   125,   126,   173,   143,   124,   125,   126,
     195,     4,    68,   125,   126,     5,   165,    19,   129,   130,
     189,   156,    18,    19,   120,   121,   122,   157,   123,     8,
     158,    68,   168,   169,   167,    38,   190,    57,   120,   121,
     122,    58,   123,    42,    59,    43,   124,     6,    60,   197,
      61,    68,   125,   126,   132,   133,   134,    44,   161,    45,
     124,    36,    37,    38,   135,   185,   125,   126,   187,     7,
      62,    63,    64,   146,   147,   170,   171,   191,    11,    13,
     175,   184,    78,   172,   171,    16,   187,    15,   136,   137,
     181,   171,   160,    26,    68,    27,    28,    29,    79,    80,
      81,    82,    83,    73,    30,    31,    84,    68,    20,    21,
      85,    86,   120,   121,   122,    25,   123,    33,    35,    46,
     192,   120,   121,   122,    55,   123,   120,   121,   122,   174,
     123,    56,    70,    71,   124,    47,    75,    94,    93,   193,
     125,   126,    95,   124,    48,    49,    50,    51,   124,   125,
     126,   101,   104,   113,   125,   126,   141,    48,    49,    50,
      51,   140,   152,    97,    38,   178,   176,   182,   177,   188,
     106,   194,   102,    72,   151,    77,   180,   155,   164,   196,
     163
};

static const yytype_uint8 yycheck[] =
{
      38,    57,    58,    24,   100,   113,    78,    15,    13,    22,
       7,     9,    59,    85,    86,    57,    59,    41,    65,    16,
      63,    24,    64,   119,     4,    38,    39,    40,    84,    42,
      38,    39,    40,    57,    42,    38,    39,    40,    35,    42,
      64,    97,    59,   139,    37,   101,    63,    60,   156,    59,
      55,    49,    60,    66,    67,    65,    94,    60,    66,    67,
      24,    49,   100,    66,    67,     0,   138,    59,    61,    62,
     178,    63,    58,    59,    38,    39,    40,    55,    42,     3,
      58,   119,    58,    59,   140,    12,   182,    14,    38,    39,
      40,    18,    42,    50,    21,    52,    60,    55,    25,   195,
      27,   139,    66,    67,    34,    35,    36,    50,    58,    52,
      60,    10,    11,    12,    44,   171,    66,    67,   174,    57,
      47,    48,    49,    96,    97,    58,    59,   183,    49,    49,
     151,   169,    33,    58,    59,     9,   192,    56,    68,    69,
      58,    59,   115,    50,   182,    52,    53,    54,    49,    50,
      51,    52,    53,    64,    61,    62,    57,   195,    60,    55,
      61,    62,    38,    39,    40,    49,    42,    49,    55,    60,
      46,    38,    39,    40,    49,    42,    38,    39,    40,    46,
      42,    49,    55,    55,    60,     7,    57,    57,    49,    65,
      66,    67,    57,    60,    29,    30,    31,    32,    60,    66,
      67,    41,    50,    63,    66,    67,    49,    29,    30,    31,
      32,    41,    45,    64,    12,     8,    50,    16,    50,    45,
      74,    50,    71,    46,   102,    56,   157,   107,   131,   192,
     127
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    71,    72,    49,     0,    55,    57,     3,    73,
      75,    49,    74,    49,    76,    56,     9,    78,    58,    59,
      60,    55,    74,    79,    83,    49,    50,    52,    53,    54,
      61,    62,    77,    49,    63,    55,    10,    11,    12,    84,
      85,    92,    50,    52,    50,    52,    60,     7,    29,    30,
      31,    32,    80,    81,    74,    49,    49,    14,    18,    21,
      25,    27,    47,    48,    49,    92,    93,    94,    96,    99,
      55,    55,    77,    64,    63,    57,    86,    86,    33,    49,
      50,    51,    52,    53,    57,    61,    62,    96,   101,   102,
     103,   104,   101,    49,    57,    57,    57,    64,    97,    13,
      55,    41,    75,    91,    50,    82,    80,     9,    74,    87,
      88,    89,    90,    63,   104,    57,   101,   104,   104,    15,
      38,    39,    40,    42,    60,    66,    67,   106,    37,    61,
      62,   105,    34,    35,    36,    44,    68,    69,   107,    24,
      41,    49,    95,    96,   100,   101,   100,   100,   101,    94,
     101,    78,    45,    59,    65,    90,    63,    55,    58,    81,
     100,    58,    94,   102,   103,   104,    94,   101,    58,    59,
      58,    59,    58,    65,    46,    92,    50,    50,     8,    81,
      88,    58,    16,    22,    96,   101,    98,   101,    45,    81,
      94,   101,    46,    65,    50,    24,    98,    94
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    74,    74,    75,    75,
      76,    76,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    81,    81,
      82,    82,    83,    83,    84,    85,    85,    86,    86,    87,
      87,    87,    88,    88,    89,    90,    91,    92,    93,    93,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    97,    97,    97,    98,    98,
      99,    99,   100,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     1,     2,     2,     1,     2,     2,     1,     1,
       0,     3,     3,     5,     1,     6,     1,     1,     1,     1,
       3,     5,     0,     3,     3,     3,     5,     0,     3,     0,
       1,     3,     1,     1,     2,     3,     3,     3,     1,     3,
       0,     3,     1,     1,     4,     4,     6,     8,     4,     4,
       1,     1,     1,     3,     2,     0,     3,     4,     2,     3,
       1,     4,     0,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     3,     4,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}

/* The location of the lookahead of this context.  */
static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx)
{
  return yyctx->yylloc;
}

/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx, const char * code_str, ProgramStmt ** program, void * scanner);

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
  switch (yykind)
    {
    case YYSYMBOL_IDENTIFIER: /* IDENTIFIER  */
#line 409 "yacc_pascal.y"
            { free(((*yyvaluep).string)); }
#line 1453 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_INTEGER: /* INTEGER  */
#line 408 "yacc_pascal.y"
            {}
#line 1459 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_BOOLEAN: /* BOOLEAN  */
#line 408 "yacc_pascal.y"
            {}
#line 1465 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_REAL: /* REAL  */
#line 409 "yacc_pascal.y"
            { free(((*yyvaluep).real)); }
#line 1471 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 408 "yacc_pascal.y"
            {}
#line 1477 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 409 "yacc_pascal.y"
            { free(((*yyvaluep).string)); }
#line 1483 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_programstruct: /* programstruct  */
#line 408 "yacc_pascal.y"
            {}
#line 1489 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_program_head: /* program_head  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).program_head); }
#line 1495 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_program_body: /* program_body  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).program_body); }
#line 1501 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_idlist: /* idlist  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).id_list); }
#line 1507 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_const_declarations: /* const_declarations  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).const_decls); }
#line 1513 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_const_declaration: /* const_declaration  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).kv_pair_list); }
#line 1519 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_const_value: /* const_value  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).value); }
#line 1525 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_var_declarations: /* var_declarations  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decls); }
#line 1531 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decls); }
#line 1537 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_type: /* type  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decl); }
#line 1543 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_basic_type: /* basic_type  */
#line 408 "yacc_pascal.y"
            {}
#line 1549 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_period_list: /* period_list  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).period_list); }
#line 1555 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_subprogram_declarations: /* subprogram_declarations  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).func_decl_list); }
#line 1561 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_subprogram: /* subprogram  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).func_decl); }
#line 1567 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_subprogram_head: /* subprogram_head  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).func_head); }
#line 1573 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_formal_parameter: /* formal_parameter  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decls); }
#line 1579 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_parameter_list: /* parameter_list  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decls); }
#line 1585 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_parameter: /* parameter  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decl); }
#line 1591 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_var_parameter: /* var_parameter  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decl); }
#line 1597 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_value_parameter: /* value_parameter  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).var_decl); }
#line 1603 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_subprogram_body: /* subprogram_body  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).func_body); }
#line 1609 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).stmt_list); }
#line 1615 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).stmt_list); }
#line 1621 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).stmt_list); }
#line 1627 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_variable_list: /* variable_list  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).lval_list); }
#line 1633 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).lval); }
#line 1639 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_id_varpart: /* id_varpart  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).expr_list); }
#line 1645 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_array_index_expression: /* array_index_expression  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).expr_list); }
#line 1651 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_procedure_call: /* procedure_call  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).func_call_stmt); }
#line 1657 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_expression_list: /* expression_list  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).expr_list); }
#line 1663 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).expr); }
#line 1669 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).add_expr); }
#line 1675 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_term: /* term  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).mul_expr); }
#line 1681 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 410 "yacc_pascal.y"
            { delete ((*yyvaluep).unary_expr); }
#line 1687 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_addop: /* addop  */
#line 408 "yacc_pascal.y"
            {}
#line 1693 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_relop: /* relop  */
#line 408 "yacc_pascal.y"
            {}
#line 1699 "yacc_pascal.cpp"
        break;

    case YYSYMBOL_mulop: /* mulop  */
#line 408 "yacc_pascal.y"
            {}
#line 1705 "yacc_pascal.cpp"
        break;

      default:
        break;
    }
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



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */


/* User initialization code.  */
#line 302 "yacc_pascal.y"
{
    *program = nullptr;
}

#line 1804 "yacc_pascal.cpp"

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
#line 425 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProgramStruct;
        ProgramStmt * program_struct = new ProgramStmt();
        program_struct->head = std::unique_ptr<ProgramHeadStmt>((yyvsp[-3].program_head));
        program_struct->body = std::unique_ptr<ProgramBodyStmt>((yyvsp[-1].program_body));
        LOG_DEBUG("DEBUG programstruct -> program_head ';' program_body '.'");
        *program = program_struct;
        (yyval.program_struct) = nullptr; // 防止报错
    }
#line 2025 "yacc_pascal.cpp"
    break;

  case 3: /* program_head: PROGRAM IDENTIFIER '(' idlist ')'  */
#line 442 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProgramHead;
        (yyval.program_head) = new ProgramHeadStmt();
        (yyval.program_head)->id_list = *(yyvsp[-1].id_list);
        delete (yyvsp[-1].id_list);
        free((yyvsp[-3].string));
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER '(' idlist ')'");
    }
#line 2038 "yacc_pascal.cpp"
    break;

  case 4: /* program_head: PROGRAM IDENTIFIER  */
#line 451 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProgramHead;
        (yyval.program_head) = new ProgramHeadStmt();
        (yyval.program_head)->id_list.emplace_back(std::string((yyvsp[0].string)));
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER");
        free((yyvsp[0].string));
    }
#line 2050 "yacc_pascal.cpp"
    break;

  case 5: /* program_body: const_declarations var_declarations subprogram_declarations compound_statement  */
#line 475 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProgramBody;
        ProgramBodyStmt* program_body = new ProgramBodyStmt();
        if((yyvsp[-3].const_decls) != nullptr) {program_body->const_decl = std::unique_ptr<ConstDeclStmt>((yyvsp[-3].const_decls));}
        if((yyvsp[-2].var_decls) != nullptr){
            for(auto var_decl : *(yyvsp[-2].var_decls)){
                program_body->var_decl.emplace_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete (yyvsp[-2].var_decls);
        }
        if((yyvsp[-1].func_decl_list) != nullptr){
            for(auto func_decl : *(yyvsp[-1].func_decl_list)){
                program_body->func_decl.emplace_back(std::unique_ptr<FuncDeclStmt>(func_decl));
            }
            delete (yyvsp[-1].func_decl_list);
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                program_body->comp_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        (yyval.program_body) = program_body;
        LOG_DEBUG("DEBUG program_body -> const_declarations var_declarations subprogram_declarations compound_statement");
    }
#line 2080 "yacc_pascal.cpp"
    break;

  case 6: /* idlist: IDENTIFIER  */
#line 511 "yacc_pascal.y"
    {
        current_rule = CurrentRule::IdList;
        (yyval.id_list) = new std::vector<std::string>();
        (yyval.id_list)->emplace_back(std::string((yyvsp[0].string)));
        LOG_DEBUG("DEBUG idlist -> IDENTIFIER");
        free((yyvsp[0].string));
    }
#line 2092 "yacc_pascal.cpp"
    break;

  case 7: /* idlist: idlist ',' IDENTIFIER  */
#line 519 "yacc_pascal.y"
    {
        current_rule = CurrentRule::IdList;
        (yyvsp[-2].id_list)->emplace_back(std::string((yyvsp[0].string)));
        (yyval.id_list) = (yyvsp[-2].id_list);
        LOG_DEBUG("DEBUG idlist -> idlist ',' IDENTIFIER");
        free((yyvsp[0].string));
    }
#line 2104 "yacc_pascal.cpp"
    break;

  case 8: /* const_declarations: %empty  */
#line 535 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ConstDeclarations;
        (yyval.const_decls) = nullptr;
        LOG_DEBUG("DEBUG const_declarations -> empty");
    }
#line 2114 "yacc_pascal.cpp"
    break;

  case 9: /* const_declarations: CONST const_declaration ';'  */
#line 541 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ConstDeclarations;
        ConstDeclStmt * const_decls = new ConstDeclStmt();
        for(auto kv_pair : *(yyvsp[-1].kv_pair_list)){
            const_decls->pairs.emplace_back(std::make_pair(kv_pair->first, kv_pair->second));
            delete kv_pair;
        }
        // 疑似内存泄漏
        delete (yyvsp[-1].kv_pair_list);
        (yyval.const_decls) = const_decls;
        for(auto &t: const_decls->pairs){
            LOG_INFO("Get Const Type:%d, pointer %p", t.second->type, t.second.get());
            if(t.second->str) {
                LOG_INFO("Get string:%s",t.second->str->val.c_str());
            }
        }
        LOG_DEBUG("DEBUG const_declarations -> CONST const_declaration ';' const_declarations");
    }
#line 2137 "yacc_pascal.cpp"
    break;

  case 10: /* const_declaration: IDENTIFIER '=' const_value  */
#line 576 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ConstDeclaration;
        std::vector<std::pair<std::string, ValueStmt *> *> * const_decls = new std::vector<std::pair<std::string, ValueStmt *> *>();
        std::pair<std::string, ValueStmt *> * kv_pair = new std::pair<std::string, ValueStmt *>((yyvsp[-2].string), (yyvsp[0].value));
        const_decls->emplace_back(kv_pair);
        free((yyvsp[-2].string));
        (yyval.kv_pair_list) = const_decls;
    }
#line 2150 "yacc_pascal.cpp"
    break;

  case 11: /* const_declaration: const_declaration ';' IDENTIFIER '=' const_value  */
#line 585 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ConstDeclaration;
        (yyvsp[-4].kv_pair_list)->emplace_back(new std::pair<std::string, ValueStmt *>((yyvsp[-2].string), (yyvsp[0].value)));
        free((yyvsp[-2].string));
        (yyval.kv_pair_list) = (yyvsp[-4].kv_pair_list); // 不需要删除
    }
#line 2161 "yacc_pascal.cpp"
    break;

  case 12: /* const_value: INTEGER  */
#line 602 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, (yyvsp[0].number));
        (yyval.value) = num_value;
    }
#line 2173 "yacc_pascal.cpp"
    break;

  case 13: /* const_value: '+' INTEGER  */
#line 610 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, (yyvsp[0].number));
        (yyval.value) = num_value;
    }
#line 2185 "yacc_pascal.cpp"
    break;

  case 14: /* const_value: '-' INTEGER  */
#line 618 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, ((yyvsp[0].number)) * -1);
        (yyval.value) = num_value;
    }
#line 2197 "yacc_pascal.cpp"
    break;

  case 15: /* const_value: REAL  */
#line 626 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof((yyvsp[0].real));
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string((yyvsp[0].real));
        free((yyvsp[0].real));
        (yyval.value) = num_value;
    }
#line 2212 "yacc_pascal.cpp"
    break;

  case 16: /* const_value: '+' REAL  */
#line 637 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof((yyvsp[0].real));
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string((yyvsp[0].real));
        free((yyvsp[0].real));
        (yyval.value) = num_value;
    }
#line 2227 "yacc_pascal.cpp"
    break;

  case 17: /* const_value: '-' REAL  */
#line 648 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof((yyvsp[0].real));
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string((yyvsp[0].real));
        free((yyvsp[0].real));
        (yyval.value) = num_value;
    }
#line 2242 "yacc_pascal.cpp"
    break;

  case 18: /* const_value: CHAR  */
#line 659 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, (yyvsp[0].charactor));
        LOG_DEBUG("DEBUG const_value -> CHAR, value: %c", (yyvsp[0].charactor));
        (yyval.value) = num_value;
    }
#line 2255 "yacc_pascal.cpp"
    break;

  case 19: /* const_value: STRING  */
#line 668 "yacc_pascal.y"
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Str;
        num_value->str = std::make_unique<StrStmt>();
        num_value->str->val = std::string((yyvsp[0].string)).substr(1, std::string((yyvsp[0].string)).length() - 2);
        free((yyvsp[0].string));
        (yyval.value) = num_value;
    }
#line 2268 "yacc_pascal.cpp"
    break;

  case 20: /* var_declarations: %empty  */
#line 687 "yacc_pascal.y"
    {
        (yyval.var_decls) = nullptr;
        LOG_DEBUG("DEBUG var_declarations -> empty");
    }
#line 2277 "yacc_pascal.cpp"
    break;

  case 21: /* var_declarations: VAR var_declaration ';'  */
#line 692 "yacc_pascal.y"
    {
        current_rule = CurrentRule::VarDeclarations;
        (yyval.var_decls) = (yyvsp[-1].var_decls);
        LOG_DEBUG("DEBUG var_declarations -> VAR var_declaration ';'");
    }
#line 2287 "yacc_pascal.cpp"
    break;

  case 22: /* var_declaration: idlist ':' type  */
#line 714 "yacc_pascal.y"
    {
        current_rule = CurrentRule::VarDeclaration;
        std::vector<VarDeclStmt *> * var_decls = new std::vector<VarDeclStmt *>();
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
        // deal with type
        var_decl->basic_type = (yyvsp[0].var_decl)->basic_type;
        var_decl->data_type = (yyvsp[0].var_decl)->data_type;
        var_decl->array_range = std::move((yyvsp[0].var_decl)->array_range);
        delete (yyvsp[-2].id_list);
        delete (yyvsp[0].var_decl);
        var_decls->emplace_back(var_decl);
        (yyval.var_decls) = var_decls;
        LOG_DEBUG("DEBUG var_declaration -> idlist ':' type");
    }
#line 2307 "yacc_pascal.cpp"
    break;

  case 23: /* var_declaration: var_declaration ';' idlist ':' type  */
#line 730 "yacc_pascal.y"
    {
        current_rule = CurrentRule::VarDeclaration;
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
        // deal with type
        var_decl->basic_type = (yyvsp[0].var_decl)->basic_type;
        var_decl->data_type = (yyvsp[0].var_decl)->data_type;
        var_decl->array_range = std::move((yyvsp[0].var_decl)->array_range);
        delete (yyvsp[-2].id_list);
        delete (yyvsp[0].var_decl);
        (yyvsp[-4].var_decls)->emplace_back(var_decl);
        (yyval.var_decls) = (yyvsp[-4].var_decls);
        LOG_DEBUG("DEBUG var_declaration -> var_declaration ';' idlist ':' type");
    }
#line 2326 "yacc_pascal.cpp"
    break;

  case 24: /* type: basic_type  */
#line 752 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Type;
        VarDeclStmt * type_stmt = new VarDeclStmt();
        // TODO 处理type_size
        type_stmt->data_type = DataType::BasicType;
        type_stmt->basic_type = (yyvsp[0].basic_type);
        (yyval.var_decl) = type_stmt;
        LOG_DEBUG("DEBUG type -> basic_type");
    }
#line 2340 "yacc_pascal.cpp"
    break;

  case 25: /* type: ARRAY '[' period_list ']' OF basic_type  */
#line 762 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Type;
        VarDeclStmt * type_stmt = new VarDeclStmt();
        type_stmt->data_type = DataType::ArrayType;
        type_stmt->basic_type = (yyvsp[0].basic_type);
        for(auto period : *(yyvsp[-3].period_list)){
            type_stmt->array_range.emplace_back(std::unique_ptr<PeriodStmt>(period));
        }
        delete (yyvsp[-3].period_list);
        (yyval.var_decl) = type_stmt;
        LOG_DEBUG("DEBUG type -> ARRAY '[' period_list ']' OF basic_type");
    }
#line 2357 "yacc_pascal.cpp"
    break;

  case 26: /* basic_type: INTEGER_KW  */
#line 782 "yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::INT;
            LOG_DEBUG("DEBUG basic_type -> INTEGER_KW");
        }
#line 2366 "yacc_pascal.cpp"
    break;

  case 27: /* basic_type: REAL_KW  */
#line 787 "yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::REAL;
            LOG_DEBUG("DEBUG basic_type -> REAL_KW");
        }
#line 2375 "yacc_pascal.cpp"
    break;

  case 28: /* basic_type: BOOLEAN_KW  */
#line 792 "yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::BOOLEAN;
            LOG_DEBUG("DEBUG basic_type -> BOOLEAN_KW");
        }
#line 2384 "yacc_pascal.cpp"
    break;

  case 29: /* basic_type: CHAR_KW  */
#line 797 "yacc_pascal.y"
        {
            (yyval.basic_type) = BasicType::CHAR;
            LOG_DEBUG("DEBUG basic_type -> CHAR_KW");
        }
#line 2393 "yacc_pascal.cpp"
    break;

  case 30: /* period_list: INTEGER DOUBLE_DOT INTEGER  */
#line 811 "yacc_pascal.y"
        {
            (yyval.period_list) = new std::vector<PeriodStmt *>();
            PeriodStmt * period = new PeriodStmt();
            period->begin = (yyvsp[-2].number);
            period->end = (yyvsp[0].number);
            (yyval.period_list)->emplace_back(period);
            // debug
            LOG_DEBUG("DEBUG period_list -> INTEGER '..' INTEGER");
        }
#line 2407 "yacc_pascal.cpp"
    break;

  case 31: /* period_list: period_list ',' INTEGER DOUBLE_DOT INTEGER  */
#line 821 "yacc_pascal.y"
        {
            PeriodStmt * period = new PeriodStmt();
            period->begin = (yyvsp[-2].number);
            period->end = (yyvsp[0].number);
            (yyvsp[-4].period_list)->emplace_back(period);
            (yyval.period_list) = (yyvsp[-4].period_list);
            // debug
            LOG_DEBUG("DEBUG period_list -> period_list ',' INTEGER '..' INTEGER");
        }
#line 2421 "yacc_pascal.cpp"
    break;

  case 32: /* subprogram_declarations: %empty  */
#line 838 "yacc_pascal.y"
        {
            (yyval.func_decl_list) = nullptr;
            LOG_DEBUG("DEBUG subprogram_declarations -> empty");
        }
#line 2430 "yacc_pascal.cpp"
    break;

  case 33: /* subprogram_declarations: subprogram_declarations subprogram ';'  */
#line 843 "yacc_pascal.y"
        {
            current_rule = CurrentRule::SubprogramDeclarations;
            if((yyvsp[-2].func_decl_list) == nullptr){
                std::vector<FuncDeclStmt *> * func_decl_list = new std::vector<FuncDeclStmt *>();
                func_decl_list->emplace_back((yyvsp[-1].func_decl));    
                (yyval.func_decl_list) = func_decl_list;
            }else{
                (yyvsp[-2].func_decl_list)->emplace_back((yyvsp[-1].func_decl));
                (yyval.func_decl_list) = (yyvsp[-2].func_decl_list);
            }
            LOG_DEBUG("DEBUG subprogram_declarations -> subprogram_declarations subprogram ';'");
        }
#line 2447 "yacc_pascal.cpp"
    break;

  case 34: /* subprogram: subprogram_head ';' subprogram_body  */
#line 865 "yacc_pascal.y"
        {
            current_rule = CurrentRule::Subprogram;
            FuncDeclStmt * subprogram = new FuncDeclStmt();
            subprogram->header = std::unique_ptr<FuncHeadDeclStmt>((yyvsp[-2].func_head));
            subprogram->body = std::unique_ptr<FuncBodyDeclStmt>((yyvsp[0].func_body));
            (yyval.func_decl) = subprogram;
            LOG_DEBUG("DEBUG subprogram -> subprogram_head ';' subprogram_body");
        }
#line 2460 "yacc_pascal.cpp"
    break;

  case 35: /* subprogram_head: PROCEDURE IDENTIFIER formal_parameter  */
#line 883 "yacc_pascal.y"
        {
            current_rule = CurrentRule::SubprogramHead;
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string((yyvsp[-1].string));
            sub_head->ret_type = BasicType::VOID;
            if((yyvsp[0].var_decls) != nullptr){
                for(auto formal_parameter : *(yyvsp[0].var_decls)){
                    sub_head->args.emplace_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete (yyvsp[0].var_decls);
            }
            (yyval.func_head) = sub_head;
            free((yyvsp[-1].string));
            LOG_DEBUG("DEBUG subprogram_head -> PROGRAM IDENTIFIER formal_parameter");
        }
#line 2480 "yacc_pascal.cpp"
    break;

  case 36: /* subprogram_head: FUNCTION IDENTIFIER formal_parameter ':' basic_type  */
#line 899 "yacc_pascal.y"
        {
            current_rule = CurrentRule::SubprogramHead;
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string((yyvsp[-3].string));
            sub_head->ret_type = (yyvsp[0].basic_type);
            if((yyvsp[-2].var_decls) != nullptr){
                for(auto formal_parameter : *(yyvsp[-2].var_decls)){
                    sub_head->args.emplace_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete (yyvsp[-2].var_decls);
            }
            (yyval.func_head) = sub_head;
            free((yyvsp[-3].string));
            LOG_DEBUG("DEBUG subprogram_head -> FUNCTION IDENTIFIER formal_parameter ':' basic_type");
        }
#line 2500 "yacc_pascal.cpp"
    break;

  case 37: /* formal_parameter: %empty  */
#line 923 "yacc_pascal.y"
        {
            (yyval.var_decls) = nullptr;
            LOG_DEBUG("DEBUG formal_parameter -> empty");
        }
#line 2509 "yacc_pascal.cpp"
    break;

  case 38: /* formal_parameter: '(' parameter_list ')'  */
#line 928 "yacc_pascal.y"
        {
            current_rule = CurrentRule::FormalParameter;
            (yyval.var_decls) = (yyvsp[-1].var_decls);
            LOG_DEBUG("DEBUG formal_parameter -> '(' parameter_list ')'");
        }
#line 2519 "yacc_pascal.cpp"
    break;

  case 39: /* parameter_list: %empty  */
#line 944 "yacc_pascal.y"
    {
        (yyval.var_decls) = nullptr;
        LOG_DEBUG("DEBUG parameter_list -> empty");
    }
#line 2528 "yacc_pascal.cpp"
    break;

  case 40: /* parameter_list: parameter  */
#line 949 "yacc_pascal.y"
        {
            (yyval.var_decls) = new std::vector<VarDeclStmt *>();
            (yyval.var_decls)->emplace_back((yyvsp[0].var_decl));
            LOG_DEBUG("DEBUG parameter_list -> parameter");
        }
#line 2538 "yacc_pascal.cpp"
    break;

  case 41: /* parameter_list: parameter_list ';' parameter  */
#line 955 "yacc_pascal.y"
        {
            (yyvsp[-2].var_decls)->emplace_back((yyvsp[0].var_decl));
            (yyval.var_decls) = (yyvsp[-2].var_decls);
            LOG_DEBUG("DEBUG parameter_list -> parameter_list ';' parameter");
        }
#line 2548 "yacc_pascal.cpp"
    break;

  case 42: /* parameter: var_parameter  */
#line 969 "yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            (yyval.var_decl)->is_var = true;
            LOG_DEBUG("DEBUG parameter -> var_parameter");
        }
#line 2558 "yacc_pascal.cpp"
    break;

  case 43: /* parameter: value_parameter  */
#line 975 "yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            (yyval.var_decl)->is_var = false;
            LOG_DEBUG("DEBUG parameter -> value_parameter");
        }
#line 2568 "yacc_pascal.cpp"
    break;

  case 44: /* var_parameter: VAR value_parameter  */
#line 989 "yacc_pascal.y"
        {
            (yyval.var_decl) = (yyvsp[0].var_decl);
            LOG_DEBUG("DEBUG var_parameter -> VAR value_parameter");
        }
#line 2577 "yacc_pascal.cpp"
    break;

  case 45: /* value_parameter: idlist ':' basic_type  */
#line 1003 "yacc_pascal.y"
        {
            VarDeclStmt* var_decl = new VarDeclStmt();
            var_decl->id.insert(var_decl->id.end(), (yyvsp[-2].id_list)->begin(), (yyvsp[-2].id_list)->end());
            var_decl->data_type = DataType::BasicType;
            var_decl-> basic_type = (yyvsp[0].basic_type);
            var_decl->is_var = false;
            // 疑似内存泄漏
            delete (yyvsp[-2].id_list);
            (yyval.var_decl) = var_decl;
            LOG_DEBUG("DEBUG value_parameter -> idlist ':' basic_type");
        }
#line 2593 "yacc_pascal.cpp"
    break;

  case 46: /* subprogram_body: const_declarations var_declarations compound_statement  */
#line 1022 "yacc_pascal.y"
    {
        current_rule = CurrentRule::SubprogramBody;
        FuncBodyDeclStmt * func_body = new FuncBodyDeclStmt();
        if((yyvsp[-2].const_decls) != nullptr) func_body->const_decl = std::unique_ptr<ConstDeclStmt>((yyvsp[-2].const_decls));
        if((yyvsp[-1].var_decls) != nullptr){
            for(auto var_decl : *(yyvsp[-1].var_decls)){
                func_body->var_decl.emplace_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete (yyvsp[-1].var_decls);
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                func_body->comp_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        (yyval.func_body) = func_body;
        LOG_DEBUG("DEBUG subprogram_body -> const_declarations var_declarations compound_statement");
    }
#line 2617 "yacc_pascal.cpp"
    break;

  case 47: /* compound_statement: BEGIN_TOKEN statement_list END  */
#line 1050 "yacc_pascal.y"
    {
        current_rule = CurrentRule::CompoundStatement;
        (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        LOG_DEBUG("DEBUG compound_statement -> BEGIN_TOKEN statement_list END");
    }
#line 2627 "yacc_pascal.cpp"
    break;

  case 48: /* statement_list: statement  */
#line 1071 "yacc_pascal.y"
    {
        (yyval.stmt_list) = (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement_list -> statement");
    }
#line 2636 "yacc_pascal.cpp"
    break;

  case 49: /* statement_list: statement_list ';' statement  */
#line 1076 "yacc_pascal.y"
    {
        // copy the vector
        current_rule = CurrentRule::StatementList;
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                (yyvsp[-2].stmt_list)->emplace_back(stmt);
            }
        }
        (yyval.stmt_list) = (yyvsp[-2].stmt_list);
        delete (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement_list -> statement_list ';' statement");
    }
#line 2653 "yacc_pascal.cpp"
    break;

  case 50: /* statement: %empty  */
#line 1108 "yacc_pascal.y"
    {
        (yyval.stmt_list) = nullptr;
        LOG_DEBUG("DEBUG statement -> empty");
    }
#line 2662 "yacc_pascal.cpp"
    break;

  case 51: /* statement: variable ASSIGNOP expression  */
#line 1113 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::unique_ptr<LValStmt>((yyvsp[-2].lval));
        assign_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[0].expr));
        stmt_list->emplace_back(assign_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> variable ASSIGNOP expression");
    }
#line 2676 "yacc_pascal.cpp"
    break;

  case 52: /* statement: procedure_call  */
#line 1136 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        stmt_list->emplace_back((yyvsp[0].func_call_stmt));
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> procedure_call");
    }
#line 2687 "yacc_pascal.cpp"
    break;

  case 53: /* statement: compound_statement  */
#line 1143 "yacc_pascal.y"
    {
        (yyval.stmt_list) = (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement -> compound_statement");
    }
#line 2696 "yacc_pascal.cpp"
    break;

  case 54: /* statement: WHILE expression DO statement  */
#line 1148 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WhileStmt * while_stmt = new WhileStmt();
        while_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[-2].expr));
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                while_stmt->stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete (yyvsp[0].stmt_list);
        }
        stmt_list->emplace_back(while_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> WHILE expression DO statement");
    }
#line 2715 "yacc_pascal.cpp"
    break;

  case 55: /* statement: IF expression THEN statement  */
#line 1163 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[-2].expr));
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                if_stmt->true_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        delete (yyvsp[0].stmt_list);
        stmt_list->emplace_back(if_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement");
    }
#line 2734 "yacc_pascal.cpp"
    break;

  case 56: /* statement: IF expression THEN statement ELSE statement  */
#line 1178 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>((yyvsp[-4].expr));
        if((yyvsp[-2].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[-2].stmt_list)){
                if_stmt->true_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                if_stmt->false_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        stmt_list->emplace_back(if_stmt);
        (yyval.stmt_list) = stmt_list;
        delete (yyvsp[-2].stmt_list);
        delete (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement ELSE statement");
    }
#line 2759 "yacc_pascal.cpp"
    break;

  case 57: /* statement: FOR IDENTIFIER ASSIGNOP expression TO expression DO statement  */
#line 1199 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ForStmt * for_stmt = new ForStmt();
        for_stmt->id = std::string((yyvsp[-6].string));
        for_stmt->begin = std::unique_ptr<ExprStmt>((yyvsp[-4].expr));
        for_stmt->end = std::unique_ptr<ExprStmt>((yyvsp[-2].expr));
        if((yyvsp[0].stmt_list) != nullptr){
            for(auto stmt : *(yyvsp[0].stmt_list)){
                for_stmt->stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        stmt_list->emplace_back(for_stmt);
        (yyval.stmt_list) = stmt_list;
        free((yyvsp[-6].string));
        delete (yyvsp[0].stmt_list);
        LOG_DEBUG("DEBUG statement -> FOR IDENTIFIER ASSIGNOP expression TO expression DO statement");
    }
#line 2781 "yacc_pascal.cpp"
    break;

  case 58: /* statement: READ '(' variable_list ')'  */
#line 1217 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ReadFuncStmt * read_stmt = new ReadFuncStmt();
        for(auto lval : *(yyvsp[-1].lval_list)){
            read_stmt->lval.emplace_back(std::unique_ptr<LValStmt>(lval));
        }
        delete (yyvsp[-1].lval_list);
        stmt_list->emplace_back(read_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> READ '(' variable_list ')'");
    }
#line 2797 "yacc_pascal.cpp"
    break;

  case 59: /* statement: WRITE '(' expression_list ')'  */
#line 1229 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WriteFuncStmt * write_stmt = new WriteFuncStmt();
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                write_stmt->expr.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
        }
        stmt_list->emplace_back(write_stmt);
        (yyval.stmt_list) = stmt_list;
        delete (yyvsp[-1].expr_list);
        LOG_DEBUG("DEBUG statement -> WRITE '(' expression_list ')'");
    }
#line 2815 "yacc_pascal.cpp"
    break;

  case 60: /* statement: BREAK  */
#line 1243 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        BreakStmt * break_stmt = new BreakStmt();
        stmt_list->emplace_back(break_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> BREAK");
    }
#line 2827 "yacc_pascal.cpp"
    break;

  case 61: /* statement: CONTINUE  */
#line 1251 "yacc_pascal.y"
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ContinueStmt * continue_stmt = new ContinueStmt();
        stmt_list->emplace_back(continue_stmt);
        (yyval.stmt_list) = stmt_list;
        LOG_DEBUG("DEBUG statement -> CONTINUE");
    }
#line 2839 "yacc_pascal.cpp"
    break;

  case 62: /* variable_list: variable  */
#line 1268 "yacc_pascal.y"
    {
        current_rule = CurrentRule::VariableList;
        std::vector<LValStmt *> * lval_list = new std::vector<LValStmt *>();
        lval_list->emplace_back((yyvsp[0].lval));
        (yyval.lval_list) = lval_list;
        LOG_DEBUG("DEBUG variable_list -> variable");
    }
#line 2851 "yacc_pascal.cpp"
    break;

  case 63: /* variable_list: variable_list ',' variable  */
#line 1276 "yacc_pascal.y"
    {
        current_rule = CurrentRule::VariableList;
        (yyvsp[-2].lval_list)->emplace_back((yyvsp[0].lval));
        (yyval.lval_list) = (yyvsp[-2].lval_list);
        LOG_DEBUG("DEBUG variable_list -> variable_list ',' variable");
    }
#line 2862 "yacc_pascal.cpp"
    break;

  case 64: /* variable: IDENTIFIER id_varpart  */
#line 1290 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Variable;
        (yyval.lval) = new LValStmt();
        (yyval.lval)->id = std::string((yyvsp[-1].string));
        if((yyvsp[0].expr_list) != nullptr){
            for(auto expr : *(yyvsp[0].expr_list)){
                (yyval.lval)->array_index.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[0].expr_list);
        }
        free((yyvsp[-1].string));
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_varpart");
    }
#line 2880 "yacc_pascal.cpp"
    break;

  case 65: /* id_varpart: %empty  */
#line 1325 "yacc_pascal.y"
    {
        (yyval.expr_list) = nullptr;
        LOG_DEBUG("DEBUG id_varpart -> empty");
    }
#line 2889 "yacc_pascal.cpp"
    break;

  case 66: /* id_varpart: '[' expression_list ']'  */
#line 1330 "yacc_pascal.y"
    {
        current_rule = CurrentRule::IdVarpart;
        if((yyvsp[-1].expr_list) != nullptr){
            (yyval.expr_list) = (yyvsp[-1].expr_list);    
        }else{
            yyerror(&(yylsp[-1]), "code_str", program, scanner, "数组下标定义出错 请检查是否符合规范");
        }
        LOG_DEBUG("DEBUG id_varpart -> '[' expression_list ']'");
    }
#line 2903 "yacc_pascal.cpp"
    break;

  case 67: /* id_varpart: '[' expression BRACE_PAIR array_index_expression  */
#line 1340 "yacc_pascal.y"
    {
        current_rule = CurrentRule::IdVarpart;
        if((yyvsp[0].expr_list) != nullptr){
            (yyval.expr_list) = (yyvsp[0].expr_list);
        } else {
            
        }
        (yyval.expr_list)->emplace_back((yyvsp[-2].expr));
        std::reverse((yyval.expr_list)->begin(), (yyval.expr_list)->end());
        LOG_DEBUG("DEBUG id_varpart -> '[' expression BRACE_PAIR array_index_expression");
    }
#line 2919 "yacc_pascal.cpp"
    break;

  case 68: /* array_index_expression: expression ']'  */
#line 1361 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ArrayIndexExpression;
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->emplace_back((yyvsp[-1].expr));
        (yyval.expr_list) = expr_list;
        LOG_DEBUG("DEBUG array_index_expression -> expression_list");
    }
#line 2931 "yacc_pascal.cpp"
    break;

  case 69: /* array_index_expression: expression BRACE_PAIR array_index_expression  */
#line 1369 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ArrayIndexExpression;
        (yyvsp[0].expr_list)->emplace_back((yyvsp[-2].expr));
        (yyval.expr_list) = (yyvsp[0].expr_list);
        LOG_DEBUG("DEBUG array_index_expression -> array_index_expression BRACE_PAIR expression ']'");
    }
#line 2942 "yacc_pascal.cpp"
    break;

  case 70: /* procedure_call: IDENTIFIER  */
#line 1387 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProcedureCall;
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string((yyvsp[0].string));
        (yyval.func_call_stmt) = proc_call;
        free((yyvsp[0].string));
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER");
    }
#line 2955 "yacc_pascal.cpp"
    break;

  case 71: /* procedure_call: IDENTIFIER '(' expression_list ')'  */
#line 1396 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ProcedureCall;
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string((yyvsp[-3].string));
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                proc_call->args.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[-1].expr_list);
        }
        (yyval.func_call_stmt) = proc_call;
        free((yyvsp[-3].string));
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER '(' expression_list ')'");
    }
#line 2974 "yacc_pascal.cpp"
    break;

  case 72: /* expression_list: %empty  */
#line 1444 "yacc_pascal.y"
                  {
        (yyval.expr_list) = nullptr;
        LOG_DEBUG("DEBUG expression_list -> empty");
    }
#line 2983 "yacc_pascal.cpp"
    break;

  case 73: /* expression_list: expression  */
#line 1449 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ExpressionList;
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->emplace_back((yyvsp[0].expr));
        (yyval.expr_list) = expr_list;
        LOG_DEBUG("DEBUG expression_list -> expression");
    }
#line 2995 "yacc_pascal.cpp"
    break;

  case 74: /* expression_list: expression_list ',' expression  */
#line 1457 "yacc_pascal.y"
    {
        current_rule = CurrentRule::ExpressionList;
        (yyvsp[-2].expr_list)->emplace_back((yyvsp[0].expr));
        (yyval.expr_list) = (yyvsp[-2].expr_list);
        LOG_DEBUG("DEBUG expression_list -> expression_list ',' expression");
    }
#line 3006 "yacc_pascal.cpp"
    break;

  case 75: /* expression: simple_expression  */
#line 1472 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Expression;
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        RelExprStmt::Term term;
        term.type = RelExprStmt::RelExprType::NULL_TYPE;
        term.add_expr = std::unique_ptr<AddExprStmt>((yyvsp[0].add_expr));
        expr->rel_expr->terms.emplace_back(std::move(term));
        (yyval.expr) = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression");
    }
#line 3022 "yacc_pascal.cpp"
    break;

  case 76: /* expression: expression relop simple_expression  */
#line 1484 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Expression;
        ExprStmt * expr = (yyvsp[-2].expr);
        RelExprStmt::Term term;
        term.type = get_rel_expr_type((yyvsp[-1].number));
        term.add_expr = std::unique_ptr<AddExprStmt>((yyvsp[0].add_expr));
        expr->rel_expr->terms.emplace_back(std::move(term));
        (yyval.expr) = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression relop simple_expression");
    }
#line 3037 "yacc_pascal.cpp"
    break;

  case 77: /* simple_expression: term  */
#line 1505 "yacc_pascal.y"
    {
        current_rule = CurrentRule::SimpleExpression;
        AddExprStmt * add_expr = new AddExprStmt();
        AddExprStmt::Term term;
        term.type = AddExprStmt::AddExprType::NULL_TYPE;
        term.mul_expr = std::unique_ptr<MulExprStmt>((yyvsp[0].mul_expr));
        add_expr->terms.emplace_back(std::move(term));
        (yyval.add_expr) = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> term");
    }
#line 3052 "yacc_pascal.cpp"
    break;

  case 78: /* simple_expression: simple_expression addop term  */
#line 1516 "yacc_pascal.y"
    {
        current_rule = CurrentRule::SimpleExpression;
        AddExprStmt * add_expr = (yyvsp[-2].add_expr);
        AddExprStmt::Term term;
        term.type = get_add_expr_type((yyvsp[-1].number));
        term.mul_expr = std::unique_ptr<MulExprStmt>((yyvsp[0].mul_expr));
        add_expr->terms.emplace_back(std::move(term));
        (yyval.add_expr) = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> simple_expression %lld term\n", (yyvsp[-1].number));
    }
#line 3067 "yacc_pascal.cpp"
    break;

  case 79: /* term: factor  */
#line 1536 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Term;
        MulExprStmt * mul_expr = new MulExprStmt();
        MulExprStmt::Term term;
        term.type = MulExprStmt::MulExprType::NULL_TYPE;
        term.unary_expr = std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr));
        mul_expr->terms.emplace_back(std::move(term));
        (yyval.mul_expr) = mul_expr;
        LOG_DEBUG("DEBUG term -> factor");
    }
#line 3082 "yacc_pascal.cpp"
    break;

  case 80: /* term: term mulop factor  */
#line 1547 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Term;
        MulExprStmt * mul_expr = (yyvsp[-2].mul_expr);
        MulExprStmt::Term term;
        term.type = get_mul_expr_type((yyvsp[-1].number));
        term.unary_expr = std::unique_ptr<UnaryExprStmt>((yyvsp[0].unary_expr));
        mul_expr->terms.emplace_back(std::move(term));
        (yyval.mul_expr) = mul_expr;
        LOG_DEBUG("DEBUG term -> term mulop factor");
    }
#line 3097 "yacc_pascal.cpp"
    break;

  case 81: /* factor: INTEGER  */
#line 1567 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].number));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> INTEGER");
    }
#line 3115 "yacc_pascal.cpp"
    break;

  case 82: /* factor: REAL  */
#line 1607 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        double val = atof((yyvsp[0].real));
        fill_number_stmt(unary_expr->primary_expr->value->number, val);
        unary_expr->primary_expr->value->number->literal = std::string((yyvsp[0].real));
        free((yyvsp[0].real));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> REAL");
    }
#line 3136 "yacc_pascal.cpp"
    break;

  case 83: /* factor: BOOLEAN  */
#line 1650 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
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
#line 3155 "yacc_pascal.cpp"
    break;

  case 84: /* factor: CHAR  */
#line 1665 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,(yyvsp[0].charactor));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> CHAR");
    }
#line 3173 "yacc_pascal.cpp"
    break;

  case 85: /* factor: variable  */
#line 1679 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::LVal;
        unary_expr->primary_expr->value->lval = std::unique_ptr<LValStmt>((yyvsp[0].lval));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> variable");
    }
#line 3190 "yacc_pascal.cpp"
    break;

  case 86: /* factor: '(' expression ')'  */
#line 1692 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Parentheses;
        unary_expr->primary_expr->expr = std::unique_ptr<ExprStmt>((yyvsp[-1].expr));
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '(' expression ')'");
    }
#line 3205 "yacc_pascal.cpp"
    break;

  case 87: /* factor: IDENTIFIER '(' expression_list ')'  */
#line 1703 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::FuncCall;
        unary_expr->primary_expr->value->func_call = std::make_unique<FuncCallStmt>();
        unary_expr->primary_expr->value->func_call->id = std::string((yyvsp[-3].string));
        if((yyvsp[-1].expr_list) != nullptr){
            for(auto expr : *(yyvsp[-1].expr_list)){
                unary_expr->primary_expr->value->func_call->args.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete (yyvsp[-1].expr_list);
        }
        (yyval.unary_expr) = unary_expr;
        free((yyvsp[-3].string));
        LOG_DEBUG("DEBUG factor -> IDENTIFIER '(' expression_list ')'");
    }
#line 3230 "yacc_pascal.cpp"
    break;

  case 88: /* factor: NOT factor  */
#line 1724 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = (yyvsp[0].unary_expr);
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Not);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> NOT factor");
    }
#line 3242 "yacc_pascal.cpp"
    break;

  case 89: /* factor: '+' factor  */
#line 1732 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        (yyval.unary_expr) = (yyvsp[0].unary_expr);
        LOG_DEBUG("DEBUG factor -> '+' factor");
    }
#line 3252 "yacc_pascal.cpp"
    break;

  case 90: /* factor: '-' factor  */
#line 1738 "yacc_pascal.y"
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = (yyvsp[0].unary_expr);
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Minus);
        (yyval.unary_expr) = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' factor");
    }
#line 3264 "yacc_pascal.cpp"
    break;

  case 91: /* addop: '+'  */
#line 1748 "yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3270 "yacc_pascal.cpp"
    break;

  case 92: /* addop: '-'  */
#line 1748 "yacc_pascal.y"
                              { (yyval.number) = 1; }
#line 3276 "yacc_pascal.cpp"
    break;

  case 93: /* addop: OR  */
#line 1748 "yacc_pascal.y"
                                               { (yyval.number) = 2; }
#line 3282 "yacc_pascal.cpp"
    break;

  case 94: /* relop: '='  */
#line 1753 "yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3288 "yacc_pascal.cpp"
    break;

  case 95: /* relop: NE  */
#line 1753 "yacc_pascal.y"
                             { (yyval.number) = 1; }
#line 3294 "yacc_pascal.cpp"
    break;

  case 96: /* relop: '<'  */
#line 1753 "yacc_pascal.y"
                                               { (yyval.number) = 2; }
#line 3300 "yacc_pascal.cpp"
    break;

  case 97: /* relop: LE  */
#line 1753 "yacc_pascal.y"
                                                                { (yyval.number) = 3; }
#line 3306 "yacc_pascal.cpp"
    break;

  case 98: /* relop: '>'  */
#line 1753 "yacc_pascal.y"
                                                                                  { (yyval.number) = 4; }
#line 3312 "yacc_pascal.cpp"
    break;

  case 99: /* relop: GE  */
#line 1753 "yacc_pascal.y"
                                                                                                   { (yyval.number) = 5; }
#line 3318 "yacc_pascal.cpp"
    break;

  case 100: /* relop: IN  */
#line 1753 "yacc_pascal.y"
                                                                                                                    { (yyval.number) = 6; }
#line 3324 "yacc_pascal.cpp"
    break;

  case 101: /* mulop: '*'  */
#line 1758 "yacc_pascal.y"
            { (yyval.number) = 0; }
#line 3330 "yacc_pascal.cpp"
    break;

  case 102: /* mulop: '/'  */
#line 1758 "yacc_pascal.y"
                              { (yyval.number) = 1; }
#line 3336 "yacc_pascal.cpp"
    break;

  case 103: /* mulop: DIV  */
#line 1758 "yacc_pascal.y"
                                                { (yyval.number) = 1; }
#line 3342 "yacc_pascal.cpp"
    break;

  case 104: /* mulop: MOD  */
#line 1758 "yacc_pascal.y"
                                                                  { (yyval.number) = 2; }
#line 3348 "yacc_pascal.cpp"
    break;

  case 105: /* mulop: AND  */
#line 1758 "yacc_pascal.y"
                                                                                    { (yyval.number) = 3; }
#line 3354 "yacc_pascal.cpp"
    break;

  case 106: /* mulop: ANDTHEN  */
#line 1758 "yacc_pascal.y"
                                                                                                          { (yyval.number) = 4; }
#line 3360 "yacc_pascal.cpp"
    break;


#line 3364 "yacc_pascal.cpp"

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
        if (yyreport_syntax_error (&yyctx, code_str, program, scanner) == 2)
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

  return yyresult;
}

#line 1761 "yacc_pascal.y"

// 此处书写相关函数，会添加在生成的代码中
extern void scan_string(const char *str, yyscan_t scanner);

void get_error_location(const char* code_str, YYLTYPE *llocp, std::string &error_note, std::string &msg, bool have_expected) {
    std::string code(code_str); // 将C风格字符串转换为std::string
    std::istringstream stream(code);
    std::string line;
    int current_line = 1;
    msg += "\t";
    while (std::getline(stream, line)) {
        if (current_line == llocp->first_line) {
            // 打印到错误开始之前的部分
            msg += line.substr(0, llocp->first_column);
            // 错误部分使用红色高亮显示
            error_note = line.substr(llocp->first_column, llocp->last_column - llocp->first_column + 1);
            msg += "\033[31m";
            msg += error_note;
            msg += "\033[0m";
            // 打印错误之后的部分
            if (llocp->last_column < line.size()) {
                msg+= line.substr(llocp->last_column + 1);
            }
            // 添加箭头
            msg += "\n\t";
            if (have_expected) {
                for (int i = 0; i < llocp->first_column; ++i) {
                    msg += " ";
                }
                for (int i = llocp->first_column; i <= llocp->last_column; ++i) {
                    msg += "\033[1;37m^\033[0m";
                }
            } else {
                for (int i = 0; i < llocp->first_column; ++i) {
                    msg += "\033[1;37m^\033[0m";
                }
            }
            
            break; // 已找到错误行，跳出循环
        }
        ++current_line;
    }
}
// 相关所需的函数，可能包含一些错误处理函数
int yyerror(YYLTYPE *llocp, const char *code_str, ProgramStmt ** program, yyscan_t scanner, const char *msg)
{
    (void)program;
    (void)scanner;
    (void)msg;
    LOG_ERROR("[Unexcepted Error] at line %d, column %d:", llocp->first_line + 1, llocp->first_column, msg);
    return 0;
}

static int yyreport_syntax_error(const yypcontext_t *ctx, const char * code_str, ProgramStmt ** program, void * scanner)
{
    int res = 0;
    std::ostringstream buf;
    buf << "\033[1;37m" << G_SETTINGS.input_file << ":" << yypcontext_location(ctx)->first_line 
        << ":" << yypcontext_location(ctx)->first_column + 1 << ":\033[0m";
    buf << " \033[1;31m" << "Syntax error:" << "\033[0m";
    bool have_expected = false;
    // Report the tokens expected at this point.
    {
        enum { TOKENMAX = 5 };
        yysymbol_kind_t expected[TOKENMAX];
        int n = yypcontext_expected_tokens (ctx, expected, TOKENMAX);
        if (n < 0)
            // Forward errors to yyparse.
            res = n;
        else
            for (int i = 0; i < n; ++i)
                buf << (i == 0 ? " expected" : " or") << " " << yysymbol_name (expected[i]);
        if (n > 0)
            have_expected = true;
    }
    // Report the unexpected token.
    {
        yysymbol_kind_t lookahead = yypcontext_token (ctx);
        if (lookahead != YYSYMBOL_YYEMPTY)
            buf << " before " << yysymbol_name (lookahead);
    }
    std::string error_note;
    std::string msg;
    
    get_error_location(code_str, yypcontext_location(ctx), error_note, msg, have_expected);
    if (have_expected)
        buf << " but found \"" << error_note << "\"";
    std::cerr<< buf.str() << std::endl;
    std::cerr<< msg << std::endl;
    switch (current_rule)
        {
            case CurrentRule::ProgramStruct:
                LOG_ERROR("程序定义出错 请检查是否符合规范");
                break;
            case CurrentRule::ProgramHead:
                LOG_ERROR("程序头定义出错 请检查是否符合规范");
                break;
            case CurrentRule::ProgramBody:
                LOG_ERROR("程序体定义出错 请检查是否符合规范");
                break;
            case CurrentRule::IdList:
                LOG_ERROR("标识符定义错误 请检查是否符合规范");
                break;
            case CurrentRule::ConstDeclarations: case CurrentRule::ConstDeclaration:
                LOG_ERROR("常量定义出错 请检查是否符合规范");
                break;
            case CurrentRule::ConstValue:
                LOG_ERROR("常量 请检查是否为合法常量");
                break;
            case CurrentRule::VarDeclarations: case CurrentRule::VarDeclaration:
                LOG_ERROR("变量定义出错 请检查是否符合规范");
                break;
            case CurrentRule::Type:
                LOG_ERROR("类型定义出错 请检查是否符合规范");
                break;
            case CurrentRule::SubprogramDeclarations: case CurrentRule::Subprogram:
                LOG_ERROR("子函数定义出错 请检查是否符合规范");
                break;
            case CurrentRule::SubprogramHead:
                LOG_ERROR("子函数头定义出错 请检查是否符合规范");
                break;
            case CurrentRule::FormalParameter:
                LOG_ERROR("参数定义出错 请检查是否符合规范");
                break;
            case CurrentRule::SubprogramBody:
                LOG_ERROR("子函数体定义出错 请检查是否符合规范");
                break;
            case CurrentRule::CompoundStatement:
                LOG_ERROR("复合语句定义出错 请检查是否符合规范");
                break;
            case CurrentRule::StatementList: case CurrentRule::Statement:
                LOG_ERROR("语句定义出错 请检查是否符合规范");
                break;
            case CurrentRule::ProcedureCall:
                LOG_ERROR("过程调用出错 请检查是否符合规范");
                break;
            case CurrentRule::VariableList: case CurrentRule::Variable:
                LOG_ERROR("变量定义出错 请检查是否符合规范");
                break;
            case CurrentRule::IdVarpart: case CurrentRule::ArrayIndexExpression:
            case CurrentRule::BracketExpressionList:
                LOG_ERROR("数组下标定义出错 请检查是否符合规范");
                break;
            case CurrentRule::ExpressionList: case CurrentRule::Expression:
            case CurrentRule::SimpleExpression: case CurrentRule::Term: case CurrentRule::Factor:
                LOG_ERROR("表达式定义出错 请检查是否符合规范");
                break;
            default:
                LOG_ERROR("请检查相关代码是否符合规范");
                break;

        }
    return res;
}



int code_parse(const char * code_str, ProgramStmt ** program) {
    yyscan_t scanner;
    yylex_init(&scanner);
    scan_string(code_str, scanner);


    int ret = yyparse(code_str,program, scanner);

    yylex_destroy(scanner);
    return ret;
}
