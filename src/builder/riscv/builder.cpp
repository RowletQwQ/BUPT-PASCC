

#include "builder/riscv/builder.hpp"
#include "builder/riscv/instruction.hpp"
#include "ir/ir.hpp"
#include "common/thpool/thpool.hpp"
#include "common/log/log.hpp"
#include "builder/riscv/operand.hpp"

#include <cstdint>
#include <cstring>
#include <future>
#include <memory>
#include <string>
#include <vector>
namespace builder {
namespace riscv {

const std::string PREFIX_PLACEHOLDER = "__PLACEHOLDER__";
// 声明线程唯一变量
thread_local std::shared_ptr<BasicBlock> cur_bb_;
thread_local std::shared_ptr<Function> cur_func_;
thread_local std::vector<std::shared_ptr<GlobalConst>> tmp_consts_;
thread_local std::shared_ptr<Register> last_result_;
thread_local Scope current_scope_;
thread_local bool need_pointer_ = false;
thread_local bool is_lval_ = false; // 用于提示当前尝试获取的是左值还是右值
thread_local bool is_reg_  = false; // 用于提示当前尝试获取的是内存还是寄存器


static inline int UpperAlign(int size, int align) {
    return (size + align - 1) & ~(align - 1);
}

// 生成一个操作数，标明是一个借助栈的内存操作数
static std::shared_ptr<Memory> gen_sp_mem(int offset, bool is_real, int size, int count = 1) {
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(offset);
    if(is_real) {
        return std::make_shared<Memory>(sp, imm, Memory::Float, size, count);
    }
    return std::make_shared<Memory>(sp, imm, Memory::Int ,size, count);
}

static std::shared_ptr<Operand> get_arg_pos(int index) {
    if(index >= 8) {
        // 超过8个参数，需要通过栈传递
        auto sp = std::make_shared<Register>(Register::Frame, 0);
        // +16 是因为要跳过上一个函数的返回地址 + s0
        auto imm = std::make_shared<Immediate>(16 + index * 8);
        return std::make_shared<Memory>(sp, imm, Memory::Int, 8);
    } 

    return std::make_shared<Register>(Register::IntArg, index);  
}

static Scope::PointerType make_pointer_type(std::shared_ptr<ir::Type> type) {
    if(type->get_tid() == ir::Type::IntegerTID) {
        return type->get_size() == 4 ? Scope::PointerType::Int32 : Scope::PointerType::Int64;
    }
    if(type->get_tid() == ir::Type::RealTID) {
        return type->get_size() == 4 ? Scope::PointerType::Float : Scope::PointerType::Double;
    }
    if(type->get_tid() == ir::Type::CharTID || type->get_tid() == ir::Type::BooleanTID){
        return Scope::PointerType::Int8;
    }
    return Scope::PointerType::NotPointer;
}

static inline std::string make_bb_name(std::string &func_name, int index) {
    return func_name + "_bb_" + std::to_string(index);
}

Scope::Scope() {
    reg_used_.resize(kMaxRegs, false);
    timestamp_ = 0;
    reg_access_timestamp_.resize(kMaxRegs, 0);
}

void Scope::push(const std::string &name, std::shared_ptr<Operand> val,bool is_pointer /*= false*/, PointerType type /*= NotPointer*/) {
    symbols_.back()[name] = val;
    if (is_pointer) {
        pointers_.back()[name] = type;
    }
}

std::shared_ptr<Operand> Scope::find(const std::string &name) {
    for(auto it = symbols_.rbegin(); it != symbols_.rend(); it++) {
        auto res = it->find(name);
        if(res != it->end()) {
            return res->second;
        }
    }
    return nullptr;
}

void Scope::enter() {
    stack_size_.emplace_back(0);
    symbols_.emplace_back();
    pointers_.emplace_back();
    reg_used_.assign(kMaxRegs, false);
    // for(int i = 0; i < 7; i++){
    //     avail_int_regs_.emplace_back(std::make_shared<Register>(Register::IntArg, i));
    // }
    for(int i = 0; i < 6; i++) {
        avail_int_regs_.emplace_back(std::make_shared<Register>(Register::Temp, i));
    }
    for(int i = 0; i < 32; i++){
        avail_float_regs_.emplace_back(std::make_shared<Register>(Register::FloatArg, i));
    }
}

// 对应指令 addi sp , sp, -size
std::shared_ptr<Instruction> Scope::alloc_stack(int size) {
    LOG_DEBUG("Alloc stack %d", size);
    auto sp = std::make_shared<Register>(Register::Stack);
    // 向下开栈
    auto imm = std::make_shared<Immediate>(-size);
    auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, sp, sp, imm);
    touch_reg(sp->getUniqueId());
    stack_size_.back() += size;
    return inst;
}

// 对应指令 addi sp ,sp, size
std::shared_ptr<Instruction> Scope::dealloc_stack(int size) {
    LOG_DEBUG("Dealloc stack %d", size);
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(size);
    auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, sp, sp, imm);
    touch_reg(sp->getUniqueId());
    stack_size_.back() -= size;
    return inst;
}

std::shared_ptr<Instruction> Scope::leave() {
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(stack_size_.back());
    auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, sp, sp, imm);
    touch_reg(sp->getUniqueId());
    stack_size_.pop_back();
    symbols_.pop_back();
    pointers_.pop_back();
    return inst;
}

std::shared_ptr<Register> Scope::alloc_tmp_reg(bool is_real) {
    // 从临时寄存器中找一个未使用的寄存器
    if(is_real) {
        for(auto &reg: avail_float_regs_) {
            if(!is_reg_allocated(reg->getUniqueId())) {
                LOG_DEBUG("Alloc float reg %s", reg->print().c_str()); 
                touch_reg(reg->getUniqueId());
                return reg;
            }
        }
    } else {
        for(auto &reg: avail_int_regs_) {
            if(!is_reg_allocated(reg->getUniqueId())) {
                LOG_DEBUG("Alloc int reg %s", reg->print().c_str());
                touch_reg(reg->getUniqueId());
                return reg;
            }
        }
    }
    LOG_FATAL("No available register");
    return nullptr;
}

void Scope::free_tmp_reg(std::shared_ptr<Register> reg) {
    LOG_DEBUG("Free reg %s", reg->print().c_str());
    reg_used_[reg->getUniqueId()] = false;
}

static int64_t get_bit_pattern(double val) {
    int64_t res;
    memcpy(&res, &val, sizeof(double));
    return res;
}

// static int32_t get_bit_pattern(float val) {
//     int32_t res;
//     memcpy(&res, &val, sizeof(float));
//     return res;
// }


static std::shared_ptr<Instruction> store_to_stack(std::shared_ptr<Register> reg, int offset) {
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(offset);
    return std::make_shared<StoreInst>(Instruction::SD, reg, sp, imm);
}

static Instruction::InstrType get_arith_type(ir::Instruction::OpID id, std::shared_ptr<ir::Type> type) 
{
    // 先判断是否是浮点数
    static std::map<ir::Instruction::OpID, Instruction::InstrType> float32_map = 
    {
        // Binary Operation
        {ir::Instruction::Add, Instruction::FADD_S},
        {ir::Instruction::Sub, Instruction::FSUB_S},
        {ir::Instruction::Mul, Instruction::FMUL_S},
        {ir::Instruction::Div, Instruction::FDIV_S},
    };

    static std::map<ir::Instruction::OpID, Instruction::InstrType> float64_map = 
    {
        // Binary Operation
        {ir::Instruction::Add, Instruction::FADD_D},
        {ir::Instruction::Sub, Instruction::FSUB_D},
        {ir::Instruction::Mul, Instruction::FMUL_D},
        {ir::Instruction::Div, Instruction::FDIV_D},
    };
    
    static std::map<ir::Instruction::OpID, Instruction::InstrType> int32_map = 
    {
        // Binary Operation
        {ir::Instruction::Add, Instruction::ADD},
        {ir::Instruction::Sub, Instruction::SUB},
        {ir::Instruction::Mul, Instruction::MUL},
        {ir::Instruction::Div, Instruction::DIV},
        {ir::Instruction::Mod, Instruction::REM},
    };

    static std::map<ir::Instruction::OpID, Instruction::InstrType> int64_map = 
    {
        // Binary Operation
        {ir::Instruction::Add, Instruction::ADD},
        {ir::Instruction::Sub, Instruction::SUB},
        {ir::Instruction::Mul, Instruction::MUL},
        {ir::Instruction::Div, Instruction::DIV},
        {ir::Instruction::Mod, Instruction::REM},
    };
    if(type->get_tid() == ir::Type::RealTID) {
        if(type->get_size() == 4) {
            return float32_map[id];
        } else {
            return float64_map[id];
        }
    } else if (type->get_tid() == ir::Type::IntegerTID){
        if (type->get_size() == 4) {
            return int32_map[id];
        } else {
            return int64_map[id];
        }
    }
    LOG_FATAL("Unknown arith result type %s", type->print().c_str());
    return Instruction::NOP;
}

