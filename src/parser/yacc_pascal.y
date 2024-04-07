%{
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
    BRACE_PAIR
    BREAK
    CONTINUE

%define api.pure full
%define parse.error custom
/* %define parse.error verbose */
/** 启用位置标识 **/
%locations
%define parse.trace
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * code_str }
%parse-param { ProgramStmt ** program}
%parse-param { void * scanner }

// 定义初始动作
%initial-action 
{
    *program = nullptr;
};


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
%type <value>               const_value
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
%type <stmt_list>           statement
%type <func_call_stmt>      procedure_call
%type <lval_list>           variable_list
%type <lval>                variable
%type <expr_list>           id_varpart
%type <expr_list>           expression_list
%type <expr_list>           array_index_expression
%type <expr>                expression   
%type <add_expr>            simple_expression
%type <mul_expr>            term
%type <unary_expr>          factor
/* %type <stmt_list>           else_part */
/* %type <expr_list>           id_random */
// 对丢弃的符号进行析构
%destructor {} <program_struct> <boolean> <number> <charactor> <basic_type>
%destructor { free($$); } IDENTIFIER <string> <real>
%destructor {
    if($$ != nullptr){
        for(auto kv_pair : *$$){
            delete kv_pair;
        }
    }
    delete $$;
} <var_decls> <period_list> <func_decl_list> <stmt_list> <lval_list> <expr_list>
%destructor {
    if($$ != nullptr){
        for(auto pair : *$$){
            delete pair->second;
            delete pair;
        }
        delete $$;
    }
} <kv_pair_list>
%destructor { delete $$; } <*>
// THEN 和 ELSE 为右结合
%nonassoc THEN
%nonassoc ELSE

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
        current_rule = CurrentRule::ProgramStruct;
        ProgramStmt * program_struct = new ProgramStmt();
        program_struct->head = std::unique_ptr<ProgramHeadStmt>($1);
        program_struct->body = std::unique_ptr<ProgramBodyStmt>($3);
        LOG_DEBUG("DEBUG programstruct -> program_head ';' program_body '.'");
        *program = program_struct;
        $$ = nullptr; // 防止报错
    }
    | error  ';'  program_body '.'
    {
        ProgramStmt * program_struct = new ProgramStmt();
        *program = program_struct;
        delete $3;
        $$ = nullptr;
        LOG_DEBUG("ERROR programstruct -> error ';' program_body '.'");
        // yyerror(&yylloc, "code_str", program, scanner, "程序头定义出错，请检查。");
    }
    | program_head  ';'  error '.'
    {
        ProgramStmt * program_struct = new ProgramStmt();
        *program = program_struct;
        delete $1;
        $$ = nullptr;
        LOG_DEBUG("ERROR programstruct -> program_head ';' error '.'");
        // yyerror(&yylloc, "code_str", program, scanner, "程序体定义出错，请检查。");
    }
    | error  ';'  error '.'
    {
        ProgramStmt * program_struct = new ProgramStmt();
        *program = program_struct;
        $$ = nullptr;
        LOG_DEBUG("ERROR programstruct -> error ';' error '.'");
        // yyerror(&yylloc, "code_str", program, scanner, "程序头、程序体定义出错，请检查。");
    }
    ;

/*
* no : 1.2
* rule  :  program_head -> "program" IDENTIFIER '(' idlist ')' | "program" IDENTIFIER
* node :  ProgramHeadStmt * program_head
* son  :  char * std::vector<std::string>
* error : 程序头定义出错 请检查是否符合规范
*/
program_head : PROGRAM IDENTIFIER '(' idlist ')'
    {
        current_rule = CurrentRule::ProgramHead;
        $$ = new ProgramHeadStmt();
        $$->id_list = *$4;
        delete $4;
        free($2);
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER '(' idlist ')'");
    }
    | PROGRAM IDENTIFIER
    {
        current_rule = CurrentRule::ProgramHead;
        $$ = new ProgramHeadStmt();
        $$->id_list.emplace_back(std::string($2));
        LOG_DEBUG("DEBUG program_head -> PROGRAM IDENTIFIER");
        free($2);
    }
    | PROGRAM error
    {
        $$ = nullptr;
        LOG_DEBUG("ERROR program_head -> PROGRAM error");
        // yyerror(&yylloc, "code_str", program, scanner, "程序名定义出错，请检查。");
        yyerrok;
    }
    ;


