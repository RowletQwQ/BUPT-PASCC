#include "ast/stmt_test.hpp"
#include <sstream>
#include <thread>
#define SPACE_NUM 3
/* 用于语法调试的TEST文件 */

std::string deep_print(int deep) {
    std::string spaces(deep * SPACE_NUM, ' ');
    return spaces;
}

std::string mark_print(int length){
    std::string marks(length * SPACE_NUM, '-');
    return marks;
}

std::string number_stmt_str(const NumberStmt stmt, int deep) {
    std::stringstream res;
    res << deep_print(deep) << "|____[NumberStmt] ";
    if (stmt.is_real) {
        res << "real: " << stmt.real_val;
    } else if (stmt.is_char) {
        res << "char: " << stmt.char_val;
    } else if (stmt.is_unsigned) {
        res << "unsigned: " << stmt.uint_val;
    } else {
        res << "int: " << stmt.int_val;
    }
    return res.str();
}


std::string kv_pair_str(const ConstDeclStmt::KvPair &pair, int deep) {
    printf("kv_pair\n");
    std::stringstream res;
    res << deep_print(deep) << pair.first << " = " << value_stmt_str(pair.second.get(), 1);
    return res.str();
}


std::string const_decl_stmt_str(const ConstDeclStmt* stmt,int deep) {
    if(stmt == nullptr){
        return "";
    }
    printf("const_decl\n");
    std::stringstream res;
    res << deep_print(deep) << "|____[ConstDeclStmt]\n";
    
    for(int i = 0; i < stmt->pairs.size(); i++){
        res << kv_pair_str(stmt->pairs[i], deep + 1);
    }
    
    return res.str();
}


std::string rel_expr_stmt_str(const RelExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res;
    res << deep_print(deep) << "|____[RelExprStmt] " << "\n";
    for(auto &term : stmt->terms){
        if (term.type != RelExprStmt::RelExprType::NULL_TYPE)
        {
            res << "\n" + deep_print(deep+1) << "===>[OP]: " + rel_op(term.type) << "\n";
        }
        res << add_expr_stmt_str(term.add_expr.get(), deep + 1);
    }
    return res.str();
};

std::string add_expr_stmt_str(const AddExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[AddExprStmt]\n";
    for(auto &term : stmt->terms){
        if (term.type != AddExprStmt::AddExprType::NULL_TYPE)
        {
            res << "\n" + deep_print(deep+1) << "===>[OP]: " + add_op(term.type) << "\n";
        }
        res << mul_expr_stmt_str(term.mul_expr.get(), deep + 1);
    }
    return res.str();
};

std::string mul_expr_stmt_str(const MulExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[MulExprStmt]\n";
    for(auto &term : stmt->terms){
        if (term.type != MulExprStmt::MulExprType::NULL_TYPE)
        {
            res << "\n" + deep_print(deep+1) << "===>[OP]: " + mul_op(term.type) << "\n";
        }
        res << unary_expr_stmt_str(term.unary_expr.get(), deep + 1);
    }
    return res.str();
};

std::string unary_expr_stmt_str(const UnaryExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[UnaryExprStmt]\n";
    for (auto &term : stmt->types)
    {
        if (term != UnaryExprStmt::UnaryExprType::NULL_TYPE)
        {
            res << "\n" + deep_print(deep+1) << "===>[OP]: " + unary_op(term) << "\n";
        }
        
    }
    res << primary_expr_stmt_str(stmt->primary_expr.get(), deep + 1);
    return res.str();
};

std::string primary_expr_stmt_str(const PrimaryExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[PrimaryExprStmt]\n";
    if(stmt->type == PrimaryExprStmt::PrimaryExprType::Value){
        res << value_stmt_str(stmt->value.get(), deep + 1);
    }else{
        res << expr_stmt_str(stmt->expr.get(), deep + 1);
    }
    res << deep_print(deep+1);
    return res.str();
};

