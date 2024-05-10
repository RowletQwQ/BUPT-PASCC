

#include "builder.hpp"
#include "instruction.hpp"
#include "ir/ir.hpp"
#include "common/thpool/thpool.hpp"
#include "common/log/log.hpp"
#include "operand.hpp"

#include <cstdint>
#include <future>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>
namespace builder {
namespace riscv {

// 声明线程唯一变量
thread_local std::shared_ptr<BasicBlock> cur_bb_;
thread_local std::shared_ptr<Function> cur_func_;
thread_local std::vector<std::shared_ptr<GlobalConst>> tmp_consts_;
thread_local std::shared_ptr<Register> last_result_;
thread_local Scope current_scope_;
thread_local bool need_pointer_ = false;


static inline int UpperAlign(int size, int align) {
    return (size + align - 1) & ~(align - 1);
}

// 生成一个操作数，标明是一个借助栈的内存操作数
static std::shared_ptr<Memory> gen_sp_mem(int offset, bool is_real, int size, int count = 1) {
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(offset);
    return std::make_shared<Memory>(sp, imm, size, count);
}

static std::shared_ptr<Operand> get_arg_pos(int index) {
    if(index >= 8) {
        // 超过8个参数，需要通过栈传递
        auto sp = std::make_shared<Register>(Register::Frame, 0);
        // +16 是因为要跳过上一个函数的返回地址 + s0
        auto imm = std::make_shared<Immediate>(16 + index * 8);
        return std::make_shared<Memory>(sp, imm, 8);
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

void Scope::enter() {
    stack_size_.emplace_back(0);
    symbols_.emplace_back();
    pointers_.emplace_back();
    reg_used_.assign(kMaxRegs, false);
    for(int i = 0; i < 7; i++){
        avail_int_regs_.emplace_back(std::make_shared<Register>(Register::IntArg, i));
    }
    for(int i = 0; i < 6; i++) {
        avail_int_regs_.emplace_back(std::make_shared<Register>(Register::Temp, i));
    }
    for(int i = 0; i < 32; i++){
        avail_float_regs_.emplace_back(std::make_shared<Register>(Register::FloatArg, i));
    }
}

// 对应指令 addi sp , sp, -size
std::shared_ptr<Instruction> Scope::alloc_stack(int size) {
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
                touch_reg(reg->getUniqueId());
                return reg;
            }
        }
    } else {
        for(auto &reg: avail_int_regs_) {
            if(!is_reg_allocated(reg->getUniqueId())) {
                touch_reg(reg->getUniqueId());
                return reg;
            }
        }
    }
    LOG_FATAL("No available register");
    return nullptr;
}

void Scope::free_tmp_reg(std::shared_ptr<Register> reg) {
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
        {ir::Instruction::And, Instruction::AND},
        {ir::Instruction::AndThen, Instruction::AND},
        {ir::Instruction::Or, Instruction::OR},
        {ir::Instruction::OrElse, Instruction::OR},
    };

