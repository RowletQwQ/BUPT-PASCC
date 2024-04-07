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
        Int32, // 32位整型
        Int64, // 64位整型
        Float32, // 32位浮点
        Float64, // 64位浮点
        Stack, // 栈专用
        Zero // 零寄存器
    };

    RegType reg_type_;
    int reg_id_; // 寄存器编号
    Register(RegType reg_type, int reg_id) : Operand(Operand::Register), 
            reg_type_(reg_type), reg_id_(reg_id) {}
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
    Memory(std::shared_ptr<riscv::Register> base, std::shared_ptr<riscv::Immediate> offset) : Operand(Operand::Memory), base_(base), offset_(offset) {}
};

// 一个label可能是基本块，也可能是函数，更可能是全局变量
class Label : public Operand {
public:
    std::string name_;
    Label(OpType type, const std::string &name) : Operand(type), name_(name) {}
    std::string print() const override;
};

// 全局变量
// 全局变量可能是个立即数，也可能是个可更改的数（存在内存里）
class GlobalVariable : public Label {
public:
    GlobalVariable(OpType type, const std::string &name) : Label(type, name) {}
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
    BasicBlock(const std::string &name, std::weak_ptr<riscv::Function> parent) : Label(OpType::Block, name), parent_(parent) {}
    std::string print() const override;
    std::weak_ptr<riscv::Function> parent_; // 所属函数
};


class Module {
public:
    std::vector<std::shared_ptr<Function>> functions_;
    std::vector<std::shared_ptr<GlobalVariable>> global_vars_;
    std::vector<std::shared_ptr<BasicBlock>> basic_blocks_;
    std::string print() const;
};


} // namespace riscv

} // namespace builder
