#include "ir/ir_gen.hpp"
#include "assert.h"
#include "ast/stmt.hpp"
#include "common/exception/exception.hpp"
#include "common/log/log.hpp"
#include "ir/ir.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

namespace ir {

// 工具函数
std::shared_ptr<Type> build_basic_type(BasicType type, bool is_pointer) {
    switch (type) {
        case BasicType::INT:
            return std::make_shared<IntegerType>(kDefaultIntegerBitWidth, is_pointer);
        case BasicType::REAL:
            return std::make_shared<RealType>(kDefaultRealBitWidth, is_pointer);
        case BasicType::CHAR:
            return std::make_shared<CharType>(is_pointer);
        case BasicType::BOOLEAN:
            return std::make_shared<BooleanType>(is_pointer);
        case BasicType::VOID:
            return std::make_shared<VoidType>();
    }
    return nullptr;
}
Instruction::OpID build_op_id(RelExprStmt::RelExprType type) {
    switch (type) {
        case RelExprStmt::RelExprType::Equal:
            return Instruction::OpID::Eq;
        case RelExprStmt::RelExprType::NotEqual:
            return Instruction::OpID::Ne;
        case RelExprStmt::RelExprType::Less:
            return Instruction::OpID::Lt;
        case RelExprStmt::RelExprType::LessEqual:
            return Instruction::OpID::Le;
        case RelExprStmt::RelExprType::Greater:
            return Instruction::OpID::Gt;
        case RelExprStmt::RelExprType::GreaterEqual:
            return Instruction::OpID::Ge;
        case RelExprStmt::RelExprType::In:
            return Instruction::OpID::In;
        default:
            break; 
    }
    return Instruction::OpID::Null;
}
Instruction::OpID build_op_id(AddExprStmt::AddExprType type) {
    switch (type) {
        case AddExprStmt::AddExprType::Plus:
            return Instruction::OpID::Add;
        case AddExprStmt::AddExprType::Minus:
            return Instruction::OpID::Sub;
        case AddExprStmt::AddExprType::Or:
            return Instruction::OpID::Or;
        default:
            break;
    }
    return Instruction::OpID::Null;
}
Instruction::OpID build_op_id(MulExprStmt::MulExprType type) {
    switch (type) {
        case MulExprStmt::MulExprType::Mul:
            return Instruction::OpID::Mul;
        case MulExprStmt::MulExprType::Div:
            return Instruction::OpID::Div;
        case MulExprStmt::MulExprType::Mod:
            return Instruction::OpID::Mod;
        case MulExprStmt::MulExprType::And:
            return Instruction::OpID::And;
        case MulExprStmt::MulExprType::AndThen:
            return Instruction::OpID::AndThen;
        default:
            break;
    }
    return Instruction::OpID::Null;
}
Instruction::OpID build_op_id(UnaryExprStmt::UnaryExprType type) {
    switch (type) {
        case UnaryExprStmt::UnaryExprType::Minus:
            return Instruction::OpID::Minus;
        case UnaryExprStmt::UnaryExprType::Not:
            return Instruction::OpID::Not;
        default:
            break;
    }
    return Instruction::OpID::Null;
}

// ------------------------------------------------------Scope------------------------------------------------------
/**
 * @brief 进入一个新的作用域
*/
void Scope::enter() {
    symbols_.emplace_back(std::map<std::string, std::shared_ptr<Value>>());
}
std::weak_ptr<BasicBlock> Scope::get_loop_body(){
    return loop_body_stack_.back();
}
std::weak_ptr<BasicBlock> Scope::get_loop_brk(){
    return loop_brk_stack_.back();
}
std::weak_ptr<BasicBlock> Scope::get_loop_cond(){
    return loop_cond_stack_.back();
}

/**
 * @brief 离开一个作用域
*/
void Scope::leave() {
    symbols_.pop_back();
}
void Scope::enter_loop(std::weak_ptr<BasicBlock> cond,std::weak_ptr<BasicBlock> body_bb, 
        std::weak_ptr<BasicBlock> brk_bb, bool is_while_stmt) {
    loop_cond_stack_.emplace_back(cond);
    loop_body_stack_.emplace_back(body_bb);
    loop_brk_stack_.emplace_back(brk_bb);
    is_while_stmt_ = is_while_stmt;
}
void Scope::leave_loop() {
    loop_cond_stack_.pop_back();
    loop_body_stack_.pop_back();
    loop_brk_stack_.pop_back();
}
/**
 * @brief 检测是否在全局作用域
*/
bool Scope::is_global() {
    return symbols_.size() == 1;
}
/**
 * @brief 向符号表加入一个符号
*/
void Scope::push(const std::string &name, std::shared_ptr<Value> value) {
    symbols_.back()[name] = value;
}
/**
 * @brief 从符号表中查找一个符号
*/
std::shared_ptr<Value> Scope::find(const std::string &name) {
    // 从栈顶开始查找
    for (int i = int(symbols_.size()) - 1; i >= 0; i--) {
        if (symbols_[i].count(name) > 0) {
            return symbols_[i][name];
        }
    }
    return nullptr;
}
void Scope::print() {
    std::cout << "当前作用域的符号表\n";
    for (const auto &m : symbols_) {
        for (const auto &pair : m) {
            std::cout << "符号名:" << pair.first << " " << "符号地址:" << pair.second->print() << "\n";
        }
    }
}

// ------------------------------------------------------IRGenerator------------------------------------------------------
void IRGenerator::visit(ExprStmt &stmt) {
    if (stmt.rel_expr != nullptr) {
        stmt.rel_expr->accept(*this);
    }
}
void IRGenerator::visit(RelExprStmt &stmt) {
    std::shared_ptr<Value> lhs; // 左侧表达式
    for (const auto &term : stmt.terms) {
        term.add_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if (lhs && term.type != RelExprStmt::RelExprType::NULL_TYPE) {
            Instruction::OpID op = build_op_id(term.type);
            if(!CompareInst::can_be_compared(lhs->type_.get(), rhs->type_.get())) {
                LOG_ERROR("比较表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                LOG_ERROR("左侧类型 %s, 右侧类型 %s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
                throw common::IRGenException("比较表达式类型不匹配");
            }

            if(op == Instruction::OpID::Null) {
                LOG_ERROR("不支持的比较操作符, 左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                throw common::IRGenException("不支持的比较操作符");
            }
            // 新建指令，并赋予基本块信息
            std::shared_ptr<CompareInst> inst = std::make_shared<CompareInst>(op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
            this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(2); // 弹出两个操作数
            this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
            inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            this->module_.all_instructions_.emplace_back(inst);
        }
        lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    }
}
void IRGenerator::visit(AddExprStmt &stmt) {
    std::shared_ptr<Value> lhs; // 左侧表达式
    for (const auto &term : stmt.terms) {
        term.mul_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

        if (lhs && term.type != AddExprStmt::AddExprType::NULL_TYPE) {
            Instruction::OpID op = build_op_id(term.type);
            //std::shared_ptr<Value> lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

            if (!BinaryInst::can_compute(lhs->type_.get(), rhs->type_.get())) {
                LOG_ERROR("二元运算表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                LOG_ERROR("左侧类型 %s, 右侧类型 %s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
                throw common::IRGenException("二元运算表达式类型不匹配");
            }
            if (op == Instruction::OpID::Null) {
                LOG_ERROR("不支持的二元运算操作符, 左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                throw common::IRGenException("不支持的二元运算操作符");
            }
            std::shared_ptr<Type> inst_type;
            if (lhs->type_->get_tid() > rhs->type_->get_tid()) {
                inst_type = lhs->type_;
            } else {
                inst_type = rhs->type_;
            }
            std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(inst_type, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
            this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(2); // 弹出两个操作数
            this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
            inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            this->module_.all_instructions_.emplace_back(inst);
        }
        lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    }
}

void IRGenerator::visit(MulExprStmt &stmt) {
    std::shared_ptr<Value> lhs; // 左侧表达式
    for (const auto &term : stmt.terms) {
        term.unary_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

        if (lhs && term.type != MulExprStmt::MulExprType::NULL_TYPE) {
            Instruction::OpID op = build_op_id(term.type);
            //std::shared_ptr<Value> lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

            if (!BinaryInst::can_compute(lhs->type_.get(), rhs->type_.get())) {
                LOG_ERROR("二元运算表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                LOG_ERROR("左侧类型 %s, 右侧类型 %s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
                throw common::IRGenException("二元运算表达式类型不匹配");
            }

            if (op == Instruction::OpID::Null) {
                LOG_ERROR("不支持的二元运算操作符, 左侧表达式：%s, 右侧表达式：%s", lhs->print().c_str(), rhs->print().c_str());
                throw common::IRGenException("不支持的二元运算操作符");
            }

            std::shared_ptr<Type> inst_type;
            if (lhs->type_->get_tid() > rhs->type_->get_tid()) {
                inst_type = lhs->type_;
            } else {
                inst_type = rhs->type_;
            }
            std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(inst_type, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
            this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(2); // 弹出两个操作数
            this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
            inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            this->module_.all_instructions_.emplace_back(inst);
        }
        lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    }
}
void IRGenerator::visit(UnaryExprStmt &stmt) {
    stmt.primary_expr->accept(*this);
    for(auto &t: stmt.types) {
        Instruction::OpID op = build_op_id(t); // 操作符
        
        std::shared_ptr<Value> val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if (op == Instruction::OpID::Null) {
            LOG_ERROR("不支持的一元运算操作符, 表达式：%s, 操作符: %d", val->print().c_str(), t);
            throw common::IRGenException("不支持的一元运算操作符");
        }
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, op, val, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
        this->module_.all_instructions_.emplace_back(inst);
    }
}
void IRGenerator::visit(PrimaryExprStmt &stmt) {
    if (stmt.type == PrimaryExprStmt::PrimaryExprType::NULL_TYPE || stmt.type == PrimaryExprStmt::PrimaryExprType::Value) { // 降级处理
        stmt.value->accept(*this);
    } else {
        stmt.expr->accept(*this);
        std::shared_ptr<Value> val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Bracket, val, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
        this->module_.all_instructions_.emplace_back(inst);
    }
}
void IRGenerator::visit(ValueStmt &stmt) {
    assert(stmt.type != ValueStmt::ValueType::NULL_TYPE);
    if (stmt.type == ValueStmt::ValueType::LVal) {
        stmt.lval->accept(*this);
    } else if (stmt.type == ValueStmt::ValueType::FuncCall) {
        stmt.func_call->accept(*this);
    } else if (stmt.type == ValueStmt::ValueType::Number) {
        stmt.number->accept(*this);
    } else if (stmt.type == ValueStmt::ValueType::Str) {
        stmt.str->accept(*this);
    }
}
void IRGenerator::visit(NumberStmt &stmt) {
    std::shared_ptr<Type> type; // 类型
    std::shared_ptr<Literal> val; // 值
    if (stmt.is_real) {
        type = std::make_shared<RealType>(kDefaultRealBitWidth, false);
        val = std::make_shared<LiteralDouble>(type, stmt.real_val, stmt.literal);
    } else if (stmt.is_char) {
        type = std::make_shared<CharType>(false);
        val = std::make_shared<LiteralChar>(type, stmt.char_val);
    } else {
        type = std::make_shared<IntegerType>(kDefaultIntegerBitWidth, false);
        val = std::make_shared<LiteralInt>(type, stmt.int_val);
    }
    std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(type, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back()); 
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
    this->module_.add_literal(val);
}
void IRGenerator::visit(StrStmt &stmt) {
    std::shared_ptr<Type> type = std::make_shared<StringType>();
    std::shared_ptr<Literal> val = std::make_shared<LiteralString>(type, stmt.val);
    std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(type, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
    this->module_.add_literal(val);
}
void IRGenerator::visit(FuncCallStmt &stmt) {
    // 先寻找函数的指针
    std::shared_ptr<Function> val = std::static_pointer_cast<Function>(this->scope_.find(stmt.id));
    if(!val) {
        LOG_FATAL("没有这样的函数：%s",stmt.id.c_str());
        throw common::IRGenException("没有这样的函数");
    }
    assert(val != nullptr);

    // 得到参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &arg : stmt.args) {
        arg->accept(*this);
        args.emplace_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(args.size()); // 弹出参数

    if(args.size() != val->args_.size()) {
        LOG_ERROR("函数调用参数个数不匹配，函数名：%s", stmt.id.c_str());
        throw common::IRGenException("函数调用参数个数不匹配");
    }
    for (auto i = 0; i < val->args_.size(); i++) {
        if (!BinaryInst::can_compute(val->args_[i]->type_.get(), args[i]->type_.get())) {
            LOG_ERROR("函数调用参数类型不匹配，函数名：%s", stmt.id.c_str());
            throw common::IRGenException("函数调用参数类型不匹配");
        }
        args[i]->type_->is_pointer_ = val->args_[i]->type_->is_pointer_;
    }
    // 构建函数调用指令
    std::shared_ptr<CallInst> inst = std::make_shared<CallInst>(val, args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
}
void IRGenerator::visit(PeriodStmt &stmt) {
    // 不需要处理   
}
void IRGenerator::visit(ConstDeclStmt &stmt) {
    for (const auto &pair : stmt.pairs) {
        std::string name = pair.first; // 常量名
        ValueStmt *value_stmt = pair.second.get();
        std::shared_ptr<Type> type; // 类型
        std::shared_ptr<Literal> val; // 值
        if (value_stmt->type == ValueStmt::ValueType::Number) {
            NumberStmt *num_stmt = value_stmt->number.get();
            if (num_stmt->is_real) {
                type = std::make_shared<RealType>(kDefaultRealBitWidth,false);
                val = std::make_shared<LiteralDouble>(type, num_stmt->real_val, num_stmt->literal);
            } else if (num_stmt->is_char) {
                type = std::make_shared<CharType>(false);
                val = std::make_shared<LiteralChar>(type, num_stmt->char_val);
            } else {
                type = std::make_shared<IntegerType>(kDefaultIntegerBitWidth,false);
                val = std::make_shared<LiteralInt>(type, num_stmt->int_val);
            }
        } else if (value_stmt->type == ValueStmt::ValueType::Str) {
            type = std::make_shared<StringType>();
            val = std::make_shared<LiteralString>(type, value_stmt->str->val);
        } else {
            LOG_ERROR("常量声明:不支持的类型, 常量名:%s, 类型:%d, 指针:%p", name.c_str(), value_stmt->type, value_stmt);
        }
        this->module_.add_literal(val);
        val->name_ = name;
        // 判断是否是全局作用域
        if (this->scope_.is_global()) {
            auto g = std::make_shared<GlobalIdentifier>(type, name, true, val);
            this->module_.add_global_identifier(g);
            this->scope_.push(name, g);
        } else {

            auto l = std::make_shared<LocalIdentifier>(type, name, true, val);
            this->scope_.current_f_->add_local_identifier(l);
            this->scope_.push(name, l);
        }
    }    
}
void IRGenerator::visit(VarDeclStmt &stmt) {
    std::shared_ptr<Type> type = build_basic_type(stmt.basic_type, false); // 类型, 如果是数组, 就是元素类型
    if (stmt.data_type == DataType::BasicType) { // 处理基本类型
        for (const auto &name : stmt.id) {
            if (this->scope_.is_global()) {
                auto g = std::make_shared<GlobalIdentifier>(type, name, false, nullptr);
                this->module_.add_global_identifier(g);
                this->scope_.push(name, g);
            } else {
                auto l = std::make_shared<LocalIdentifier>(type, name, false, nullptr);
                this->scope_.current_f_->add_local_identifier(l);
                this->scope_.push(name, l);
            }
        }
    } else if (stmt.data_type == DataType::ArrayType) { // 处理数组类型
        std::vector<unsigned> dims_elem_num;
        for (const auto &range : stmt.array_range) {
            dims_elem_num.emplace_back(range->end + 1);
        }
        std::shared_ptr<ArrayType> array_type = std::make_shared<ArrayType>(type, dims_elem_num); // 数组类型
        for (const auto &name : stmt.id) {
            if (this->scope_.is_global()) {
                auto g = std::make_shared<GlobalIdentifier>(array_type, name, false, nullptr);
                this->module_.add_global_identifier(g);
                this->scope_.push(name, g);
            } else {
                auto l = std::make_shared<LocalIdentifier>(array_type, name, false, nullptr);
                this->scope_.current_f_->add_local_identifier(l);
                this->scope_.push(name, l);
            }
        }
    } else { // 处理其他类型
        std::cout << "暂不支持其他类型\n";
    }
}
void IRGenerator::visit(FuncHeadDeclStmt &stmt) {
    std::string func_name = stmt.func_name; // 函数名 
    std::shared_ptr<Type> ret_type = build_basic_type(stmt.ret_type, false); // 返回值类型

    // 记录参数时, 就要进入一个新的作用域
    if (!this->scope_.is_global()) { // 如果不是全局作用域, 就先退出当前作用域
        this->scope_.leave();
    }
    std::vector<std::shared_ptr<Type>> args_type; // 参数类型 
    std::vector<std::string> args_name; // 参数名
    for (const auto &arg : stmt.args) {
        for (const auto &arg_name : arg->id) {
            args_type.emplace_back(build_basic_type(arg->basic_type, arg->is_var));
            args_name.emplace_back(arg_name);
        }
    }
    std::shared_ptr<FunctionType> func_type = std::make_shared<FunctionType>(ret_type, args_type);
    std::shared_ptr<Function> f = std::make_shared<Function>(func_type, func_name, args_name);
    this->module_.add_function(f);
    this->scope_.current_f_ = f; // 记录当前作用域的函数
    this->scope_.push(func_name, f); // 记录函数到全局作用域中
    this->scope_.enter(); // 进入一个新的作用域

    // 记录参数
    for (const auto &arg_stmt : stmt.args) {
        arg_stmt->accept(*this);
        if(arg_stmt->is_var) {
            // 如果是引用，更改scope中的参数类型
            std::shared_ptr<Value> val = this->scope_.find(arg_stmt->id[0]);
            val->type_->is_pointer_ = true;
        }
    }
}
void IRGenerator::visit(FuncBodyDeclStmt &stmt) {
    // 局部常量
    if (stmt.const_decl != nullptr) {
        stmt.const_decl->accept(*this);
    }

    // 局部变量
    for (const auto &decl : stmt.var_decl) {
        decl->accept(*this);
    }

    // 函数体
    // 进入函数体时, 需要新建一个基本块作为初始块
    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("begin_basic_block");
    this->scope_.current_f_->add_basic_block(bb);
    ////this->module_.add_basic_block(bb);
    for (const auto &stmt : stmt.comp_stmt) {
        stmt->accept(*this);
    }
}
void IRGenerator::visit(FuncDeclStmt &stmt) {
    if (stmt.header != nullptr) {
        stmt.header->accept(*this);
    }    
    if (stmt.body != nullptr) {
        stmt.body->accept(*this);
    }
}
void IRGenerator::visit(LValStmt &stmt) {
    std::shared_ptr<Value> val = this->scope_.find(stmt.id); // 符号表寻找对应 value
    if (!val) {
        LOG_FATAL("没有这样的符号：%s",stmt.id.c_str());
    }
    assert (val != nullptr);
    if (stmt.array_index.size() == 0) { // 如果不是数组, 就说明是一个普通变量, 如 a、b 等
        // 判断是不是函数，Pascal可以不用()直接进行函数调用
        if (val->get_val_id() == Value::ValueID::Function) {
            // 构建函数调用指令
            std::shared_ptr<Function> func = std::static_pointer_cast<Function>(val);
            std::vector<std::shared_ptr<Value>> args; // 参数为0
            std::shared_ptr<CallInst> inst = std::make_shared<CallInst>(func, args, this->scope_.current_f_->basic_blocks_.back());
            this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
            inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            this->module_.all_instructions_.emplace_back(inst);
        } else {
            std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(val->type_, val, this->scope_.current_f_->basic_blocks_.back());
            this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
            inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            this->module_.all_instructions_.emplace_back(inst);
        }
    } else {
        // 处理数组
        // 获取数组维度信息
        auto tmp = std::static_pointer_cast<ArrayType>(val->type_);
        for (int i = 0; i < stmt.array_index.size(); i++) {
            stmt.array_index[i] -> accept(*this);
            std::shared_ptr<Value> idx = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
            // 如果 index 是最后一个, 那就将目标类型视作数组元素类型
            if (i == int(stmt.array_index.size()) - 1) {
                ArrayType *at = (ArrayType *)val->type_.get();
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(at->elem_type_, val, idx, this->scope_.current_f_->basic_blocks_.back());
                this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst); 
                inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
                this->module_.all_instructions_.emplace_back(inst);
            } else {
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(tmp, val, idx, this->scope_.current_f_->basic_blocks_.back());
                this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
                inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
                this->module_.all_instructions_.emplace_back(inst);
            }
            val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            if (i != int(stmt.array_index.size()) - 1) {
                this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
            }
        }
    }
}
void IRGenerator::visit(BreakStmt &stmt) {
    if(!this->scope_.is_in_loop()) {
        LOG_ERROR("break 语句不在循环内");
        throw common::IRGenException("break 语句不在循环内");
    }
    std::shared_ptr<BreakInst> inst = std::make_shared<BreakInst>(this->scope_.get_loop_brk().lock(), this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
}
void IRGenerator::visit(ContinueStmt &stmt) {
    if(!this->scope_.is_in_loop()) {
        LOG_ERROR("continue 语句不在循环内");
        throw common::IRGenException("continue 语句不在循环内");
    }
    std::shared_ptr<Instruction> inst;
    if (this->scope_.is_while_stmt()) {
        inst = std::make_shared<ContinueInst>(this->scope_.get_loop_cond().lock(), this->scope_.current_f_->basic_blocks_.back());
    } else {
        inst = std::make_shared<ContinueIncInst>(this->scope_.get_loop_body().lock(), this->scope_.get_loop_cond().lock(), this->scope_.current_f_->basic_blocks_.back());
    }   
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
}
void IRGenerator::visit(AssignStmt &stmt) {
    std::shared_ptr<Instruction> inst; // 对应的指令
    // 处理左值
    std::shared_ptr<Instruction> val;
    stmt.lval->accept(*this);
    val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    // 判断构造的 val 是不是一个函数名
    bool is_return = false;
    if (val->get_op_id() == Instruction::OpID::Call) {
        is_return = true;
        if(!this->scope_.find(DefaultReturnName)) {
            // 获取函数信息
            std::shared_ptr<Function> func = std::static_pointer_cast<Function>(val->get_operand(0).lock());
            // 获取返回值类型
            auto ret_type = func->func_type_.lock()->result_;
            auto id = std::make_shared<LocalIdentifier>(ret_type, DefaultReturnName, false, nullptr);
            this->scope_.current_f_->add_local_identifier(id);
            this->scope_.push(DefaultReturnName, id);
        }
        // 更改val
        std::unique_ptr<LValStmt> lval = std::make_unique<LValStmt>();
        lval->id = DefaultReturnName;
        lval->accept(*this);
        val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    }

    // 处理右值
    std::shared_ptr<Value> ptr;
    stmt.expr->accept(*this);
    ptr = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    // 构建赋值指令 or 返回指令
    // if (!is_return) {
        inst = std::make_shared<StoreInst>(val, ptr, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
        this->module_.all_instructions_.emplace_back(inst);
    // } else {
    //     inst = std::make_shared<ReturnInst>(ptr, this->scope_.current_f_->basic_blocks_.back());
    //     this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    //     inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    //     this->module_.all_instructions_.emplace_back(inst);
    // }
}
void IRGenerator::visit(IfStmt &stmt) {
    // 得到 if 的条件
    stmt.expr->accept(*this);
    std::shared_ptr<Instruction> cond_inst = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数

    // if 会多产生两个基本块
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块
    std::shared_ptr<BasicBlock> then_bb = std::make_shared<BasicBlock>("then_basic_block"); // then 基本块
    //this->module_.add_basic_block(then_bb);
    this->scope_.current_f_->add_basic_block(then_bb);
    for (const auto &stmt : stmt.true_stmt) {
        stmt->accept(*this);
    }

    std::shared_ptr<BasicBlock> else_bb = std::make_shared<BasicBlock>("else_basic_block"); // else 基本块
    //this->module_.add_basic_block(else_bb);
    this->scope_.current_f_->add_basic_block(else_bb);
    for (const auto &stmt : stmt.false_stmt) {
        stmt->accept(*this);
    }
   
    // 构建条件跳转指令, 这个指令应该是在当前基本块的最后一条指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, then_bb, else_bb, cur_bb);
    cur_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cur_bb->instructions_.end()));
    this->module_.all_instructions_.emplace_back(branch_inst);

    // 再次新建一个基本块
    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("nxt_basic_block");
    this->scope_.current_f_->add_basic_block(bb);
    cur_bb->add_succ_bb(bb);
    ////this->module_.add_basic_block(bb);
}
void IRGenerator::visit(ForStmt &stmt) {
    // 先是一个赋值指令, 也就是循环变量赋初值
    std::shared_ptr<Value> id = this->scope_.find(stmt.id); // 符号表寻找对应的循环变量
    assert (id != nullptr);
    stmt.begin->accept(*this);
    std::shared_ptr<Value> begin_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    std::shared_ptr<StoreInst> store_inst = std::make_shared<StoreInst>(id, begin_val, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(store_inst);
    store_inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(store_inst);
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块

    // 然后新建一个基本块, 这个基本块是一个 if 条件
    std::shared_ptr<BasicBlock> cond_bb = std::make_shared<BasicBlock>("cond_basic_block");
    this->scope_.current_f_->add_basic_block(cond_bb);
    //this->module_.add_basic_block(cond_bb);
    cur_bb->add_succ_bb(cond_bb);
    cond_bb->add_pre_bb(cur_bb);
    stmt.end->accept(*this);
    std::shared_ptr<Value> end_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    std::shared_ptr<Instruction> cond_inst = std::make_shared<CompareInst>(Instruction::OpID::Le, id, end_val, cond_bb);
    cond_bb->instructions_.emplace_back(cond_inst);
    cond_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));
    this->module_.all_instructions_.emplace_back(cond_inst);

    
    // 再新建一个基本块, 这个基本块是循环体
    std::shared_ptr<BasicBlock> body_bb = std::make_shared<BasicBlock>("body_basic_block");
    //this->module_.add_basic_block(body_bb);
    // 最后新建一个循环外的基本块
    std::shared_ptr<BasicBlock> nxt_bb = std::make_shared<BasicBlock>("nxt_basic_block");
    //this->module_.add_basic_block(nxt_bb);
    // 进入循环，记录循环外基本块位置
    this->scope_.enter_loop(cond_bb, body_bb, nxt_bb, false);
    this->scope_.current_f_->add_basic_block(body_bb);
    for (const auto &stmt : stmt.stmt) {
        stmt->accept(*this);
    }
    // 退出循环
    this->scope_.leave_loop();
    body_bb->add_succ_bb(cond_bb);
    // 循环体的最后一条指令是循环变量加 1
    std::shared_ptr<UnaryInst> inc_inst = std::make_shared<UnaryInst>(id->type_, Instruction::OpID::Inc, id, body_bb);
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inc_inst);
    inc_inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inc_inst);
    
    if(body_bb.get() != this->scope_.current_f_->basic_blocks_.back().get()) {
        // 循环体中有多个基本块
        body_bb->name_ = "body_begin_basic_block";
        this->scope_.current_f_->basic_blocks_.back()->name_ = "body_end_basic_block";
        body_bb->add_succ_bb(this->scope_.current_f_->basic_blocks_.back());
    }

    
    this->scope_.current_f_->add_basic_block(nxt_bb);
    //cond_bb->add_succ_bb(nxt_bb);

    // 补充上面的 if 指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, body_bb, nxt_bb, cond_bb, true);
    cond_bb->pop_back_inst(1); // 弹出条件判断操作数
    cond_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));
    this->module_.all_instructions_.emplace_back(branch_inst);
    cond_bb->add_succ_bb(nxt_bb);
}
void IRGenerator::visit(WhileStmt &stmt) {
    // 先得到当前基本块
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back();

    // 然后新建一个条件基本块
    std::shared_ptr<BasicBlock> cond_bb = std::make_shared<BasicBlock>("cond_basic_block");
    this->scope_.current_f_->add_basic_block(cond_bb);
    //this->module_.add_basic_block(cond_bb);
    cur_bb->add_succ_bb(cond_bb);
    cond_bb->add_pre_bb(cur_bb);
    stmt.expr->accept(*this);
    std::shared_ptr<Instruction> cond_inst = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
    // 再新建一个循环体基本块
    std::shared_ptr<BasicBlock> body_bb = std::make_shared<BasicBlock>("body_basic_block");
    // 最后新建一个循环外的基本块
    std::shared_ptr<BasicBlock> nxt_bb = std::make_shared<BasicBlock>("nxt_basic_block");
    //this->module_.add_basic_block(nxt_bb);
    //this->module_.add_basic_block(body_bb);
    // 进入循环
    this->scope_.enter_loop(cond_bb, body_bb, nxt_bb, true);
    this->scope_.current_f_->add_basic_block(body_bb);

    for (const auto &stmt : stmt.stmt) {
        stmt->accept(*this);
    }
    // 退出循环
    this->scope_.leave_loop();
    body_bb->add_succ_bb(cond_bb);

    if(body_bb.get() != this->scope_.current_f_->basic_blocks_.back().get()) {
        // 循环体中有多个基本块
        body_bb->name_ = "body_begin_basic_block";
        this->scope_.current_f_->basic_blocks_.back()->name_ = "body_end_basic_block";
        body_bb->add_succ_bb(this->scope_.current_f_->basic_blocks_.back());
    }
    
    this->scope_.current_f_->add_basic_block(nxt_bb);

    // 创建 while 指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, body_bb, nxt_bb, cond_bb, true);
    cond_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));
    this->module_.all_instructions_.emplace_back(branch_inst);
    cond_bb->add_succ_bb(nxt_bb);
}
void IRGenerator::visit(ReadFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &lval : stmt.lval) {
        lval->accept(*this);
        auto val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if (val->get_op_id() == Instruction::OpID::Call) {
            if(!this->scope_.find(DefaultReturnName)) {
                // 获取函数信息
                std::shared_ptr<Function> func = std::static_pointer_cast<Function>(val->get_operand(0).lock());
                // 获取返回值类型
                auto ret_type = func->func_type_.lock()->result_;
                auto id = std::make_shared<LocalIdentifier>(ret_type, DefaultReturnName, false, nullptr);
                this->scope_.current_f_->add_local_identifier(id);
                this->scope_.push(DefaultReturnName, id);
            }
            // 更改val
            std::unique_ptr<LValStmt> lval = std::make_unique<LValStmt>();
            lval->id = DefaultReturnName;
            lval->accept(*this);
            val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(1); // 弹出一个操作数
        }
        args.emplace_back(val);
    }
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(args.size()); // 弹出参数
    std::shared_ptr<ReadInst> inst = std::make_shared<ReadInst>(args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
}
void IRGenerator::visit(WriteFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &expr : stmt.expr) {
        expr->accept(*this);
        args.emplace_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    this->scope_.current_f_->basic_blocks_.back()->pop_back_inst(args.size()); // 弹出参数
    std::shared_ptr<WriteInst> inst = std::make_shared<WriteInst>(args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    this->module_.all_instructions_.emplace_back(inst);
}
void IRGenerator::visit(ProgramHeadStmt &stmt) {
    // 暂时不需要处理
}
void IRGenerator::visit(ProgramBodyStmt &stmt) {
    // 全局常量
    if (stmt.const_decl != nullptr) {
        stmt.const_decl->accept(*this);
    }

    // 全局变量
    for (const auto &decl : stmt.var_decl) {
        decl->accept(*this);
    }

    // 函数
    for (const auto &decl : stmt.func_decl) {
        decl->accept(*this);
    }

    // 主函数体
    if (!this->scope_.is_global()) {
        this->scope_.leave();
    }
    std::vector<std::shared_ptr<Type>> main_args_type;
    std::vector<std::string> main_args_name;
    std::shared_ptr<FunctionType> main_func_type = std::make_shared<FunctionType>(std::make_shared<IntegerType>(kDefaultIntegerBitWidth,false), main_args_type);
    std::shared_ptr<Function> main_f = std::make_shared<Function>(main_func_type, "main", main_args_name);
    this->module_.add_function(main_f);
    this->scope_.current_f_ = main_f; // 记录当前作用域的函数
    this->scope_.push("main", main_f); // 记录函数到全局作用域中
    this->scope_.enter(); // 进入一个新的作用域

    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("main_begin_basic_block");
    ////this->module_.add_basic_block(bb);
    this->scope_.current_f_->add_basic_block(bb);
    for (const auto &stmt : stmt.comp_stmt) {
        stmt->accept(*this);
    }
}
void IRGenerator::visit(ProgramStmt &stmt) {
    // 先访问 head
    if (stmt.head != nullptr) {
        stmt.head->accept(*this);
    }

    // 再访问 body
    if (stmt.body != nullptr) {
        stmt.body->accept(*this);
    }
}
} // namespace ir