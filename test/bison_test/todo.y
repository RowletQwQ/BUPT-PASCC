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
* no : 1.4
* rule  : id_list -> IDENTIFIER | id_list ',' IDENTIFIER 
* node :  std::vector<std::string> * 
* son  :  std::string
* error : 程序头定义出错 请检查是否符合规范
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
    }
    | error{
        syntax_error("程序头定义出错 请检查是否符合规范");
    };

