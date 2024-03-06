//  因为含有未定义的类型无法编译，所以这里存放已经写好的 但是仍然存在未定义依赖的内容
/*
* no : 1.1
* rule  :  programstruct -> program_head ‘;’ program_body '.'
* node :  ProgramStmt * program_struct
* son  :  ProgramHeadStmt * program_head ProgramBodyStmt * program_body
* error : 程序定义出错 请检查是否符合规范
*/
programstruct : program_head  ';'  program_body '.'
    {
        $$ = new ProgramStmt();
        $$->head = $1;
        $$->body = $3;
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
        // TODO
    }
    | PROGRAM IDENTIFIER
    {
        $$ = new ProgramHeadStmt();
        $$->id_list.push_back($2);
        delete $2;
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
        $$ = new ProgramBodyStmt();
        $$->const_decl = $1;
        $$->var_decl = *$2;
        $$->func_decl = *$3;
        $$->comp_stmt = *$4;
        delete $2;
        delete $3;
        delete $4;
    }
    | error{
        syntax_error("程序体定义出错 请检查是否符合规范");
    };


/*
* no : 2.8-2.9
* rule  : subprogram_head -> PROCEDURE IDENTIFIER | PROCEDURE IDENTIFIER '(' parameter_list')' | FUNCTION IDENTIFIER ':' basic_type | FUNCTION IDENTIFIER '(' parameter_list')' ':' basic_type
* node :  FuncHeadDeclStmt *
* son  :  VarDeclStmt*
* error :
*
* TODO:unique_ptr
*/

subprogram_head : PROCEDURE IDENTIFIER
        | PROCEDURE IDENTIFIER '(' parameter_list')'
        | FUNCTION IDENTIFIER ':' basic_type
        | FUNCTION IDENTIFIER '(' parameter_list')' ':' basic_type

/*
* no : 2.2
* rule  : var_declaration -> idlist ':' type | var_declaration ';' idlist ':' type
* node :  std::vector<VarDeclStmt *> *
* son :
* TODO: data_type中period list； unique_ptr
*/
var_declaration: idlist ':' type
        {
            $$ = new std::vector<VarDeclStmt *>();
            VarDeclStmt * var_decl = new VarDeclStmt();
            var_decl->id = idlist;
            var_decl->
        }
        | var_declaration ';' idlist ':' type
        {
        }


/*
* no : 2.3
* rule  : type -> basic_type | ARRAY '[' period_list ']' OF basic_type
* node :  DataType
*
* TODO: period_list未存储
*/
type: basic_type
        {
            $$ = DataType::BasicType;
            printf("%s", data_type_str($$).c_str());
        }
        | ARRAY '[' period_list ']' OF basic_type
        {
            $$ = DataType::ArrayType;
            printf("%s", data_type_str($$).c_str());
        }
