
#include "ast/stmt_test.hpp"

/* 用于语法调试的TEST文件 */

std::string deep_print(int deep) {
    std::string res = "";
    for (int i = 0; i < deep; i++) {
        res += "  ";
    }
    return res;
}

std::string number_stmt_str(const NumberStmt stmt, int deep) {
    std::string res = deep_print(deep) + "[NumberStmt] ";
    
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
    std::string res = deep_print(deep) + "[ConstDeclStmt]\n";
    for (auto &pair : stmt.pairs) {
        res += kv_pair_str(pair, deep + 1) + "\n";
    }
    return res;
}