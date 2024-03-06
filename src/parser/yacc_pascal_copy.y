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

RelExprStmt::RelExprType get_rel_expr_type(const char *op) {
    if (strcmp(op, "=") == 0) {
        return RelExprStmt::RelExprType::Equal;
    } else if (strcmp(op, "<>") == 0) {
        return RelExprStmt::RelExprType::NotEqual;
    } else if (strcmp(op, "<") == 0) {
        return RelExprStmt::RelExprType::Less;
    } else if (strcmp(op, "<=") == 0) {
        return RelExprStmt::RelExprType::LessEqual;
    } else if (strcmp(op, ">") == 0) {
        return RelExprStmt::RelExprType::Greater;
    } else if (strcmp(op, ">=") == 0) {
        return RelExprStmt::RelExprType::GreaterEqual;
    } else if (strcmp(op, "in") == 0) {
        return RelExprStmt::RelExprType::In;
    } else {
        return RelExprStmt::RelExprType::NULL_TYPE;
    }
}

AddExprStmt::AddExprType get_add_expr_type(const char *op) {
    if (strcmp(op, "+") == 0) {
        return AddExprStmt::AddExprType::Plus;
    } else if (strcmp(op, "-") == 0) {
        return AddExprStmt::AddExprType::Minus;
    } else if (strcmp(op, "or") == 0) {
        return AddExprStmt::AddExprType::Or;
    } else {
        return AddExprStmt::AddExprType::NULL_TYPE;
    }
}

