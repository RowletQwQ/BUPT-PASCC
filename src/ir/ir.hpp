#pragma once

#include <list>
#include <memory>
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
    explicit Use(std::shared_ptr<Value> val, unsigned arg_no) : val_(val), arg_no_(arg_no) {}
    std::weak_ptr<Value> val_; // 某次使用的 Value 指针
    unsigned arg_no_; // 操作数的序号, 如 func(a, b) 中 a 的序号为 0, b 的序号为 1
};

// ----------------------------------------------------------------Type---------------------------------------------------------------
/**
 * @brief Type 基类
 * 
*/
class Type : public std::enable_shared_from_this<Type>{
public:
    enum TID {
        VoidTID, 
        IntegerTID,
        RealTID,
        BooleanTID,
        CharTID,
        StringTID,
        ArrayTID,
        FunctionTID,
        BlockTID, 
    };
    explicit Type(TID tid) : tid_(tid) {}
    ~Type() = default;

    TID tid_;
};

/**
 * @brief Void 类型
*/
class VoidType : public Type {
public:
    explicit VoidType() : Type(Type::VoidTID) {}
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
    explicit ArrayType(std::shared_ptr<Type> elem_type, std::vector<unsigned> dims_elem_num) : Type(Type::ArrayTID), elem_type_(elem_type), dims_elem_num_(dims_elem_num) {}
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
    std::shared_ptr<Type> result_;
    std::vector<std::shared_ptr<Type> > args_; 
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
class Value : std::enable_shared_from_this<Value> {
public:
    std::shared_ptr<Value> get_this() { return shared_from_this(); }
    explicit Value(std::shared_ptr<Type> type, const std::string name = "") : type_(type), name_(name) {}
    ~Value() = default;

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



    std::shared_ptr<Type> type_; // 类型
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
    Literal(std::shared_ptr<Type> type, const std::string name = "") : Value(type, name) {}
    ~Literal() = default;
};

/**
 * @brief int 类型
 * 
*/
class LiteraltInt : public Literal {
public:
    LiteraltInt(std::shared_ptr<Type> type, int val) : Literal(type), val_(val) {}
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
};

/**
 * @brief float 类型
 * 
*/
class LiteralFloat : public Literal {
public:
    LiteralFloat(std::shared_ptr<Type> type, float val) : Literal(type), val_(val) {}
    float val_;
};

/**
 * @brief double 类型
 * 
*/
class LiteralDouble : public Literal {
public:
    LiteralDouble(std::shared_ptr<Type> type, double val) : Literal(type), val_(val) {}
    double val_;
};

/**
 * @brief bool 类型
 * 
*/
class LiteralBool : public Literal {
public:
    LiteralBool(std::shared_ptr<Type> type, bool val) : Literal(type), val_(val) {}
    bool val_;
};

/**
 * @brief char 类型
 * 
*/
class LiteralChar : public Literal {
public:
    LiteralChar(std::shared_ptr<Type> type, char val) : Literal(type), val_(val) {}
    char val_;
};

/**
 * @brief string 类型
 * 
*/
class LiteralString : public Literal {
public:
    LiteralString(std::shared_ptr<Type> type, const std::string val) : Literal(type), val_(val) {}
    std::string val_;
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
    std::vector<std::shared_ptr<Literal> > const_array;
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
    GlobalIdentifier(std::shared_ptr<Type> type, const std::string name, std::shared_ptr<Module> m, bool is_const, std::shared_ptr<Literal> init_val);
    ~GlobalIdentifier() = default;

    void init();
    std::weak_ptr<Module> parent_; 
    bool is_const_; // 是否为常量
    std::weak_ptr<Literal> init_val_; // 初始值
};

// ----------------------------------------------------------------LocalIdentifier---------------------------------------------------------------
class LocalIdentifier : public Value {
public:
    LocalIdentifier(std::shared_ptr<Type> type, const std::string name, std::shared_ptr<Function> f, bool is_const, std::shared_ptr<Literal> init_val);  
    ~LocalIdentifier() = default;

