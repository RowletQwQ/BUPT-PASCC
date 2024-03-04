#include "ir/ir_gen.hpp"

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
    
}
void IRGenerator::visit(RelExprStmt &stmt) {
    
}
void IRGenerator::visit(AddExprStmt &stmt) {
    
}
void IRGenerator::visit(MulExprStmt &stmt) {
    
}
void IRGenerator::visit(UnaryExprStmt &stmt) {
    
}
void IRGenerator::visit(PrimaryExprStmt &stmt) {
    
}
void IRGenerator::visit(ValueStmt &stmt) {
    
}
void IRGenerator::visit(NumberStmt &stmt) {
    
}
void IRGenerator::visit(StrStmt &stmt) {
    
}
void IRGenerator::visit(LValStmt &stmt) {
    
}
void IRGenerator::visit(FuncCallStmt &stmt) {
    
}
void IRGenerator::visit(PeriodStmt &stmt) {
    
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




void IRGenerator::visit(AssignStmt &stmt) {
    
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