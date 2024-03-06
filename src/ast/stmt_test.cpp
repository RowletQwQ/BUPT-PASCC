
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