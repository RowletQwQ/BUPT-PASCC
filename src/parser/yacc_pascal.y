%{
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


void syntax_error(const char *msg){
    printf("[SYNTAX ERROR] ");
    printf("%s\n", msg);
}




// 相关所需的函数，可能包含一些错误处理函数
int yyerror(YYLTYPE *llocp, const char *code_str, ProgramStmt * program, yyscan_t scanner, const char *msg)
{
    syntax_error(msg);
    return 0;
}
%}


// 定义Token


%token INTEGER
    REAL
    IDENTIFIER
    CHAR
    STRING
    BOOLEAN
    CONST
    PROGRAM
    CONST
    TYPE
    RECORD
    ARRAY
    OF
    VAR
    FUNCTION
    PROCEDURE
    BEGIN_TOKEN
    END
    IF
    THEN
    ELSE
    CASE
    WHILE
    REPEAT
    UNTIL
    FOR
    TO
    DOWNTO
    DO
    READ
    READLN
    WRITE
    WRITELN
    CHAR_KW
    INTEGER_KW
    REAL_KW
    BOOLEAN_KW
    NOT
    DIV
    MOD
    AND
    OR
    NE
    LE
    GE
    ASSIGNOP
    IN
    ORELSE
    ANDTHEN
    DOUBLE_DOT

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
    std::vector<std::pair<std::string, NumberStmt>*> * kv_pair_list;
    NumberStmt *                                    num_value;
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

    char *                                          string;
    long long                                       number;
    bool                                            boolean;
    double                                          real;
    char                                           charactor;
}



%token <string> IDENTIFIER
%token <number> INTEGER
%token <boolean> BOOLEAN
%token <real> REAL
%token <charactor> CHAR
%token <string> STRING

// 下面定义非终结符
%type <string> relop
%type <string> addop
%type <string> mulop
%type <program_struct>      programstruct
%type <program_head>        program_head
%type <program_body>        program_body
%type <id_list>             idlist
%type <const_decls>         const_declarations
%type <kv_pair_list>             const_declaration
%type <num_value>           const_value
%type <var_decls>           var_declarations
%type <var_decls>           var_declaration
%type <var_type>            type
%type <basic_type>          basic_type
%type <period_list>         period_item
%type <period_list>         period_list
%type <period>              period
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

/*
* no : 2.10
* rule  : parameter_list -> parameter | parameter_list ';' parameter
* node :  std::vector<VarDeclStmt *>*
* son  :  VarDeclStmt*
* error :
*/

parameter_list : parameter
        {
            $$ = new std::vector<VarDeclStmt *>();
            $$->push_back($1);
            delete $1;
        }
        | parameter_list ';' parameter
        {
            $1->push_back($3);
            delete $3;
            $$ = $1;
        };

/*
* no : 3.1 - 3.3
* rule  : parameter -> VAR idlist ':' basic_type | idlist ':' basic_type
* node :  VarDeclStmt*
* son  :  std::vector<std::string> *, BaiscType
* error :
*/

parameter: VAR idlist ':' basic_type
        {
            VarDeclStmt* var_decl = new VarDeclStmt();
            var_decl->id.insert(var_decl->id.end(), $2->begin(), $2->end());
            var_decl-> basic_type = $4;
            delete $2;
            printf("parameter: var %s", var_decl_stmt_str($$,0).c_str());
        }
        | idlist ':' basic_type
        {
            VarDeclStmt* var_decl = new VarDeclStmt();
            var_decl->id.insert(var_decl->id.end(), $1->begin(), $1->end());
            var_decl-> basic_type = $3;
            delete $1;
            printf("parameter: %s", var_decl_stmt_str($$,0).c_str());
        };

/*
* no : 2.4
* rule  : basic_type -> INTEGER_KW | REAL_KW | BOOLEAN_KW | CHAR_KW
* node :  BasicType
*/

basic_type: INTEGER_KW
        {
            $$ = BasicType::INT;
            printf("%s", basic_type_str($$).c_str());
        }
        | REAL_KW
        {
            $$ = BasicType::REAL;
        }
        | BOOLEAN_KW
        {
            $$ = BasicType::BOOLEAN;
        }
        | CHAR_KW
        {
            $$ = BasicType::CHAR;
        }


/*
* no : 2.5
* rule  : period_list -> INTEGER '..' INTEGER | period_list ',' INTEGER '..' INTEGER
* node :  std::vector<PeriodStmt *>*
* son  :  PeriodStmt *
* error :
*/

period_list: INTEGER DOUBLE_DOT INTEGER
        {
            $$ = new std::vector<PeriodStmt *>();
            PeriodStmt * period = new PeriodStmt();
            period->begin = $1;
            period->end = $3;
            $$->push_back(period);
            // debug
            printf("%s", period_list_str($$,0).c_str());
        }
        | period_list ',' INTEGER DOUBLE_DOT INTEGER
        {
            PeriodStmt * period = new PeriodStmt();
            period->begin = $3;
            period->end = $5;
            $1->push_back(period);
            $$ = $1;
            // debug
            printf("%s", period_list_str($$,0).c_str());
        };