static void make_unary_inst
(ir::Instruction::OpID id, std::shared_ptr<ir::Type> type, std::shared_ptr<Register> reg)
{
    // 同理, RISC-V中没有完整的一元运算符支持，此处需要更多转换
    // 最后的结果一定保存在reg中
    auto imm_1 = std::make_shared<Immediate>(1);
    auto imm_neg1 = std::make_shared<Immediate>(-1);
    switch(id) {
        case ir::Instruction::Minus:
            cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::SUB, reg, std::make_shared<Register>(Register::Zero), reg));
            break;
        case ir::Instruction::LogicalNot:
            cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg, reg, imm_1));
            break;
        case ir::Instruction::BitReverse:
            cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg, reg, imm_neg1));
            break;
        case ir::Instruction::Not:
            cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg, reg, imm_neg1));
            break;
        case ir::Instruction::Inc:
            cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::ADDI, reg, reg, imm_1));
            break;
        case ir::Instruction::Bracket:
            break; // 空指令
        default:
            LOG_FATAL("Unknown unary operator");
    }
}

static void make_cmp_inst
(ir::Instruction::OpID id, std::shared_ptr<ir::Type> type, std::shared_ptr<Register> reg1, std::shared_ptr<Register> reg2)
{
    // RISC-V中的比较指令集并不完善，故需要转换
    // 最后的结果一定保存在reg1中
    // 先进行类型转换
    if(reg1->is_real() != reg2->is_real()) {
        // 需要进行类型转换
        // 必须要一律转换成浮点数才能计算
        if(reg1->is_real()) {
            // reg1是浮点数，reg2是整数
            auto reg3 = current_scope_.alloc_tmp_reg(true);
            auto zero = std::make_shared<Register>(Register::Zero);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_D_L, reg3, reg2);
            cur_bb_->insts_.emplace_back(ins);
            current_scope_.free_tmp_reg(reg2);
            reg2 = reg3;
        } else {
            // reg1是整数，reg2是浮点数
            auto reg3 = current_scope_.alloc_tmp_reg(true);
            auto zero = std::make_shared<Register>(Register::Zero);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_L_D, reg3, reg1);
            cur_bb_->insts_.emplace_back(ins);
            current_scope_.free_tmp_reg(reg1);
            reg1 = reg3;
        }
    }
    // 此时reg1和reg2的类型一定相同
    auto zero = std::make_shared<Register>(Register::Zero);
    if(reg1->is_real()) {
        // 此时为浮点数
        switch (id) {
            case ir::Instruction::Eq:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FEQ_D, reg1, reg1, reg2));
                break;
            case ir::Instruction::Ne:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FEQ_D, reg1, reg1, reg2));
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FEQ_D, reg1, reg1, zero));
                break;
            case ir::Instruction::Lt:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FLT_D, reg1, reg1, reg2));
                break;
            case ir::Instruction::Le:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FLE_D, reg1, reg1, reg2));
                break;
            case ir::Instruction::Gt:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FLT_D, reg1, reg2, reg1));
                break;
            case ir::Instruction::Ge:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::FLE_D, reg1, reg2, reg1));
                break;
            default:
                LOG_FATAL("Unknown compare operator");
        }
    } else {
        // 此时为整数
        auto imm_true = std::make_shared<Immediate>(1);
        std::string true_label_name = cur_bb_->label_->name_ + "_true_" + std::to_string(cur_bb_->branch_label_cnt_);
        std::string false_label_name = cur_bb_->label_->name_ + "_false_" + std::to_string(cur_bb_->branch_label_cnt_);
        cur_bb_->branch_label_cnt_++;
        auto true_label = std::make_shared<Label>(Operand::Block, true_label_name);
        auto false_label = std::make_shared<Label>(Operand::Block, false_label_name);
        auto true_label_inst = std::make_shared<LabelInst>(true_label);
        auto false_label_inst = std::make_shared<LabelInst>(false_label);
        switch (id) {
            case ir::Instruction::Eq:
                cur_bb_->insts_.emplace_back(std::make_shared<BranchInst>(Instruction::BEQ, reg1, reg2, true_label));
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XOR, reg1, zero, zero));
                cur_bb_->insts_.emplace_back(std::make_shared<BranchInst>(Instruction::BEQ, zero, zero, false_label));
                cur_bb_->insts_.emplace_back(true_label_inst);
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg1, zero, imm_true));
                cur_bb_->insts_.emplace_back(false_label_inst);
                break;
            case ir::Instruction::Ne:
                cur_bb_->insts_.emplace_back(std::make_shared<BranchInst>(Instruction::BNE, reg1, reg2, true_label));
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XOR, reg1, zero, zero));
                cur_bb_->insts_.emplace_back(std::make_shared<BranchInst>(Instruction::BEQ, zero, zero, false_label));
                cur_bb_->insts_.emplace_back(true_label_inst);
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg1, zero, imm_true));
                cur_bb_->insts_.emplace_back(false_label_inst);
                break;
            case ir::Instruction::Lt:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::SLT, reg1, reg1, reg2));
                break;
            case ir::Instruction::Le:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::SLT, reg1, reg2, reg1));
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg1, reg1, imm_true));
                break;
            case ir::Instruction::Gt:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::SLT, reg1, reg2, reg1));
                break;
            case ir::Instruction::Ge:
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::SLT, reg1, reg1, reg2));
                cur_bb_->insts_.emplace_back(std::make_shared<BinaryInst>(Instruction::XORI, reg1, reg1, imm_true));
                break;
            default:
                LOG_FATAL("Unknown compare operator");
        }
    }
}