MulExprStmt::MulExprType get_mul_expr_type(const char *op) {
    if (strcmp(op, "*") == 0) {
        return MulExprStmt::MulExprType::Mul;
    } else if (strcmp(op, "/") == 0) {
        return MulExprStmt::MulExprType::Div;
    } else if (strcmp(op, "mod") == 0) {
        return MulExprStmt::MulExprType::Mod;
    } else if (strcmp(op, "and") == 0) {
        return MulExprStmt::MulExprType::And;
    } else if(strcmp(op, "and then") == 0){
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
* no : 4.3
* rule  :  variable -> IDENTIFIER id_varpart
* node :  LValStmt *  lval
* son  :  std::string id  std::vector<std::unique_ptr<ExprStmt>> array_index
* error : 变量定义出错 请检查是否符合规范 
*/
variable : IDENTIFIER id_varpart
    {
        $$ = new LValStmt();
        $$->id = $1;
        for(auto expr : *$2){
            $$->array_index.push_back(std::unique_ptr<ExprStmt>(expr));
        }
        delete $1;
        delete $2;
    }
    | error
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 4.4
* rule  :  id_varpart -> empty | '[' expression_list ']'
* node :    std::vector<ExprStmt *> * expr_list  
* son : ExprStmt * 
* error : 数组下标定义出错 请检查是否符合规范
*/
id_varpart : /*empty*/
    {
        $$ = nullptr;
    }
    | '[' expression_list ']'
    {
        $$ = $2;
    }
    | error
    {
        syntax_error("数组下标定义出错 请检查是否符合规范");
    }
    ;





/*
* no : 5.3
* rule  :  expression_list -> expression | expression_list  ','  expression
* node :   std::vector<ExprStmt *> * expr_list
* son : ExprStmt *
* error : 表达式定义出错 请检查是否符合规范
*/
expression_list : expression
    {
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->push_back($1);
        $$ = expr_list;
    }
    | expression_list ',' expression
    {
        $1->push_back($3);
        $$ = $1;
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.4
* rule  :  expression -> simple_expression | simple_expression relop simple_expression
* node :   ExprStmt * expr 
* son : RelExprStmt * rel_expr
* error : 表达式定义出错 请检查是否符合规范
*/
expression : simple_expression
    {
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::unique_ptr<RelExprStmt>($1);
        $$ = expr;
        printf("%s",expr_stmt_str(expr,0).c_str());
    }
    | simple_expression relop simple_expression
    {
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->type = get_rel_expr_type($2);
        expr->rel_expr->add_expr = std::move($1->add_expr);
        expr->rel_expr->rel_expr = std::unique_ptr<RelExprStmt>($3);
        expr->rel_expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        delete $1;
        $$ = expr;
        printf("%s",expr_stmt_str(expr,0).c_str());
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;


/*
* no : 5.5
* rule  :  simple_expression -> term | simple_expression addop term
* node :   RelExprStmt * rel_expr
* son : RelExprType type AddExprStmt * add_expr  RelExprStmt * rel_expr
* error : 表达式定义出错 请检查是否符合规范
*/
simple_expression : term
    {
        RelExprStmt * rel_expr = new RelExprStmt();
        rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        rel_expr->add_expr = std::unique_ptr<AddExprStmt>($1);
        $$ = rel_expr;
    }
    | simple_expression addop term
    {
        RelExprStmt * rel_expr = new RelExprStmt();
        rel_expr->type = get_add_expr_type($2);
        rel_expr->add_expr = std::unique_ptr<AddExprStmt>($3);
        rel_expr->rel_expr = std::unique_ptr<RelExprStmt>($1);
        $$ = rel_expr;
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.6
* rule  :  term -> factor | term mulop factor
* node :   AddExprStmt * add_expr
* son : AddExprType type; MulExprStmt * mul_expr; AddExprStmt * add_expr
* error : 表达式定义出错 请检查是否符合规范
*/
term : factor
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = AddExprType::NULL_TYPE;
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>($1);
        $$ = add_expr;
    }
    | term mulop factor
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = get_mul_expr_type($2);
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>($3);
        add_expr->add_expr = std::unique_ptr<AddExprStmt>($1);
        $$ = add_expr;
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.7
* rule  :  factor -> INTEGER | REAL | variable | '(' expression ')' | IDENTIFIER '(' expression_list ')' | '-' factor 
* node :   MulExprStmt *  mul_expr
* son : MulExprType type UnaryExprStmt * unary_expr  MulExprStmt * mul_expr
* error : 表达式定义出错 请检查是否符合规范
*/
factor : INTEGER
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::Value;
        mul_expr->unary_expr->primary_expr->value  = std::make_unique<ValueStmt>();
        mul_expr->unary_expr->primary_expr->value->type = ValueType::Number;
        mul_expr->unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(mul_expr->unary_expr->primary_expr->value->number,$1);
        $$ = mul_expr;
    }
    | REAL
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::Value;
        mul_expr->unary_expr->primary_expr->value  = std::make_unique<ValueStmt>();
        mul_expr->unary_expr->primary_expr->value->type = ValueType::Number;
        mul_expr->unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(mul_expr->unary_expr->primary_expr->value->number,$1);
        $$ = mul_expr;
    }
    | variable
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::LVal;
        mul_expr->unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        mul_expr->unary_expr->primary_expr->value->type = ValueType::LVal;
        mul_expr->unary_expr->primary_expr->value->lval = std::unique_ptr<LValStmt>($1);
        $$ = mul_expr;
    }
    | '(' expression ')'
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::Parentheses;
        mul_expr->unary_expr->primary_expr->expr = std::unique_ptr<ExprStmt>($2);
        $$ = mul_expr;
    }
    | IDENTIFIER '(' expression_list ')'
    {
        // std::vector<ExprStmt *> * expr_list
        // args : std::vector<ExprStmt> 
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::Value;
        mul_expr->unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        mul_expr->unary_expr->primary_expr->value->type = ValueType::FuncCall;
        mul_expr->unary_expr->primary_expr->value->func_call = std::make_unique<FuncCallStmt>();
        mul_expr->unary_expr->primary_expr->value->func_call->id = $1;
        mul_expr->unary_expr->primary_expr->func_call->args = new std::vector<std::unique_ptr<ExprStmt>>();
        for(auto expr : *$3){
            mul_expr->unary_expr->primary_expr->func_call->args->push_back(*expr);
        }
        delete $1;
        delete $3;
        $$ = mul_expr;
    }
    | '-' factor
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::make_unique<UnaryExprStmt>();
        mul_expr->unary_expr->type = UnaryExprType::Minus;
        mul_expr->unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        mul_expr->unary_expr->primary_expr->type = PrimaryExprType::Parentheses;
        mul_expr->unary_expr->primary_expr->expr = std::make_unique<ExprStmt>();
        mul_expr->unary_expr->primary_expr->expr->rel_expr = std::make_unique<RelExprStmt>();
        mul_expr->unary_expr->primary_expr->expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr->expr->rel_expr->add_expr = std::make_unique<AddExprStmt>();
        mul_expr->unary_expr->primary_expr->expr->rel_expr->add_expr->type = AddExprType::NULL_TYPE;
        mul_expr->unary_expr->primary_expr->expr->rel_expr->add_expr->mul_expr = std::unique_ptr<MulExprStmt>($2);
        $$ = mul_expr;
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
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

NumberStmt * new_number_stmt(long long int_val){
    NumberStmt * num_value = new NumberStmt();
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->int_val = int_val;
    return num_value;
}

NumberStmt * new_number_stmt(double real_val){
    NumberStmt * num_value = new NumberStmt();
    num_value->is_signed = true;
    num_value->is_real = true;
    num_value->is_char = false;
    num_value->is_unsigned = false;
    num_value->real_val = real_val;
    return num_value;
}

NumberStmt * new_number_stmt(char char_val){
    NumberStmt * num_value = new NumberStmt();
    num_value->is_signed = true;
    num_value->is_real = false;
    num_value->is_char = true;
    num_value->is_unsigned = false;
    num_value->char_val = char_val;
    return num_value;
}