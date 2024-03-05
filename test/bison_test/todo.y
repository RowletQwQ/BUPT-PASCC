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



// original


var_declarations:
    /* empty */
    {
        $$ = nullptr;
    }
    | VAR var_declaration
    {
        $$ = $2;
    };

var_declaration:
    /* empty */
    {
        $$ = nullptr;
    }
    | ID idlist COLON basic_type SEMICOLON var_declaration
    {
        if ($6) {
            $$ = $6;
        } else {
            $$ = new std::vector<VarDeclStmt *>();
        }
        VarDeclStmt * var_decl = new VarDeclStmt();
        if ($2) {
            var_decl->id_list = *$2;
            delete $2;
        }
        var_decl->id_list.emplace_back($1);
        std::reverse(var_decl->id_list.begin(), var_decl->id_list.end()); 
        var_decl->data_type = DataType::BasicType;
        var_decl->basic_type = $4;
        $$->emplace_back(var_decl);
    }
    | ID idlist COLON ARRAY LEFT_BRACKET period_item RIGHT_BRACKET OF basic_type SEMICOLON var_declaration
    {
        if ($11) {
            $$ = $11;
        } else {
            $$ = new std::vector<VarDeclStmt *>();
        }
        VarDeclStmt * var_decl = new VarDeclStmt();
        if ($2) {
            var_decl->id_list = *$2;
            delete $2;
        }
        var_decl->id_list.emplace_back($1);
        std::reverse(var_decl->id_list.begin(), var_decl->id_list.end()); 
        var_decl->data_type = DataType::ArrayType;
        if ($6) {
            std::reverse($6->begin(), $6->end());
            for (auto period : *$6) {
                var_decl->period_list.emplace_back(std::unique_ptr<PeriodStmt>(period));
            }
            delete $6;
        }
        var_decl->basic_type = $8;
        $$->emplace_back(var_decl);
    };

idlist:
    /* empty */
    {
        $$ = nullptr;
    }
    | COMMA ID idlist
    {
        if ($3) {
            $$ = $3;
        } else {
            $$ = new std::vector<std::string>();
        }
        $$->emplace_back($2);
    };

basic_type:
    INTEGER_KW
    {
        $$ = BasicType::INT;
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
    };

period_item:
    period period_list
    {
        if ($2) {
            $$ = $2;
        } else {
            $$ = new std::vector<PeriodStmt *>();
        }
        $$->emplace_back($1);
    };

period_list:
    /* empty */
    {
        $$ = nullptr;
    }
    | COMMA period period_list
    {
        if ($3) {
            $$ = $3;
        } else {
            $$ = new std::vector<PeriodStmt *>();
        }
        $$->emplace_back($2);
    };

period:
    NUMBER DOT DOT NUMBER
    {
        $$ = new PeriodStmt();
        $$->start = $1;
        $$->end = $4;
    };