void RiscvBuilder::visit(const ir::BinaryInst* inst) {
    // 先处理操作数
    if(inst->is_logical()) {
        // 创建新的基本块
        std::string true_label_name = cur_bb_->label_->name_ + "_target_" + std::to_string(cur_bb_->branch_label_cnt_);
        cur_bb_->branch_label_cnt_++;
        auto true_label = std::make_shared<Label>(Operand::Block, true_label_name);
        auto true_label_inst = std::make_shared<LabelInst>(true_label);
        // 逻辑运算符和其他运算符不同，需要特殊处理
        // 如 a1 and a2, 需要先计算a1, 如果a1为0, 则结果为0, 否则计算a2
        auto op1 = inst->operands_[0].lock();
        if(op1->is_inst()) {
            auto inst1 = std::static_pointer_cast<ir::Instruction>(op1);
            inst1->accept(*this);
        } else if (op1->is_literal()) {
            auto literal = std::static_pointer_cast<ir::Literal>(op1);
            literal->accept(*this);
        }
        // 将结果保存在reg1中
        auto reg1 = current_scope_.alloc_tmp_reg(false);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto ins = std::make_shared<BinaryInst>(Instruction::ADD, reg1, zero, last_result_);
        cur_bb_->insts_.emplace_back(ins);
        current_scope_.free_tmp_reg(last_result_);
        // 插入一条空指令占位，随后用条件跳转指令替换
        auto zero_inst = std::make_shared<BinaryInst>(Instruction::ADD, zero, zero, zero);
        size_t index = cur_bb_->insts_.size();
        cur_bb_->insts_.emplace_back(zero_inst);
        // 计算第二个操作数
        auto op2 = inst->operands_[1].lock();
        if(op2->is_inst()) {
            auto inst2 = std::static_pointer_cast<ir::Instruction>(op2);
            inst2->accept(*this);
        } else if (op2->is_literal()) {
            auto literal = std::static_pointer_cast<ir::Literal>(op2);
            literal->accept(*this);
        }
        // 此时第二个操作数的计算结果被存在last_result_中
        // 计算此时的结果
        if (inst->op_id_ == ir::Instruction::And || inst->op_id_ == ir::Instruction::AndThen) {
            auto res_inst = std::make_shared<BinaryInst>(Instruction::AND, last_result_, reg1, last_result_);
            cur_bb_->insts_.emplace_back(res_inst);
        } else {
            auto res_inst = std::make_shared<BinaryInst>(Instruction::OR, last_result_, reg1, last_result_);
            cur_bb_->insts_.emplace_back(res_inst);
        }
        if(inst->op_id_ == ir::Instruction::And || inst->op_id_ == ir::Instruction::AndThen) {
            // 如果是and, 需要判断第一个操作数是否为0
            // 第一个操作数为0直接跳转
            auto jmp_inst = std::make_shared<BranchInst>(Instruction::BEQ, reg1, zero, true_label);
            cur_bb_->insts_[index] = jmp_inst;
        } else {
            // 如果是or, 需要判断第一个操作数是否为1
            // 第一个操作数为1直接跳转
            auto jmp_inst = std::make_shared<BranchInst>(Instruction::BNE, reg1, zero, true_label);
            cur_bb_->insts_[index] = jmp_inst;
        }
        // 加上标记
        cur_bb_->insts_.emplace_back(true_label_inst);
        return;
    }
    auto op1 = inst->operands_[0].lock();
    if(op1->is_inst()) {
        auto inst1 = std::static_pointer_cast<ir::Instruction>(op1);
        inst1->accept(*this);
    } else if (op1->is_literal()) {
        auto literal = std::static_pointer_cast<ir::Literal>(op1);
        literal->accept(*this);
    }
    // 将计算结果暂存到reg1中
    std::shared_ptr<Register> reg1;
    auto zero = std::make_shared<Register>(Register::Zero);
    if(last_result_->is_real()) {
        reg1 = current_scope_.alloc_tmp_reg(true);
        auto ins = std::make_shared<BinaryInst>(Instruction::FADD_D, reg1, last_result_, zero);
        cur_bb_->insts_.emplace_back(ins);
    } else {
        reg1 = current_scope_.alloc_tmp_reg(false);
        auto ins = std::make_shared<BinaryInst>(Instruction::ADD, reg1, last_result_, zero);
        cur_bb_->insts_.emplace_back(ins);
    }
    auto op2 = inst->operands_[1].lock();
    if(op2->is_inst()) {
        auto inst2 = std::static_pointer_cast<ir::Instruction>(op2);
        inst2->accept(*this);
    } else if (op2->is_literal()) {
        auto literal = std::static_pointer_cast<ir::Literal>(op2);
        literal->accept(*this);
    }
    // 注意类型转换！
    if(reg1->is_real() != last_result_->is_real()) {
        // 需要进行类型转换
        // 必须要一律转换成浮点数才能计算
        if(reg1->is_real()) {
            // reg1是浮点数，last_result_是整数
            auto reg2 = current_scope_.alloc_tmp_reg(true);
            auto zero = std::make_shared<Register>(Register::Zero);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_D_L, reg2, last_result_);
            cur_bb_->insts_.emplace_back(ins);
            current_scope_.free_tmp_reg(last_result_);
            last_result_ = reg2;
        } else {
            // reg1是整数，last_result_是浮点数
            auto reg2 = current_scope_.alloc_tmp_reg(true);
            auto zero = std::make_shared<Register>(Register::Zero);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_L_D, reg2, reg1);
            cur_bb_->insts_.emplace_back(ins);
            current_scope_.free_tmp_reg(reg1);
            reg1 = reg2;
        }
    }
    auto type = get_arith_type(inst->op_id_, inst->type_);
    auto ins = std::make_shared<BinaryInst>(type, last_result_, reg1, last_result_);
    cur_bb_->insts_.emplace_back(ins);
    current_scope_.free_tmp_reg(reg1);
}
void RiscvBuilder::visit(const ir::UnaryInst* inst) {
    // 先处理操作数
    auto op1 = inst->operands_[0].lock();
    if(op1->is_inst()) {
        auto inst1 = std::static_pointer_cast<ir::Instruction>(op1);
        inst1->accept(*this);
    } else if (op1->is_literal()) {
        auto literal = std::static_pointer_cast<ir::Literal>(op1);
        literal->accept(*this);
    }
    if(inst->op_id_ == ir::Instruction::Null) {
        // 空指令，直接返回
        return;
    }
    make_unary_inst(inst->op_id_, inst->type_, last_result_);
}
void RiscvBuilder::visit(const ir::CompareInst* inst) {
    // 先处理操作数
    auto op1 = inst->operands_[0].lock();
    if(op1->is_inst()) {
        auto inst1 = std::static_pointer_cast<ir::Instruction>(op1);
        inst1->accept(*this);
    } else if (op1->is_literal()) {
        auto literal = std::static_pointer_cast<ir::Literal>(op1);
        literal->accept(*this);
    }
    auto reg1 = last_result_;
    auto op2 = inst->operands_[1].lock();
    if(op2->is_inst()) {
        auto inst2 = std::static_pointer_cast<ir::Instruction>(op2);
        inst2->accept(*this);
    } else if (op2->is_literal()) {
        auto literal = std::static_pointer_cast<ir::Literal>(op2);
        literal->accept(*this);
    }
    make_cmp_inst(inst->op_id_, inst->type_, reg1, last_result_);
    current_scope_.free_tmp_reg(last_result_);
    last_result_ = reg1;
}
void RiscvBuilder::visit(const ir::StoreInst* inst) {
    // 先接收左值
    is_lval_ = true;
    auto op1 = std::static_pointer_cast<ir::Instruction>(inst->operands_[0].lock());
    op1->accept(*this);
    is_lval_ = false;
    if(is_reg_) {
        LOG_DEBUG("StoreInst target: Reg %s", last_result_->print().c_str());
        auto res_reg = last_result_;
        // 接收右值
        auto op2 = std::static_pointer_cast<ir::Instruction>(inst->operands_[1].lock());
        op2->accept(*this);
        // 将last_result_的值存入res_reg
        if(last_result_->is_real()) {
            // 将浮点寄存器的值存入整型寄存器
            auto int_reg = current_scope_.alloc_tmp_reg(false);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_W_D, int_reg, last_result_);
            current_scope_.free_tmp_reg(last_result_);
            last_result_ = int_reg;
        }
        auto zero = std::make_shared<Register>(Register::Zero);
        auto store_inst = std::make_shared<BinaryInst>(Instruction::ADD, res_reg, zero, last_result_);
        cur_bb_->insts_.emplace_back(store_inst);
        current_scope_.free_tmp_reg(last_result_);
        last_result_ = res_reg;
        is_reg_ = false; // 消除标记
    } else {
        LOG_DEBUG("StoreInst target: Mem Addr In %s", last_result_->print().c_str());
        auto mem_reg = current_scope_.alloc_tmp_reg(false);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto ins = std::make_shared<BinaryInst>(Instruction::ADD, mem_reg, zero, last_result_);
        cur_bb_->insts_.emplace_back(ins);
        current_scope_.free_tmp_reg(last_result_);
        // 接收右值
        auto op2 = std::static_pointer_cast<ir::Instruction>(inst->operands_[1].lock());
        op2->accept(*this);
        // 将last_result_的值存入内存
        // 判断是不是浮点寄存器
        if(last_result_->is_real()) {
            // 将浮点寄存器的值存入整型寄存器
            auto int_reg = current_scope_.alloc_tmp_reg(false);
            auto ins = std::make_shared<UnaryInst>(Instruction::FCVT_W_D, int_reg, last_result_);
            current_scope_.free_tmp_reg(last_result_);
            last_result_ = int_reg;
        }
        if(inst->type_->get_size() == 8) {
            auto store_inst = std::make_shared<StoreInst>(Instruction::SD, last_result_, mem_reg, std::make_shared<Immediate>(0));
            cur_bb_->insts_.emplace_back(store_inst);
        } else {
            auto store_inst = std::make_shared<StoreInst>(Instruction::SW, last_result_, mem_reg, std::make_shared<Immediate>(0));
            cur_bb_->insts_.emplace_back(store_inst);
        }
        current_scope_.free_tmp_reg(mem_reg); 
    }
    current_scope_.free_tmp_reg(last_result_); // Store之后的寄存器没有必要继续使用
}
void RiscvBuilder::visit(const ir::LoadInst* inst) {
    // 先判断是不是数组
    if(inst->is_array_visit()) {
        // 两个操作数都是指令
        auto op1 = std::static_pointer_cast<ir::Instruction>(inst->operands_[0].lock());
        auto op2 = std::static_pointer_cast<ir::Instruction>(inst->operands_[1].lock());
        // 接受左边，算出偏移地址
        op1->accept(*this);
        // 保存在新寄存器中
        auto reg1 = current_scope_.alloc_tmp_reg(false);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto ins = std::make_shared<BinaryInst>(Instruction::ADD, reg1, zero, last_result_);
        cur_bb_->insts_.emplace_back(ins);
        current_scope_.free_tmp_reg(last_result_);
        // 接受idx
        op2->accept(*this);
        // 获取要偏移的值
        int64_t shift = inst->type_->get_size();
        auto shift_imm = std::make_shared<Immediate>(shift);
        auto shift_inst = std::make_shared<BinaryInst>(Instruction::MUL, last_result_, last_result_, shift_imm);
        cur_bb_->insts_.emplace_back(shift_inst);
        // 此时，last_result_中保存了偏移量
    }
    // 在current scope中查找是否有对应的变量
    auto res = current_scope_.find(inst->name_);
    if(res == nullptr) {
        // 看看全局变量
        std::shared_ptr<GlobalId> res;
        for(auto &global:modules_->global_vars_) {
            if(global->name_ == inst->name_) {
                res = global;
                break;
            }
        }
        std::shared_ptr<GlobalConst> res_const;
        for(auto &g_const: modules_->consts_) {
            if(g_const->name_ == inst->name_) {
                res_const = g_const;
                break;
            }
        }
        if(!res && !res_const)
            LOG_FATAL("LoadInst: identifier %s not found in scope", inst->name_.c_str());
        auto label = std::make_shared<Label>(Operand::Immediate, inst->name_);
        if(need_pointer_ || is_lval_) {
            last_result_ = current_scope_.alloc_tmp_reg(false);
            auto la_inst = std::make_shared<LoadInst>(Instruction::LA, last_result_, label);
            cur_bb_->insts_.emplace_back(la_inst);
        } else {
            auto reg = current_scope_.alloc_tmp_reg(false);
            auto imm_zero = std::make_shared<Immediate>(0);
            auto la_inst = std::make_shared<LoadInst>(Instruction::LA, reg, label);
            cur_bb_->insts_.emplace_back(la_inst);
            switch (inst->type_->get_size()) {
                case 1:
                    cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LB, last_result_, reg, imm_zero));
                    break;
                case 2:
                    cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LH, last_result_, reg, imm_zero));
                    break;
                case 4:
                    cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LW, last_result_, reg, imm_zero));
                    break;
                case 8:
                    cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LD, last_result_, reg, imm_zero));
                    break;
                default:
                    LOG_FATAL("Unknown align memory size %d", inst->type_->get_size());
            
            }
            current_scope_.free_tmp_reg(reg);
            is_reg_ = true;
        }
        return;
    }
    if(need_pointer_ || is_lval_) {
        // 需要将对应操作数的内存地址存入last_result_
        if(res->isRegister()) {
            LOG_FATAL("LoadInst: Data is in register %s", res->print().c_str());
        }
        auto mem = std::static_pointer_cast<Memory>(res);
        last_result_ = current_scope_.alloc_tmp_reg(false);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, last_result_, mem->base_, mem->offset_);
        cur_bb_->insts_.emplace_back(inst);
    } else {
        // 只需要将值传入即可
        if(res->isRegister()) {
            auto res_reg = std::static_pointer_cast<Register>(res);
            if(res_reg->is_real()) {
                last_result_ = current_scope_.alloc_tmp_reg(true);
                auto ins = std::make_shared<BinaryInst>(Instruction::FADD_D, last_result_, res_reg, std::make_shared<Register>(Register::Zero));
                cur_bb_->insts_.emplace_back(ins);
            } else {
                last_result_ = current_scope_.alloc_tmp_reg(false);
                auto ins = std::make_shared<BinaryInst>(Instruction::ADD, last_result_, std::make_shared<Register>(Register::Zero), res_reg);
                cur_bb_->insts_.emplace_back(ins);
            }
            is_reg_ = true;
        } else {
            auto mem = std::static_pointer_cast<Memory>(res);
            if(mem->type_ == Memory::Float) {
                last_result_ = current_scope_.alloc_tmp_reg(true);
                if (mem->size_ == 4) {
                    auto inst = std::make_shared<LoadInst>(Instruction::FLW, last_result_, mem->base_, mem->offset_);
                    cur_bb_->insts_.emplace_back(inst);
                } else {
                    auto inst = std::make_shared<LoadInst>(Instruction::FLD, last_result_, mem->base_, mem->offset_);
                    cur_bb_->insts_.emplace_back(inst);
                }
            } else {
                last_result_ = current_scope_.alloc_tmp_reg(false);
                switch(mem->size_) {
                    case 1:
                        cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LB, last_result_, mem->base_, mem->offset_));
                        break;
                    case 2:
                        cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LH, last_result_, mem->base_, mem->offset_));
                        break;
                    case 4:
                        cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LW, last_result_, mem->base_, mem->offset_));
                        break;
                    case 8:
                        cur_bb_->insts_.emplace_back(std::make_shared<LoadInst>(Instruction::LD, last_result_, mem->base_, mem->offset_));
                        break;
                    default:
                        LOG_FATAL("Unknown align memory size %d", mem->size_);
                }
            }
            
        }
    }
}
void RiscvBuilder::visit(const ir::ReadInst* inst) {
    // 在函数调用前保存调用环境
    // 先将s1-s11写入栈
    auto alloc = current_scope_.alloc_stack(88);
    cur_bb_->insts_.emplace_back(alloc);
    auto sp = std::make_shared<Register>(Register::Stack);
    auto zero = std::make_shared<Register>(Register::Zero);
    for(int i = 1; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 1));
        auto store_inst = std::make_shared<StoreInst>(Instruction::SD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(store_inst);
    }
    // 随后, 将a0-a7存入s2-s9
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto save_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, s_reg, zero, a_reg);
        cur_bb_->insts_.emplace_back(save_reg_inst);
    }
    // 组装占位符
    std::string ph_name = PREFIX_PLACEHOLDER + cur_bb_->label_->name_ +  "_" + std::to_string(cur_bb_->placeholder_cnt_++);
    std::string placeholder;
    for(auto &op:inst->operands_) {
        placeholder += op.lock()->type_->placeholder();
    }
    // 生成一个占位符
    auto ph = std::make_shared<GlobalConst>(placeholder, ph_name);
    modules_->add_const(ph);
    // 把占位符的地址传入a0
    auto ph_op = std::make_shared<Label>(Operand::Immediate, ph_name);
    auto a0 = std::make_shared<Register>(Register::IntArg, 0);
    auto ph_load = std::make_shared<LoadInst>(Instruction::LA, a0, ph_op);
    cur_bb_->insts_.emplace_back(ph_load);
    // read传参要传指针
    need_pointer_ = true;
    // 计算是否需要开栈
    if (inst->operands_.size() > 7) {
        // 需要开栈
        auto alloc = current_scope_.alloc_stack((inst->operands_.size() - 7) * 8);
        cur_bb_->insts_.emplace_back(alloc);
    }
    for(int i = 0; i < inst->operands_.size(); i++) {
        auto op = inst->operands_[i].lock();
        if(!op->is_inst()) {
            LOG_FATAL("ReadInst operand must be a LoadInst");
        }
        auto load_inst = std::static_pointer_cast<ir::Instruction>(op);
        load_inst->accept(*this);
        // 结果会保存在last_result_中
        // 此时last_result_必定是一个指针，故一定是个整数寄存器
        // 根据i的值分配对应寄存器
        if(i > 7) {
            // 超过8个参数，需要通过栈传递
            auto sp = std::make_shared<Register>(Register::Stack);
            auto imm = std::make_shared<Immediate>((i - 7) * 8);
            auto store_inst = std::make_shared<StoreInst>(Instruction::SD, last_result_, sp, imm);
            cur_bb_->insts_.emplace_back(store_inst);
        } else {
            auto dest = std::make_shared<Register>(Register::IntArg, i + 1);
            auto move_inst = std::make_shared<BinaryInst>(Instruction::ADD, dest, std::make_shared<Register>(Register::Zero), last_result_);
            cur_bb_->insts_.emplace_back(move_inst);
        }
    }
    // 调用
    auto scanf_label = std::make_shared<Label>(Operand::Function, "scanf");
    // 保存返回值
    auto s1 = std::make_shared<Register>(Register::Saved, 1);
    auto ra = std::make_shared<Register>(Register::Return);
    auto save_ra_inst = std::make_shared<BinaryInst>(Instruction::XOR, s1, zero, ra);
    auto jal_inst = std::make_shared<JumpInst>(Instruction::JAL, ra, scanf_label);
    auto recover_ra_inst = std::make_shared<BinaryInst>(Instruction::XOR, ra, zero, s1);
    cur_bb_->insts_.emplace_back(save_ra_inst);
    cur_bb_->insts_.emplace_back(jal_inst);
    cur_bb_->insts_.emplace_back(recover_ra_inst);
    // 传参结束，需要恢复栈
    if (inst->operands_.size() > 7) {
        // 需要退栈
        auto dealloc = current_scope_.dealloc_stack((inst->operands_.size() - 7) * 8);
        cur_bb_->insts_.emplace_back(dealloc);
    }
    // 恢复a0-a7
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto load_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, a_reg, zero, s_reg);
        cur_bb_->insts_.emplace_back(load_reg_inst);
    }
    // 恢复s1-s11
    for(int i = 1; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 1));
        auto load_inst = std::make_shared<LoadInst>(Instruction::LD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(load_inst);
    }
    // 退栈
    auto dealloc = current_scope_.dealloc_stack(88);
    cur_bb_->insts_.emplace_back(dealloc);

}
void RiscvBuilder::visit(const ir::WriteInst* inst) {
    // 在函数调用前保存调用环境
    // 先将s1-s11写入栈
    auto alloc = current_scope_.alloc_stack(88);
    cur_bb_->insts_.emplace_back(alloc);
    auto sp = std::make_shared<Register>(Register::Stack);
    auto zero = std::make_shared<Register>(Register::Zero);
    for(int i = 1; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 1));
        auto store_inst = std::make_shared<StoreInst>(Instruction::SD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(store_inst);
    }
    // 随后, 将a0-a7存入s2-s9
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto save_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, s_reg, zero, a_reg);
        cur_bb_->insts_.emplace_back(save_reg_inst);
    }
    // 先组装占位符
    std::string ph_name = PREFIX_PLACEHOLDER + cur_bb_->label_->name_ + "_" + std::to_string(cur_bb_->placeholder_cnt_++);
    std::string placeholder;
    for(auto &op:inst->operands_) {
        placeholder += op.lock()->type_->placeholder();
    }
    
    // 计算是否需要开栈
    if (inst->operands_.size() > 7) {
        // 需要开栈
        auto alloc = current_scope_.alloc_stack((inst->operands_.size() - 7) * 8);
        cur_bb_->insts_.emplace_back(alloc);
    }
    // 开始传参
    for(int i = 0; i < inst->operands_.size(); i++) {
        auto op = inst->operands_[i].lock();
        if(!op->is_inst()) {
            LOG_FATAL("ReadInst operand must be a LoadInst");
        }
        auto load_inst = std::static_pointer_cast<ir::Instruction>(op);
        load_inst->accept(*this);
        // 结果会保存在last_result_中
        // 需要判断last_result_是不是浮点寄存器
        if(last_result_->is_real()) {
            // 需要将浮点寄存器转换成整数寄存器
            auto reg = current_scope_.alloc_tmp_reg(false);
            auto ins = std::make_shared<UnaryInst>(Instruction::FMV_X_D, reg, last_result_);
            cur_bb_->insts_.emplace_back(ins);
            current_scope_.free_tmp_reg(last_result_);
            last_result_ = reg;
        }
        // 根据i的值分配对应寄存器
        if(i > 7) {
            // 超过8个参数，需要通过栈传递
            auto sp = std::make_shared<Register>(Register::Stack);
            auto imm = std::make_shared<Immediate>((i - 7) * 8);
            auto store_inst = std::make_shared<StoreInst>(Instruction::SD, last_result_, sp, imm);
            cur_bb_->insts_.emplace_back(store_inst);
        } else {
            auto dest = std::make_shared<Register>(Register::IntArg, i + 1);
            auto move_inst = std::make_shared<BinaryInst>(Instruction::ADD, dest, std::make_shared<Register>(Register::Zero), last_result_);
            cur_bb_->insts_.emplace_back(move_inst);
        }
    }
    // 生成一个占位符
    auto ph = std::make_shared<GlobalConst>(placeholder, ph_name);
    modules_->add_const(ph);
    // 把占位符的地址传入a0
    auto ph_op = std::make_shared<Label>(Operand::Immediate, ph_name);
    auto a0 = std::make_shared<Register>(Register::IntArg, 0);
    auto ph_load = std::make_shared<LoadInst>(Instruction::LA, a0, ph_op);
    cur_bb_->insts_.emplace_back(ph_load);
    // 调用
    auto printf_label = std::make_shared<Label>(Operand::Function, "printf");
    // 将ra保存在s1
    auto s1 = std::make_shared<Register>(Register::Saved, 1);
    auto ra = std::make_shared<Register>(Register::Return);
    auto save_ra = std::make_shared<BinaryInst>(Instruction::XOR, s1, zero, ra);
    auto jal_inst = std::make_shared<JumpInst>(Instruction::JAL, ra, printf_label);
    // 恢复ra
    auto recover_ra = std::make_shared<BinaryInst>(Instruction::XOR, ra, zero, s1);
    cur_bb_->insts_.emplace_back(save_ra);
    cur_bb_->insts_.emplace_back(jal_inst);
    cur_bb_->insts_.emplace_back(recover_ra);
    // 传参结束，需要恢复栈
    if (inst->operands_.size() > 7) {
        // 需要退栈
        auto dealloc = current_scope_.dealloc_stack((inst->operands_.size() - 7) * 8);
        cur_bb_->insts_.emplace_back(dealloc);
    }
    // 恢复a0-a7
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto load_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, a_reg, zero, s_reg);
        cur_bb_->insts_.emplace_back(load_reg_inst);
    }
    // 恢复s1-s11
    for(int i = 1; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 1));
        auto load_inst = std::make_shared<LoadInst>(Instruction::LD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(load_inst);
    }
    // 退栈
    auto dealloc = current_scope_.dealloc_stack(88);
    cur_bb_->insts_.emplace_back(dealloc);

}
void RiscvBuilder::visit(const ir::CallInst* inst) {
    // 在函数调用前保存调用环境
    // 先将s2-s11写入栈
    auto alloc = current_scope_.alloc_stack(80);
    cur_bb_->insts_.emplace_back(alloc);
    auto sp = std::make_shared<Register>(Register::Stack);
    auto zero = std::make_shared<Register>(Register::Zero);
    for(int i = 2; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 2));
        auto store_inst = std::make_shared<StoreInst>(Instruction::SD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(store_inst);
    }
    // 随后, 将a0-a7存入s2-s9
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto save_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, s_reg, zero, a_reg);
        cur_bb_->insts_.emplace_back(save_reg_inst);
    }
    // 开始上参数
    int arg_index = 0;
    // 先计算参数个数, 确定参数的数量
    int arg_cnt = inst->operands_.size() - 1;
    int stack_for_arg = 0;
    if(arg_cnt > 8) {
        // 参数个数大于8，需要将多余的参数放入栈中
        stack_for_arg = (arg_cnt - 8) * 8;
    }
    // 开辟栈空间
    if(stack_for_arg > 0) {
        alloc = current_scope_.alloc_stack(stack_for_arg);
        cur_bb_->insts_.emplace_back(alloc);
    }

    // 获取目标函数
    auto func = std::static_pointer_cast<ir::Function>(inst->operands_.back().lock());
    for(int i = 0; i < arg_cnt; i++) {
        if(func->args_[i]->type_->is_pointer_) {
            // 如果是pointer，那这个操作数是也只能是一个指针，即ir::LoadInst
            need_pointer_ = true;
            auto arg = inst->operands_[i].lock();
            if(!arg->is_inst()) {
                LOG_FATAL("Pointer argument must be a LoadInst");
            }
            auto load_inst = std::static_pointer_cast<ir::Instruction>(arg);
            if(!load_inst->is_load_inst()) {
                LOG_FATAL("Pointer argument must be a LoadInst");
            }
            load_inst->accept(*this);
            need_pointer_ = false;

        } else {
            auto arg = inst->operands_[i].lock();
            if(arg->is_inst()) {
                auto inst = std::static_pointer_cast<ir::Instruction>(arg);
                inst->accept(*this);
            } else if (arg->is_literal()) {
                auto literal = std::static_pointer_cast<ir::Literal>(arg);
                literal->accept(*this);
            }
        }
        // 将参数放入正确的位置
        if (i < 8) {
            auto dest = std::make_shared<Register>(Register::IntArg, i);
            auto move_inst = std::make_shared<BinaryInst>(Instruction::ADD, dest, zero, last_result_);
            cur_bb_->insts_.emplace_back(move_inst);
        } else {
            // 参数放入栈中
            auto sp = std::make_shared<Register>(Register::Stack);
            auto imm = std::make_shared<Immediate>(8 * (i - 8));
            auto store_inst = std::make_shared<StoreInst>(Instruction::SD, last_result_, sp, imm);
            cur_bb_->insts_.emplace_back(store_inst);
        }
        current_scope_.free_tmp_reg(last_result_);
    }
    // 申请栈空间
    alloc = current_scope_.alloc_stack(8);
    cur_bb_->insts_.emplace_back(alloc);
    // 将s1存入栈顶
    auto s1 = std::make_shared<Register>(Register::Saved, 1);
    auto imm = std::make_shared<Immediate>(0);
    auto store_inst = std::make_shared<StoreInst>(Instruction::SD, s1, sp, imm);
    // 将ra存入s1
    auto ra = std::make_shared<Register>(Register::Return);
    auto save_ra_inst = std::make_shared<BinaryInst>(Instruction::ADD, s1, zero, ra);
    cur_bb_->insts_.emplace_back(save_ra_inst);
    // 组装jal指令
    auto func_label = std::make_shared<Label>(Operand::Function, func->name_);
    auto jal_inst = std::make_shared<JumpInst>(Instruction::JAL, ra, func_label);
    cur_bb_->insts_.emplace_back(jal_inst);
    // 调用返回，需要恢复环境
    // 先把a0的值存入last_result_
    auto a0 = std::make_shared<Register>(Register::IntArg, 0);
    last_result_ = current_scope_.alloc_tmp_reg(false);
    auto load_a0_inst = std::make_shared<BinaryInst>(Instruction::ADD, last_result_, a0, zero);
    cur_bb_->insts_.emplace_back(load_a0_inst);
    // 将s1存入ra
    auto load_ra_inst = std::make_shared<BinaryInst>(Instruction::ADD, ra, zero, s1);
    cur_bb_->insts_.emplace_back(load_ra_inst);
    // 将栈顶存入s1
    auto store_inst_1 = std::make_shared<LoadInst>(Instruction::LD, s1, sp, imm);
    cur_bb_->insts_.emplace_back(store_inst_1);
    // 退栈
    auto dealloc = current_scope_.dealloc_stack(8 + stack_for_arg);
    cur_bb_->insts_.emplace_back(dealloc);
    // 恢复a0-a7
    for(int i = 0; i < 8; i++) {
        auto a_reg = std::make_shared<Register>(Register::IntArg, i);
        auto s_reg = std::make_shared<Register>(Register::Saved, i + 2);
        auto load_reg_inst = std::make_shared<BinaryInst>(Instruction::ADD, a_reg, zero, s_reg);
        cur_bb_->insts_.emplace_back(load_reg_inst);
    }
    // 恢复s2-s11
    for(int i = 2; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * (i - 2));
        auto load_inst = std::make_shared<LoadInst>(Instruction::LD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(load_inst);
    }
    // 退栈
    dealloc = current_scope_.dealloc_stack(80);
    cur_bb_->insts_.emplace_back(dealloc);
}
void RiscvBuilder::visit(const ir::ReturnInst* inst) {
    // 什么都不用做
}
void RiscvBuilder::visit(const ir::BreakInst* inst) {
    auto op = inst->operands_[0].lock();
    auto bb = std::static_pointer_cast<ir::BasicBlock>(op);
    auto label = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, bb->index_));
    auto ins = std::make_shared<JumpInst>(Instruction::J, label);
    cur_bb_->insts_.emplace_back(ins);
}
void RiscvBuilder::visit(const ir::ContinueInst* inst) {
    auto op = inst->operands_[0].lock();
    auto bb = std::static_pointer_cast<ir::BasicBlock>(op);
    auto label = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, bb->index_));
    auto ins = std::make_shared<JumpInst>(Instruction::J, label);
    cur_bb_->insts_.emplace_back(ins);
}
void RiscvBuilder::visit(const ir::ContinueIncInst* inst) {
    // 与上面一条指令不同的是，这里需要先执行第一条操作数的最后一条指令
    auto op1 = inst->operands_[0].lock();
    auto bb1 = std::static_pointer_cast<ir::BasicBlock>(op1);
    bb1->instructions_.back()->accept(*this);
    auto op2 = inst->operands_[1].lock();
    auto bb2 = std::static_pointer_cast<ir::BasicBlock>(op2);
    auto label = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, bb2->index_));
    auto ins = std::make_shared<JumpInst>(Instruction::J, label);
    cur_bb_->insts_.emplace_back(ins);
}
void RiscvBuilder::visit(const ir::BranchInst* inst) {
    // 先执行条件判断语句
    auto cond = std::static_pointer_cast<ir::Instruction>(inst->operands_[0].lock());
    // 执行比较运算，结果保存在last_result_中，0为假，非0为真
    cond->accept(*this);
    auto then_bb = std::static_pointer_cast<ir::BasicBlock>(inst->operands_[1].lock());
    auto else_bb = std::static_pointer_cast<ir::BasicBlock>(inst->operands_[2].lock());
    auto then_label = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, then_bb->index_));
    auto zero = std::make_shared<Register>(Register::Zero);
    // 如果条件为真，跳转到then_label
    auto ins = std::make_shared<BranchInst>(Instruction::BNE, last_result_, zero, then_label);
    cur_bb_->insts_.emplace_back(ins);
    if(else_bb) {
        // 如果存在else分支，则跳转到else分支
        auto else_label = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, else_bb->index_));
        auto ins = std::make_shared<JumpInst>(Instruction::J, else_label);
        cur_bb_->insts_.emplace_back(ins);
    }
    // 释放寄存器
    current_scope_.free_tmp_reg(last_result_);
    // 先保存当前bb
    auto now_bb = cur_bb_;
    // 接着接受then分支
    then_bb->accept(*this);
    auto then_rv_bb = cur_bb_;
    // 如果存在else分支
    if(else_bb) {
        // 接受else分支
        else_bb->accept(*this);
    }
    cur_bb_ = now_bb;
    // 在当前位置加个label，表示分支的结束
    auto end_label = std::make_shared<Label>(Operand::Block, "END_OF_" + then_label->name_);
    auto label_inst = std::make_shared<LabelInst>(end_label);
    cur_bb_->insts_.emplace_back(label_inst);
    // 在then分支的最后加上一个跳转指令
    auto jump_inst = std::make_shared<JumpInst>(Instruction::J, end_label);
    then_rv_bb->insts_.emplace_back(jump_inst);
}

