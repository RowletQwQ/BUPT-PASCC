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
        VoidTID, // 空类型
        IntegerTID,
        RealTID,
        BooleanTID,
        CharTID,
        StringTID,
        ArrayTID,
        FunctionTID,
        BlockTID, // 基本块类型
        PointerTID // TODO: 有没有必要加上指针类型?
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
    explicit ArrayType(std::shared_ptr<Type> elem_type, unsigned num_elems) : Type(Type::ArrayTID), elem_type_(elem_type), num_elems_(num_elems) {}
    std::shared_ptr<Type> elem_type_; // 元素类型
    unsigned num_elems_; // 元素个数
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



/**
 * @brief 指针类型
 * 
*/
class PointerType : public Type {
public:
    explicit PointerType(std::shared_ptr<Type> contained) : Type(Type::PointerTID), contained_(contained) {}
    std::shared_ptr<Type> contained_; // 指向的类型
};

// ----------------------------------------------------------------Value---------------------------------------------------------------
/**
 * @brief Value 基类
 * 
*/
class Value :std::enable_shared_from_this<Value> {
public:
    std::shared_ptr<Value> get_this() { return shared_from_this(); }
    explicit Value(std::shared_ptr<Type> type, const char *name) : type_(type), name_(name) {}
    ~Value() = default;

    // 由子类实现
    virtual std::string print() = 0;

    // 移除某个
    void remove_use(std::shared_ptr<Value>val);

    //******************************************************************
    std::list<Use>::iterator add_use(std::shared_ptr<Value> val, unsigned arg_no);
    // 删除迭代器指出的use
    void remove_use(std::list<Use>::iterator it) { use_list_.erase(it); }
    // user的第i个操作数准备不再使用this，因此删除this与user相关的use联系
    bool remove_used(std::shared_ptr<Instruction> user, unsigned i);

    // Return if the value is a constant.
    bool is_constant();


    void replace_all_use_with(std::shared_ptr<Value> new_val);
    std::shared_ptr<Type> type_;
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
    Literal(std::shared_ptr<Type> type, const char *name = "") : Value(type, name) {}
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
    std::string print() override;
};


/**
 * @brief long long 类型
 * 
*/
class LiteralLong : public Literal {
public:
    LiteralLong(std::shared_ptr<Type> type, long long val) : Literal(type), val_(val) {}
    long long val_;
    std::string print() override;
};

/**
 * @brief float 类型
 * 
*/
class LiteralFloat : public Literal {
public:
    LiteralFloat(std::shared_ptr<Type> type, float val) : Literal(type), val_(val) {}
    float val_;
    std::string print() override;
};

/**
 * @brief double 类型
 * 
*/
class LiteralDouble : public Literal {
public:
    LiteralDouble(std::shared_ptr<Type> type, double val) : Literal(type), val_(val) {}
    double val_;
    std::string print() override;
};

/**
 * @brief bool 类型
 * 
*/
class LiteralBool : public Literal {
public:
    LiteralBool(std::shared_ptr<Type> type, bool val) : Literal(type), val_(val) {}
    bool val_;
    std::string print() override;
};

/**
 * @brief char 类型
 * 
*/
class LiteralChar : public Literal {
public:
    LiteralChar(std::shared_ptr<Type> type, char val) : Literal(type), val_(val) {}
    char val_;
    std::string print() override;
};

/**
 * @brief string 类型
 * 
*/
class LiteralString : public Literal {
public:
    LiteralString(std::shared_ptr<Type> type, const char *val) : Literal(type), val_(val) {}
    std::string val_;
    std::string print() override;
};

/**
 * @brief 数组类型
 * 
*/
class LiteralArray : public Literal {
public:
    LiteralArray(std::shared_ptr<ArrayType> ty, const std::vector<std::shared_ptr<Literal> > &val);
    ~LiteralArray() = default;
    virtual std::string print() override;
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
    GlobalIdentifier(const char *name, std::shared_ptr<Module> m, std::shared_ptr<Type> type, bool is_const, 
                        std::shared_ptr<Literal> init_val);
    virtual std::string print() override;

    void init();
    std::weak_ptr<Module> parent_; // 所属模块
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
    explicit Argument(std::shared_ptr<Type> type, const char *name, 
    std::shared_ptr<Function> f, unsigned arg_no = 0) : Value(type, name), belong_f_(f), arg_no_(arg_no) {}
    ~Argument() {}
    virtual std::string print() override;
    std::weak_ptr<Function> belong_f_; // 所属函数
    unsigned arg_no_; // 参数序号
};

/**
 * @brief 函数类
 * 
*/
class Function : public Value{
public:
    Function(std::shared_ptr<FunctionType> type, const char *name, std::shared_ptr<Module> m);
    /**
     * @brief 初始化函数，将函数加入到模块中
     */
    void init();

    
    ~Function();
    virtual std::string print() override;

    /**
     * @brief 添加基本块
     * @param bb 基本块
    */
    void add_basic_block(std::shared_ptr<BasicBlock> bb) { basic_blocks_.push_back(bb); }
    
    /**
     * @brief 得到返回值类型
     * @return Type*
    */ 
    std::shared_ptr<Type> get_return_type() const {
        return func_type_.lock()->result_;
    }



    // bool is_declaration() { return basic_blocks_.empty(); }
    // void set_instr_name();

    /**
     * @brief 移除基本块
     * @param bb 基本块
    */
    void remove_bb(std::shared_ptr<BasicBlock> bb);
    
    std::shared_ptr<BasicBlock> getRetBB();


