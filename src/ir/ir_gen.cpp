#include "ir/ir_gen.hpp"
#include "assert.h"
#include "common/exception/exception.hpp"
#include "common/log/log.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

namespace ir {

// 常量
constexpr unsigned kDefaultRealBitWidth = 64;
constexpr unsigned kDefaultIntegerBitWidth = 32;

// 工具函数
std::shared_ptr<Type> build_basic_type(BasicType type) {
    switch (type) {
        case BasicType::INT:
            return std::make_shared<IntegerType>(kDefaultIntegerBitWidth);
        case BasicType::REAL:
            return std::make_shared<RealType>(kDefaultRealBitWidth);
        case BasicType::CHAR:
            return std::make_shared<CharType>();
        case BasicType::BOOLEAN:
            return std::make_shared<BooleanType>();
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
    }
    return Instruction::OpID::Null;
}
Instruction::OpID build_op_id(UnaryExprStmt::UnaryExprType type) {
    switch (type) {
        case UnaryExprStmt::UnaryExprType::Minus:
            return Instruction::OpID::Sub;
        case UnaryExprStmt::UnaryExprType::Not:
            return Instruction::OpID::Not;
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
/**
 * @brief 离开一个作用域
*/
void Scope::leave() {
    symbols_.pop_back();
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
    if (stmt.type == RelExprStmt::RelExprType::NULL_TYPE) { // 降级处理
        stmt.add_expr->accept(*this);
    } else {
        Instruction::OpID op = build_op_id(stmt.type); // 操作符
        stmt.rel_expr->accept(*this);
        std::shared_ptr<Value> lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        stmt.add_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if(!CompareInst::can_be_compared(lhs->type_.get(), rhs->type_.get())) {
            LOG_ERROR("比较表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
            throw common::IRGenException("比较表达式类型不匹配");
        }
        // 新建指令，并赋予基本块信息
        std::shared_ptr<CompareInst> inst = std::make_shared<CompareInst>(op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));

    }
}
void IRGenerator::visit(AddExprStmt &stmt) {
    if (stmt.type == AddExprStmt::AddExprType::NULL_TYPE) { // 降级处理
        stmt.mul_expr->accept(*this);
    } else {
        Instruction::OpID op = build_op_id(stmt.type); // 操作符
        stmt.add_expr->accept(*this);
        std::shared_ptr<Value> lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        stmt.mul_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if (!BinaryInst::can_compute(lhs->type_.get(), rhs->type_.get())) {
            LOG_ERROR("二元运算表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
            throw common::IRGenException("二元运算表达式类型不匹配");
        }
        auto inst_type_id = std::max(lhs->type_->tid_, rhs->type_->tid_); // 选择更大的类型
        auto inst_type = std::make_shared<Type>(inst_type_id);
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(inst_type, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    }
}
void IRGenerator::visit(MulExprStmt &stmt) {
    if (stmt.type == MulExprStmt::MulExprType::NULL_TYPE) { // 降级处理
        stmt.unary_expr->accept(*this);
    } else {
        Instruction::OpID op = build_op_id(stmt.type); // 操作符
        stmt.mul_expr->accept(*this);
        std::shared_ptr<Value> lhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        stmt.unary_expr->accept(*this);
        std::shared_ptr<Value> rhs = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        if (!BinaryInst::can_compute(lhs->type_.get(), rhs->type_.get())) {
            LOG_ERROR("二元运算表达式类型不匹配，左侧表达式：%s, 右侧表达式：%s", lhs->type_->print().c_str(), rhs->type_->print().c_str());
            throw common::IRGenException("二元运算表达式类型不匹配");
        }
        auto inst_type_id = std::max(lhs->type_->tid_, rhs->type_->tid_); // 选择更大的类型
        auto inst_type = std::make_shared<Type>(inst_type_id);
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(inst_type, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    }
    
}
void IRGenerator::visit(UnaryExprStmt &stmt) {
    if (stmt.type == UnaryExprStmt::UnaryExprType::NULL_TYPE) { // 降级处理
        stmt.primary_expr->accept(*this);
    } else {
        Instruction::OpID op = build_op_id(stmt.type); // 操作符
        stmt.primary_expr->accept(*this);
        std::shared_ptr<Value> val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, op, val, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    }
}
void IRGenerator::visit(PrimaryExprStmt &stmt) {
    if (stmt.type == PrimaryExprStmt::PrimaryExprType::NULL_TYPE || stmt.type == PrimaryExprStmt::PrimaryExprType::Value) { // 降级处理
        stmt.value->accept(*this);
    } else {
        stmt.expr->accept(*this);
        std::shared_ptr<Value> val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Bracket, val, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
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
        type = std::make_shared<RealType>(kDefaultRealBitWidth);
        val = std::make_shared<LiteralDouble>(type, stmt.real_val);
    } else if (stmt.is_char) {
        type = std::make_shared<CharType>();
        val = std::make_shared<LiteralChar>(type, stmt.char_val);
    } else {
        type = std::make_shared<IntegerType>(kDefaultIntegerBitWidth);
        val = std::make_shared<LiteraltInt>(type, stmt.int_val);
    }
    std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(type, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back()); 
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
}
void IRGenerator::visit(StrStmt &stmt) {
    std::shared_ptr<Type> type = std::make_shared<StringType>();
    std::shared_ptr<Literal> val = std::make_shared<LiteralString>(type, stmt.val);
    std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(type, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
}
void IRGenerator::visit(FuncCallStmt &stmt) {
    // 先寻找函数的指针
    std::shared_ptr<Function> val = std::static_pointer_cast<Function>(this->scope_.find(stmt.id));
    assert(val != nullptr);

    // 得到参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &arg : stmt.args) {
        arg->accept(*this);
        args.emplace_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }

    // 构建函数调用指令
    std::shared_ptr<CallInst> inst = std::make_shared<CallInst>(val, args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
}
void IRGenerator::visit(PeriodStmt &stmt) {
    // 不需要处理   
}
void IRGenerator::visit(ConstDeclStmt &stmt) {
    for (const auto &pair : stmt.pairs) {
        std::string name = pair.first; // 常量名
        NumberStmt num_stmt = pair.second;
        std::shared_ptr<Type> type; // 类型
        std::shared_ptr<Literal> val; // 值
        if (num_stmt.is_real) {
            type = std::make_shared<RealType>(kDefaultRealBitWidth);
            val = std::make_shared<LiteralDouble>(type, num_stmt.real_val);
        } else {
            type = std::make_shared<IntegerType>(kDefaultIntegerBitWidth);
            val = std::make_shared<LiteraltInt>(type, num_stmt.int_val);
        }

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
    std::shared_ptr<Type> type = build_basic_type(stmt.basic_type); // 类型, 如果是数组, 就是元素类型
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
    std::shared_ptr<Type> ret_type = build_basic_type(stmt.ret_type); // 返回值类型

    // 记录参数时, 就要进入一个新的作用域
    if (!this->scope_.is_global()) { // 如果不是全局作用域, 就先退出当前作用域
        this->scope_.leave();
    }
    std::vector<std::shared_ptr<Type>> args_type; // 参数类型 
    std::vector<std::string> args_name; // 参数名
    for (const auto &arg : stmt.args) {
        for (const auto &arg_name : arg->id) {
            args_type.emplace_back(build_basic_type(arg->basic_type));
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
    assert (val != nullptr);
    if (stmt.array_index.size() == 0) { // 如果不是数组, 就说明是一个普通变量, 如 a、b 等, 当成一个 Null 的一元指令
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back()); 
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    } else {
        // 处理数组
        for (int i = 0; i < stmt.array_index.size(); i++) {
            stmt.array_index[i] -> accept(*this);
            std::shared_ptr<Value> idx = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            // 如果 index 是最后一个, 那就将目标类型视作数组元素类型
            if (i == int(stmt.array_index.size()) - 1) {
                ArrayType *at = (ArrayType *)val->type_.get();
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(at->elem_type_, val, idx, this->scope_.current_f_->basic_blocks_.back());
                this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst); 
                inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            } else {
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(val->type_, val, idx, this->scope_.current_f_->basic_blocks_.back());
                this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
                inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
            }
            val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        }
    }
}
void IRGenerator::visit(AssignStmt &stmt) {
    std::shared_ptr<Instruction> inst; // 对应的指令
    // 处理左值
    std::shared_ptr<Instruction> val;
    stmt.lval->accept(*this);
    val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    // 判断构造的 val 是不是一个函数名
    bool is_return = false;
    if (this->scope_.current_f_->basic_blocks_.back()->instructions_.back()->op_id_ == Instruction::OpID::Null && 
    this->scope_.current_f_->basic_blocks_.back()->instructions_.back()->operands_[0]->type_->tid_ == Type::FunctionTID) {
        is_return = true;
    }

    // 处理右值
    std::shared_ptr<Value> ptr;
    stmt.expr->accept(*this);
    ptr = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    // 构建赋值指令 or 返回指令
    if (!is_return) {
        inst = std::make_shared<StoreInst>(val, ptr, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    } else {
        inst = std::make_shared<ReturnInst>(ptr, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
        inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    }
}
void IRGenerator::visit(IfStmt &stmt) {
    // 得到 if 的条件
    stmt.expr->accept(*this);
    std::shared_ptr<Instruction> cond_inst = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    // if 会多产生两个基本块
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块
    std::shared_ptr<BasicBlock> then_bb = std::make_shared<BasicBlock>("then_basic_block"); // then 基本块
    this->scope_.current_f_->add_basic_block(then_bb);
    for (const auto &stmt : stmt.true_stmt) {
        stmt->accept(*this);
    }

    std::shared_ptr<BasicBlock> else_bb = std::make_shared<BasicBlock>("else_basic_block"); // else 基本块
    this->scope_.current_f_->add_basic_block(else_bb);
    for (const auto &stmt : stmt.false_stmt) {
        stmt->accept(*this);
    }
   
    // 构建条件跳转指令, 这个指令应该是在当前基本块的最后一条指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, then_bb, else_bb, cur_bb);
    cur_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cur_bb->instructions_.end()));

    // 再次新建一个基本块
    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("nxt_basic_block");
    this->scope_.current_f_->add_basic_block(bb);
}
void IRGenerator::visit(ForStmt &stmt) {
    // 先是一个赋值指令, 也就是循环变量赋初值
    std::shared_ptr<Value> id = this->scope_.find(stmt.id); // 符号表寻找对应的循环变量
    assert (id != nullptr);
    stmt.begin->accept(*this);
    std::shared_ptr<Value> begin_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    std::shared_ptr<StoreInst> store_inst = std::make_shared<StoreInst>(id, begin_val, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(store_inst);
    store_inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块

    // 然后新建一个基本块, 这个基本块是一个 if 条件
    std::shared_ptr<BasicBlock> cond_bb = std::make_shared<BasicBlock>("cond_basic_block");
    this->scope_.current_f_->add_basic_block(cond_bb);
    cur_bb->add_succ_bb(cond_bb);
    cond_bb->add_pre_bb(cur_bb);
    stmt.end->accept(*this);
    std::shared_ptr<Value> end_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    std::shared_ptr<Instruction> cond_inst = std::make_shared<CompareInst>(Instruction::OpID::Le, id, end_val, cond_bb);
    cond_bb->instructions_.emplace_back(cond_inst);
    cond_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));

    // 再新建一个基本块, 这个基本块是循环体
    std::shared_ptr<BasicBlock> body_bb = std::make_shared<BasicBlock>("body_basic_block");
    this->scope_.current_f_->add_basic_block(body_bb);
    for (const auto &stmt : stmt.stmt) {
        stmt->accept(*this);
    }
    // 循环体的最后一条指令是循环变量加 1
    std::shared_ptr<UnaryInst> inc_inst = std::make_shared<UnaryInst>(id->type_, Instruction::OpID::Inc, id, body_bb);
    body_bb->instructions_.emplace_back(inc_inst);
    inc_inst->set_pos_in_bb(std::prev(body_bb->instructions_.end()));
    body_bb->add_succ_bb(cond_bb);

    // 最后新建一个循环外的基本块
    std::shared_ptr<BasicBlock> nxt_bb = std::make_shared<BasicBlock>("nxt_basic_block");
    this->scope_.current_f_->add_basic_block(nxt_bb);

    // 补充上面的 if 指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, body_bb, nxt_bb, cond_bb, true);
    cond_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));
}
void IRGenerator::visit(WhileStmt &stmt) {
    // 先得到当前基本块
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back();

    // 然后新建一个条件基本块
    std::shared_ptr<BasicBlock> cond_bb = std::make_shared<BasicBlock>("cond_basic_block");
    this->scope_.current_f_->add_basic_block(cond_bb);
    cur_bb->add_succ_bb(cond_bb);
    cond_bb->add_pre_bb(cur_bb);
    stmt.expr->accept(*this);
    std::shared_ptr<Instruction> cond_inst = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    // 再新建一个循环体基本块
    std::shared_ptr<BasicBlock> body_bb = std::make_shared<BasicBlock>("body_basic_block");
    this->scope_.current_f_->add_basic_block(body_bb);
    for (const auto &stmt : stmt.stmt) {
        stmt->accept(*this);
    }
    body_bb->add_succ_bb(cond_bb);

    // 最后新建一个循环外的基本块
    std::shared_ptr<BasicBlock> nxt_bb = std::make_shared<BasicBlock>("nxt_basic_block");
    this->scope_.current_f_->add_basic_block(nxt_bb);

    // 创建 while 指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, body_bb, nxt_bb, cond_bb, true);
    cond_bb->instructions_.emplace_back(branch_inst);
    branch_inst->set_pos_in_bb(std::prev(cond_bb->instructions_.end()));
}
void IRGenerator::visit(ReadFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &lval : stmt.lval) {
        lval->accept(*this);
        args.emplace_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    std::shared_ptr<ReadInst> inst = std::make_shared<ReadInst>(args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
}
void IRGenerator::visit(WriteFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &expr : stmt.expr) {
        expr->accept(*this);
        args.emplace_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    std::shared_ptr<WriteInst> inst = std::make_shared<WriteInst>(args, this->scope_.current_f_->basic_blocks_.back());
    this->scope_.current_f_->basic_blocks_.back()->instructions_.emplace_back(inst);
    inst->set_pos_in_bb(std::prev(this->scope_.current_f_->basic_blocks_.back()->instructions_.end()));
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
    std::shared_ptr<FunctionType> main_func_type = std::make_shared<FunctionType>(std::make_shared<IntegerType>(kDefaultIntegerBitWidth), main_args_type);
    std::shared_ptr<Function> main_f = std::make_shared<Function>(main_func_type, "main", main_args_name);
    this->module_.add_function(main_f);
    this->scope_.current_f_ = main_f; // 记录当前作用域的函数
    this->scope_.push("main", main_f); // 记录函数到全局作用域中
    this->scope_.enter(); // 进入一个新的作用域

    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("main_begin_basic_block");
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