void RiscvBuilder::visit(const ir::BasicBlock* bb) {
    // 无脑接收指令就行
    auto bb_name = make_bb_name(cur_func_->label_->name_, bb->index_);
    if(cur_func_->scan_bb_.find(bb_name) != cur_func_->scan_bb_.end()) {
        // 说明这个基本块已经被扫描过了
        return;
    }
    cur_func_->scan_bb_.insert(bb_name);
    cur_bb_ = std::make_shared<BasicBlock>();
    cur_bb_->label_ = std::make_shared<Label>(Operand::Block, bb_name);
    LOG_DEBUG("Generating code for basic block %s", cur_bb_->label_->name_.c_str());
    for(auto &inst : bb->instructions_) {
        inst->accept(*this);
    }
    // 记录基本块信息
    // cur_func_->bb_map_[bb_name] = cur_bb_;
    // // 把后继基本块的信息保存在里面
    // for(auto &succ : bb->succ_bbs_) {
    //     bb_name = make_bb_name(cur_func_->label_->name_, succ.lock()->index_);
    //     cur_bb_->succ_.emplace_back(bb_name);
    // }
    cur_func_->bbs_.emplace_back(cur_bb_);
    
}

void RiscvBuilder::visit(const ir::Function* func) {
    LOG_DEBUG("Generating code for function %s", func->name_.c_str());
    auto function = std::make_shared<Function>();
    function->label_ = std::make_shared<Label>(Operand::Function,func->name_);
    cur_func_ = function;
    // 首先保存先前的栈指针
    auto alloc_stack = current_scope_.alloc_stack(8);
    function->before_insts_.emplace_back(alloc_stack);
    // 将s0寄存器的值保存到栈顶，即保存上一个函数的栈指针
    auto sp = std::make_shared<Register>(Register::Stack);
    auto s0 = std::make_shared<Register>(Register::Frame);
    auto zero = std::make_shared<Register>(Register::Zero);
    auto imm_zero = std::make_shared<Immediate>(0);
    auto save_s0 = std::make_shared<StoreInst>(Instruction::SD, s0, sp, imm_zero);
    auto update_s0 = std::make_shared<BinaryInst>(Instruction::ADD, s0, sp, zero);
    function->before_insts_.emplace_back(save_s0);
    function->before_insts_.emplace_back(update_s0);
    // 首先根据函数参数和函数对应的局部变量/ 常量 ，分配寄存器和栈空间
    // 先计算要给局部变量/常量开辟的栈空间
    int stack_size = 0;
    current_scope_.enter();
    // 进入新的作用域
    for(auto &local : func->local_identifiers_) {
        bool isFuncParam = false;
        for(auto &local_args : func->args_) {
            if(local->name_ == local_args->name_) {
                isFuncParam = true;
                break;
            }
        }
        if(!isFuncParam) {
            auto tid = local->get_elem_tid();
            auto mem = gen_sp_mem(stack_size, tid == ir::Type::RealTID, local->type_->get_size());
            current_scope_.push(local->name_, mem);
            stack_size += local->type_->get_size();
            LOG_DEBUG("Alloc %d byte(s) for variable %s", local->type_->get_size(), local->name_.c_str());
        }
    }
    stack_size = UpperAlign(stack_size, 8);
    // 开辟栈空间
    auto enter_inst = current_scope_.alloc_stack(stack_size);
    LOG_DEBUG("Function %s stack size: %d", func->name_.c_str(), stack_size);
    // 随后加入函数参数
    int arg_index = 0;
    for(auto &arg : func->args_) {
        if(arg->type_->is_pointer_) {
            // 指针,类型为整数
            auto mem = get_arg_pos(arg_index++);
            current_scope_.push(arg->name_, mem);
            current_scope_.add_pointer(arg->name_, make_pointer_type(arg->type_));
            if(mem->isRegister()) {
                auto reg = std::static_pointer_cast<Register>(mem);
                current_scope_.touch_reg(reg->getUniqueId());
            }
        } else {
            // 非指针，类型为整数或者实数
            auto tid = arg->type_->get_tid();
            auto mem = get_arg_pos(arg_index++);
            current_scope_.push(arg->name_, mem);
            if(mem->isRegister()) {
                auto reg = std::static_pointer_cast<Register>(mem);
                current_scope_.touch_reg(reg->getUniqueId());
            }
        }
    }
    cur_func_->before_insts_.emplace_back(enter_inst);
    // 遍历基本块
    for(auto &bb : func->basic_blocks_) {
        bb->accept(*this);
    }
    // 离开当前作用域
    // 检查有没有返回值，有就保存到a0
    if(func->func_type_.lock()->result_->is_number()) {
        if(func->name_ != "main")  {
                auto ret = current_scope_.find("__");
            if(ret == nullptr) {
                LOG_FATAL("Function %s has no return value", func->name_.c_str());
            }
            if(ret->isRegister()) {
                auto ret_reg = std::static_pointer_cast<Register>(ret);
                auto a0 = std::make_shared<Register>(Register::IntArg, 0);
                auto move_inst = std::make_shared<BinaryInst>(Instruction::ADD, a0, std::make_shared<Register>(Register::Zero), ret_reg);
                cur_func_->after_insts_.emplace_back(move_inst);
            } else {
                auto mem = std::static_pointer_cast<Memory>(ret);
                auto a0 = std::make_shared<Register>(Register::IntArg, 0);
                auto load_inst = std::make_shared<LoadInst>(Instruction::LD, a0, mem->base_, mem->offset_);
                cur_func_->after_insts_.emplace_back(load_inst);
            }
        }
    }
    // 先恢复s0
    auto load_s0 = std::make_shared<LoadInst>(Instruction::LD, s0, s0, imm_zero);
    auto leave_inst = current_scope_.leave();
    cur_func_->after_insts_.emplace_back(leave_inst);
    cur_func_->after_insts_.emplace_back(load_s0);
    // 退s0的栈空间
    auto dealloc_stack = current_scope_.dealloc_stack(8);
    cur_func_->after_insts_.emplace_back(dealloc_stack);
    // 如果是main函数，需要ret退出
    if(func->name_ == "main") {
        auto a0 = std::make_shared<Register>(Register::IntArg, 0);
        auto set_a0 = std::make_shared<BinaryInst>(Instruction::XOR, a0, zero, zero);
        auto ra = std::make_shared<Register>(Register::Return);
        auto ret_inst = std::make_shared<JumpInst>(Instruction::JALR, zero, ra, imm_zero);
        cur_func_->after_insts_.emplace_back(set_a0);
        cur_func_->after_insts_.emplace_back(ret_inst);
        modules_->add_func(cur_func_);
        return;
    }
    // 加上返回指令
    auto ra = std::make_shared<Register>(Register::Return);
    auto ret_inst = std::make_shared<JumpInst>(Instruction::JALR, zero, ra, imm_zero);
    cur_func_->after_insts_.emplace_back(ret_inst);
    modules_->add_func(cur_func_);
    
}
void RiscvBuilder::visit(const ir::GlobalIdentifier* global) {
    // 先判断是否初始化
    if(global->init_val_) {
        // 初始化即当literal处理
        global->init_val_->accept(*this);
    } else {
        // 未初始化，直接在bss段声明
        auto global_id = std::make_shared<GlobalId>(global->name_, global->type_->get_size());
        modules_->add_global(global_id);
    }
}