/*
* no : 1.3
* rule  :  program_body -> const_declarations var_declarations subprogram_declarations compound_statement
* node :  ProgramBodyStmt * program_body
* son  :  ConstDeclStmt * const_decl std::vector<VarDeclStmt *> var_decl  std::vector<FuncDeclStmt *>  func_decl  std::vector<BaseStmt *>  comp_stmt
* error : 程序体定义出错 请检查是否符合规范
*/
program_body : const_declarations var_declarations subprogram_declarations compound_statement
    {
        current_rule = CurrentRule::ProgramBody;
        ProgramBodyStmt* program_body = new ProgramBodyStmt();
        if($1 != nullptr) {program_body->const_decl = std::unique_ptr<ConstDeclStmt>($1);}
        if($2 != nullptr){
            for(auto var_decl : *$2){
                program_body->var_decl.emplace_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete $2;
        }
        if($3 != nullptr){
            for(auto func_decl : *$3){
                program_body->func_decl.emplace_back(std::unique_ptr<FuncDeclStmt>(func_decl));
            }
            delete $3;
        }
        if($4 != nullptr){
            for(auto stmt : *$4){
                program_body->comp_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete $4;
        }
        $$ = program_body;
        LOG_DEBUG("DEBUG program_body -> const_declarations var_declarations subprogram_declarations compound_statement");
    }
    | error_recovery const_declarations var_declarations subprogram_declarations compound_statement
    {
        if($2 != nullptr) {delete $2;}
        if($3 != nullptr){
            for(auto var_decl : *$3){
                delete var_decl;
            }
            delete $3;
        }
        if($4 != nullptr){
            for(auto func_decl : *$4){
                delete func_decl;
            }
            delete $4;
        }
        if($5 != nullptr){
            for(auto stmt : *$5){
                delete stmt;
            }
            delete $5;
        }
        $$ = nullptr;
        LOG_DEBUG("DEBUG program_body -> error_recovery const_declarations var_declarations subprogram_declarations compound_statement");
    }
    ;

    

/*
* no : 1.4
* rule  :  idlist -> IDENTIFIER | idlist ',' IDENTIFIER
* node :  std::vector<std::string> * id_list
* son  :  string
* error : 标识符定义错误 请检查是否符合规范
*/
idlist : IDENTIFIER
    {
        current_rule = CurrentRule::IdList;
        $$ = new std::vector<std::string>();
        $$->emplace_back(std::string($1));
        LOG_DEBUG("DEBUG idlist -> IDENTIFIER");
        free($1);
    }
    | idlist ',' IDENTIFIER
    {
        current_rule = CurrentRule::IdList;
        $1->emplace_back(std::string($3));
        $$ = $1;
        LOG_DEBUG("DEBUG idlist -> idlist ',' IDENTIFIER");
        free($3);
    }
    ;

/*
* no : 1.5
* rule  :  const_declarations -> empty | "const" const_declaration ';'
* node :  ConstDeclStmt * const_decls
* son  :  std::vector<std::pair<std::string, ValueStmt *> *> *
* error : 常量定义出错 请检查是否符合规范
*/
const_declarations : /*empty*/
    {
        current_rule = CurrentRule::ConstDeclarations;
        $$ = nullptr;
        LOG_DEBUG("DEBUG const_declarations -> empty");
    }
    | CONST const_declaration ';' 
    {
        current_rule = CurrentRule::ConstDeclarations;
        ConstDeclStmt * const_decls = new ConstDeclStmt();
        for(auto kv_pair : *$2){
            const_decls->pairs.emplace_back(std::make_pair(kv_pair->first, kv_pair->second));
            delete kv_pair;
        }
        // 疑似内存泄漏
        delete $2;
        $$ = const_decls;
        for(auto &t: const_decls->pairs){
            LOG_INFO("Get Const Type:%d, pointer %p", t.second->type, t.second.get());
            if(t.second->str) {
                LOG_INFO("Get string:%s",t.second->str->val.c_str());
            }
        }
        LOG_DEBUG("DEBUG const_declarations -> CONST const_declaration ';' const_declarations");
    }
    | CONST error ';'
    {
        $$ = nullptr;
        LOG_DEBUG("ERROR const_declarations -> CONST error ;");
        yyerrok;
    }
    ;


/*
* no : 1.6
* rule  :  const_declaration -> IDENTIFIER = const_value | const_declaration ; IDENTIFIER = const_value
* node :  std::vector<std::pair<std::string, ValueStmt *> *> *
* son  :  char *   ValueStmt *
*/
const_declaration : IDENTIFIER '=' const_value
    {
        current_rule = CurrentRule::ConstDeclaration;
        std::vector<std::pair<std::string, ValueStmt *> *> * const_decls = new std::vector<std::pair<std::string, ValueStmt *> *>();
        std::pair<std::string, ValueStmt *> * kv_pair = new std::pair<std::string, ValueStmt *>($1, $3);
        const_decls->emplace_back(kv_pair);
        free($1);
        $$ = const_decls;
    }
    | const_declaration ';' IDENTIFIER '=' const_value
    {
        current_rule = CurrentRule::ConstDeclaration;
        $1->emplace_back(new std::pair<std::string, ValueStmt *>($3, $5));
        free($3);
        $$ = $1; // 不需要删除
    }
    |  error ';' IDENTIFIER '=' const_value
    {
        $$ = nullptr;
        LOG_DEBUG("ERROR const_declaration -> error ';' IDENTIFIER = const_value");
        free($3);
        delete $5;
        yyerrok;
    }
    ;


/*
* no : 1.7
* rule  :  const_value -> INTEGER | REAL | CHAR | '-' INTEGER | '-' REAL | '+' INTEGER | '+' REAL | ' CHAR '
* node :  ValueStmt * num_value
* son  :  long long | double | char
* error : 常量 请检查是否为合法常量
*/
const_value: INTEGER
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, $1);
        $$ = num_value;
    }
    | '+' INTEGER
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, $2);
        $$ = num_value;
    }
    | '-' INTEGER
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, ($2) * -1);
        $$ = num_value;
    }
    | REAL
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof($1);
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string($1);
        free($1);
        $$ = num_value;
    }
    | '+' REAL
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof($2);
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string($2);
        free($2);
        $$ = num_value;
    }
    | '-' REAL
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        double val = atof($2);
        fill_number_stmt(num_value->number, val);
        num_value->number->literal = std::string($2);
        free($2);
        $$ = num_value;
    }
    | CHAR
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Number;
        num_value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(num_value->number, $1);
        LOG_DEBUG("DEBUG const_value -> CHAR, value: %c", $1);
        $$ = num_value;
    }
    | STRING 
    {
        ValueStmt * num_value = new ValueStmt();
        num_value->type = ValueStmt::ValueType::Str;
        num_value->str = std::make_unique<StrStmt>();
        num_value->str->val = std::string($1).substr(1, std::string($1).length() - 2);
        free($1);
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
        LOG_DEBUG("DEBUG var_declarations -> empty");
    }
    | VAR var_declaration ';'
    {
        current_rule = CurrentRule::VarDeclarations;
        $$ = $2;
        LOG_DEBUG("DEBUG var_declarations -> VAR var_declaration ';'");
    }
    | VAR error ';'
    {
        $$ = nullptr;
        LOG_DEBUG("ERROR var_declarations -> VAR error ;");
        yyerrok;
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
        current_rule = CurrentRule::VarDeclaration;
        std::vector<VarDeclStmt *> * var_decls = new std::vector<VarDeclStmt *>();
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), $1->begin(), $1->end());
        // deal with type
        var_decl->basic_type = $3->basic_type;
        var_decl->data_type = $3->data_type;
        var_decl->array_range = std::move($3->array_range);
        delete $1;
        delete $3;
        var_decls->emplace_back(var_decl);
        $$ = var_decls;
        LOG_DEBUG("DEBUG var_declaration -> idlist ':' type");
    }
    | var_declaration ';' idlist ':' type
    {
        current_rule = CurrentRule::VarDeclaration;
        VarDeclStmt * var_decl = new VarDeclStmt();
        var_decl->id.insert(var_decl->id.end(), $3->begin(), $3->end());
        // deal with type
        var_decl->basic_type = $5->basic_type;
        var_decl->data_type = $5->data_type;
        var_decl->array_range = std::move($5->array_range);
        delete $3;
        delete $5;
        $1->emplace_back(var_decl);
        $$ = $1;
        LOG_DEBUG("DEBUG var_declaration -> var_declaration ';' idlist ':' type");
    }
    | error ';' idlist ':' type
    {
        $$ = nullptr;
        LOG_DEBUG("ERROR var_declaration -> error ';' idlist ':' type");
        delete $3;
        delete $5;
        yyerrok;
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
        current_rule = CurrentRule::Type;
        VarDeclStmt * type_stmt = new VarDeclStmt();
        // TODO 处理type_size
        type_stmt->data_type = DataType::BasicType;
        type_stmt->basic_type = $1;
        $$ = type_stmt;
        LOG_DEBUG("DEBUG type -> basic_type");
    }
    | ARRAY '[' period_list ']' OF basic_type
    {
        current_rule = CurrentRule::Type;
        VarDeclStmt * type_stmt = new VarDeclStmt();
        type_stmt->data_type = DataType::ArrayType;
        type_stmt->basic_type = $6;
        for(auto period : *$3){
            type_stmt->array_range.emplace_back(std::unique_ptr<PeriodStmt>(period));
        }
        delete $3;
        $$ = type_stmt;
        LOG_DEBUG("DEBUG type -> ARRAY '[' period_list ']' OF basic_type");
    };


