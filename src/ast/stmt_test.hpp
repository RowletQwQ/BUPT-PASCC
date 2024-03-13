#pragma once
#include <iostream>
#include <string>
#include "ast/stmt.hpp"
/*
    * @brief 用于打印stmt的内容
*/
std::string deep_print(int deep);

std::string number_stmt_str(const NumberStmt stmt, int deep);

std::string kv_pair_str(const ConstDeclStmt::KvPair &pair, int deep);

std::string const_decl_stmt_str(const ConstDeclStmt* stmt,int deep);

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

std::string id_list_str(const std::vector<std::string>& id_list, int deep);

std::string period_stmt_str(const PeriodStmt* period, int deep);

std::string period_list_str(const std::vector<PeriodStmt*>* period_list, int deep);

std::string basic_type_str(BasicType type);

std::string data_type_str(DataType type);

std::string var_decl_stmt_str(const VarDeclStmt* var_decl, int deep);

std::string var_decl_stmt_list_str(const std::vector<VarDeclStmt*>* var_decl_list, int deep);

std::string func_head_decl_stmt_str(const FuncHeadDeclStmt* func_head, int deep);

std::string func_decl_stmt_str(const FuncDeclStmt* func_decl, int deep);

std::string func_body_decl_stmt_str(const FuncBodyDeclStmt* func_body, int deep);

std::string assign_stmt_str(const AssignStmt* assign, int deep);

std::string if_stmt_str(const IfStmt* if_stmt, int deep);

std::string for_stmt_str(const ForStmt* for_stmt, int deep);

std::string read_func_stmt_str(const ReadFuncStmt* read_func, int deep);

std::string write_func_stmt_str(const WriteFuncStmt* write_func, int deep);

std::string program_head_stmt_str(const ProgramHeadStmt* program_head, int deep);

std::string program_body_stmt_str(const ProgramBodyStmt* program_body, int deep);

std::string program_stmt_str(const ProgramStmt* program, int deep);

std::string base_stmt_str(const BaseStmt* stmt, int deep);

std::string while_stmt_str(const WhileStmt* while_stmt, int deep);