std::string value_stmt_str(const ValueStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; res << deep_print(deep) << "|____[ValueStmt]\n";
    if(stmt->type == ValueStmt::ValueType::Number){
        res << number_stmt_str(*stmt->number, deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::Str){
        res << str_stmt_str(stmt->str.get(), deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::LVal){
        res << lval_stmt_str(stmt->lval.get(), deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::FuncCall){
        res << func_call_stmt_str(stmt->func_call.get(), deep + 1);
    }
    return res.str();
};

std::string str_stmt_str(const StrStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[StrStmt] " + stmt->val;
    return res.str();
};

std::string lval_stmt_str(const LValStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[LValStmt] \n" ;
    res << deep_print(deep+1) << "id: " + stmt->id + "\n";
    for(auto &expr : stmt->array_index){
        res << expr_stmt_str(expr.get(), deep + 1);
    }
    return res.str();
};

std::string func_call_stmt_str(const FuncCallStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[FuncCallStmt] \n";
    res << deep_print(deep+1) << "id: " + stmt->id + "\n";
    for(auto &expr : stmt->args){
        res << expr_stmt_str(expr.get(), deep + 1);
    }
    return res.str();
};

std::string expr_stmt_list_str(const std::vector<ExprStmt *> *stmts, int deep){
    if(stmts == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[ExprStmtList]\n";
    for(auto &stmt : *stmts){
        res << expr_stmt_str(stmt, deep + 1);
    }
    return res.str();
};


std::string id_list_str(const std::vector<std::string>& id_list, int deep){
    std::stringstream res; 
    res << deep_print(deep) << "|____[IDList]\n";
    for(auto &id : id_list){
        res << deep_print(deep+1) + id + "\n";
    }
    return res.str();
};

std::string period_stmt_str(const PeriodStmt* period, int deep){
    if(period == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[PeriodStmt]\n";
    res << deep_print(deep+1) << "begin: " + std::to_string(period->begin) << " end: " + std::to_string(period->end) << "\n";
    return res.str();
};

std::string period_list_str(const std::vector<PeriodStmt*>* period_list, int deep){
    if(period_list == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[PeriodList]\n";
    for(auto &period : *period_list){
        res << period_stmt_str(period, deep + 1);
    }
    return res.str();
};

std::string basic_type_str(BasicType type){
    if(type == BasicType::INT){
        return "int";
    }else if(type == BasicType::REAL){
        return "real";
    }else if(type == BasicType::CHAR){
        return "char";
    }else if(type == BasicType::BOOLEAN){
        return "boolean";
    }else{
        return "ERROR";
    }
};

std::string data_type_str(DataType type){
    if(type == DataType::NULL_TYPE){
        return "null";
    }else if(type == DataType::BasicType){
        return "BasicType";
    }else if(type == DataType::ArrayType){
        return "ArrayType";
    }else{
        return "ERROR";
    }
};

std::string var_decl_stmt_str(const VarDeclStmt* var_decl, int deep){
    if(var_decl == nullptr){
        return "";
    }
    printf("var_decl\n");
    std::stringstream res; res << deep_print(deep) << "|____[VarDeclStmt]\n";
    res << id_list_str(var_decl->id, deep + 1);
    res << deep_print(deep+1) << "data_type: " + data_type_str(var_decl->data_type) << "\n";
    res << deep_print(deep+1) << "basic_type: " + basic_type_str(var_decl->basic_type) << "\n";
    for(auto &period : var_decl->array_range){
        res << period_stmt_str(period.get(), deep + 1);
    }
    return res.str();
};

std::string var_decl_stmt_list_str(const std::vector<VarDeclStmt*>* var_decl_list, int deep){
    if(var_decl_list == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[VarDeclStmtList]\n";
    for(auto &var_decl : *var_decl_list){
        res << var_decl_stmt_str(var_decl, deep + 1);
    }
    return res.str();
};

std::string func_stmt_str(const FuncDeclStmt* func_decl, int deep){
    if(func_decl == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[FuncDeclStmt]\n";
    res << func_head_decl_stmt_str(func_decl->header.get(), deep + 1);
    res << func_body_decl_stmt_str(func_decl->body.get(), deep + 1);
    return res.str();
};

std::string func_head_decl_stmt_str(const FuncHeadDeclStmt* func_head, int deep){
    if(func_head == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[FuncHeadDeclStmt]\n";
    res << deep_print(deep+1) << "func_name: " + func_head->func_name + "\n";
    res << deep_print(deep+1) << "ret_type: " + basic_type_str(func_head->ret_type) << "\n";
    res << deep_print(deep+1) << "args:\n";
    for(auto &var_decl : func_head->args){
        res << var_decl_stmt_str(var_decl.get(), deep + 1);
    }
    return res.str();
};

std::string func_body_decl_stmt_str(const FuncBodyDeclStmt* func_body, int deep){
    if(func_body == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[FuncBodyDeclStmt]\n";
    res << const_decl_stmt_str(func_body->const_decl.get(), deep + 1);
    for(auto &var_decl : func_body->var_decl){
        res << var_decl_stmt_str(var_decl.get(), deep + 1);
    }
    int i = 0;
    // std::string res1 = "";
    for(auto &stmt : func_body->comp_stmt){
        // 根据 BaseStmt 类型的子类，调用对应的函数
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    return res.str();
};

std::string assign_stmt_str(const AssignStmt* assign, int deep){
    if(assign == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[AssignStmt]\n";
    res << deep_print(deep+1) << "is_lval_func: " + std::to_string(assign->is_lval_func) << "\n";
    res << lval_stmt_str(assign->lval.get(), deep + 1);
    res << expr_stmt_str(assign->expr.get(), deep + 1);
    return res.str();
};

std::string if_stmt_str(const IfStmt* if_stmt, int deep){
    if(if_stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[IfStmt]\n";
    res << deep_print(deep+1) << "expr:\n";
    res << expr_stmt_str(if_stmt->expr.get(), deep + 1);
    res << deep_print(deep+1) << "true_stmt:\n";
    for(auto &stmt : if_stmt->true_stmt){
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    res << deep_print(deep+1) << "-----------------------\n";
    res << deep_print(deep+1) << "false_stmt:\n";
    for(auto &stmt : if_stmt->false_stmt){
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    res << deep_print(deep+1) << "-----------------------\n";
    return res.str();
};

std::string for_stmt_str(const ForStmt* for_stmt, int deep){
    if(for_stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[ForStmt]\n";
    res << deep_print(deep+1) << "id: " + for_stmt->id + "\n";
    res << expr_stmt_str(for_stmt->begin.get(), deep + 1);
    res << expr_stmt_str(for_stmt->end.get(), deep + 1);
    for(auto &stmt : for_stmt->stmt){
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    return res.str();
};


std::string read_func_stmt_str(const ReadFuncStmt* read_func, int deep){
    if(read_func == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[ReadFuncStmt]\n";
    for(auto &lval : read_func->lval){
        res << lval_stmt_str(lval.get(), deep + 1);
    }
    return res.str();
};

std::string write_func_stmt_str(const WriteFuncStmt* write_func, int deep){
    if(write_func == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[WriteFuncStmt]\n";
    for(auto &expr : write_func->expr){    
        res << expr_stmt_str(expr.get(), deep + 1);
    }
    return res.str();
};

std::string expr_stmt_str(const ExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::stringstream res; 
    res << deep_print(deep) << "|____[ExprStmt]\n";
    res << rel_expr_stmt_str(stmt->rel_expr.get(), deep + 1) << "\n";
    return res.str();
};


std::string program_head_stmt_str(const ProgramHeadStmt* program_head, int deep){
    if(program_head == nullptr){
        return "";
    }
    printf("program_head\n");
    std::stringstream res; 
    res << deep_print(deep) << "|____[ProgramHeadStmt]\n";
    for(auto &id : program_head->id_list){
        res << deep_print(deep+1) + id + "\n";
    }
    return res.str();
};

std::string program_body_stmt_str(const ProgramBodyStmt* program_body, int deep){
    if(program_body == nullptr){
        return "";
    }
    printf("program_body\n");
    std::stringstream res; 
    res << deep_print(deep) << "|____[ProgramBodyStmt]\n";
    res << const_decl_stmt_str(program_body->const_decl.get(), deep + 1);
    for(auto &var_decl : program_body->var_decl){
        res << var_decl_stmt_str(var_decl.get(), deep + 1);
    }
    for(auto &func_decl : program_body->func_decl){
        res << func_stmt_str(func_decl.get(), deep + 1);
    }
    for(auto &stmt : program_body->comp_stmt){
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    return res.str();
};


std::string program_stmt_str(const ProgramStmt* program, int deep){
    if(program == nullptr){
        return "";
    }
    printf("program\n");
    std::stringstream res; 
    res << deep_print(deep) << "|____[ProgramStmt]\n";
    res << program_head_stmt_str(program->head.get(), deep + 1);
    res << program_body_stmt_str(program->body.get(), deep + 1);
    return res.str();
};



std::string rel_op(RelExprStmt::RelExprType type){
    if(type == RelExprStmt::RelExprType::Equal){
        return "=";
    }else if(type == RelExprStmt::RelExprType::NotEqual){
        return "<>";
    }else if(type == RelExprStmt::RelExprType::Less){
        return "<";
    }else if(type == RelExprStmt::RelExprType::LessEqual){
        return "<=";
    }else if(type == RelExprStmt::RelExprType::Greater){
        return ">";
    }else if(type == RelExprStmt::RelExprType::GreaterEqual){
        return ">=";
    }else if(type == RelExprStmt::RelExprType::In){
        return "in";
    }else{
        return "ERROR";
    }
};

std::string add_op(AddExprStmt::AddExprType type){
    if(type == AddExprStmt::AddExprType::Plus){
        return "+";
    }else if(type == AddExprStmt::AddExprType::Minus){
        return "-";
    }else if(type == AddExprStmt::AddExprType::Or){
        return "or";
    }else{
        return "ERROR";
    }
};

std::string mul_op(MulExprStmt::MulExprType type){
    if(type == MulExprStmt::MulExprType::Mul){
        return "*";
    }else if(type == MulExprStmt::MulExprType::Div){
        return "/";
    }else if(type == MulExprStmt::MulExprType::Mod){
        return "mod";
    }else if(type == MulExprStmt::MulExprType::And){
        return "and";
    }else if(type == MulExprStmt::MulExprType::AndThen){
        return "and then";
    }else{
        return "ERROR";
    }
};

std::string unary_op(UnaryExprStmt::UnaryExprType type){
    if(type == UnaryExprStmt::UnaryExprType::Minus){
        return "-";
    }else if(type == UnaryExprStmt::UnaryExprType::Not){
        return "not";
    }else{
        return "ERROR";
    }
};

std::string base_stmt_str(const BaseStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    // 根据 BaseStmt 类型的子类，调用对应的函数
    if (typeid(*stmt) == typeid(AssignStmt)){
        printf("assign\n");
        return assign_stmt_str((const AssignStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(IfStmt)){
        printf("if\n");
        return if_stmt_str((const IfStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(WhileStmt)){
        printf("while\n");
        return while_stmt_str((const WhileStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(ForStmt)){
        printf("for\n");
        return for_stmt_str((const ForStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(ReadFuncStmt)){
        printf("read\n");
        return read_func_stmt_str((const ReadFuncStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(WriteFuncStmt)){
        printf("write\n");
        return write_func_stmt_str((const WriteFuncStmt *)stmt, deep);
    }else if(typeid(*stmt) == typeid(FuncCallStmt)){
        printf("func\n");
        return func_call_stmt_str((const FuncCallStmt *)stmt, deep);
    }else {
        return "ERROR";
    }
};

std::string while_stmt_str(const WhileStmt* while_stmt, int deep){
    if(while_stmt == nullptr){
        return "";
    }
    std::stringstream res; res << deep_print(deep) << "|____[WhileStmt]\n";
    res << deep_print(deep+1) << "expr:\n";
    res << expr_stmt_str(while_stmt->expr.get(), deep + 1);
    for(auto &stmt : while_stmt->stmt){
        res << base_stmt_str(stmt.get(), deep + 1);
    }
    return res.str();
};