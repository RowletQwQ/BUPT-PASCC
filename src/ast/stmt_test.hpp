#pragma once
#include <iostream>
#include <string>
#include "ast/stmt.hpp"
/*
    * @brief 用于打印stmt的内容
*/
std::string deep_print(int deep);

std::string number_stmt_str(const NumberStmt stmt, int deep);

std::string kv_pair_str(const ConstDeclStmt::KvPair pair, int deep);

std::string const_decl_stmt_str(const ConstDeclStmt stmt,int deep);