/*
* no : 2.4
* rule  : basic_type -> INTEGER_KW | REAL_KW | BOOLEAN_KW | CHAR_KW
* node :  BasicType
*/
basic_type: INTEGER_KW
        {
            $$ = BasicType::INT;
            LOG_DEBUG("DEBUG basic_type -> INTEGER_KW");
        }
        | REAL_KW
        {
            $$ = BasicType::REAL;
            LOG_DEBUG("DEBUG basic_type -> REAL_KW");
        }
        | BOOLEAN_KW
        {
            $$ = BasicType::BOOLEAN;
            LOG_DEBUG("DEBUG basic_type -> BOOLEAN_KW");
        }
        | CHAR_KW
        {
            $$ = BasicType::CHAR;
            LOG_DEBUG("DEBUG basic_type -> CHAR_KW");
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
            $$->emplace_back(period);
            // debug
            LOG_DEBUG("DEBUG period_list -> INTEGER '..' INTEGER");
        }
        | period_list ',' INTEGER DOUBLE_DOT INTEGER
        {
            PeriodStmt * period = new PeriodStmt();
            period->begin = $3;
            period->end = $5;
            $1->emplace_back(period);
            $$ = $1;
            // debug
            LOG_DEBUG("DEBUG period_list -> period_list ',' INTEGER '..' INTEGER");
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
            $$ = nullptr;
            LOG_DEBUG("DEBUG subprogram_declarations -> empty");
        }
        | subprogram_declarations subprogram ';'
        {
            current_rule = CurrentRule::SubprogramDeclarations;
            if($1 == nullptr){
                std::vector<FuncDeclStmt *> * func_decl_list = new std::vector<FuncDeclStmt *>();
                func_decl_list->emplace_back($2);    
                $$ = func_decl_list;
            }else{
                $1->emplace_back($2);
                $$ = $1;
            }
            LOG_DEBUG("DEBUG subprogram_declarations -> subprogram_declarations subprogram ';'");
        }
        ;