    std::vector<std::shared_ptr<BasicBlock> > basic_blocks_; // 基本块, 一个函数体包含多个基本块
    std::vector<std::shared_ptr<Argument> > args_;      // 参数列表
    std::weak_ptr<Module> parent_; // 所属模块
    std::weak_ptr<FunctionType> func_type_; // 函数类型 
    unsigned seq_cnt_; 
    // std::vector<std::set<std::shared_ptr<Value> >> vreg_set_; 
    int use_ret_cnt; // 程序中真正使用返回值的次数
};

// ----------------------------------------------------------------BasicBlock---------------------------------------------------------------
/**
 * @brief 基本块类
 * 
*/
class BasicBlock : public Value {
public:

    explicit BasicBlock(std::shared_ptr<Module> m, const char *name, std::shared_ptr<Function> f) 
        : Value(std::make_shared<Type>(Type::BlockTID), name), belong_f_(f) {}

    /**
     * @brief 初始化
     * @details 由于shared_from_this()不能在构造函数中使用，所以需要单独写一个初始化函数
     */
    void init(){
        // 将基本块加入到函数的基本块列表中
        belong_f_.lock()->add_basic_block(std::static_pointer_cast<ir::BasicBlock>(get_this()));
    }

    /**
     * @brief 添加指令
     *  
    */
    void add_instruction(std::shared_ptr<Instruction> i) { instructions_.push_back(i); }

    /**
     * @brief 判断是否支配某个基本块
     * @param bb 被判断的基本块
     * @return int 返回 1 表示支配，0 表示不支配, -1 表示不在同一个函数中
    */
    int is_dominate(std::shared_ptr<BasicBlock> bb);

    virtual std::string print() override;


    std::weak_ptr<Function> belong_f_; // 基本块所属函数
    std::vector<std::shared_ptr<Instruction> > instructions_; // 指令列表
    
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

        // Alloc Operation
        Alloc, 
        
    };
    explicit Instruction(std::shared_ptr<Type> ty, OpID id, unsigned num_ops, std::shared_ptr<BasicBlock> parent, bool before = false);

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
    bool is_alloca_inst() { return op_id_ == OpID::Alloc; }

    virtual std::string print() = 0;
    std::weak_ptr<BasicBlock> parent_; // 指令所属基本块
    OpID op_id_; // 操作码
    unsigned num_ops_; // 操作数个数
    std::vector<std::shared_ptr<Value> > operands_; // 操作数
    std::vector<std::list<Use>::iterator> use_pos_; // 与操作数数组一一对应，是对应的操作数的uselist里面，与当前指令相关的use的迭代器
    std::vector<std::list<std::shared_ptr<Instruction> >::iterator> pos_in_bb; // 在bb的指令list的位置迭代器,最多只能有一个
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
    virtual std::string print() override;
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
    virtual std::string print() override;    
};

/**
 * @brief 存储指令，即赋值运算指令
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
    StoreInst(std::shared_ptr<Type> ty, std::shared_ptr<Value> val, std::shared_ptr<Value> ptr, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Assign, 2, bb) {
        set_operand(0, val);
        set_operand(1, ptr);
    }
    virtual std::string print() override;
};

// 加载指令,比如数组下标取值时，需要用此表示
class LoadInst : public Instruction {
public:
    /**
     * @brief Construct a new Load Inst object
     * 
     * @param ty 目标数据类型
     * @param ptr 加载的地址
     * @param bb 所属基本块
     * @details 形如 a = *b, a = b[1] 等式，即为加载表达式
     */
    LoadInst(std::shared_ptr<Type> ty, std::shared_ptr<Value> ptr, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Visit, 1, bb) {
        set_operand(0, ptr);
    }
    virtual std::string print() override;
};

// 用于给变量在栈上申请空间
class AllocaInst : public Instruction {
public:
    /**
     * @brief Construct a new Alloca Inst object
     * 
     * @param ty 目标数据类型,里面会保存分配的类型，包括分配的对应类型信息(如数组类型和长度)
     * @param bb 所属基本块
     * @details 用于分配内存
     */
    AllocaInst(std::shared_ptr<Type> ty, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Alloc, 0, bb) {}
    virtual std::string print() override;

};

// 函数调用指令
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
    CallInst(std::shared_ptr<Type> ty, std::shared_ptr<Function> func, std::shared_ptr<BasicBlock> bb)
      : Instruction(ty, OpID::Call, 1, bb), func_(func) {
        set_operand(0, func);
    }
    virtual std::string print() override;

    std::weak_ptr<Function> func_; // 被调用的函数
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
        set_operand(0, cond);
        set_operand(1, then_bb);
        set_operand(2, else_bb);
    }
    virtual std::string print() override;

};

// 返回指令
// ret i32 %4
// ret void
// 注：ret的返回值类型一定是VoidTyID, 如果有返回值，那么返回值的类型一定是函数的返回值类型
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
    virtual std::string print() override;
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
    void add_global_identifier(std::shared_ptr<GlobalIdentifier> g) { global_identifiers_.push_back(g); }

    /**
     * @brief 添加函数
     * @param f 函数
    */
    void add_function(std::shared_ptr<Function> f) { functions_.push_back(f); }

    /**
     * @brief 获取指针类型
     * @param contained 指针指向的类型
     * @return PointerType* 
    */
    std::shared_ptr<PointerType> get_pointer_type(std::shared_ptr<Type> contained) {
        if (!pointer_map_.count(contained)) {
            pointer_map_[contained] = std::make_shared<PointerType>(contained);
        }
        return pointer_map_[contained];
    }


    std::vector<std::shared_ptr<GlobalIdentifier> > global_identifiers_; // 全局标识符, 包括全局变量和常量
    std::vector<std::shared_ptr<Function> > functions_; // 函数


    std::map<std::shared_ptr<Type> , std::shared_ptr<PointerType> > pointer_map_; // 指针类型映射
};


} // namespace ir