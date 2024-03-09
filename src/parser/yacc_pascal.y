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

%token 
    CONST
    PROGRAM
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
%type <number> relop
%type <number> addop
%type <number> mulop
%type <program_struct>      programstruct
%type <program_head>        program_head
%type <program_body>        program_body
%type <id_list>                   idlist
%type <const_decls>         const_declarations
%type <kv_pair_list>             const_declaration
%type <num_value>           const_value
%type <var_decls>           var_declarations
%type <var_decls>           var_declaration
%type <var_decl>            type
%type <basic_type>          basic_type
%type <period_list>         period_list
%type <func_decl_list>      subprogram_declarations
%type <func_decl>           subprogram
%type <func_head>           subprogram_head
%type <var_decls>           parameter_list
%type <var_decls>           formal_parameter
%type <var_decl>            parameter
%type <var_decl>            var_parameter
%type <var_decl>            value_parameter
%type <func_body>           subprogram_body
%type <stmt_list>           compound_statement
%type <stmt_list>           statement_list
%type <stmt>                statement
%type <func_call_stmt>      procedure_call
%type <lval_list>           variable_list
%type <lval>                variable
%type <expr_list>           id_varpart
%type <expr_list>           expression_list
%type <expr>                expression   
%type <add_expr>            simple_expression
%type <mul_expr>            term
%type <unary_expr>          factor
%type <stmt>        else_part

%%
// TODO 此处书写文法规则
/*
* no : 1.1
* rule  :  programstruct -> program_head ‘;’ program_body '.'
* node :  ProgramStmt * program_struct
* son  :  ProgramHeadStmt * program_head ProgramBodyStmt * program_body
* error : 程序定义出错 请检查是否符合规范
*/
programstruct : program_head  ';'  program_body '.'
    {
        ProgramStmt * program_struct = new ProgramStmt();
        program_struct->head = std::unique_ptr<ProgramHeadStmt>($1);
        program_struct->body = std::unique_ptr<ProgramBodyStmt>($3);
        LOG_DEBUG("DEBUG programstruct -> program_head ';' program_body '.'\n");
    }
    | error{
        syntax_error("程序定义出错 请检查是否符合规范");
    };
/*
* no : 1.2
* rule  :  program_head -> "program" IDENTIFIER '(' idlist ')' | "program" IDENTIFIER
* node :  ProgramHeadStmt * program_head
* son  :  char * std::vector<std::string>
* error : 程序头定义出错 请检查是否符合规范
*/
program_head : PROGRAM IDENTIFIER '(' idlist ')'
    {
        $$ = new ProgramHeadStmt();
        $$->id_list = *$4;
        delete $4;
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER '(' idlist ')'\n");
    }
    | PROGRAM IDENTIFIER
    {
        $$ = new ProgramHeadStmt();
        $$->id_list.push_back(std::string($2));
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER\n");
    }
    | error{
        syntax_error("程序头定义出错 请检查是否符合规范");
    };