void RiscvBuilder::visit(const ir::LiteralDouble* literal) {
    if(!cur_func_) {
        auto global_const = std::make_shared<GlobalConst>(literal->get_real(), literal->name_);
        modules_->add_const(global_const);
        tmp_consts_.emplace_back(global_const);
    } else {
        // 没有在解析函数，此时在运算，将常量放入寄存器
        auto reg = current_scope_.alloc_tmp_reg(false);
        auto imm = std::make_shared<Immediate>(get_bit_pattern(literal->get_real()));
        auto zero = std::make_shared<Register>(Register::Zero);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, reg, zero, imm);
        cur_bb_->insts_.emplace_back(inst);
        last_result_ = current_scope_.alloc_tmp_reg(true);
        auto convert_inst = std::make_shared<UnaryInst>(Instruction::FMV_D_X, last_result_, reg);
        cur_bb_->insts_.emplace_back(convert_inst);
        current_scope_.free_tmp_reg(reg);
    }
}

void RiscvBuilder::visit(const ir::LiteralInt* literal) {
    if(!cur_func_) {
        auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
        modules_->add_const(global_const);
        tmp_consts_.emplace_back(global_const);
    } else {
        // 没有在解析函数，此时在运算，将常量放入寄存器
        auto reg = current_scope_.alloc_tmp_reg(false);
        auto imm = std::make_shared<Immediate>(literal->val_);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, reg, zero, imm);
        cur_bb_->insts_.emplace_back(inst);
        last_result_ = reg;
    }
}

