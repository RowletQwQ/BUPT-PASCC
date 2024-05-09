#pragma once

#include <memory>
#include <string>
#include <vector>
namespace builder {

namespace riscv {

class Operand {
public:
    enum OpType {
        Void, // 空类型，为无函数返回值专用的类型
        Immediate, // 立即数
        Register, // 寄存器
        Function, // 函数
        Memory, // 内存
        Const, // 常量
        Block // 基本块
    };
    explicit Operand(OpType type) : type_(type) {}
    ~Operand() = default;
    virtual std::string print() const = 0;
    OpType type_;
    // 快速判断
    bool isRegister() const { return type_ == Register; }
    bool isMemory() const { return type_ == Memory; }
    bool isImmediate() const { return type_ == Immediate; }
    bool isFunction() const { return type_ == Function; }
    bool isBlock() const { return type_ == Block; }
};

class Register : public Operand {
public:
    enum RegType {
        Zero, // 零寄存器, zero
        Return, // 返回地址寄存器，ra
        Stack, // 栈专用, sp
        Thread, // 线程指针, gp
        Temp, // 临时寄存器，t0-t6
        Frame, // 帧指针，s0
        Saved, // 保存寄存器，s1-s11
        IntArg, // 整型参数寄存器，a0-a7, 需要注意的是,a0兼顾返回值/函数的第一个参数
        FloatArg, // 浮点参数寄存器，fa0-fa7
        Float // 浮点寄存器
    };

    RegType reg_type_;
    int reg_id_; // 寄存器编号
    Register(RegType reg_type, int reg_id = -1);
    std::string print() const override;
};

class Immediate : public Operand {
public:
    enum ImmType {
        Int32,
        Int64,
        Float32,
        Float64,
    };
    ImmType imm_type_;
    union {
        int imm_i32_;
        long imm_i64_;
        float imm_f32_;
        double imm_f64_;
    };
    Immediate(int imm) : Operand(Operand::Immediate), imm_type_(ImmType::Int32), imm_i32_(imm) {}
    Immediate(long imm) : Operand(Operand::Immediate), imm_type_(ImmType::Int64), imm_i64_(imm) {}
    Immediate(float imm) : Operand(Operand::Immediate), imm_type_(ImmType::Float32), imm_f32_(imm) {}
    Immediate(double imm) : Operand(Operand::Immediate), imm_type_(ImmType::Float64), imm_f64_(imm) {}
    std::string print() const override;
};

// 指向一个内存
// 主要便于对内存的管理，故单独拿出来
class Memory : public Operand {
public:
    std::shared_ptr<riscv::Register> base_; // 基地址寄存器
    std::shared_ptr<riscv::Immediate> offset_; // 偏移寄存器
    Memory(std::shared_ptr<riscv::Register> base, std::shared_ptr<riscv::Immediate> offset) 
        : Operand(Operand::Memory), base_(base), offset_(offset) {}
    std::string print() const override;
};

// 一个label可能是基本块，也可能是函数
class Label : public Operand {
public:
    std::string name_;
    Label(OpType type, const std::string &name) : Operand(type), name_(name) {}
    std::string print() const override;
};

// 全局常量
class GlobalConst : public Operand {
public:
    enum ConstType {
        Word,
        DWord,
        Float, 
        Double, 
        ASCIIZ, // 字符串
    };
    GlobalConst(int val, const std::string &name) 
        : Operand(OpType::Const), name_(name) , type_(Word), i32_(val){}
    GlobalConst(long val, const std::string &name) 
        : Operand(OpType::Const), name_(name) , type_(DWord), i64_(val){}
    GlobalConst(float val, const std::string &name)
        : Operand(OpType::Const), name_(name), type_(Float), f32_(val){}
    GlobalConst(double val, const std::string &name)
        : Operand(OpType::Const), name_(name), type_(Double), f64_(val){}
    GlobalConst(std::string &val, const std::string &name)
        : Operand(OpType::Const), name_(name), type_(ASCIIZ), str_val_(val){}

    union {
        int i32_;
        long i64_;
        float f32_;
        double f64_;
    };
    std::string name_;
    std::string str_val_;
    ConstType type_;
    std::string print() const override;
};

class Function : public Label {
public:
    int num_args_; // 参数个数,根据参数个数决定弹栈数
    OpType ret_type_; // 返回值类型
    std::vector<std::shared_ptr<Operand>> args_; // 参数列表
    Function(const std::string &name, int num_args, OpType ret_type);
    void setArgs(int index, std::shared_ptr<Operand> op);
};

// 基本块
class BasicBlock : public Label {
public:
    BasicBlock(const std::string &name, std::weak_ptr<riscv::Function> parent) 
    : Label(OpType::Block, parent.lock()->name_ + "_" + name), parent_(parent) {}
    std::weak_ptr<riscv::Function> parent_; // 所属函数
};


// class Module {
// public:
//     std::vector<std::shared_ptr<Function>> functions_;
//     std::vector<std::shared_ptr<GlobalConst>> global_vars_;
//     std::vector<std::shared_ptr<BasicBlock>> basic_blocks_;
// };


} // namespace riscv

} // namespace builder
