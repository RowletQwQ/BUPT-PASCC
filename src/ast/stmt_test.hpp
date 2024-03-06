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

std::string expr_stmt_str(const ExprStmt* stmt, int deep);

std::string rel_expr_stmt_str(const RelExprStmt* stmt, int deep);

std::string add_expr_stmt_str(const AddExprStmt* stmt, int deep);

std::string mul_expr_stmt_str(const MulExprStmt* stmt, int deep);

std::string unary_expr_stmt_str(const UnaryExprStmt* stmt, int deep);

std::string primary_expr_stmt_str(const PrimaryExprStmt* stmt, int deep);

std::string value_stmt_str(const ValueStmt* stmt, int deep);

std::string str_stmt_str(const StrStmt* stmt, int deep);

std::string lval_stmt_str(const LValStmt* stmt, int deep);

std::string func_call_stmt_str(const FuncCallStmt* stmt, int deep);

std::string expr_stmt_list_str(const std::vector<ExprStmt *> *stmts, int deep);

std::string rel_op(RelExprStmt::RelExprType type);

std::string add_op(AddExprStmt::AddExprType type);

std::string mul_op(MulExprStmt::MulExprType type);

std::string unary_op(UnaryExprStmt::UnaryExprType type);
