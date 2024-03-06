#include "ir/ir_gen.hpp"
#include "assert.h"

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
    }
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
}
Instruction::OpID build_op_id(UnaryExprStmt::UnaryExprType type) {
    switch (type) {
        case UnaryExprStmt::UnaryExprType::Minus:
            return Instruction::OpID::Sub;
        case UnaryExprStmt::UnaryExprType::Not:
            return Instruction::OpID::Not;
    }
}



// ----------------- Scope -----------------
// 进入一个新的作用域
void Scope::enter() {
    symbols_.push_back(std::map<std::string, Value *>());
}

// 离开一个作用域
void Scope::leave() {
    symbols_.pop_back();
}

// 检测是否在全局作用域
bool Scope::is_global() {
    return symbols_.size() == 1;
}

// 加入一个符号
bool Scope::push(const std::string &name, Value *value) {
    return symbols_.back().insert({name, value}).second;
}

// 查找一个符号
Value *Scope::find(const std::string &name) {
    // 从栈顶开始查找
    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return found->second;
        }
    }
    return nullptr;
}




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
        std::shared_ptr<CompareInst> inst = std::make_shared<CompareInst>(op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
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
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(lhs->type_, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
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
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(lhs->type_, op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
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
    }
}
void IRGenerator::visit(PrimaryExprStmt &stmt) {
    if (stmt.type == PrimaryExprStmt::PrimaryExprType::NULL_TYPE || stmt.type == PrimaryExprStmt::PrimaryExprType::Value) { // 降级处理
        stmt.value->accept(*this);
    } else {
        stmt.expr->accept(*this);
        std::shared_ptr<Value> val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Bracket, val, this->scope_.current_f_->basic_blocks_.back());
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
}
void IRGenerator::visit(StrStmt &stmt) {
    std::shared_ptr<Type> type = std::make_shared<StringType>();
    std::shared_ptr<Literal> val = std::make_shared<LiteralString>(type, stmt.val);
    std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(type, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back());
}
void IRGenerator::visit(FuncCallStmt &stmt) {
    // 先寻找函数的指针
    Function *val = (Function *)this->scope_.find(stmt.id);
    assert(val != nullptr);

    // 得到参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &arg : stmt.args) {
        arg->accept(*this);
        args.push_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }

    // 构建函数调用指令
    std::shared_ptr<CallInst> inst = std::make_shared<CallInst>(std::make_shared<Function>(*val), args, this->scope_.current_f_->basic_blocks_.back());
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
            auto g = std::make_shared<GlobalIdentifier>(type, name, std::make_shared<Module>(this->module_), true, val);
            this->scope_.push(name, g.get());
        } else {
            auto l = std::make_shared<LocalIdentifier>(type, name, this->scope_.current_f_, true, val);
            this->scope_.push(name, l.get());
        }
    }    
}
void IRGenerator::visit(VarDeclStmt &stmt) {
    std::shared_ptr<Type> type = build_basic_type(stmt.basic_type); // 类型, 如果是数组, 就是元素类型
    if (stmt.data_type == DataType::BasicType) { // 处理基本类型
        for (const auto &name : stmt.id) {
            if (this->scope_.is_global()) {
                auto g = std::make_shared<GlobalIdentifier>(type, name, std::make_shared<Module>(this->module_), false, nullptr);
                this->scope_.push(name, g.get());
            } else {
                auto l = std::make_shared<LocalIdentifier>(type, name, this->scope_.current_f_, false, nullptr); 
                this->scope_.push(name, l.get());
            }
        }
    } else if (stmt.data_type == DataType::ArrayType) { // 处理数组类型
        std::vector<unsigned> dims_elem_num;
        for (const auto &range : stmt.array_range) {
            dims_elem_num.push_back(range->end - range->begin + 1);
        }
        std::shared_ptr<ArrayType> array_type = std::make_shared<ArrayType>(type, dims_elem_num); // 数组类型
        for (const auto &name : stmt.id) {
            if (this->scope_.is_global()) {
                auto g = std::make_shared<GlobalIdentifier>(array_type, name, std::make_shared<Module>(this->module_), false, nullptr);
                this->scope_.push(name, g.get());
            } else {
                auto l = std::make_shared<LocalIdentifier>(array_type, name, this->scope_.current_f_, false, nullptr);
                this->scope_.push(name, l.get());
            }
        }
    } else { // 处理其他类型

    }
}


