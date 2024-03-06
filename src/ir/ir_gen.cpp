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
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
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
        std::shared_ptr<BinaryInst> inst = std::make_shared<BinaryInst>(op, lhs, rhs, this->scope_.current_f_->basic_blocks_.back());
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
    } else if (stmt.)
}
void IRGenerator::visit(StrStmt &stmt) {
    
}
void IRGenerator::visit(FuncCallStmt &stmt) {
    
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
            auto g = std::make_shared<GlobalIdentifier>(type, name, &this->module_, true, val);
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
                auto g = std::make_shared<GlobalIdentifier>(type, name, &this->module_, false, nullptr);
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
                auto g = std::make_shared<GlobalIdentifier>(array_type, name, &this->module_, false, nullptr);
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
    this->scope_.enter();
    std::vector<std::shared_ptr<Type>> args_type;
    for (const auto &arg : stmt.args) {
        args_type.push_back(build_basic_type(arg->basic_type));
    }
    std::shared_ptr<FunctionType> func_type = std::make_shared<FunctionType>(ret_type, args_type);
    std::shared_ptr<Function> f = std::make_shared<Function>(func_type, func_name, &this->module_);
    this->scope_.current_f_ = f; // 记录当前作用域的函数

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
        std::shared_ptr<UnaryInst> inst = std::make_shared<UnaryInst>(val->type_, Instruction::OpID::Null, val, this->scope_.current_f_->basic_blocks_.back());
    } else {
        // 处理数组
        for (int i = 0; i < stmt.array_index.size(); i++) {
            stmt.array_index[i] -> accept(*this);
            std::shared_ptr<Value> idx = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
            // 如果 index 是最后一个, 那就将目标类型视作数组元素类型
            if (i == int(stmt.array_index.size()) - 1) {
                ArrayType *at = (ArrayType *)val->type_.get();
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(at->elem_type_, val, idx, this->scope_.current_f_->basic_blocks_.back()); 
            } else {
                std::shared_ptr<LoadInst> inst = std::make_shared<LoadInst>(val->type_, val, idx, this->scope_.current_f_->basic_blocks_.back());
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
    
        // 处理右值
        std::shared_ptr<Value> ptr;
        stmt.expr->accept(*this);
        ptr = this->scope_.current_f_->basic_blocks_.back()->instructions_.back();
    
        // 构建赋值指令
        inst = std::make_shared<StoreInst>(val, ptr, this->scope_.current_f_->basic_blocks_.back());
        this->scope_.current_f_->basic_blocks_.back()->add_instruction(inst); 

        // TODO: 改变变量的值
    }
}


void IRGenerator::visit(IfStmt &stmt) {
    
}
void IRGenerator::visit(ForStmt &stmt) {
    
}
void IRGenerator::visit(ReadFuncStmt &stmt) {
    
}
void IRGenerator::visit(WriteFuncStmt &stmt) {
    
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