/*
* no : 1.3
* rule  :  program_body -> const_declarations var_declarations subprogram_declarations compound_statement
* node :  ProgramBodyStmt * program_body
* son  :  ConstDeclStmt * const_decl std::vector<VarDeclStmt *> var_decl  std::vector<FuncDeclStmt *>  func_decl  std::vector<BaseStmt *>  comp_stmt
* error : 程序体定义出错 请检查是否符合规范
*/
program_body : const_declarations var_declarations subprogram_declarations compound_statement
    {
        ProgramBodyStmt* program_body = new ProgramBodyStmt();
        program_body->const_decl = std::unique_ptr<ConstDeclStmt>($1);
        for(auto var_decl : *$2){
            program_body->var_decl.push_back(std::unique_ptr<VarDeclStmt>(var_decl));
        }
        for(auto func_decl : *$3){
            program_body->func_decl.push_back(std::unique_ptr<FuncDeclStmt>(func_decl));
        }
        for(auto stmt : *$4){
            program_body->comp_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
        }
        $$ = program_body;
        delete $2;
        delete $3;
        delete $4;
        LOG_DEBUG("DEBUG program_body -> const_declarations var_declarations subprogram_declarations compound_statement\n");
    }
    | error{
        syntax_error("程序体定义出错 请检查是否符合规范");
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
        $$->push_back(std::string($1));
        LOG_DEBUG("DEBUG idlist -> IDENTIFIER\n");
    }
    | idlist ',' IDENTIFIER
    {
        $1->push_back(std::string($3));
        $$ = $1;
        LOG_DEBUG("DEBUG idlist -> idlist ',' IDENTIFIER\n");
    }
    | error{
        syntax_error("标识符定义错误 请检查是否符合规范");
    };

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
        LOG_DEBUG("DEBUG id_varpart -> empty\n");
    }
    | CONST const_declaration ';' const_declarations
    {
        $$ = new ConstDeclStmt();
        std::vector<std::pair<std::string, NumberStmt> *> kv_pair_list = *$2;
        for (auto kv_pair : kv_pair_list) {
            $$->pairs.push_back(*kv_pair);
            delete kv_pair;
        }
        delete $2;
        // DEBUG
        printf("%s",const_decl_stmt_str(*$$,0).c_str());
        LOG_DEBUG("DEBUG const_declarations -> CONST const_declaration ';' const_declarations\n");
    }
    | error
    {
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
* no : 2.1
* rule : var_declarations -> empty | "var" var_declaration ';' 
* node : std::vector<VarDeclStmt *> * var_decls
* son  : VarDeclStmt *
* error : 变量定义出错 请检查是否符合规范
*/
var_declarations : /*empty*/
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG var_declarations -> empty\n");
    }
    | VAR var_declaration ';'
    {
        $$ = $2;
        LOG_DEBUG("DEBUG var_declarations -> VAR var_declaration ';'\n");
    }
    | error
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 2.2
* rule  : var_declaration -> idlist ':' type | var_declaration ';' idlist ':' type
* node :  std::vector<VarDeclStmt *> * var_decls
* son  :  VarDeclStmt *
* error : 变量定义出错 请检查是否符合规范
*/
var_declaration : idlist ':' type
    {
        std::vector<VarDeclStmt *> * var_decls = new std::vector<VarDeclStmt *>();
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), $1->begin(), $1->end());
        // deal with type
        var_decl->basic_type = $3->basic_type;
        var_decl->data_type = $3->data_type;
        var_decl->array_range = std::move($3->array_range);
        delete $1;
        delete $3;
        var_decls->push_back(var_decl);
        $$ = var_decls;
        LOG_DEBUG("DEBUG var_declaration -> idlist ':' type\n");
    }
    | var_declaration ';' idlist ':' type
    {
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), $3->begin(), $3->end());
        // deal with type
        var_decl->basic_type = $5->basic_type;
        var_decl->data_type = $5->data_type;
        var_decl->array_range = std::move($5->array_range);
        delete $3;
        delete $5;
        $1->push_back(var_decl);
        $$ = $1;
        LOG_DEBUG("DEBUG var_declaration -> var_declaration ';' idlist ':' type\n");
    }
    | error
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
    ;
/*
* no : 2.3
* rule  : type -> basic_type | ARRAY '[' period_list ']' OF basic_type 
* node : VarDeclStmt * type_stmt
* son  : BasicType | DataType
* error : 类型定义出错 请检查是否符合规范
*/
type : basic_type
    {
        VarDeclStmt * type_stmt = new VarDeclStmt();
        // TODO 处理type_size
        type_stmt->data_type = DataType::BasicType;
        type_stmt->basic_type = $1;
        $$ = type_stmt;
        LOG_DEBUG("DEBUG type -> basic_type\n");
    }
    | ARRAY '[' period_list ']' OF basic_type
    {
        VarDeclStmt * type_stmt = new VarDeclStmt();
        type_stmt->data_type = DataType::ArrayType;
        type_stmt->basic_type = $6;
        for(auto period : *$3){
            type_stmt->array_range.push_back(std::unique_ptr<PeriodStmt>(period));
        }
        delete $3;
        $$ = type_stmt;
        LOG_DEBUG("DEBUG type -> ARRAY '[' period_list ']' OF basic_type\n");
    }
    | error
    {
        syntax_error("类型定义出错 请检查是否符合规范");
    }
    ;


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
* no : 2.6
* rule  :  subprogram_declarations -> empty | subprogram_declarations subprogram ';'
* node :  std::vector<FuncDeclStmt *> * func_decl_list
* son  :  FuncDeclStmt *
* error : 子函数定义出错 请检查是否符合规范
*/
subprogram_declarations : /*empty*/
        {
            $$ = new std::vector<FuncDeclStmt *>();
        }
        | subprogram_declarations subprogram ';'
        {
            $1->push_back($2);
            $$ = $1;
        };