    static std::map<ir::Instruction::OpID, Instruction::InstrType> int64_map = 
    {
        // Binary Operation
        {ir::Instruction::Add, Instruction::ADD},
        {ir::Instruction::Sub, Instruction::SUB},
        {ir::Instruction::Mul, Instruction::MUL},
        {ir::Instruction::Div, Instruction::DIV},
        {ir::Instruction::Mod, Instruction::REM},
        {ir::Instruction::And, Instruction::AND},
        {ir::Instruction::AndThen, Instruction::AND},
        {ir::Instruction::Or, Instruction::OR},
        {ir::Instruction::OrElse, Instruction::OR},
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
    // TODO
}

static void make_cmp_inst
(ir::Instruction::OpID id, std::shared_ptr<ir::Type> type, std::shared_ptr<Register> reg1, std::shared_ptr<Register> reg2)
{
    // RISC-V中的比较指令集并不完善，故需要转换
    // 最后的结果一定保存在reg1中
    // TODO
}

void RiscvBuilder::visit(const ir::BinaryInst* inst) {
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

}
void RiscvBuilder::visit(const ir::LoadInst* inst) {
    if(need_pointer_) {
        // 需要将对应操作数的内存地址存入last_result_
    } else {
        
    }
}
void RiscvBuilder::visit(const ir::ReadInst* inst) {

}
void RiscvBuilder::visit(const ir::WriteInst* inst) {

}
void RiscvBuilder::visit(const ir::CallInst* inst) {
    // 在函数调用前保存调用环境
    // 先将s2-s11写入栈
    auto alloc = current_scope_.alloc_stack(72);
    cur_bb_->insts_.emplace_back(alloc);
    auto sp = std::make_shared<Register>(Register::Stack);
    auto zero = std::make_shared<Register>(Register::Zero);
    for(int i = 2; i < 12; i++){
        auto s_reg = std::make_shared<Register>(Register::Saved, i);
        auto imm = std::make_shared<Immediate>(8 * i);
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

    // 调用返回，需要恢复环境
    // 将s1存入ra
    auto load_ra_inst = std::make_shared<BinaryInst>(Instruction::ADD, ra, zero, s1);
    cur_bb_->insts_.emplace_back(load_ra_inst);
    // 将栈顶存入s1
    store_inst = std::make_shared<LoadInst>(Instruction::LD, s1, sp, imm);
    cur_bb_->insts_.emplace_back(store_inst);
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
        auto imm = std::make_shared<Immediate>(8 * i);
        auto load_inst = std::make_shared<LoadInst>(Instruction::LD, s_reg, sp, imm);
        cur_bb_->insts_.emplace_back(load_inst);
    }
    // 退栈
    dealloc = current_scope_.dealloc_stack(72);
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
        ins = std::make_shared<JumpInst>(Instruction::J, else_label);
        cur_bb_->insts_.emplace_back(ins);
    }
    // 释放寄存器
    current_scope_.free_tmp_reg(last_result_);
}

void RiscvBuilder::visit(const ir::BasicBlock* bb) {
    // 无脑接收指令就行
    cur_bb_ = std::make_shared<BasicBlock>();
    cur_bb_->label_ = std::make_shared<Label>(Operand::Block, make_bb_name(cur_func_->label_->name_, bb->index_));
    for(auto &inst : bb->instructions_) {
        inst->accept(*this);
    }
    cur_func_->bbs_.emplace_back(cur_bb_);
}

void RiscvBuilder::visit(const ir::Function* func) {
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
        }
    }
    stack_size = UpperAlign(stack_size, 8);
    // 开辟栈空间
    auto enter_inst = current_scope_.alloc_stack(stack_size);
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
    // 先恢复s0
    auto load_s0 = std::make_shared<LoadInst>(Instruction::LD, s0, s0, imm_zero);
    auto leave_inst = current_scope_.leave();
    cur_func_->after_insts_.emplace_back(leave_inst);
    cur_func_->after_insts_.emplace_back(load_s0);
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
    std::vector<std::future<void>> futures;
    // 接着添加全局标识符, 在bss段或者data段声明
    for(auto &const_ : program.global_identifiers_) {
        futures.emplace_back(
            common::g_thpool->enqueue(
                [this, &const_] {
                    const_->accept(*this);
                }
            )
        );
    }
    // 添加常量， 在data段声明
    for(auto &const_ : program.all_literals_) {
        futures.emplace_back(
            common::g_thpool->enqueue(
                [this, &const_] {
                    const_->accept(*this);
                }
            )
        );
    }
    // 接着开始解析所有函数
    for(auto &func : program.functions_) {
        futures.emplace_back(
            common::g_thpool->enqueue(
                [this, &func] {
                    func->accept(*this);
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

void Function::output(std::ofstream &out) const{
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
            out << "\t" << inst->print() << "\n";
        }
    }
    // 输出函数结束后的指令
    for(auto &inst : after_insts_) {
        out << "\t" << inst->print() << "\n";
    }
}

} // namespace riscv
} // namespace builder