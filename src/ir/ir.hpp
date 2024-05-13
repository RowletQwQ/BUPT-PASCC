#pragma once

#include <cstddef>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace opt {
    class Optimize;
} // namespace optimize

namespace ir {
class Use;
class Type;
class Value;
class Instruction;
class Module;
class BasicBlock;
class Function;
class IrVisitor;

// 常量
constexpr unsigned kDefaultRealBitWidth = 32;
constexpr unsigned kDefaultIntegerBitWidth = 32;
const char* const DefaultReturnName = "__"; // 默认返回值名称

/**
 * @brief Use 类
 * 
*/
class Use {
public:
    explicit Use(std::shared_ptr<Value> val, unsigned arg_no) : val_(val), arg_no_(arg_no) {}
    std::weak_ptr<Value> val_; // 某次使用的 Value 指针
    unsigned arg_no_; // 操作数的序号, 如 func(a, b) 中 a 的序号为 0, b 的序号为 1
};

// ----------------------------------------------------------------Type---------------------------------------------------------------
/**
 * @brief Type 基类
 * 
*/
class Type {
public:
    enum TID {
        VoidTID,
        BooleanTID,
        CharTID, 
        IntegerTID,
        RealTID,
        StringTID,
        ArrayTID,
        FunctionTID,
        BlockTID, 
    };
    explicit Type(TID tid,bool is_pointer = false) : tid_(tid), is_pointer_(is_pointer) {}
    ~Type() = default;
    virtual std::string print() { return "";}
    virtual std::string placeholder() { return "";}
    virtual bool is_number() const { return tid_ == IntegerTID || tid_ == RealTID || tid_ == CharTID || tid_ == BooleanTID; }
    virtual bool is_real() const { return tid_ == RealTID; }
    virtual TID get_tid() const { return tid_; }
    virtual size_t get_size() { return 0; }
    virtual size_t get_elem_size() { return get_size(); }
    TID tid_;
    bool is_pointer_;
};

/**
 * @brief Void 类型
*/
class VoidType : public Type {
public:
    explicit VoidType() : Type(Type::VoidTID, false) {}
    virtual std::string print() override { return "void"; }
    virtual std::string placeholder() override { return ""; }
    virtual size_t get_size() override { return 0; }
};

/**
 * @brief 整数类型
 * 
*/
class IntegerType : public Type {
public:
    explicit IntegerType(unsigned num_bits, bool is_pointer) : Type(Type::IntegerTID, is_pointer), num_bits_(num_bits) {}
    unsigned num_bits_; // 位数: 32 or 64, int or long long 
    virtual std::string print() override {
        return num_bits_ == 32 ? "int" : "long long";
    }
    virtual std::string placeholder() override {
        return num_bits_ == 32 ? "%d" : "%lld";
    }
    virtual size_t get_size() override { return num_bits_ / 8; }
};

/**
 * @brief 实数类型
 * 
*/
class RealType : public Type {
public:
    explicit RealType(unsigned num_bits, bool is_pointer) : Type(Type::RealTID, is_pointer), num_bits_(num_bits) {}
    unsigned num_bits_; // 位数: 32 or 64, float or double
    virtual std::string print() override {
        return num_bits_ == 32 ? "float" : "double";
    }
    virtual std::string placeholder() override {
        return num_bits_ == 32 ? "%f" : "%lf";
    }
    virtual size_t get_size() override { return num_bits_ / 8; }
};

/**
 * @brief 布尔类型
 * 
*/
class BooleanType : public Type {
public:
    explicit BooleanType(bool is_pointer) : Type(Type::BooleanTID, is_pointer) {}
    virtual std::string print() override { return "int"; } // c 语言中没有 bool 类型
    virtual std::string placeholder() override { return "%d"; }
    virtual size_t get_size() override { return 1; }
};

/**
 * @brief 字符类型
 * 
*/
class CharType : public Type {
public:
    explicit CharType(bool is_pointer) : Type(Type::CharTID, is_pointer) {}
    virtual std::string print() override { return "char"; }
    virtual std::string placeholder() override { return "%c"; }
    virtual size_t get_size() override { return 1; }
};

/**
 * @brief 字符串类型
 * 
*/
class StringType : public Type {
public:
    explicit StringType() : Type(Type::StringTID, false) {}
    virtual std::string print() override { return "const char *"; }
    virtual std::string placeholder() override { return "%s"; }
    virtual size_t get_size() override { return 8; } // 指针大小
};

/**
 * @brief 数组类型
 * 
*/
class ArrayType : public Type {
public:
    explicit ArrayType(std::shared_ptr<Type> elem_type, std::vector<unsigned> dims_elem_num) : Type(Type::ArrayTID, false), elem_type_(elem_type), dims_elem_num_(dims_elem_num) {}
    virtual std::string print() override {
        std::string type_str = elem_type_->print();
        type_str = type_str + " ";
        for (unsigned i = 0; i < dims_elem_num_.size(); i++) {
            type_str = type_str + "[" + std::to_string(dims_elem_num_[i]) + "]";
        }
        return type_str;
    }
    virtual std::string placeholder() override { return ""; }
    virtual size_t get_size() override { 
        unsigned sum = 0;
        for (unsigned i = 0; i < dims_elem_num_.size(); i++) {
            sum += dims_elem_num_[i];
        }
        return sum * elem_type_->get_size();
    }
    Type::TID get_elem_tid() const { 
        if(elem_type_->tid_ == Type::ArrayTID) {
            return std::dynamic_pointer_cast<ArrayType>(elem_type_)->get_elem_tid();
        }
        return elem_type_->tid_;
    }
    bool is_number() const override {
        return elem_type_->is_number();
    }
    bool is_real() const override {
        return elem_type_->is_real();
    }
    size_t get_elem_size() override {
        if(elem_type_->tid_ == ArrayTID) {
            return elem_type_->get_elem_size();
        }
        return elem_type_->get_size();
    }