/*
* no : 2.7
* rule  :  subprogram -> subprogram_head ';' subprogram_body
* node :  FuncDeclStmt * func_decl
* son  :  FuncHeadDeclStmt * func_head FuncBodyDeclStmt * func_body
* error : 子函数定义出错 请检查是否符合规范
*/
subprogram : subprogram_head ';' subprogram_body
        {
            FuncDeclStmt * subprogram = new FuncDeclStmt();
            subprogram->header = std::unique_ptr<FuncHeadDeclStmt>($1);
            subprogram->body = std::unique_ptr<FuncBodyDeclStmt>($3);
            $$ = subprogram;
        };


/*
* no : 2.8
* rule  :  subprogram_head -> PROGRAM IDENTIFIER formal_parameter | FUNCTION IDENTIFIER formal_parameter ':' basic_type
* node :  FuncHeadDeclStmt * func_head
* son  :  std::string func_name;  BasicType ret_type; std::vector<std::unique_ptr<VarDeclStmt>> args;
* error : 子函数头定义出错 请检查是否符合规范
*/
subprogram_head: PROGRAM IDENTIFIER formal_parameter
        {
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = $2;
            for(auto formal_parameter : *$3){
                sub_head->args.push_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
            }
            delete $3;
            $$ = sub_head;
        }
        | FUNCTION IDENTIFIER formal_parameter ':' basic_type
        {
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = $2;
            sub_head->ret_type = $5;
            for(auto formal_parameter : *$3){
                sub_head->args.push_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
            }
            delete $3;
            $$ = sub_head;
        }

/*
* no : 2.9
* rule  :  formal_parameter -> empty | '(' parameter_list ')'
* node :  std::vector<VarDeclStmt *>*
* son  :  VarDeclStmt *
* error : 参数定义出错 请检查是否符合规范
*/
 formal_parameter: /*empty*/
        {
            $$ = new std::vector<VarDeclStmt *>();
        }
        | '(' parameter_list ')'
        {
            $$ = $2;
        };



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
* no : 3.1
* rule  : parameter -> var_parameter | value_parameter
* node :  VarDeclStmt*
* son  :  VarDeclStmt*
* error : 
*/
parameter: var_parameter
        {
            $$ = new VarDeclStmt();
            $$ = $1;
        }
        | value_parameter
        {
            $$ = new VarDeclStmt();
            $$ = $1;
        }
        ;
/*
* no : 3.2
* rule  : var_parameter -> VAR value_parameter
* node :  VarDeclStmt*
* son  :  VarDeclStmt*
* error :
*/
var_parameter: VAR value_parameter
        {
            $$ = new VarDeclStmt();
            $$ = $2;
        }
        ;

/*
* no : 3.3
* rule  : value_parameter -> idlist ':' basic_type
* node :  VarDeclStmt*
* son  :  std::vector<std::string> *, BasicType
* error :
*/
value_parameter: idlist ':' basic_type
        {
            VarDeclStmt* var_decl = new VarDeclStmt();
            var_decl->id.insert(var_decl->id.end(), $1->begin(), $1->end());
            var_decl-> basic_type = $3;
            delete $1;
            $$ = var_decl;
        };