/*
* no : 1.4
* rule  :  idlist -> IDENTIFIER | idlist ',' IDENTIFIER
* node :  std::vector<std::string> * id_list
* son  :  string
* error : 标识符定义错误 请检查是否符合规范
*/
idlist : IDENTIFIER
    {
        $$ = new std::vector<std::string>();
        $$->push_back($1);
        delete $1;
    }
    | idlist ',' IDENTIFIER
    {
        $1->push_back($3);
        delete $3;
        $$ = $1;
         // DEBUG
        printf("id_list:\n");
        printf("%s",id_list_str(*$$,0).c_str());
    }
    /*| error{
        syntax_error("标识符定义错误 请检查是否符合规范");
    };*/

/*
* no : 1.5
* rule  :  const_declarations -> empty | "const" const_declaration ';' const_declarations
* node :  ConstDeclStmt * const_decls
* son  :  std::vector<std::pair<std::string, NumberStmt> *> *
* error : 常量定义出错 请检查是否符合规范
*/
const_declarations : /*empty*/
    {
        $$ = nullptr;
    }
    | CONST const_declaration ';'
    {
        $$ = new ConstDeclStmt();
        std::vector<std::pair<std::string, NumberStmt> *> kv_pair_list = *$2;
        for (auto kv_pair : kv_pair_list) {
            $$->pairs.push_back(*kv_pair);
            delete kv_pair;
        }
        delete $2;

        // DEBUG
        printf("const_declarations:\n");
        printf("%s",const_decl_stmt_str(*$$,0).c_str());
    }
    |error{
        syntax_error("常量定义出错 请检查是否符合规范");
    };


/*
* no : 1.6
* rule  :  const_declaration -> IDENTIFIER = const_value | const_declaration ; IDENTIFIER = const_value
* node :  std::vector<std::pair<std::string, NumberStmt> *> *
* son  :  char *   NumberStmt *
*/
const_declaration : IDENTIFIER '=' const_value
    {
        $$ = new std::vector<std::pair<std::string, NumberStmt> *>();
        $$->push_back(new std::pair<std::string, NumberStmt>($1, *$3));
        delete $1;
        delete $3;
    }
    | const_declaration ';' IDENTIFIER '=' const_value
    {
        $1->push_back(new std::pair<std::string, NumberStmt>($3, *$5));
        delete $3;
        delete $5;
        $$ = $1; // 不需要删除
    }
    ;


/*
* no : 1.7
* rule  :  const_value -> INTEGER | REAL | CHAR | '-' INTEGER | '-' REAL | '+' INTEGER | '+' REAL | ' CHAR '
* node :  NumberStmt * num_value
* son  :  long long | double | char
* error : 常量 请检查是否为合法常量
*/
const_value: INTEGER
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_signed = true;
        num_value->int_val = $1;
        $$ = num_value;
    }|
    '+' INTEGER
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_signed = true;
        num_value->int_val = $2;
        $$ = num_value;
    }
    | '-' INTEGER
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_signed = true;
        num_value->int_val = -$2;
        $$ = num_value;
    }
    | REAL
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_real = true;
        num_value->real_val = $1;
        $$ = num_value;
    }
    | '+' REAL
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_real = true;
        num_value->real_val = $2;
        $$ = num_value;
    }
    | '-' REAL
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_real = true;
        num_value->real_val = -$2;
        $$ = num_value;
    }
    | '\'' CHAR  '\''
    {
        NumberStmt * num_value = new NumberStmt();
        num_value->is_char = true;
        num_value->char_val = $2;
        $$ = num_value;
    }
    ;


/*
* addop ->  + | - | or
*/
addop : '+' { $$ = "+"; } | '-' { $$ = "-"; } | OR { $$ = "or"; }

/*
* relop -> = | <> | < | <= | > | >=
*/
relop : '=' { $$ = "="; } | NE { $$ = "<>"; } | '<' { $$ = "<"; } | LE { $$ = "<="; } | '>' { $$ = ">"; } | GE { $$ = ">="; }

/*
* mulop -> * | / | div | mod | and
*/
mulop : '*' { $$ = "*"; } | '/' { $$ = "/"; } | DIV { $$ = "div"; } | MOD { $$ = "mod"; } | AND { $$ = "and"; }



%%
// 此处书写相关函数，会添加在生成的代码中
extern void scan_string(const char *str, yyscan_t scanner);

int code_parse(const char * code_str, ProgramStmt * program) {
    yyscan_t scanner;
    yylex_init(&scanner);
    scan_string(code_str, scanner);
    int ret = yyparse(code_str,program, scanner);
    yylex_destroy(scanner);
    return ret;
}