    std::vector<unsigned> all_dims() const {
        return dims_elem_num_;
    }
    std::shared_ptr<Type> elem_type_; // 元素类型
    std::vector<unsigned> dims_elem_num_; // 数组各维度元素数量
};

/**
 * @brief 函数类型
 * 包括参数列表的类型和返回值的类型
*/
class FunctionType : public Type {
public:
    explicit FunctionType(std::shared_ptr<Type> result, std::vector<std::shared_ptr<Type> > params);
    virtual std::string print() override {return result_->print();}
    virtual std::string placeholder() override { return result_->placeholder(); }
    bool is_number() const override { return result_->is_number(); }
    TID get_tid() const override { return result_->tid_; }
    std::shared_ptr<Type> result_;
    std::vector<std::shared_ptr<Type> > args_; 
    virtual size_t get_size() override { return result_->get_size(); }
};

// /**
//  * @brief 指针类型
//  * 
// */
// class PointerType : public Type {
// public:
//     explicit PointerType(std::shared_ptr<Type> contained) : Type(Type::PointerTID), contained_(contained) {}
//     std::shared_ptr<Type> contained_; // 指向的类型
// };

// ----------------------------------------------------------------Value---------------------------------------------------------------
/**
 * @brief Value 基类
 * 
*/
class Value {
public:
    enum class ValueID {
        Value,
        Literal,
        GlobalIdentifier,
        LocalIdentifier,
        Argument,
        Function,
        BasicBlock,
        Instruction
    };
    explicit Value(std::shared_ptr<Type> type,const Value::ValueID id = ValueID::Value, 
                    const std::string name = "") : type_(type), val_id_(id), name_(name) {}
    ~Value() = default;
    virtual std::string print() { return "";}

    /**
     * @brief 移除所有某个值的所有引用

     * 
     * @param val 要移除的值 
    */
    void remove_use(std::shared_ptr<Value> val) { use_list_.remove_if([val](Use u) { return u.val_.lock() == val; }); }


    /**
     * @brief 添加引用
     * 
     * @param val 引用的值
     * @param arg_no 引用的位置
     * @return std::list<Use>::iterator
    */
    std::list<Use>::iterator add_use(std::shared_ptr<Value> val, unsigned arg_no) {
        use_list_.push_back(Use(val, arg_no));
        std::list<Use>::iterator re = use_list_.end();
        return --re;
    }
    
    /**
     * @brief 移除引用
     * 
     * @param it 引用的迭代器
    */
    void remove_use(std::list<Use>::iterator it) { use_list_.erase(it); }

    /**
     * @brief 获取value的对应子类
     * 
     * @return ValueID
    */
    Value::ValueID get_val_id() { return val_id_; }

    bool is_inst() { return val_id_ == ValueID::Instruction; }
    bool is_literal() { return val_id_ == ValueID::Literal; }
    bool is_real() { return type_->tid_ == Type::RealTID; }
    bool is_integer() { return type_->tid_ == Type::IntegerTID || type_->tid_ == Type::BooleanTID || type_->tid_ == Type::CharTID; }
    bool is_array() { return type_->tid_ == Type::ArrayTID; }

