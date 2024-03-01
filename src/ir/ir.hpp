#pragma once

#include <list>
#include <string>
#include <vector>
#include <map>

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

/**
 * @brief Use 类
 * 
*/
class Use {
public:
    explicit Use(Value *val, unsigned arg_no) : val_(val), arg_no_(arg_no) {}
    Value *val_; // 某次使用的 Value 指针
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
        IntegerTID,
        RealTID,
        BooleanTID,
        CharTID,
        StringTID,
        ArrayTID,
        FunctionTID,
        ProcedureTID,
        PointerTID
        // TODO 扩展
    };
    explicit Type(TID tid) : tid_(tid) {}
    ~Type() = default;

    virtual std::string print();
    TID tid_;
};

/**
 * @brief 整数类型
 * 
*/
class IntegerType : public Type {
public:
    explicit IntegerType(unsigned num_bits) : Type(Type::IntegerTID), num_bits_(num_bits) {}
    unsigned num_bits_; // 位数: 32 or 64, int or long long 
};

/**
 * @brief 实数类型
 * 
*/
class RealType : public Type {
public:
    explicit RealType(unsigned num_bits) : Type(Type::RealTID), num_bits_(num_bits) {}
    unsigned num_bits_; // 位数: 32 or 64, float or double
};

/**
 * @brief 布尔类型
 * 
*/
class BooleanType : public Type {
public:
    explicit BooleanType() : Type(Type::BooleanTID) {}
};

/**
 * @brief 字符类型
 * 
*/
class CharType : public Type {
public:
    explicit CharType() : Type(Type::CharTID) {}
};

/**
 * @brief 字符串类型
 * 
*/
class StringType : public Type {
public:
    explicit StringType() : Type(Type::StringTID) {}
};

/**
 * @brief 数组类型
 * 
*/
class ArrayType : public Type {
public:
    explicit ArrayType(Type *elem_type, unsigned num_elems) : Type(Type::ArrayTID), elem_type_(elem_type), num_elems_(num_elems) {}
    Type *elem_type_; // 元素类型
    unsigned num_elems_; // 元素个数
};

/**
 * @brief 函数类型
 * 包括参数列表的类型和返回值的类型
*/
class FunctionType : public Type {
public:
    explicit FunctionType(Type *result, std::vector<Type *> params) : Type(Type::FunctionTID) {
        result_ = result; // 返回值类型
        for (Type *p : params) {
            args_.push_back(p); // 参数列表类型
        }
    }
    Type *result_;
    std::vector<Type *> args_; 
};

/**
 * @brief 过程类型
 * 只包括参数列表的类型, 不包括返回值类型
*/
class ProcedureType : public Type {
public:
    explicit ProcedureType(std::vector<Type *> params) : Type(Type::ProcedureTID) {
        for (Type *p : params) {
            args_.push_back(p); // 参数列表类型
        }
    }
    std::vector<Type *> args_; 
};

/**
 * @brief 指针类型
 * 
*/
class PointerType : public Type {
public:
    explicit PointerType(Type *contained) : Type(Type::PointerTID), contained_(contained) {}
    Type *contained_; // 指向的类型
};

// ----------------------------------------------------------------Value---------------------------------------------------------------
/**
 * @brief Value 基类
 * 
*/





// 值

class Value {
public:
    explicit Value(Type *type, const std::string &name) : type_(type), name_(name) {}
    ~Value() = default;

    // 由子类实现
    virtual std::string print() = 0;

    // 移除某个
    void remove_use(Value *val);

    //******************************************************************
    std::list<Use>::iterator add_use(Value *val, unsigned arg_no);
    // 删除迭代器指出的use
    void remove_use(std::list<Use>::iterator it) { use_list_.erase(it); }
    // user的第i个操作数准备不再使用this，因此删除this与user相关的use联系
    bool remove_used(Instruction *user, unsigned i);

    // Return if the value is a constant.
    bool is_constant();


    void replace_all_use_with(Value *new_val);
    Type *type_;
    std::string name_;
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
    Literal(Type *type, const std::string &name = "") : Value(type, name) {}
    ~Literal() = default;
};

/**
 * @brief int 类型
 * 
*/
class LiteraltInt : public Literal {
public:
    LiteraltInt(Type *type, int val) : Literal(type), val_(val) {}
    int val_;
    std::string print() override;
};


/**
 * @brief long long 类型
 * 
*/
class LiteralLong : public Literal {
public:
    LiteralLong(Type *type, long long val) : Literal(type), val_(val) {}
    long long val_;
    std::string print() override;
};

