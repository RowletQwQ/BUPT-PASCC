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

std::string id_list_str(const std::vector<std::string>& id_list, int deep);

std::string period_stmt_str(const PeriodStmt* period, int deep);

std::string period_list_str(const std::vector<PeriodStmt*>* period_list, int deep);

std::string basic_type_str(BasicType type);

std::string data_type_str(DataType type);

std::string var_decl_stmt_str(const VarDeclStmt* var_decl, int deep);