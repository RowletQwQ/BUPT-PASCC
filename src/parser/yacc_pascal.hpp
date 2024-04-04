/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_PASCAL_HPP_INCLUDED
# define YY_YY_YACC_PASCAL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    PROGRAM = 259,                 /* PROGRAM  */
    TYPE = 260,                    /* TYPE  */
    RECORD = 261,                  /* RECORD  */
    ARRAY = 262,                   /* ARRAY  */
    OF = 263,                      /* OF  */
    VAR = 264,                     /* VAR  */
    FUNCTION = 265,                /* FUNCTION  */
    PROCEDURE = 266,               /* PROCEDURE  */
    BEGIN_TOKEN = 267,             /* BEGIN_TOKEN  */
    END = 268,                     /* END  */
    IF = 269,                      /* IF  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    CASE = 272,                    /* CASE  */
    WHILE = 273,                   /* WHILE  */
    REPEAT = 274,                  /* REPEAT  */
    UNTIL = 275,                   /* UNTIL  */
    FOR = 276,                     /* FOR  */
    TO = 277,                      /* TO  */
    DOWNTO = 278,                  /* DOWNTO  */
    DO = 279,                      /* DO  */
    READ = 280,                    /* READ  */
    READLN = 281,                  /* READLN  */
    WRITE = 282,                   /* WRITE  */
    WRITELN = 283,                 /* WRITELN  */
    CHAR_KW = 284,                 /* CHAR_KW  */
    INTEGER_KW = 285,              /* INTEGER_KW  */
    REAL_KW = 286,                 /* REAL_KW  */
    BOOLEAN_KW = 287,              /* BOOLEAN_KW  */
    NOT = 288,                     /* NOT  */
    DIV = 289,                     /* DIV  */
    MOD = 290,                     /* MOD  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    NE = 293,                      /* NE  */
    LE = 294,                      /* LE  */
    GE = 295,                      /* GE  */
    ASSIGNOP = 296,                /* ASSIGNOP  */
    IN = 297,                      /* IN  */
    ORELSE = 298,                  /* ORELSE  */
    ANDTHEN = 299,                 /* ANDTHEN  */
    DOUBLE_DOT = 300,              /* DOUBLE_DOT  */
    BRACE_PAIR = 301,              /* BRACE_PAIR  */
    BREAK = 302,                   /* BREAK  */
    CONTINUE = 303,                /* CONTINUE  */
    IDENTIFIER = 304,              /* IDENTIFIER  */
    INTEGER = 305,                 /* INTEGER  */
    BOOLEAN = 306,                 /* BOOLEAN  */
    REAL = 307,                    /* REAL  */
    CHAR = 308,                    /* CHAR  */
    STRING = 309                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 308 "yacc_pascal.y"

    ProgramStmt *                                   program_struct;
    ProgramHeadStmt *                               program_head;
    ProgramBodyStmt *                               program_body;
    std::vector<std::string> *                      id_list;
    ConstDeclStmt *                                 const_decls;
    std::pair<std::string, ValueStmt *> *            kv_pair;
    std::vector<std::pair<std::string, ValueStmt *>*> * kv_pair_list;
    ValueStmt *                                    value;
    std::vector<VarDeclStmt *> *                    var_decls;
    VarDeclStmt *                                   var_decl;
    DataType                                        var_type;
    BasicType                                       basic_type;
    std::vector<PeriodStmt *> *                     period_list;
    PeriodStmt *                                    period;
    std::vector<FuncDeclStmt *> *                   func_decl_list;
    FuncDeclStmt *                                  func_decl;
    FuncHeadDeclStmt *                              func_head;
    FuncBodyDeclStmt *                              func_body;
    std::vector<BaseStmt *> *                       stmt_list;
    AssignStmt *                                    assign_stmt;
    IfStmt *                                        if_stmt;
    ForStmt *                                       for_stmt;
    ReadFuncStmt *                                      read_stmt;
    WriteFuncStmt *                                     write_stmt;
    FuncCallStmt *                                  func_call_stmt;
    std::vector<LValStmt *> *                       lval_list;
    LValStmt *                                      lval;
    BaseStmt *                                      stmt;

    std::vector<ExprStmt *> *                       expr_list;
    ExprStmt *                                      expr;
    RelExprStmt *                                   rel_expr;
    AddExprStmt *                                   add_expr;
    MulExprStmt *                                   mul_expr;
    UnaryExprStmt *                                 unary_expr;
    PrimaryExprStmt *                               primary_expr;

    BreakStmt *                                     break_stmt;
    ContinueStmt *                                  continue_stmt;

    char *                                          string;
    long long                                       number;
    bool                                            boolean;
    char *                                          real;
    char                                           charactor;
    int                                            token;

#line 167 "yacc_pascal.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * code_str, ProgramStmt ** program, void * scanner);


#endif /* !YY_YY_YACC_PASCAL_HPP_INCLUDED  */