/**
 * @brief float 类型
 * 
*/
class LiteralFloat : public Literal {
public:
    LiteralFloat(Type *type, float val) : Literal(type), val_(val) {}
    float val_;
    std::string print() override;
};

/**
 * @brief double 类型
 * 
*/
class LiteralDouble : public Literal {
public:
    LiteralDouble(Type *type, double val) : Literal(type), val_(val) {}
    double val_;
    std::string print() override;
};

/**
 * @brief bool 类型
 * 
*/
class LiteralBool : public Literal {
public:
    LiteralBool(Type *type, bool val) : Literal(type), val_(val) {}
    bool val_;
    std::string print() override;
};

/**
 * @brief char 类型
 * 
*/
class LiteralChar : public Literal {
public:
    LiteralChar(Type *type, char val) : Literal(type), val_(val) {}
    char val_;
    std::string print() override;
};

/**
 * @brief string 类型
 * 
*/
class LiteralString : public Literal {
public:
    LiteralString(Type *type, const std::string &val) : Literal(type), val_(val) {}
    std::string val_;
    std::string print() override;
};

/**
 * @brief 数组类型
 * 
*/
class LiteralArray : public Literal {
public:
    LiteralArray(ArrayType *ty, const std::vector<Literal *> &val) : Literal(ty) {
        this->const_array.assign(val.begin(), val.end());
    }
    ~LiteralArray() = default;
    virtual std::string print() override;
    std::vector<Literal *> const_array;
};

// ----------------------------------------------------------------GlobalIdentifier---------------------------------------------------------------
class GlobalIdentifier : public Value {
public:
    GlobalIdentifier(const std::string &name, Module *m, Type *type, bool is_const, 
                        Literal *init_val);
    virtual std::string print() override;
    bool is_const_; // 是否为常量
    Literal *init_val_; // 初始值
};

// ----------------------------------------------------------------Function---------------------------------------------------------------
/**
 * @brief 函数参数类
 * 
*/
class Argument : public Value {
public:
    explicit Argument(Type *type, const std::string &name, Function *f, unsigned arg_no = 0) : Value(type, name), belong_f_(f), arg_no_(arg_no) {}
    ~Argument() {}
    virtual std::string print() override;
private:
    Function *belong_f_; // 所属函数
    unsigned arg_no_; // 参数序号
};

/**
 * @brief 函数类
 * 
*/
class Function : public Value {
public:
    Function(FunctionType *type, const std::string &name, Module *m);
    ~Function();
    virtual std::string print() override;

    /**
     * @brief 添加基本块
     * @param bb 基本块
    */
    void add_basic_block(BasicBlock *bb) { basic_blocks_.push_back(bb); }
    Type *get_return_type() const {
        return static_cast<FunctionType *>(type_)->result_;
    }
    bool is_declaration() { return basic_blocks_.empty(); }
    // void set_instr_name();

    /**
     * @brief 移除基本块
     * @param bb 基本块
    */
    void remove_bb(BasicBlock *bb);
    
    BasicBlock *getRetBB();

    std::vector<BasicBlock *> basic_blocks_; // 基本块, 一个函数体包含多个基本块
    std::vector<Argument *> args_;      // 参数列表
    Module *parent_; 
    unsigned seq_cnt_; 
    // std::vector<std::set<Value *>> vreg_set_; 
    int use_ret_cnt; // 程序中真正使用返回值的次数
};

// ----------------------------------------------------------------BasicBlock---------------------------------------------------------------
class BasicBlock {
};




// ----------------------------------------------------------------Module---------------------------------------------------------------
/**
 * 整个 ir 的核心类, 用来表示整个程序
 * 
*/
class Module {
public:
    /**
     * @brief 添加全局标识符
     * @param g 全局标识符
    */
    void add_global_identifier(GlobalIdentifier *g) { global_identifiers_.push_back(g); }

    /**
     * @brief 添加函数
     * @param f 函数
    */
    void add_function(Function *f) { functions_.push_back(f); }

    /**
     * @brief 获取指针类型
     * @param contained 指针指向的类型
     * @return PointerType* 
    */
    PointerType *get_pointer_type(Type *contained) {
        if (!pointer_map_.count(contained)) {
            pointer_map_[contained] = new PointerType(contained);
        }
        return pointer_map_[contained];
    }


    std::vector<GlobalIdentifier *> global_identifiers_; // 全局标识符, 包括全局变量和常量
    std::vector<Function *> functions_; // 函数


    std::map<Type *, PointerType *> pointer_map_; // 指针类型映射
};


} // namespace ir