/*
* no : 3.4
* rule  :  subprogram_body -> const_declarations var_declarations compound_statement
* node :  FuncBodyDeclStmt * func_body
* son  :  std::unique_ptr<ConstDeclStmt> const_decl; std::vector<std::unique_ptr<VarDeclStmt>> var_decl;  std::vector<std::unique_ptr<BaseStmt>> comp_stmt;   
* error : 子函数体定义出错 请检查是否符合规范
*/
subprogram_body : const_declarations var_declarations compound_statement
    {
        FuncBodyDeclStmt * func_body = new FuncBodyDeclStmt();
        func_body->const_decl = std::unique_ptr<ConstDeclStmt>($1);
        for(auto var_decl : *$2){
            func_body->var_decl.push_back(std::unique_ptr<VarDeclStmt>(var_decl));
        }
        for(auto stmt : *$3){
            func_body->comp_stmt.push_back(std::unique_ptr<BaseStmt>(stmt));
        }
        $$ = func_body;
        delete $2;
        delete $3;
        LOG_DEBUG("DEBUG subprogram_body -> const_declarations var_declarations compound_statement\n");
    }
    | error
    {
        syntax_error("子函数体定义出错 请检查是否符合规范");
    };
/*
* no : 3.5
* rule  :  compound_statement -> BEGIN_TOKEN statement_list END
* node :  std::vector<BaseStmt *> * stmt_list
* son  :  BaseStmt *
* error : 复合语句定义出错 请检查是否符合规范
*/
compound_statement : BEGIN_TOKEN statement_list END
    {
        $$ = $2;
        LOG_DEBUG("DEBUG compound_statement -> BEGIN_TOKEN statement_list END\n");
    }
    | error
    {
        syntax_error("复合语句定义出错 请检查是否符合规范");
    };
