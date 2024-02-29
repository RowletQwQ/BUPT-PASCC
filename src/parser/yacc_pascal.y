%{
// 此处为相关头文件和函数，会添加在生成的代码中

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/log/log.hpp"
#include "ast/stmt.hpp"
#include "parser/lex_pascal.hpp"
#include "parser/yacc_pascal.hpp"


// 相关所需的函数，可能包含一些错误处理函数

%}


%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * code_str }
%parse-param { ProgramStmt * program}
%parse-param { void * scanner }

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
    ProgramStmt *                                   program_struct;
    ProgramHeadStmt *                               program_head;
    ProgramBodyStmt *                               program_body;
    std::vector<std::string> *                      id_list;
    ConstDeclStmt *                                 const_decls;
    std::pair<std::string, NumberStmt> *            kv_pair;
    NumberStmt *                                    num_value;
    std::vector<VarDeclStmt *> *                    var_decls;
    VarDeclStmt *                                   var_decl;
    DataType                                        var_type;
    BasicType                                       basic_type;
    std::vector<PeriodStmt *>                       period_list;
    std::vector<FuncDeclStmt *> *                   func_decl_list;
    FuncDeclStmt *                                  func_decl;
    FuncHeadDeclStmt *                              func_head;
    FuncBodyDeclStmt *                              func_body;
    std::vector<BaseStmt *> *                       stmt_list;
    AssignStmt *                                    assign_stmt;
    IfStmt *                                        if_stmt;
    ForStmt *                                       for_stmt;
    ReadStmt *                                      read_stmt;
    WriteStmt *                                     write_stmt;
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

    char *                                          string;
    long long                                       number;
    bool                                            boolean;
    double                                          real;
}


// 下面定义非终结符
%type <program_struct>      programstruct
%type <program_head>        program_head
%type <program_body>        program_body
%type <id_list>             idlist
%type <const_decls>         const_declarations
%type <kv_pair>             const_declaration
%type <num_value>           const_value
%type <var_decls>           var_declarations
%type <var_decl>            var_declaration
%type <var_type>            type
%type <basic_type>          basic_type
%type <period_list>         period
%type <func_decl_list>      subprogram_declarations
%type <func_decl>           subprogram
%type <func_head>           subprogram_head
%type <var_decls>           parameter_list
%type <var_decl>            parameter
%type <func_body>           subprogram_body
%type <stmt_list>           compound_statement
%type <stmt_list>           statement_list
%type <stmt>                statement
%type <assign_stmt>         assignment
%type <if_stmt>             if_clause
%type <for_stmt>            for_clause
%type <func_call_stmt>      procedure_call
%type <read_stmt>           read_clause
%type <write_stmt>          write_clause
%type <lval_list>           variable_list
%type <lval>                variable
%type <expr_list>           id_varpart

%type <expr_list>           expression_list
%type <expr>                expression
%type <rel_expr>            simple_expression
%type <add_expr>            term
%type <mul_expr>            factor
%type <unary_expr>          unary_expression
%type <primary_expr>        primary_expression

%%
// TODO 此处书写文法规则

%%
// 此处书写相关函数，会添加在生成的代码中
extern void scan_string(const char *str, yyscan_t scanner);

int code_parse(const char * code_str, ProgramStmt * program) {
    yyscan_t scanner;
    yylex_init(&scanner);
    scan_string(code_str, scanner);
    int ret = yyparse(program, scanner);
    yylex_destroy(scanner);
    return ret;
}