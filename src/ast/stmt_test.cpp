
#include "ast/stmt_test.hpp"
#define SPACE_NUM 3
/* 用于语法调试的TEST文件 */

std::string deep_print(int deep) {
    std::string res = "";
    for (int i = 0; i < deep; i++) {
        for (int j = 0; j < SPACE_NUM; j++) {
            res += " ";
        }
    }
    return res;
}

std::string mark_print(int length){
    std::string res = "";
    for (int i = 0; i < length; i++) {
        for(int j = 0; j < SPACE_NUM; j++){
            res += "-";
        }
    }
    return res;
}

std::string number_stmt_str(const NumberStmt stmt, int deep) {
    std::string res = deep_print(deep) + "|____[NumberStmt] ";
    if (stmt.is_real) {
        res += "real: " + std::to_string(stmt.real_val);
    } else if (stmt.is_char) {
        res += "char: " + std::to_string(stmt.char_val);
    } else if (stmt.is_unsigned) {
        res += "unsigned: " + std::to_string(stmt.uint_val);
    } else {
        res += "int: " + std::to_string(stmt.int_val);
    }
    return res;
}


std::string kv_pair_str(const ConstDeclStmt::KvPair pair, int deep) {
    return deep_print(deep) + pair.first + " = " + number_stmt_str(pair.second, 1);
}


std::string const_decl_stmt_str(const ConstDeclStmt stmt,int deep) {
    std::string res = deep_print(deep) + "|____[ConstDeclStmt]\n";

    for (auto &pair : stmt.pairs) {
        res += kv_pair_str(pair, deep + 1) + "\n";
    }
    return res;
}

std::string expr_stmt_str(const ExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[ExprStmt]\n";
    res += rel_expr_stmt_str(stmt->rel_expr.get(), deep + 1);
    return res + "\n";
};

std::string rel_expr_stmt_str(const RelExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[RelExprStmt] "+"\n";
    if(stmt->type == RelExprStmt::RelExprType::NULL_TYPE){
        res += add_expr_stmt_str(stmt->add_expr.get(), deep + 1);
    }else{
        res += add_expr_stmt_str(stmt->add_expr.get(), deep + 1);
        res += "\n" + deep_print(deep+1) + "===>[OP]: " + rel_op(stmt->type) + "\n";
        res += rel_expr_stmt_str(stmt->rel_expr.get(), deep + 1);
    }
    return res;
};

std::string add_expr_stmt_str(const AddExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[AddExprStmt]\n";
    if(stmt->type == AddExprStmt::AddExprType::NULL_TYPE){
        res += mul_expr_stmt_str(stmt->mul_expr.get(), deep + 1);
    }else{
        res += mul_expr_stmt_str(stmt->mul_expr.get(), deep + 1);
        res += "\n" + deep_print(deep+1) + "===>[OP]: " + add_op(stmt->type) + "\n";
        res += add_expr_stmt_str(stmt->add_expr.get(), deep + 1);
    }
    return res;
};

std::string mul_expr_stmt_str(const MulExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[MulExprStmt]\n";
    if(stmt->type == MulExprStmt::MulExprType::NULL_TYPE){
        res += unary_expr_stmt_str(stmt->unary_expr.get(), deep + 1);
    }else{
        res += unary_expr_stmt_str(stmt->unary_expr.get(), deep + 1);
        res += "\n" + deep_print(deep+1) + "===>[OP]: " + mul_op(stmt->type) + "\n";
        res += mul_expr_stmt_str(stmt->mul_expr.get(), deep + 1);
    }
    return res ;
};

std::string unary_expr_stmt_str(const UnaryExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[UnaryExprStmt]\n";
    if(stmt->type == UnaryExprStmt::UnaryExprType::NULL_TYPE){
        res += primary_expr_stmt_str(stmt->primary_expr.get(), deep + 1);
    }else{
        res += "\n" + deep_print(deep+1) + "===>[OP]: " + unary_op(stmt->type) + "\n";
        res += primary_expr_stmt_str(stmt->primary_expr.get(), deep + 1);
    }
    return res ;
};