void IRGenerator::visit(FuncHeadDeclStmt &stmt) {
    std::string func_name = stmt.func_name; // 函数名 
    std::shared_ptr<Type> ret_type = build_basic_type(stmt.ret_type); // 返回值类型

    // 记录参数时, 就要进入一个新的作用域
    if (!this->scope_.is_global()) { // 如果不是全局作用域, 就先退出当前作用域
        this->scope_.leave();
    }
    std::vector<std::shared_ptr<Type>> args_type;
    for (const auto &arg : stmt.args) {
        args_type.push_back(build_basic_type(arg->basic_type));
    }
    std::shared_ptr<FunctionType> func_type = std::make_shared<FunctionType>(ret_type, args_type);
    std::shared_ptr<Function> f = std::make_shared<Function>(func_type, func_name, std::make_shared<Module>(this->module_));
    this->scope_.current_f_ = f; // 记录当前作用域的函数
    this->scope_.push(func_name, f.get()); // 记录函数到全局作用域中
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
    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("begin_basic_block", this->scope_.current_f_);
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
    Value *val = this->scope_.find(stmt.id); // 符号表寻找对应 value
    assert (val != nullptr);
    if (stmt.array_index.size() == 0) { // 如果不是数组
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Null, std::make_shared<Value>(*val), this->scope_.current_f_->basic_blocks_.back());
    } else {
        // 处理数组
        for (int i = 0; i < stmt.array_index.size(); i++) {
            stmt.array_index[i] -> accept(*this);
            std::shared_ptr<Value> idx = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            // 如果 index 是最后一个, 那就将目标类型视作数组元素类型
            if (i == int(stmt.array_index.size()) - 1) {
                ArrayType *at = (ArrayType *)val->type_.get();
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(at->elem_type_, std::make_shared<Value>(*val), idx, this->scope_.current_f_->basic_blocks_.back()); 
            } else {
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(val->type_, std::make_shared<Value>(*val), idx, this->scope_.current_f_->basic_blocks_.back());
            }
            val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back().get();
        }
    }
}
void IRGenerator::visit(AssignStmt &stmt) {
    std::shared_ptr<Instruction> inst; // 对应的指令
    if (!stmt.is_lval_func) { // 左值不是函数的情况
        // 处理左值
        std::shared_ptr<Value> val;
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
    
        // 构建赋值指令
        if (!is_return) {
            inst = std::make_shared<StoreInst>(val, ptr, this->scope_.current_f_->basic_blocks_.back());
        } else {
            inst = std::make_shared<ReturnInst>(ptr, this->scope_.current_f_->basic_blocks_.back());
        }
        // TODO: 改变变量的值？？？需要吗？？？
    }
}




void IRGenerator::visit(IfStmt &stmt) {
    // 得到 if 的条件
    stmt.expr->accept(*this);
    std::shared_ptr<Instruction> cond_inst = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();

    // if 会多产生两个基本块
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块
    std::shared_ptr<BasicBlock> then_bb = std::make_shared<BasicBlock>("then_basic_block", this->scope_.current_f_); // then 基本块
    for (const auto &stmt : stmt.true_stmt) {
        stmt->accept(*this);
    }
    std::shared_ptr<BasicBlock> else_bb = std::make_shared<BasicBlock>("else_basic_block", this->scope_.current_f_); // else 基本块
    for (const auto &stmt : stmt.false_stmt) {
        stmt->accept(*this);
    }

    // 构建条件跳转指令, 这个指令应该是在当前基本块的最后一条指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, then_bb, else_bb, cur_bb);

    // 再次新建一个基本块
    std::shared_ptr<BasicBlock> bb = std::make_shared<BasicBlock>("nxt_basic_block", this->scope_.current_f_);
}
void IRGenerator::visit(ForStmt &stmt) {
    // 先是一个赋值指令, 也就是循环变量赋初值
    Value *id = this->scope_.find(stmt.id); // 符号表寻找对应的循环变量
    assert (id != nullptr);
    stmt.begin->accept(*this);
    std::shared_ptr<Value> begin_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    std::shared_ptr<StoreInst> store_inst = std::make_shared<StoreInst>(std::make_shared<Value>(*id), begin_val, this->scope_.current_f_->basic_blocks_.back());
    std::shared_ptr<BasicBlock> cur_bb = this->scope_.current_f_->basic_blocks_.back(); // 当前基本块

    // 然后新建一个基本块, 这个基本块是一个 if 条件
    std::shared_ptr<BasicBlock> cond_bb = std::make_shared<BasicBlock>("cond_basic_block", this->scope_.current_f_);
    cur_bb->add_succ_bb(cond_bb);
    cond_bb->add_pre_bb(cur_bb);
    stmt.end->accept(*this);
    std::shared_ptr<Value> end_val = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    std::shared_ptr<Instruction> cond_inst = std::make_shared<CompareInst>(Instruction::OpID::Le, std::make_shared<Value>(*id), end_val, cond_bb);

    // 再新建一个基本块, 这个基本块是循环体
    std::shared_ptr<BasicBlock> body_bb = std::make_shared<BasicBlock>("body_basic_block", this->scope_.current_f_);
    for (const auto &stmt : stmt.stmt) {
        stmt->accept(*this);
    }
    body_bb->add_succ_bb(cond_bb);

    // 最后新建一个循环外的基本块
    std::shared_ptr<BasicBlock> nxt_bb = std::make_shared<BasicBlock>("nxt_basic_block", this->scope_.current_f_);

    // 补充上面的 if 指令
    std::shared_ptr<BranchInst> branch_inst = std::make_shared<BranchInst>(cond_inst, body_bb, nxt_bb, cond_bb);
}

void IRGenerator::visit(ReadFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &lval : stmt.lval) {
        lval->accept(*this);
        args.push_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    std::shared_ptr<ReadInst> inst = std::make_shared<ReadInst>(args, this->scope_.current_f_->basic_blocks_.back());
}
void IRGenerator::visit(WriteFuncStmt &stmt) {
    // 构建参数
    std::vector<std::shared_ptr<Value>> args;
    for (const auto &expr : stmt.expr) {
        expr->accept(*this);
        args.push_back(this->scope_.current_f_->basic_blocks_.back()->instructions_.back());
    }
    std::shared_ptr<WriteInst> inst = std::make_shared<WriteInst>(args, this->scope_.current_f_->basic_blocks_.back());
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