/*
* no : 2.7
* rule  :  subprogram -> subprogram_head ';' subprogram_body
* node :  FuncDeclStmt * func_decl
* son  :  FuncHeadDeclStmt * func_head FuncBodyDeclStmt * func_body
* error : 子函数定义出错 请检查是否符合规范
*/
subprogram : subprogram_head ';' subprogram_body
        {
            current_rule = CurrentRule::Subprogram;
            FuncDeclStmt * subprogram = new FuncDeclStmt();
            subprogram->header = std::unique_ptr<FuncHeadDeclStmt>($1);
            subprogram->body = std::unique_ptr<FuncBodyDeclStmt>($3);
            $$ = subprogram;
            LOG_DEBUG("DEBUG subprogram -> subprogram_head ';' subprogram_body");
        }
        ;


/*
* no : 2.8
* rule  :  subprogram_head -> PROCEDURE IDENTIFIER formal_parameter | FUNCTION IDENTIFIER formal_parameter ':' basic_type
* node :  FuncHeadDeclStmt * func_head
* son  :  std::string func_name;  BasicType ret_type; std::vector<std::unique_ptr<VarDeclStmt>> args;
* error : 子函数头定义出错 请检查是否符合规范
*/
subprogram_head: PROCEDURE IDENTIFIER formal_parameter
        {
            current_rule = CurrentRule::SubprogramHead;
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string($2);
            sub_head->ret_type = BasicType::VOID;
            if($3 != nullptr){
                for(auto formal_parameter : *$3){
                    sub_head->args.emplace_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete $3;
            }
            $$ = sub_head;
            free($2);
            LOG_DEBUG("DEBUG subprogram_head -> PROGRAM IDENTIFIER formal_parameter");
        }
        | FUNCTION IDENTIFIER formal_parameter ':' basic_type
        {
            current_rule = CurrentRule::SubprogramHead;
            FuncHeadDeclStmt * sub_head = new FuncHeadDeclStmt();
            sub_head->func_name = std::string($2);
            sub_head->ret_type = $5;
            if($3 != nullptr){
                for(auto formal_parameter : *$3){
                    sub_head->args.emplace_back(std::unique_ptr<VarDeclStmt>(formal_parameter));
                }
                delete $3;
            }
            $$ = sub_head;
            free($2);
            LOG_DEBUG("DEBUG subprogram_head -> FUNCTION IDENTIFIER formal_parameter ':' basic_type");
        }
        | FUNCTION error
        {
            $$ = nullptr;
            LOG_DEBUG("ERROR subprogram_head -> FUNCTION error");
            // yyerror(&yylloc, "code_str", program, scanner, "子程序头中标识符定义出错，请检查。");
            yyerrok;
        }
        | PROCEDURE error
        {
            $$ = nullptr;
            LOG_DEBUG("ERROR subprogram_head -> PROCEDURE error");
            // yyerror(&yylloc, "code_str", program, scanner, "子程序头中标识符定义出错，请检查。");
            yyerrok;
        };

/*
* no : 2.9
* rule  :  formal_parameter -> empty | '(' parameter_list ')'
* node :  std::vector<VarDeclStmt *>*
* son  :  VarDeclStmt *
* error : 参数定义出错 请检查是否符合规范
*/
formal_parameter : /* empty */
        {
            $$ = nullptr;
            LOG_DEBUG("DEBUG formal_parameter -> empty");
        }
        | '(' parameter_list ')'
        {
            current_rule = CurrentRule::FormalParameter;
            $$ = $2;
            LOG_DEBUG("DEBUG formal_parameter -> '(' parameter_list ')'");
        };



/*
* no : 2.10
* rule  : parameter_list -> parameter | parameter_list ';' parameter
* node :  std::vector<VarDeclStmt *>*
* son  :  VarDeclStmt*
* error :
*/
parameter_list :/* empty */
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG parameter_list -> empty");
    }
    |parameter
    {
        $$ = new std::vector<VarDeclStmt *>();
        $$->emplace_back($1);
        LOG_DEBUG("DEBUG parameter_list -> parameter");
    }
    | parameter_list ';' parameter
    {
        $1->emplace_back($3);
        $$ = $1;
        LOG_DEBUG("DEBUG parameter_list -> parameter_list ';' parameter");
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
            $$ = $1;
            $$->is_var = true;
            LOG_DEBUG("DEBUG parameter -> var_parameter");
        }
        | value_parameter
        {
            $$ = $1;
            $$->is_var = false;
            LOG_DEBUG("DEBUG parameter -> value_parameter");
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
            $$ = $2;
            LOG_DEBUG("DEBUG var_parameter -> VAR value_parameter");
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
            var_decl->data_type = DataType::BasicType;
            var_decl-> basic_type = $3;
            var_decl->is_var = false;
            // 疑似内存泄漏
            delete $1;
            $$ = var_decl;
            LOG_DEBUG("DEBUG value_parameter -> idlist ':' basic_type");
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
        current_rule = CurrentRule::SubprogramBody;
        FuncBodyDeclStmt * func_body = new FuncBodyDeclStmt();
        if($1 != nullptr) func_body->const_decl = std::unique_ptr<ConstDeclStmt>($1);
        if($2 != nullptr){
            for(auto var_decl : *$2){
                func_body->var_decl.emplace_back(std::unique_ptr<VarDeclStmt>(var_decl));
            }
            delete $2;
        }
        if($3 != nullptr){
            for(auto stmt : *$3){
                func_body->comp_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete $3;
        }
        $$ = func_body;
        LOG_DEBUG("DEBUG subprogram_body -> const_declarations var_declarations compound_statement");
    }
    ;
/*
* no : 3.5
* rule  :  compound_statement -> BEGIN_TOKEN statement_list END
* node :  std::vector<BaseStmt *> * stmt_list
* son  :  BaseStmt *
* error : 复合语句定义出错 请检查是否符合规范
*/
compound_statement : BEGIN_TOKEN statement_list END
    {
        current_rule = CurrentRule::CompoundStatement;
        $$ = $2;
        LOG_DEBUG("DEBUG compound_statement -> BEGIN_TOKEN statement_list END");
    }
    ;
/*
* no : 3.6
* rule  :  statement_list -> statement | statement_list ';' statement
* node :  std::vector<BaseStmt *> * stmt_list
* son  :  BaseStmt *
* error : 语句定义出错 请检查是否符合规范
*/
statement_list : statement
    {
        $$ = $1;
        LOG_DEBUG("DEBUG statement_list -> statement");
    }
    | statement_list ';' statement
    {
        // copy the vector
        current_rule = CurrentRule::StatementList;
        if($3 != nullptr){
            for(auto stmt : *$3){
                if($1 != nullptr){
                    $1->emplace_back(stmt);
                }
                else{
                    std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
                    stmt_list->emplace_back(stmt);
                    $1 = stmt_list;
                }
            }
        }
        $$ = $1;
        delete $3;
        LOG_DEBUG("DEBUG statement_list -> statement_list ';' statement");
    }
    | error ';' statement
    {
        if($3 != nullptr){
            for(auto kv_pair : *$3){
                delete kv_pair;
            }
        }
        delete $3;
        $$ = nullptr;
        LOG_DEBUG("ERROR statement_list -> error ';' statement");
        // yyerror(&yylloc, "code_str", program, scanner, "语句定义出错，请检查。");
        yyerrok;
    }
    | statement_list ';' error
    {
        if($1 != nullptr){
            for(auto kv_pair : *$1){
                delete kv_pair;
            }
        }
        delete $1;
        $$ = nullptr;
        LOG_DEBUG("ERROR statement_list -> statement_list ';' error");
        // yyerror(&yylloc, "code_str", program, scanner, "语句定义出错，请检查。");
        yyerrok;
    }
    ;

/*
* no : 4.1
* rule  :  statement -> empty | variable ASSIGNOP expression |
* IDENTIFIER ASSIGNOP expression | procedure_call | compound_statement | 
* IF expression THEN statement else_part | FOR IDENTIFIER ASSIGNOP expression TO expression DO statement | 
* READ '(' variable_list ')' | WRITE '(' expression_list ')' 
* node :   std::vector<BaseStmt *> *
* son :  Stmt *
* error : 函数体定义出错 请检查是否符合规范
*/
statement : /*empty*/
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG statement -> empty");
    }
    | variable ASSIGNOP expression
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::unique_ptr<LValStmt>($1);
        assign_stmt->expr = std::unique_ptr<ExprStmt>($3);
        stmt_list->emplace_back(assign_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> variable ASSIGNOP expression");
    }
    /* | IDENTIFIER ASSIGNOP expression
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        AssignStmt * assign_stmt = new AssignStmt();
        assign_stmt->lval = std::make_unique<LValStmt>();
        assign_stmt->lval->id = std::string($1);
        // how to deal with array_index
        // assign_stmt->lval->array_index = std::vector<std::unique_ptr<ExprStmt>>();
        assign_stmt->expr = std::unique_ptr<ExprStmt>($3);
        stmt_list->emplace_back(assign_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> IDENTIFIER ASSIGNOP expression");
    } */
    | procedure_call
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        stmt_list->emplace_back($1);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> procedure_call");
    }
    | compound_statement
    {
        $$ = $1;
        LOG_DEBUG("DEBUG statement -> compound_statement");
    }
    | WHILE expression DO statement
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WhileStmt * while_stmt = new WhileStmt();
        while_stmt->expr = std::unique_ptr<ExprStmt>($2);
        if($4 != nullptr){
            for(auto stmt : *$4){
                while_stmt->stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
            delete $4;
        }
        stmt_list->emplace_back(while_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> WHILE expression DO statement");
    }
    | IF expression THEN statement %prec THEN
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>($2);
        if($4 != nullptr){
            for(auto stmt : *$4){
                if_stmt->true_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        delete $4;
        stmt_list->emplace_back(if_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement");
    }
    | IF expression THEN statement ELSE statement
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        IfStmt * if_stmt = new IfStmt();
        if_stmt->expr = std::unique_ptr<ExprStmt>($2);
        if($4 != nullptr){
            for(auto stmt : *$4){
                if_stmt->true_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        if($6 != nullptr){
            for(auto stmt : *$6){
                if_stmt->false_stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        stmt_list->emplace_back(if_stmt);
        $$ = stmt_list;
        delete $4;
        delete $6;
        LOG_DEBUG("DEBUG statement -> IF expression THEN statement ELSE statement");
    }
    | FOR IDENTIFIER ASSIGNOP expression TO expression DO statement
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ForStmt * for_stmt = new ForStmt();
        for_stmt->id = std::string($2);
        for_stmt->begin = std::unique_ptr<ExprStmt>($4);
        for_stmt->end = std::unique_ptr<ExprStmt>($6);
        if($8 != nullptr){
            for(auto stmt : *$8){
                for_stmt->stmt.emplace_back(std::unique_ptr<BaseStmt>(stmt));
            }
        }
        stmt_list->emplace_back(for_stmt);
        $$ = stmt_list;
        free($2);
        delete $8;
        LOG_DEBUG("DEBUG statement -> FOR IDENTIFIER ASSIGNOP expression TO expression DO statement");
    }
    | READ '(' variable_list ')'
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ReadFuncStmt * read_stmt = new ReadFuncStmt();
        for(auto lval : *$3){
            read_stmt->lval.emplace_back(std::unique_ptr<LValStmt>(lval));
        }
        delete $3;
        stmt_list->emplace_back(read_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> READ '(' variable_list ')'");
    }
    | WRITE '(' expression_list ')'
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        WriteFuncStmt * write_stmt = new WriteFuncStmt();
        if($3 != nullptr){
            for(auto expr : *$3){
                write_stmt->expr.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
        }
        stmt_list->emplace_back(write_stmt);
        $$ = stmt_list;
        delete $3;
        LOG_DEBUG("DEBUG statement -> WRITE '(' expression_list ')'");
    }
    | BREAK
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        BreakStmt * break_stmt = new BreakStmt();
        stmt_list->emplace_back(break_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> BREAK");
    }
    | CONTINUE
    {
        std::vector<BaseStmt *> * stmt_list = new std::vector<BaseStmt *>();
        ContinueStmt * continue_stmt = new ContinueStmt();
        stmt_list->emplace_back(continue_stmt);
        $$ = stmt_list;
        LOG_DEBUG("DEBUG statement -> CONTINUE");
    }
    ;

/*
* no : 4.2
* rule  :  variable_list -> variable | variable_list ',' variable
* node :   std::vector<LValStmt *> *  lval_list
* son :  std::string id  std::vector<std::unique_ptr<ExprStmt>> array_index
* error : 变量定义出错 请检查是否符合规范
*/
variable_list : variable
    {
        current_rule = CurrentRule::VariableList;
        std::vector<LValStmt *> * lval_list = new std::vector<LValStmt *>();
        lval_list->emplace_back($1);
        $$ = lval_list;
        LOG_DEBUG("DEBUG variable_list -> variable");
    }
    | variable_list ',' variable
    {
        current_rule = CurrentRule::VariableList;
        if($3 != nullptr){
                $1->emplace_back($3);
            }
            else{
                std::vector<LValStmt *> * lval_list = new std::vector<LValStmt *>();
                lval_list->emplace_back($3);
                $1 = lval_list;
            }

        $$ = $1;
        LOG_DEBUG("DEBUG variable_list -> variable_list ',' variable");
    }
    | error ',' variable
    {
        delete $3;
        $$ = nullptr;
        LOG_DEBUG("ERROR variable_list -> error ',' variable");
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
        current_rule = CurrentRule::Variable;
        $$ = new LValStmt();
        $$->id = std::string($1);
        if($2 != nullptr){
            for(auto expr : *$2){
                $$->array_index.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete $2;
        }
        free($1);
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_varpart");
    }
    /* | IDENTIFIER id_random
    {
        $$ = new LValStmt();
        $$->id = std::string($1);
        if($2 != nullptr){
            for(auto expr : *$2){
                $$->array_index.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete $2;
        }
        LOG_DEBUG("DEBUG variable -> IDENTIFIER id_random");
    } */
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
        LOG_DEBUG("DEBUG id_varpart -> empty");
    }
    | '[' expression_list ']'
    {
        current_rule = CurrentRule::IdVarpart;
        if($2 != nullptr){
            $$ = $2;    
        }else{
            yyerror(&@2, "code_str", program, scanner, "数组下标定义出错 请检查是否符合规范");
        }
        LOG_DEBUG("DEBUG id_varpart -> '[' expression_list ']'");
    }
    | '[' expression BRACE_PAIR array_index_expression
    {
        current_rule = CurrentRule::IdVarpart;
        if($4 != nullptr){
            $$ = $4;
        } else {
            
        }
        $$->emplace_back($2);
        std::reverse($$->begin(), $$->end());
        LOG_DEBUG("DEBUG id_varpart -> '[' expression BRACE_PAIR array_index_expression");
    }
    ;

/*
* no : 4.5
* rule  :  array_index_expression -> expression ']' | ex
* node :   std::vector<ExprStmt *> * expr_list
* son :  ExprStmt *
* error : 随机存取数组定义出错 请检查是否符合规范
*/
array_index_expression: expression ']'
    {
        current_rule = CurrentRule::ArrayIndexExpression;
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->emplace_back($1);
        $$ = expr_list;
        LOG_DEBUG("DEBUG array_index_expression -> expression_list");
    }
    | expression BRACE_PAIR array_index_expression
    {
        current_rule = CurrentRule::ArrayIndexExpression;
        $3->emplace_back($1);
        $$ = $3;
        LOG_DEBUG("DEBUG array_index_expression -> array_index_expression BRACE_PAIR expression ']'");
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
        current_rule = CurrentRule::ProcedureCall;
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string($1);
        $$ = proc_call;
        free($1);
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER");
    }
    | IDENTIFIER '(' expression_list ')'
    {
        current_rule = CurrentRule::ProcedureCall;
        FuncCallStmt * proc_call = new FuncCallStmt();
        proc_call->id = std::string($1);
        if($3 != nullptr){
            for(auto expr : *$3){
                proc_call->args.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete $3;
        }
        $$ = proc_call;
        free($1);
        LOG_DEBUG("DEBUG procedure_call -> IDENTIFIER '(' expression_list ')'");
    }
    ;


/*
* no : 5.2
* rule  :  else_part -> empty | ELSE statement
* node :   std::vector<BaseStmt *> * stmt 
* son :  Stmt * 
* error : else 语法定义出错 请检查是否符合规范
*/
/* else_part : //empty
    {
        $$ = nullptr;
        LOG_DEBUG("DEBUG else_part -> empty");
    }
    | ELSE statement
    {
        // 强行取第一个
        $$ = $2;
        LOG_DEBUG("DEBUG else_part -> ELSE statement");
    }
    | error
    {
        syntax_error(&@1, "else 语法定义出错 请检查是否符合规范");
    }
    ; */

/*
* no : 5.3
* rule  :  expression_list ->empty | expression | expression_list  ','  expression
* node :   std::vector<ExprStmt *> * expr_list
* son : ExprStmt *
* error : 表达式定义出错 请检查是否符合规范
*/
expression_list : {
        $$ = nullptr;
        LOG_DEBUG("DEBUG expression_list -> empty");
    }
    | expression
    {
        current_rule = CurrentRule::ExpressionList;
        std::vector<ExprStmt *> * expr_list = new std::vector<ExprStmt *>();
        expr_list->emplace_back($1);
        $$ = expr_list;
        LOG_DEBUG("DEBUG expression_list -> expression");
    }
    | expression_list ',' expression
    {
        current_rule = CurrentRule::ExpressionList;
        $1->emplace_back($3);
        $$ = $1;
        LOG_DEBUG("DEBUG expression_list -> expression_list ',' expression");
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
        current_rule = CurrentRule::Expression;
        ExprStmt * expr = new ExprStmt();
        expr->rel_expr = std::make_unique<RelExprStmt>();
        RelExprStmt::Term term;
        term.type = RelExprStmt::RelExprType::NULL_TYPE;
        term.add_expr = std::unique_ptr<AddExprStmt>($1);
        expr->rel_expr->terms.emplace_back(std::move(term));
        $$ = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression");
    }
    | expression relop simple_expression
    {
        current_rule = CurrentRule::Expression;
        ExprStmt * expr = $1;
        RelExprStmt::Term term;
        term.type = get_rel_expr_type($2);
        term.add_expr = std::unique_ptr<AddExprStmt>($3);
        expr->rel_expr->terms.emplace_back(std::move(term));
        $$ = expr;
        LOG_DEBUG("DEBUG expression -> simple_expression relop simple_expression");
    };



/*
* no : 5.5
* rule  :  simple_expression -> term | simple_expression addop term
* node :   AddExprStmt * add_expr
* son : AddExprType type; AddExprStmt * add_expr; MulExprStmt * mul_expr
* error : 表达式定义出错 请检查是否符合规范
*/
simple_expression : term
    {
        current_rule = CurrentRule::SimpleExpression;
        AddExprStmt * add_expr = new AddExprStmt();
        AddExprStmt::Term term;
        term.type = AddExprStmt::AddExprType::NULL_TYPE;
        term.mul_expr = std::unique_ptr<MulExprStmt>($1);
        add_expr->terms.emplace_back(std::move(term));
        $$ = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> term");
    }
    | simple_expression addop term
    {
        current_rule = CurrentRule::SimpleExpression;
        AddExprStmt * add_expr = $1;
        AddExprStmt::Term term;
        term.type = get_add_expr_type($2);
        term.mul_expr = std::unique_ptr<MulExprStmt>($3);
        add_expr->terms.emplace_back(std::move(term));
        $$ = add_expr;
        LOG_DEBUG("DEBUG simple_expression -> simple_expression %lld term\n", $2);
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
        current_rule = CurrentRule::Term;
        MulExprStmt * mul_expr = new MulExprStmt();
        MulExprStmt::Term term;
        term.type = MulExprStmt::MulExprType::NULL_TYPE;
        term.unary_expr = std::unique_ptr<UnaryExprStmt>($1);
        mul_expr->terms.emplace_back(std::move(term));
        $$ = mul_expr;
        LOG_DEBUG("DEBUG term -> factor");
    }
    | term mulop factor
    {
        current_rule = CurrentRule::Term;
        MulExprStmt * mul_expr = $1;
        MulExprStmt::Term term;
        term.type = get_mul_expr_type($2);
        term.unary_expr = std::unique_ptr<UnaryExprStmt>($3);
        mul_expr->terms.emplace_back(std::move(term));
        $$ = mul_expr;
        LOG_DEBUG("DEBUG term -> term mulop factor");
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
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> INTEGER");
    }
    /* | '+' INTEGER
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$2);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '+' INTEGER");
    }
    | '-' INTEGER
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,($2)*-1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' INTEGER");
    } */
    | REAL
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        double val = atof($1);
        fill_number_stmt(unary_expr->primary_expr->value->number, val);
        unary_expr->primary_expr->value->number->literal = std::string($1);
        free($1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> REAL");
    }
    /* | '+' REAL
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$2);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '+' REAL");
    }
    | '-' REAL
    {
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Minus;
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,($2)*-1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' REAL");
    } */
    | BOOLEAN
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        long long int val = $1 == true ? 1 : 0;
        fill_number_stmt(unary_expr->primary_expr->value->number,val);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> BOOLEAN");
    }
    | CHAR
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::Number;
        unary_expr->primary_expr->value->number = std::make_unique<NumberStmt>();
        fill_number_stmt(unary_expr->primary_expr->value->number,$1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> CHAR");
    }
    | variable
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::LVal;
        unary_expr->primary_expr->value->lval = std::unique_ptr<LValStmt>($1);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> variable");
    }
    | '(' expression ')'
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Parentheses;
        unary_expr->primary_expr->expr = std::unique_ptr<ExprStmt>($2);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '(' expression ')'");
    }
    | IDENTIFIER '(' expression_list ')'
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = new UnaryExprStmt();
        //unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::NULL_TYPE);
        unary_expr->primary_expr = std::make_unique<PrimaryExprStmt>();
        unary_expr->primary_expr->type =PrimaryExprStmt::PrimaryExprType::Value;
        unary_expr->primary_expr->value = std::make_unique<ValueStmt>();
        unary_expr->primary_expr->value->type =ValueStmt::ValueType::FuncCall;
        unary_expr->primary_expr->value->func_call = std::make_unique<FuncCallStmt>();
        unary_expr->primary_expr->value->func_call->id = std::string($1);
        if($3 != nullptr){
            for(auto expr : *$3){
                unary_expr->primary_expr->value->func_call->args.emplace_back(std::unique_ptr<ExprStmt>(expr));
            }
            delete $3;
        }
        $$ = unary_expr;
        free($1);
        LOG_DEBUG("DEBUG factor -> IDENTIFIER '(' expression_list ')'");
    }
    | NOT factor
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = $2;
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Not);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> NOT factor");
    }
    | '+' factor
    {
        current_rule = CurrentRule::Factor;
        $$ = $2;
        LOG_DEBUG("DEBUG factor -> '+' factor");
    }
    | '-' factor
    {
        current_rule = CurrentRule::Factor;
        UnaryExprStmt * unary_expr = $2;
        unary_expr->types.emplace_back(UnaryExprStmt::UnaryExprType::Minus);
        $$ = unary_expr;
        LOG_DEBUG("DEBUG factor -> '-' factor");
    };
/*
* addop ->  + | - | or
*/
addop : '+' { $$ = 0; } | '-' { $$ = 1; } | OR { $$ = 2; }

/*
* relop -> = | <> | < | <= | > | >= 
*/
relop : '=' { $$ = 0; } | NE { $$ = 1; } | '<' { $$ = 2; } | LE { $$ = 3; } | '>' { $$ = 4; } | GE { $$ = 5; } | IN { $$ = 6; }

/*
* mulop -> * | / | div | mod | and
*/
mulop : '*' { $$ = 0; } | '/' { $$ = 1; } | DIV { $$ = 1; } | MOD { $$ = 2; } | AND { $$ = 3; } | ANDTHEN { $$ = 4; } 

error_recovery
    : error ';'
    {
        yyerrok;
    }
    ;

%%
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
    hadError = true;
    LOG_ERROR("[Unexcepted Error] at line %d, column %d: %s", llocp->first_line, llocp->first_column + 1, msg);
    return 0;
}

static int yyreport_syntax_error(const yypcontext_t *ctx, const char * code_str, ProgramStmt ** program, void * scanner)
{
    hadError = true;
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
    if (hadError) {
        return -1;
    }
    return ret;
}