    void init();
    std::weak_ptr<Function> parent_;
    bool is_const_; // 是否为常量
    std::weak_ptr<Literal> init_val_; // 初始值  
};


// ----------------------------------------------------------------Function---------------------------------------------------------------
/**
 * @brief 函数参数类
 * 
*/
class Argument : public Value {
public:
    explicit Argument(std::shared_ptr<Type> type, const char *name, std::shared_ptr<Function> f, unsigned arg_no = 0) 
        : Value(type, name), belong_f_(f), arg_no_(arg_no) {}
    ~Argument() {}
    std::weak_ptr<Function> belong_f_; // 所属函数
    unsigned arg_no_; // 参数序号
};

/**
 * @brief 函数类
 * 
*/
class Function : public Value {
public:
    Function(std::shared_ptr<FunctionType> type, const std::string name, std::shared_ptr<Module> m);
    ~Function();
    void init();

    /**
     * @brief 添加基本块
     * @param bb 基本块
    */
    void add_basic_block(std::shared_ptr<BasicBlock> bb) { basic_blocks_.push_back(bb); }

    /**
     * @brief 添加局部标识符
     * @param l 局部标识符
    */
    void add_local_identifier(std::shared_ptr<LocalIdentifier> l) { local_identifiers_.push_back(l); }

    std::vector<std::shared_ptr<LocalIdentifier> > local_identifiers_; // 局部标识符
    std::vector<std::shared_ptr<BasicBlock> > basic_blocks_; // 基本块
    std::vector<std::shared_ptr<Argument> > args_; // 参数列表
    std::weak_ptr<Module> parent_; 

    std::weak_ptr<FunctionType> func_type_; // 函数类型
};

// ----------------------------------------------------------------BasicBlock---------------------------------------------------------------
/**
 * @brief 基本块类
 * 
*/
class BasicBlock : public Value {
public:
    explicit BasicBlock(const std::string name, std::shared_ptr<Function> f) : Value(std::make_shared<Type>(Type::BlockTID), name), belong_f_(f) {
        init();
    }
    ~BasicBlock() = default;
    void init() { belong_f_.lock()->add_basic_block(std::static_pointer_cast<ir::BasicBlock>(get_this())); }
    /**
     * @brief 添加指令
     *  
    */
    void add_instruction(std::shared_ptr<Instruction> i) { instructions_.push_back(i); }

    /**
     * @brief 添加前驱基本块
     * 
    */
    void add_pre_bb(std::shared_ptr<BasicBlock> bb) { pre_bbs_.push_back(bb); }
    /**
     * @brief 添加后继基本块
    */
    void add_succ_bb(std::shared_ptr<BasicBlock> bb) { succ_bbs_.push_back(bb); }

    std::weak_ptr<Function> belong_f_; // 基本块所属函数
    std::vector<std::shared_ptr<Instruction> > instructions_; // 指令列表
    std::vector<std::shared_ptr<BasicBlock> > pre_bbs_; // 前驱基本块
    std::vector<std::shared_ptr<BasicBlock> > succ_bbs_; // 后继基本块
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
        // Null
        Null,

        // Function
        Call, 
        Ret, 
        