std::string primary_expr_stmt_str(const PrimaryExprStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[PrimaryExprStmt]\n";
    if(stmt->type == PrimaryExprStmt::PrimaryExprType::Value){
        res += value_stmt_str(stmt->value.get(), deep + 1);
    }else{
        res += value_stmt_str(stmt->value.get(), deep + 1);
    }
    res += deep_print(deep+1);
    return res;
};

std::string value_stmt_str(const ValueStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[ValueStmt]\n";
    if(stmt->type == ValueStmt::ValueType::Number){
        res += number_stmt_str(*stmt->number, deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::Str){
        res += str_stmt_str(stmt->str.get(), deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::LVal){
        res += lval_stmt_str(stmt->lval.get(), deep + 1);
    }else if(stmt->type == ValueStmt::ValueType::FuncCall){
        res += func_call_stmt_str(stmt->func_call.get(), deep + 1);
    }
    return res ;
};

std::string str_stmt_str(const StrStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[StrStmt] " + stmt->val;
    return res;
};

std::string lval_stmt_str(const LValStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[LValStmt] \n" ;
    res += deep_print(deep+1) + "id: " + stmt->id + "\n";
    for(auto &expr : stmt->array_index){
        res += expr_stmt_str(expr.get(), deep + 1);
    }
    return res;
};

std::string func_call_stmt_str(const FuncCallStmt* stmt, int deep){
    if(stmt == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[FuncCallStmt] \n";
    res += deep_print(deep+1) + "id: " + stmt->id + "\n";
    for(auto &expr : stmt->args){
        res += expr_stmt_str(expr.get(), deep + 1);
    }
    return res ;
};

std::string expr_stmt_list_str(const std::vector<ExprStmt *> *stmts, int deep){
    if(stmts == nullptr){
        return "";
    }
    std::string res = deep_print(deep) + "|____[ExprStmtList]\n";
    for(auto &stmt : *stmts){
        res += expr_stmt_str(stmt, deep + 1);
    }
    return res;
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
std::string id_list_str(const std::vector<std::string>& id_list, int deep) {
    std::string res = deep_print(deep) + "[id_list]\n";
    for (const auto& id : id_list) {
        res += deep_print(deep + 1)+ "[string]" + id + "\n";
    }
    return res;
}

std::string period_stmt_str(const PeriodStmt* period, int deep) {
    return deep_print(deep) + "[PeriodStmt] begin: " + std::to_string(period->begin) + ", end: " + std::to_string(period->end);
}

std::string period_list_str(const std::vector<PeriodStmt*>* period_list, int deep) {
    std::string res = deep_print(deep) + "[PeriodList]\n";
    for (const auto& period : *period_list) {
        res += period_stmt_str(period, deep + 1) + "\n";
    }
    return res;
}

std::string basic_type_str(BasicType type) {
    switch (type) {
        case BasicType::INT:
            return "[BasicType] INT\n";
        case BasicType::REAL:
            return "[BasicType] REAL\n";
        case BasicType::BOOLEAN:
            return "[BasicType] BOOLEAN\n";
        case BasicType::CHAR:
            return "[BasicType] CHAR\n";
        default:
            return "[BasicType] Unknown\n";
    }
}

std::string data_type_str(DataType type) {
    switch (type) {
        case DataType::BasicType:
            return "[DataType] BasicType\n";
        case DataType::ArrayType:
            return "[DataType] ArrayType\n";
        default:
            return "[DataType] Unknown\n";
    }
}

std::string var_decl_stmt_str(const VarDeclStmt* var_decl, int deep) {
    std::string res = deep_print(deep) + "[VarDeclStmt]\n";
    res += deep_print(deep + 1) + "ID List: ";
    for (const auto& id : (var_decl->id)) {
        res += id + " ";
    }
    res += "\n";
    res += deep_print(deep + 1) + "Basic Type: " + basic_type_str(var_decl->basic_type) + "\n";
    return res;
}