    Value::ValueID val_id_; // 值的类型
    std::shared_ptr<Type> type_; // 返回值类型
    std::string name_; // 名称
    std::list<Use> use_list_; // 所有引用该Value的Instruction的集合，以及该Value在该Instruction的第几个操作数位置被引用
};

// ----------------------------------------------------------------Literal---------------------------------------------------------------
/**
 * @brief 字面量类
 * 字面量是指代码中直接出现的常量, 如 1, 2, 3, "hello", 'a', true, false 等, 它们都是没有名称的
 * 
*/
class Literal : public Value {
public:
    Literal(std::shared_ptr<Type> type, const std::string name = "") : Value(type, ValueID::Literal, name) {}
    virtual long get_int() const = 0;
    virtual double get_real() const  = 0;
    virtual void accept(IrVisitor &visitor) = 0;
    static std::shared_ptr<ir::Literal> make_literal(bool val);
    static std::shared_ptr<ir::Literal> make_literal(long val);
    static std::shared_ptr<ir::Literal> make_literal(double val);
    ~Literal() = default;
};

/**
 * @brief int 类型
 * 
*/
class LiteralInt : public Literal {
public:
    LiteralInt(std::shared_ptr<Type> type, int val) : Literal(type), val_(val) {}
    virtual std::string print() override { return std::to_string(val_); }
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
    int val_;
};


/**
 * @brief long long 类型
 * 
*/
class LiteralLong : public Literal {
public:
    LiteralLong(std::shared_ptr<Type> type, long long val) : Literal(type), val_(val) {}
    long long val_;
    virtual std::string print() override { return std::to_string(val_); }
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief float 类型
 * 
*/
class LiteralFloat : public Literal {
public:
    LiteralFloat(std::shared_ptr<Type> type, float val) : Literal(type), val_(val) {}
    float val_;
    virtual std::string print() override { return std::to_string(val_); }
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief double 类型
 * 
*/
class LiteralDouble : public Literal {
public:
    LiteralDouble(std::shared_ptr<Type> type, double val, std::string literal) : Literal(type), val_(val), str_(literal)  {}
    double val_;
    std::string str_;
    virtual std::string print() override { return str_; }
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief bool 类型
 * 
*/
class LiteralBool : public Literal {
public:
    LiteralBool(std::shared_ptr<Type> type, bool val) : Literal(type), val_(val) {}
    bool val_;
    virtual std::string print() override { return val_ ? "true" : "false"; }
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief char 类型
 * 
*/
class LiteralChar : public Literal {
public:
    LiteralChar(std::shared_ptr<Type> type, char val) : Literal(type), val_(val) {}
    char val_;
    virtual std::string print() override { return "'" + std::string(1, val_) + "'";}
    virtual long get_int() const override { return val_; }
    virtual double get_real() const  override { return val_; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief string 类型
 * 
*/
class LiteralString : public Literal {
public:
    LiteralString(std::shared_ptr<Type> type, const std::string val) : Literal(type), val_(val) {}
    std::string val_;
    virtual std::string print() override { return "\"" + val_ + "\"";}
    virtual long get_int() const override { throw "string can't be converted to integer"; }
    virtual double get_real() const  override { throw "string can't be converted to real"; }
    void accept(IrVisitor &visitor) override;
};

/**
 * @brief 数组类型
 * 
*/
class LiteralArray : public Literal {
public:
    LiteralArray(std::shared_ptr<ArrayType> ty, const std::vector<std::shared_ptr<Literal> > &val): Literal(ty) {
        this->const_array.assign(val.begin(), val.end());
    }
    ~LiteralArray() = default;
    virtual std::string print() override {
        std::string ret = "{";
        for (int i = 0; i < const_array.size(); i++) {
            ret = ret + const_array[i]->print();
            if (i != const_array.size() - 1) {
                ret = ret + ", ";
            }
        }
        ret = ret + "}";
        return ret;
    }
    virtual long get_int() const override { throw "array can't be converted to integer"; }
    virtual double get_real() const  override { throw "array can't be converted to real"; }
    std::vector<std::shared_ptr<Literal> > const_array;
    void accept(IrVisitor &visitor) override;
};

// ----------------------------------------------------------------GlobalIdentifier---------------------------------------------------------------
class GlobalIdentifier : public Value {
public:
    /**
     * @brief Construct a new Global Identifier object
     * 
     * @param name 
     * @param m 所属模块
     * @param type 
     * @param is_const 
     * @param init_val 
     */
    GlobalIdentifier(std::shared_ptr<Type> type, const std::string name, bool is_const, std::shared_ptr<Literal> init_val);
    ~GlobalIdentifier() = default;
    virtual std::string print() override {
        return name_;
    }
    void accept(IrVisitor &visitor);
    bool is_const_; // 是否为常量
    std::shared_ptr<Literal> init_val_; // 初始值
};

// ----------------------------------------------------------------LocalIdentifier---------------------------------------------------------------
class LocalIdentifier : public Value {
public:
    LocalIdentifier(std::shared_ptr<Type> type, const std::string name, bool is_const, std::shared_ptr<Literal> init_val);  
    ~LocalIdentifier() = default;
    virtual std::string print() override {
        if (type_->is_pointer_) {
            return "*" + name_;
        }
        return name_;
    }
    virtual Type::TID get_elem_tid() const { 
        if(type_->tid_ == Type::ArrayTID) {
            return std::dynamic_pointer_cast<ArrayType>(type_)->get_elem_tid();
        }
        return type_->tid_;
    }
    bool is_const_; // 是否为常量
    std::shared_ptr<Literal> init_val_; // 初始值  
};


// ----------------------------------------------------------------Function---------------------------------------------------------------
/**
 * @brief 函数参数类
 * 
*/
class Argument : public Value {
public:
    explicit Argument(std::shared_ptr<Type> type, const std::string name, unsigned arg_no = 0) : Value(type, ValueID::Argument, name), arg_no_(arg_no) {}
    ~Argument() {}
    virtual std::string print() override {
        return name_;
    }
    unsigned arg_no_; // 参数序号
};

/**
 * @brief 函数类
 * 
*/
class Function : public Value, public std::enable_shared_from_this<Function> {
public:
    Function(std::shared_ptr<FunctionType> type, const std::string name, std::vector<std::string> arg_name);
    ~Function() = default;
    virtual std::string print() override {
        std::string type_str = func_type_.lock()->result_->print();
        std::string ret = type_str + " " + name_ + "(";
        for (int i = 0; i < args_.size(); i++) {
            ret += args_[i]->type_->print();
            if(args_[i]->type_->is_pointer_) {
                ret += "*";
            }
            ret += " " + args_[i]->name_;
            if (i != args_.size() - 1) {
                ret = ret + ", ";
            }
        }
        ret = ret + ")";
        return ret;
    }

    void accept(IrVisitor &visitor);
    
    /**
     * @brief 添加基本块
     * @param bb 基本块
    */
    void add_basic_block(std::shared_ptr<BasicBlock> bb);

    /**
     * @brief 添加局部标识符
     * @param l 局部标识符
    */
    void add_local_identifier(std::shared_ptr<LocalIdentifier> l) { local_identifiers_.emplace_back(l); }

    std::vector<std::shared_ptr<LocalIdentifier> > local_identifiers_; // 局部标识符
    std::vector<std::shared_ptr<BasicBlock> > basic_blocks_; // 基本块
    std::vector<std::shared_ptr<Argument> > args_; // 参数列表
    std::weak_ptr<FunctionType> func_type_; // 函数类型
};

// ----------------------------------------------------------------BasicBlock---------------------------------------------------------------
/**
 * @brief 基本块类
 * 
*/
class BasicBlock : public Value {
public:
    explicit BasicBlock(const std::string name) : Value(std::make_shared<Type>(Type::BlockTID), ValueID::BasicBlock, name) {}
    ~BasicBlock() = default;
    virtual std::string print() override;
    /**
     * @brief 添加指令
     *  
    */
    void add_instruction(std::shared_ptr<Instruction> i) { instructions_.emplace_back(i); }

    /**
     * @brief 添加前驱基本块
     * 
    */
    void add_pre_bb(std::weak_ptr<BasicBlock> bb) { pre_bbs_.emplace_back(bb); }
    /**
     * @brief 添加后继基本块
    */
    void add_succ_bb(std::weak_ptr<BasicBlock> bb) { succ_bbs_.emplace_back(bb); }

    void pop_back_inst(int n) { instructions_.erase(instructions_.end() - n, instructions_.end()); }

    void accept(IrVisitor &visitor);

    std::vector<std::shared_ptr<ir::Instruction> > instructions_; // 指令列表
    std::vector<std::weak_ptr<BasicBlock> > pre_bbs_; // 前驱基本块
    std::vector<std::weak_ptr<BasicBlock> > succ_bbs_; // 后继基本块
    int index_; // 基本块的索引
};

// ----------------------------------------------------------------Instruction---------------------------------------------------------------
/**
 * @brief 指令基类
 * 
*/
class Instruction : public Value {
public:
    // 操作码
    enum OpID {
        // Function
        Call, 
        Ret, 
        
        // Branch Jump
        Br,
        Break,
        Continue,
        ContinueInc,

        // Binary Operation
        Add, 
        Sub, 
        Mul, 
        Div, 
        Mod, 
        And, 
        Or,
        OrElse,
        AndThen,

        // Unary Operation
        Not,
        BitReverse,
        LogicalNot,
        Bracket,
        Null, // 这个一元运算就是当做本身
        Minus, // -a
        Inc, // ++a
        
        

        // Compare Operation
        Eq,
        Ne,
        Gt,
        Ge,
        Lt,
        Le,
        In,
        
        // Assign(Store) Operation
        Assign,

        // Array(Load) Operation
        Visit, 

        // Inner Function Call
        Read,
        Write
    };

    virtual void accept(IrVisitor &visitor) = 0;
    static std::map<Instruction::OpID, std::string> op2str_;
    explicit Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, 
        std::weak_ptr<BasicBlock> bb, bool before = false);
    explicit Instruction(const std::string name, std::shared_ptr<Type> ty, OpID id, unsigned num_ops, 
        std::weak_ptr<BasicBlock> bb, bool before = false);
    ~Instruction() = default;
    void init();

    static std::string op_to_string(OpID op);

    /**
     * @brief 设置操作数
     * 
    */
    virtual void set_operand(unsigned i, std::weak_ptr<Value> val) {
        if (operands_[i].expired()) {
            operands_[i] = val;
        } else {
            operands_[i].lock() = val.lock();
            operands_[i] = val;
        }
    }

    /**
     * @brief 获取操作数
     * 
    */
    virtual std::weak_ptr<Value> get_operand(unsigned i) {
        return operands_[i];
    }

    virtual OpID get_op_id() { return op_id_; }
    
    unsigned get_num_ops() { return num_ops_; }

    /**
     * @brief 设置操作数的位置
     * 
    */
    virtual void set_pos_in_bb(std::vector<std::shared_ptr<ir::Instruction> >::iterator pos) {
        pos_in_bb_ = pos;
    }

    // 以下是判断指令类型的函数
    bool is_call_inst() { return op_id_ == OpID::Call; }
    bool is_ret_inst() { return op_id_ == OpID::Ret; }
    bool is_br_inst() { return op_id_ == OpID::Br; }
    bool is_binary_inst() { return op_id_ >= OpID::Add && op_id_ <= OpID::AndThen; }
    bool is_unary_inst() { return op_id_ >= OpID::Not && op_id_ <= OpID::Inc; }
    bool is_assign_inst() { return op_id_ == OpID::Assign; }
    bool is_load_inst() { return op_id_ == OpID::Visit; }
    bool is_expr() { return is_binary_inst() || is_unary_inst() || is_assign_inst() || is_load_inst(); }
    bool is_io_inst() { return op_id_ == OpID::Read || op_id_ == OpID::Write; }
    bool is_arith_inst() { return op_id_ >= OpID::Add && op_id_ <= OpID::Le; }
    bool is_array_visit_inst() { return op_id_ == OpID::Visit && num_ops_ == 2; }
    

    OpID op_id_; // 操作码
    unsigned num_ops_; // 操作数个数
    std::vector<std::weak_ptr<Value>> operands_; // 操作数
    std::vector<std::list<Use>::iterator> use_pos_; // 与操作数数组一一对应，是对应的操作数的 uselist 里面，与当前指令相关的 use 的迭代器
    std::vector<std::shared_ptr<ir::Instruction> >::iterator pos_in_bb_; // 在 bb 的指令 list 的位置迭代器, 最多只能有一个
    std::weak_ptr<BasicBlock> bb_; // 所属基本块
};

/**
 * @brief 二元指令
 * 
*/
class BinaryInst : public Instruction {
public:
    /**
     * @brief Construct a new Binary Inst object
     * 
     * @param ty 目标数据类型
     * @param op 操作码
     * @param v1 第一个操作数
     * @param v2 第二个操作数
     * @param bb 所属基本块
     * @details 形如 b+c, a-b, a*b, a/b, a%b 等式，即为二元表达式
     *          这个类用来表示这些表达式，同时起到承载这些表达式的作用
     */
    BinaryInst(std::shared_ptr<Type> ty, OpID op, std::shared_ptr<Value> v1, std::shared_ptr<Value> v2, 
        std::weak_ptr<BasicBlock> bb)
      : Instruction(ty, op, 2, bb) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    ~BinaryInst() = default;
    virtual std::string print() override {
        return operands_[0].lock()->print() + " " + Instruction::op2str_[op_id_] + " " + operands_[1].lock()->print();
    }
    virtual void accept(IrVisitor &visitor) override;