        // Branch Jump
        Br,

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
    };
    explicit Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::shared_ptr<BasicBlock> parent, bool before = false);
    ~Instruction() = default;
    void init();

    /**
     * @brief 设置操作数
     * 
    */
    void set_operand(unsigned i, std::shared_ptr<Value> val) {
        operands_[i] = val;
        use_pos_[i] = val->add_use(get_this(), i);
    }

    // 以下是判断指令类型的函数
    bool is_call_inst() { return op_id_ == OpID::Call; }
    bool is_ret_inst() { return op_id_ == OpID::Ret; }
    bool is_br_inst() { return op_id_ == OpID::Br; }
    bool is_binary_inst() { return op_id_ >= OpID::Add && op_id_ <= OpID::In; }
    bool is_unary_inst() { return op_id_ >= OpID::Not && op_id_ <= OpID::LogicalNot; }
    bool is_assign_inst() { return op_id_ == OpID::Assign; }
    bool is_load_inst() { return op_id_ == OpID::Visit; }

    std::weak_ptr<BasicBlock> parent_; // 指令所属基本块
    OpID op_id_; // 操作码
    unsigned num_ops_; // 操作数个数
    std::vector<std::shared_ptr<Value>> operands_; // 操作数
    std::vector<std::list<Use>::iterator> use_pos_; // 与操作数数组一一对应，是对应的操作数的 uselist 里面，与当前指令相关的 use 的迭代器
    std::vector<std::list<std::shared_ptr<Instruction>>::iterator> pos_in_bb_; // 在 bb 的指令 list 的位置迭代器, 最多只能有一个
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
    BinaryInst(std::shared_ptr<Type> ty, OpID op, std::shared_ptr<Value> v1, std::shared_ptr<Value> v2, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, op, 2, bb) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    ~BinaryInst() = default;
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
    UnaryInst(std::shared_ptr<Type> ty, OpID op, std::shared_ptr<Value> val, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, op, 1, bb) {
        set_operand(0, val);
    }
    ~UnaryInst() = default;
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
    CompareInst(OpID op, std::shared_ptr<Value> v1, std::shared_ptr<Value> v2, std::shared_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::BooleanTID), op, 2, bb) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    ~CompareInst() = default;
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
    StoreInst(std::shared_ptr<Value> val, std::shared_ptr<Value> ptr, std::shared_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::BooleanTID), OpID::Assign, 2, bb) {
        set_operand(0, val);
        set_operand(1, ptr);
    }
    ~StoreInst() = default;
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
    LoadInst(std::shared_ptr<Type> ty, std::shared_ptr<Value> array, std::shared_ptr<Value> idx, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Visit, 2, bb) {
        set_operand(0, array);
        set_operand(1, idx);
    }
    ~LoadInst() = default;
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
    CallInst(std::shared_ptr<Function> func, std::vector<std::shared_ptr<Value>> args, std::shared_ptr<BasicBlock> bb)
      : Instruction(func->func_type_.lock()->result_, OpID::Call, args.size() + 1, bb) {
        // 前面的操作数是参数，最后一个操作数是函数
        int num_ops = args.size() + 1;
        for (int i = 0; i < num_ops - 1; i++) {
            set_operand(i, args[i]);
        }
        set_operand(num_ops - 1, func);
    }
    ~CallInst() = default;
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
    ReturnInst(std::shared_ptr<Value> val, std::shared_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Ret, 1, bb) {
        set_operand(0, val);
    }
    ~ReturnInst() = default;
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
    BranchInst(std::shared_ptr<Value> cond, std::shared_ptr<BasicBlock> then_bb, std::shared_ptr<BasicBlock> else_bb, std::shared_ptr<BasicBlock> bb)
      : Instruction(std::make_shared<Type>(Type::VoidTID), OpID::Br, 3, bb) {
        then_bb->add_pre_bb(bb);
        else_bb->add_pre_bb(bb);
        bb->add_succ_bb(then_bb);
        bb->add_succ_bb(else_bb);
        set_operand(0, cond);
        set_operand(1, then_bb);
        set_operand(2, else_bb);
    }
    ~BranchInst() = default;

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
    void add_global_identifier(std::shared_ptr<GlobalIdentifier> g) { global_identifiers_.push_back(g); }

    /**
     * @brief 添加函数
     * @param f 函数
    */
    void add_function(std::shared_ptr<Function> f) { functions_.push_back(f); }

    std::vector<std::shared_ptr<GlobalIdentifier> > global_identifiers_; // 全局标识符, 包括全局变量和常量
    std::vector<std::shared_ptr<Function> > functions_; // 函数
};


} // namespace ir