void RiscvBuilder::visit(const ir::LiteralString* literal) {
    auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralChar* literal) {
    if (!cur_func_) {
        auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
        modules_->add_const(global_const);
        tmp_consts_.emplace_back(global_const);
    } else {
        // 没有在解析函数，此时在运算，将常量放入寄存器
        auto reg = current_scope_.alloc_tmp_reg(false);
        auto imm = std::make_shared<Immediate>(literal->val_);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, reg, zero, imm);
        cur_bb_->insts_.emplace_back(inst);
        last_result_ = reg;
    }
}

void RiscvBuilder::visit(const ir::LiteralBool* literal) {
    if (!cur_func_) {
        auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
        modules_->add_const(global_const);
        tmp_consts_.emplace_back(global_const);
    } else {
        // 没有在解析函数，此时在运算，将常量放入寄存器
        auto reg = current_scope_.alloc_tmp_reg(false);
        auto imm = std::make_shared<Immediate>(literal->val_);
        auto zero = std::make_shared<Register>(Register::Zero);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, reg, zero, imm);
        cur_bb_->insts_.emplace_back(inst);
        last_result_ = reg;
    }
}

void RiscvBuilder::visit(const ir::LiteralArray* literal) {
    std::vector<std::shared_ptr<GlobalConst>> array_val;
    for(auto &val : literal->const_array) {
        val->accept(*this);
        auto tmp = tmp_consts_.back();
        tmp_consts_.pop_back();
        array_val.emplace_back(tmp);
    }
    auto global_const = std::make_shared<GlobalConst>(array_val, literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralFloat* literal) {
    if (!cur_func_) {
        auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
        modules_->add_const(global_const);
        tmp_consts_.emplace_back(global_const);
    } else {
        // 没有在解析函数，此时在运算，将常量放入寄存器
        auto reg = current_scope_.alloc_tmp_reg(false);
        auto imm = std::make_shared<Immediate>(get_bit_pattern(literal->val_));
        auto zero = std::make_shared<Register>(Register::Zero);
        auto inst = std::make_shared<BinaryInst>(Instruction::ADDI, reg, zero, imm);
        cur_bb_->insts_.emplace_back(inst);
        last_result_ = current_scope_.alloc_tmp_reg(true);
        auto convert_inst = std::make_shared<UnaryInst>(Instruction::FMV_D_X, last_result_, reg);
        cur_bb_->insts_.emplace_back(convert_inst);
    }
}

void RiscvBuilder::build(ir::Module &program) {
    // 第一步，创建module
    modules_ = std::make_unique<Module>();
    std::vector<std::future<void>> globals;
    std::vector<std::future<void>> futures;
    // 接着添加全局标识符, 在bss段或者data段声明
    for(auto &const_ : program.global_identifiers_) {
        globals.emplace_back(
            common::g_thpool->enqueue(
                [this, &const_] {
                    const_->accept(*this);
                }
            )
        );
    }
    // 等待所有任务完成
    for(auto &fut : globals) {
        fut.get();
    }
    // 接着开始解析所有函数
    for(auto &func : program.functions_) {
        futures.emplace_back(
            common::g_thpool->enqueue(
                [this, &func] {
                    current_scope_.enter();
                    func->accept(*this);
                    current_scope_.leave();
                }
            )
        );
    }

    // 等待所有任务完成
    for(auto &fut : futures) {
        fut.get();
    }
    
}
void RiscvBuilder::output(std::ofstream &out) {
    // 输出所有常量
    out << ".data\n";
    for(auto &const_ : modules_->consts_) {
        out << const_->print() << std::endl;
    }
    // 输出未初始化的全局变量
    out << ".bss\n";
    for(auto &global : modules_->global_vars_) {
        out << global->print() << std::endl;
    }
    // 输出所有函数
    out << ".text\n";
    // 先声明所有函数名称
    for(auto &func : modules_->funcs_) {
        out << ".globl " << func->label_->print() << "\n";
    }
    // 随后输出函数
    for(auto &func : modules_->funcs_) {
        func->output(out);
    }
}

void Module::add_const(std::shared_ptr<GlobalConst> global) {
    std::lock_guard<std::mutex> lock(const_mutex_);
    consts_.emplace_back(global);
}

void Module::add_func(std::shared_ptr<Function> func) {
    std::lock_guard<std::mutex> lock(func_mutex_);
    funcs_.emplace_back(func);
}

void Module::add_global(std::shared_ptr<GlobalId> global) {
    std::lock_guard<std::mutex> lock(global_mutex_);
    global_vars_.emplace_back(global);
}

// void Function::handle_bb(std::shared_ptr<BasicBlock> bb, std::ofstream &out) {
//     // 检查是否处理过
//     if(scan_bb_.find(bb->label_->name_) != scan_bb_.end()) {
//         return;
//     }
//     scan_bb_.insert(bb->label_->name_);
//     // 输出基本块的label
//     out << bb->label_->print() << ":\n";
//     // 输出基本块的指令
//     for(auto &inst : bb->insts_) {
//         out << "\t" << inst->print() << "\n";
//     }
//     // 处理基本块的后继基本块
//     for(auto &succ : bb->succ_) {
//         handle_bb(bb_map_[succ], out);
//     }
// }

void Function::output(std::ofstream &out) const {
    // 先输出Label
    out << label_->print() << ":\n";
    // 输出函数开始前的指令
    for(auto &inst : before_insts_) {
        out << "\t" << inst->print() << "\n";
    }
    // 输出基本块
    for(auto &bb : bbs_) {
        out << bb->label_->print() << ":\n";
        for(auto &inst : bb->insts_) {
            if(inst->is_label()) {
                out << inst->print() << "\n";
            } else {
                out << "\t" << inst->print() << "\n";
            }
        }
        // handle_bb(bb, out);
    }
    // 输出函数结束后的指令
    for(auto &inst : after_insts_) {
        out << "\t" << inst->print() << "\n";
    }
}

} // namespace riscv
} // namespace builder