    /**
     * @brief 用来判断两个类型是否可以进行计算
     * 
     * @param t1 
     * @param t2 
     * @return true 
     * @return false 
     */
    static bool can_compute(const Type *t1, const Type *t2);
    bool is_logical() const { return op_id_ == And || op_id_ == Or || op_id_ == AndThen || op_id_ == OrElse; }
};

/**
 * @brief 一元指令
*/
class UnaryInst : public Instruction {
public:
    /**
     * @brief Construct a new Unary Inst object
     * 
     * @param ty 目标数据类型
     * @param op 操作码
     * @param val 操作数
     * @param bb 所属基本块
     * @details 形如 -a, !a, ~a 等式，即为一元表达式
     */
    UnaryInst(std::shared_ptr<Type> ty, OpID op, std::shared_ptr<Value> val,
        std::weak_ptr<BasicBlock> bb)
      : Instruction(ty, op, 1, bb) {
        set_operand(0, val);
    }
    UnaryInst(std::shared_ptr<Type> ty, OpID op, std::shared_ptr<Value> val,
        std::weak_ptr<BasicBlock> bb, const std::string name)
      : Instruction(name, ty, op, 1, bb) {
        set_operand(0, val);
    }
    ~UnaryInst() = default;
    virtual std::string print() override {
        if (op_id_ == Instruction::Bracket) {
            return "(" + operands_[0].lock()->print() + ")"; 
        } else if (op_id_ == Instruction::Null) {
            if (operands_[0].lock()->type_->tid_ == Type::FunctionTID) {
                return operands_[0].lock()->name_ + "()";
            }
            if (operands_[0].lock()->type_->is_pointer_) {
                return operands_[0].lock()->print();
            }
            return operands_[0].lock()->print();
        } else {
            // 如果组成的表达式最前面是连续3个-, 就让他们空格开
            std::string ret = Instruction::op2str_[op_id_] + operands_[0].lock()->print();
            if (ret.length() > 3 && ret[0] == '-' && ret[1] == '-' && ret[2] == '-') {
                return "- - " + ret.substr(2);
            } else {
                return Instruction::op2str_[op_id_] + operands_[0].lock()->print();
            }
        }
    }