/*
* no : 3.6
* rule  :  statement_list -> statement | statement_list ';' statement
* node :  std::vector<BaseStmt *> * stmt_list
* son  :  BaseStmt *
* error : 语句定义出错 请检查是否符合规范
*/
statement_list : statement
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        stmt_list->push_back($1);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement_list -> statement\n");
    }
    | statement_list ';' statement
    {
        $1->push_back($3);
        $$ = $1;
        LOG_DEBUG("DEBUG statement_list -> statement_list ';' statement\n");
    }
    | error
    {
        syntax_error("语句定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 4.1
* rule  :  statement -> empty | variable ASSIGNOP expression |
* IDENTIFIER ASSIGNOP expression | procedure_call | compound_statement | 
* IF expression THEN statement else_part | FOR IDENTIFIER ASSIGNOP expression TO expression DO statement | 
* READ '(' variable_list ')' | WRITE '(' expression_list ')' 
* node :   BaseStmt *  stmt
* son :  Stmt *
* error : 函数体定义出错 请检查是否符合规范
*/
statement : /*empty*/
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG statement -> empty\n");
    }
    | variable ASSIGNOP expression
    {
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::unique_ptr<LValStmt>($1);
        assign_stmt->expr = std::unique_ptr<ExprStmt>($3);
        $$ = assign_stmt;
        LOG_DEBUG("DEBUG statement -> variable ASSIGNOP expression\n");
    }
    | IDENTIFIER ASSIGNOP expression
    {
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::make_unique<LValStmt>();
        assign_stmt->lval->id = $1;
        // how to deal with array_index
        // assign_stmt->lval->array_index = std::vector<std::unique_ptr<ExprStmt>>();
        assign_stmt->expr = std::unique_ptr<ExprStmt>($3);
        delete $1;
        $$ = assign_stmt;
        LOG_DEBUG("DEBUG statement -> IDENTIFIER ASSIGNOP expression\n");
    }
    | procedure_call
    {
        $$ = $1;
        LOG_DEBUG("DEBUG statement -> procedure_call\n");
    }
    | compound_statement
    {
        $$ = $1;
        LOG_DEBUG("DEBUG statement -> compound_statement\n");
    }
    | IF expression THEN statement else_part
    {
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>($2);
        if_stmt->then_stmt = std::unique_ptr<BaseStmt>($4);
        if_stmt->false_stmt = std::unique_ptr<BaseStmt>($5);
        $$ = if_stmt;
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement else_part\n");
    }
    | FOR IDENTIFIER ASSIGNOP expression TO expression DO statement
    {
        ForStmt * for_stmt = new ForStmt();
        for_stmt->id = $2;
        for_stmt->start_expr = std::unique_ptr<ExprStmt>($4);
        for_stmt->end_expr = std::unique_ptr<ExprStmt>($6);
        for_stmt->stmt = std::unique_ptr<Stmt>($8);
        delete $2;
        $$ = for_stmt;
        LOG_DEBUG("DEBUG statement -> FOR IDENTIFIER ASSIGNOP expression TO expression DO statement\n");
    }
    | READ '(' variable_list ')'
    {
        ReadFuncStmt * read_stmt = new ReadFuncStmt();
        read_stmt->lval_list = std::unique_ptr<std::vector<LValStmt *>>($3);
        $$ = read_stmt;
        LOG_DEBUG("DEBUG statement -> READ '(' variable_list ')'\n");
    }
    | WRITE '(' expression_list ')'
    {
        WriteFuncStmt * write_stmt = new WriteFuncStmt();
        write_stmt->expr_list = std::unique_ptr<std::vector<ExprStmt *>>($3);
        $$ = write_stmt;
        LOG_DEBUG("DEBUG statement -> WRITE '(' expression_list ')'\n");
    }

/*
* no : 4.2
* rule  :  variable_list -> variable | variable_list ',' variable
* node :   std::vector<LValStmt *> *  lval_list
* son :  std::string id  std::vector<std::unique_ptr<ExprStmt>> array_index
* error : 变量定义出错 请检查是否符合规范
*/
variable_list : variable
    {
        std::vector<LValStmt *> * lval_list = new std::vector<LValStmt *>();
        lval_list->push_back($1);
        $$ = lval_list;
        LOG_DEBUG("DEBUG variable_list -> variable\n");
    }
    | variable_list ',' variable
    {
        $1->push_back($3);
        $$ = $1;
        LOG_DEBUG("DEBUG variable_list -> variable_list ',' variable\n");
    }
    | error
    {
        syntax_error("变量定义出错 请检查是否符合规范");
    }
    ;
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
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_varpart\n");
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
        $$ = new std::vector<ExprStmt *>();
        LOG_DEBUG("DEBUG id_varpart -> empty\n");
    }
    | '[' expression_list ']'
    {
        $$ = $2;
        LOG_DEBUG("DEBUG id_varpart -> '[' expression_list ']'\n");
    }
    | error
    {
        syntax_error("数组下标定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.1 
* rule  :  procedure_call -> IDENTIFIER | IDENTIFIER '(' expression_list ')'
* node :   FuncCallStmt * proc_call
* son :  std::string id  std::vector<ExprStmt *> * args
* error : 过程调用定义出错 请检查是否符合规范
*/
procedure_call : IDENTIFIER
    {
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = $1;
        $$ = proc_call;
        delete $1;
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER\n");
    }
    | IDENTIFIER '(' expression_list ')'
    {
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = $1;
        for(auto expr : *$3){
            proc_call->args.push_back(std::unique_ptr<ExprStmt>(expr));
        }
        delete $1;
        delete $3;
        $$ = proc_call;
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER '(' expression_list ')'\n");
    }
    | error
    {
        syntax_error("过程调用定义出错 请检查是否符合规范");
    }
    ;


/*
* no : 5.2
* rule  :  else_part -> empty | ELSE statement
* node :   Stmt * stmt
* son :  Stmt * 
* error : else 语法定义出错 请检查是否符合规范
*/
else_part : /*empty*/
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG else_part -> empty\n");
    }
    | ELSE statement
    {
        $$ = $2;
        LOG_DEBUG("DEBUG else_part -> ELSE statement\n");
    }
    | error
    {
        syntax_error("else 语法定义出错 请检查是否符合规范");
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
        LOG_DEBUG("DEBUG expression_list -> expression\n");
        printf("%s",expr_stmt_list_str($$,0).c_str());
    }
    | expression_list ',' expression
    {
        $1->push_back($3);
        $$ = $1;
        LOG_DEBUG("DEBUG expression_list -> expression_list ',' expression\n");
        printf("%s",expr_stmt_list_str($$,0).c_str());
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
        expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->type = RelExprStmt::RelExprType::NULL_TYPE;
        expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>($1);
        $$ = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression\n");
    }
    | simple_expression relop simple_expression
    {
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->type = get_rel_expr_type($2);
        expr->rel_expr->rel_expr = std::make_unique<RelExprStmt>();
        expr->rel_expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>($1);
        expr->rel_expr->add_expr = std::unique_ptr<AddExprStmt>($3);
        $$ = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression relop simple_expression\n");
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;


/*
* no : 5.5
* rule  :  simple_expression -> term | simple_expression addop term
* node :   AddExprStmt * add_expr
* son : AddExprType type; AddExprStmt * add_expr; MulExprStmt * mul_expr
* error : 表达式定义出错 请检查是否符合规范
*/
simple_expression : term
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = AddExprStmt::AddExprType::NULL_TYPE;
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>($1);
        $$ = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> term\n");
    }
    | simple_expression addop term
    {
        AddExprStmt * add_expr = new AddExprStmt();
        add_expr->type = get_add_expr_type($2);
        add_expr->mul_expr = std::unique_ptr<MulExprStmt>($3);
        add_expr->add_expr = std::unique_ptr<AddExprStmt>($1);
        $$ = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> simple_expression %lld term\n", $2);
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.6
* rule  :  term -> factor | term mulop factor
* node :   MulExprStmt *  mul_expr
* son : MulExprType type UnaryExprStmt * unary_expr  MulExprStmt * mul_expr
* error : 表达式定义出错 请检查是否符合规范
*/
term : factor
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = MulExprStmt::MulExprType::NULL_TYPE;
        mul_expr->unary_expr = std::unique_ptr<UnaryExprStmt>($1);
        $$ = mul_expr;
        LOG_DEBUG("DEBUG term -> factor\n");
    }
    | term mulop factor
    {
        MulExprStmt * mul_expr = new MulExprStmt();
        mul_expr->type = get_mul_expr_type($2);
        mul_expr->mul_expr = std::unique_ptr<MulExprStmt>($1);
        mul_expr->unary_expr = std::unique_ptr<UnaryExprStmt>($3);
        $$ = mul_expr;
        LOG_DEBUG("DEBUG term -> term mulop factor\n");
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
    ;

/*
* no : 5.7
* rule  :  factor -> INTEGER | REAL | variable | '(' expression ')' | IDENTIFIER '(' expression_list ')' | '-' factor 
* node :    UnaryExprStmt * unary_expr
* son :  UnaryExprType type; PrimaryExprStmt * primary_expr; 
* error : 表达式定义出错 请检查是否符合规范
*/
factor : INTEGER
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> INTEGER\n");
    }
    | REAL
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> REAL\n");
    }
    | variable
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::LVal;
        unary_expr->primary_expr->value->lval = std::unique_ptr<LValStmt>($1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> variable\n");
    }
    | '(' expression ')'
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Parentheses;
        unary_expr->primary_expr->expr = std::unique_ptr<ExprStmt>($2);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '(' expression ')'\n");
    }
    | IDENTIFIER '(' expression_list ')'
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::NULL_TYPE;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::FuncCall;
        unary_expr->primary_expr->value->func_call = std::make_unique<FuncCallStmt>();
        unary_expr->primary_expr->value->func_call->id = $1;
        for(auto expr : *$3){
            unary_expr->primary_expr->value->func_call->args.push_back(std::unique_ptr<ExprStmt>(expr));
        }
        delete $1;
        delete $3;
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> IDENTIFIER '(' expression_list ')'\n");
    }
    | '-' factor
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->type =UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = std::move($2->primary_expr);
        delete $2;
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' factor\n");
    }
    | error
    {
        syntax_error("表达式定义出错 请检查是否符合规范");
    }
/*
* addop ->  + | - | or
*/
addop : '+' { $$ = 0; } | '-' { $$ = 1; } | OR { $$ = 2; }

/*
* relop -> = | <> | < | <= | > | >= 
*/
relop : '=' { $$ = 0; } | NE { $$ = 1; } | '<' { $$ = 2; } | LE { $$ = 3; } | '>' { $$ = 4; } | GE { $$ = 5; }

/*
* mulop -> * | / | div | mod | and
*/
mulop : '*' { $$ = 0; } | '/' { $$ = 1; } | DIV { $$ = 2; } | MOD { $$ = 3; } | AND { $$ = 4; }


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