    virtual void accept(IrVisitor &visitor) override;
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }

    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }

};

/**
 * @brief 比较指令
*/
// 比较指令返回值一定是 bool 类型
class CompareInst : public Instruction {
public:
    /**
     * @brief Construct a new Compare Inst object
     * 
     * @param op 操作码
     * @param v1 第一个操作数
     * @param v2 第二个操作数
     * @param bb 所属基本块
     * @details 形如 a==b, a!=b, a>b, a>=b, a<b, a<=b 等式，即为比较表达式
     */
    CompareInst(OpID op, std::shared_ptr<Value> v1, std::shared_ptr<Value> v2, 
        std::weak_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::BooleanTID), op, 2, bb) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    ~CompareInst() = default;

    virtual std::string print() override {
        return operands_[0].lock()->print() + " " + Instruction::op2str_[op_id_] + " " + operands_[1].lock()->print();
    }

    static bool can_be_compared(const Type *t1, const Type *t2);
    virtual void accept(IrVisitor &visitor) override;
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }

    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }

}; 


/**
 * @brief 存储指令，即赋值运算指令
 *
 */
class StoreInst : public Instruction {
public:
    /**
     * @brief Construct a new Store Inst object
     * 
     * @param ty 目标数据类型
     * @param val 要存储的值
     * @param ptr 存储的地址
     * @param bb 所属基本块
     * @details 形如 a = b, a = 1, a = b[1] 等式，即为赋值表达式
     */
    StoreInst(std::shared_ptr<Value> val, std::shared_ptr<Value> ptr,
            std::weak_ptr<BasicBlock> bb )
      : Instruction(std::make_shared<Type>(Type::BooleanTID), OpID::Assign, 2, bb) {
        set_operand(0, val);
        set_operand(1, ptr);
    }
    ~StoreInst() = default;
    virtual std::string print() override {
        // 如果发现存储的是一个函数, 那么左值就是函数名_
        if (operands_[0].lock()->type_->tid_ == Type::FunctionTID) {
            std::stringstream ss;
            ss << DefaultReturnName << " = " << operands_[1].lock()->print();
            return ss.str();
        } else if (operands_[0].lock()->type_->is_pointer_) {
            return operands_[0].lock()->print() + " = " + operands_[1].lock()->print();
        }
        return operands_[0].lock()->print() + " = " + operands_[1].lock()->print();
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

/**
 * @brief 加载指令
 *
*/
class LoadInst : public Instruction {
public:
    /**
     * @brief Construct a new Load Inst object
     * 
     * @param ty 目标数据类型
     * @param ptr 加载的地址
     * @param bb 所属基本块
     * @details 形如 *b, a = b[1] 等式
     */
    LoadInst(std::shared_ptr<Type> ty, std::shared_ptr<Value> array, std::shared_ptr<Value> idx,
            std::weak_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Visit, 2, bb) {
        set_operand(0, array);
        set_operand(1, idx);
        name_ = array->name_;
    }

    LoadInst(std::shared_ptr<Type> ty, std::shared_ptr<Value> id,
            std::weak_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Visit, 1, bb) {
        set_operand(0, id);
        name_ = id->name_;
    }
    ~LoadInst() = default;
    virtual std::string print() override {
        if (num_ops_ == 1) {
            return operands_[0].lock()->print();
        }
        return operands_[0].lock()->print() + "[" + operands_[1].lock()->print() + "]";
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
    bool is_array_visit() const { return num_ops_ == 2; }
};

/**
 * @brief 读指令
*/
class ReadInst : public Instruction {
public:
    ReadInst(std::vector<std::shared_ptr<Value>> args, 
            std::weak_ptr<BasicBlock> bb)
      : Instruction("read", std::make_shared<Type>(Type::VoidTID), OpID::Read, args.size(), bb) {
        for (int i = 0; i < args.size(); i++) {
            set_operand(i, args[i]);
        }
    }
    ~ReadInst() = default;
    virtual std::string print() override {
        std::string ans = "scanf(\"";
        for (int i = 0; i < operands_.size(); i++) {
            std::string placeholder = operands_[i].lock()->type_->placeholder();
            ans = ans + placeholder;
            // if (i != operands_.size() - 1) {
            //     ans = ans + ", ";
            // }
        }
        ans = ans + "\", ";
        for (int i = 0; i < operands_.size(); i++) {
            ans = ans + "&" + operands_[i].lock()->print();
            if (operands_[i].lock()->type_->tid_ == Type::FunctionTID) {
                ans = DefaultReturnName;
            }
            if (i != operands_.size() - 1) {
                ans = ans + ", ";
            }
        }
        ans = ans + ")";
        return ans;
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

/**
 * @brief 写指令
*/
class WriteInst : public Instruction {
public:
    WriteInst(std::vector<std::shared_ptr<Value>> args,
            std::weak_ptr<BasicBlock> bb)
        : Instruction("write", std::make_shared<Type>(Type::VoidTID), OpID::Read, args.size(), bb) {
        for (int i = 0; i < args.size(); i++) {
            set_operand(i, args[i]);
        }
    }
    ~WriteInst() = default;
    virtual std::string print() override {
        std::string ans = "printf(\"";
        for (int i = 0; i < operands_.size(); i++) {
            std::string placeholder = operands_[i].lock()->type_->placeholder();
            ans = ans + placeholder;
        }
        ans = ans + "\", ";
        for (int i = 0; i < operands_.size(); i++) {
            ans = ans + operands_[i].lock()->print();
            if (i != operands_.size() - 1) {
                ans = ans + ", ";
            }
        }
        ans = ans + ")";
        return ans;
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

/**
 * @brief 调用指令
*/
class CallInst : public Instruction {
public:
    /**
     * @brief Construct a new Call Inst object
     * 
     * @param ty 目标数据类型
     * @param func 被调用的函数
     * @param bb 所属基本块
     * @details 用于调用函数
     */
    CallInst(std::shared_ptr<Function> func, std::vector<std::shared_ptr<Value>> args,
            std::weak_ptr<BasicBlock> bb)
      : Instruction(func->func_type_.lock()->result_, OpID::Call, args.size() + 1, bb) {
        // 前面的操作数是参数，最后一个操作数是函数
        int num_ops = args.size() + 1;
        for (int i = 0; i < num_ops - 1; i++) {
            set_operand(i, args[i]);
        }
        set_operand(num_ops - 1, func);
    }
    ~CallInst() = default;
    virtual std::string print() override {
        std::string ret = operands_[num_ops_ - 1].lock()->name_;
        ret += "(";
        std::shared_ptr<Function> func = std::dynamic_pointer_cast<Function>(operands_[num_ops_ - 1].lock());
        for (int i = 0; i < num_ops_ - 1; i++) {
            if (func->args_[i]->type_->is_pointer_) {
                ret += "&";
            }
            ret += operands_[i].lock()->print();
            
            if (i != num_ops_ - 2) {
                ret += ", ";
            }
        }
        ret += ")";
        return ret;
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

/**
 * @brief 返回指令
*/
class ReturnInst : public Instruction {
public:
    /**
     * @brief Construct a new Return Inst object
     * 
     * @param val 返回值
     * @param bb 所属基本块
     * @details 用于返回
     */
    ReturnInst(std::shared_ptr<Value> val, 
            std::weak_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Ret, 1, bb) {
        set_operand(0, val);
    }
    ~ReturnInst() = default;
    virtual std::string print() override {
        return "return " + operands_[0].lock()->print()+"";
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

class BreakInst : public Instruction {
public:
    /**
     * @brief Construct a new Break Inst object
     * 
     * @param brk_bb 跳转的基本块
     * @param bb 所属基本块
     */
    BreakInst(std::shared_ptr<BasicBlock> brk_bb,std::weak_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Break, 1, bb) {
        set_operand(0, brk_bb);
      }
    ~BreakInst() = default;
    virtual std::string print() override {
        return "break";
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    std::weak_ptr<Value> get_operand(unsigned i) override {
        return operands_[i];
    }
    virtual void accept(IrVisitor &visitor) override;
};

class ContinueInst : public Instruction {
public:
    /**
     * @brief Construct a new Continue Inst object
     * 
     * @param jmp_bb 跳转的基本块
     * @param bb 所属基本块
     */
    ContinueInst(std::shared_ptr<BasicBlock> jmp_bb, std::weak_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Continue, 1, bb) {
        set_operand(0, jmp_bb);
      }
    ~ContinueInst() = default;
    virtual std::string print() override {
        return "continue";
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

class ContinueIncInst : public Instruction {
public:
    /**
     * @brief Construct a new Continue Inc Inst object
     * 
     * @param cont_bb 循环所在的基本块（需要执行这个基本块的最后一条指令）
     * @param jmp_bb 跳转的基本块
     * @param bb 所属基本块
     */
    ContinueIncInst(std::shared_ptr<BasicBlock> cont_bb, std::shared_ptr<BasicBlock> jmp_bb,std::weak_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::ContinueInc, 2, bb) {
        set_operand(0, cont_bb);
        set_operand(1, jmp_bb);
      }
    ~ContinueIncInst() = default;
    virtual std::string print() override {
        return "continue_inc";
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};

// 分支跳转指令
class BranchInst : public Instruction {
public:
    /**
     * @brief Construct a new Branch Inst object
     * 
     * @param cond 条件
     * @param then_bb 真分支
     * @param else_bb 假分支
     * @param bb 所属基本块
     * @details 用于分支跳转
     */
    BranchInst(std::shared_ptr<Value> cond, std::shared_ptr<BasicBlock> then_bb, std::shared_ptr<BasicBlock> else_bb, 
                std::weak_ptr<BasicBlock> bb, bool is_loop_cond = false)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Br, 3, bb) {
        then_bb->add_pre_bb(bb);
        else_bb->add_pre_bb(bb);
        bb.lock()->add_succ_bb(then_bb);
        bb.lock()->add_succ_bb(else_bb);
        set_operand(0, cond);
        set_operand(1, then_bb);
        set_operand(2, else_bb);
        is_loop_cond_ = is_loop_cond;
    }
    ~BranchInst() = default;
    bool is_loop_cond_; // 是否为循环条件
    virtual std::string print() override {
        std::string res;
        if (!is_loop_cond_) {
            res += "if (";
            res += operands_[0].lock()->print();
            res += ")";
        } else {
            res += "while (";
            res += operands_[0].lock()->print();
            res += ")";
        }
        return res;
    }
    // void set_operand(unsigned i, std::shared_ptr<Value> val) {
    //     operands_[i] = val;
    // }
    // std::weak_ptr<Value> get_operand(unsigned i) override {
    //     return operands_[i];
    // }
    virtual void accept(IrVisitor &visitor) override;
};




// ----------------------------------------------------------------Module---------------------------------------------------------------
/**
 * 整个 ir 的核心类, 用来表示整个程序
 * 
*/
class Module {
public:
    explicit Module() {}
    /**
     * @brief 添加全局标识符
     * @param g 全局标识符
    */
    void add_global_identifier(std::shared_ptr<GlobalIdentifier> g) { 
        global_identifiers_.emplace_back(g); 

    }

    /**
     * @brief 添加函数
     * @param f 函数
    */
    void add_function(std::shared_ptr<Function> f) { functions_.emplace_back(f); }

    /**
     * @brief 添加常量
     * @param l 常量
     */
    void add_literal(std::shared_ptr<Literal> l) { all_literals_.emplace_back(l); }

    /**
     * @brief 添加指令
     * @param i 指令
    */
    void add_instruction(std::shared_ptr<Instruction> i) { all_instructions_.emplace_back(i); }

    void accept(IrVisitor &visitor);

    std::vector<std::shared_ptr<GlobalIdentifier> > global_identifiers_; // 全局标识符, 包括全局变量和常量
    std::vector<std::shared_ptr<Function> > functions_; // 函数
    // 为防止循环引用，这里保存生成过程中会出现的所有指令
    std::vector<std::shared_ptr<Instruction> > all_instructions_;
    // 下面保存所有的常量
    std::vector<std::shared_ptr<Literal> > all_literals_;
    // 下面保存优化阶段生成的所有的value
    std::vector<std::shared_ptr<Value> > all_values_;
};


} // namespace ir