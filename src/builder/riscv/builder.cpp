

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
#include <vector>
namespace builder {
namespace riscv {

// 声明线程唯一变量
thread_local std::shared_ptr<BasicBlock> cur_bb_;
thread_local std::shared_ptr<Function> cur_func_;
thread_local std::vector<std::shared_ptr<GlobalConst>> tmp_consts_;
thread_local std::shared_ptr<Register> last_result_;
thread_local Scope current_scope_;


static inline int UpperAlign(int size, int align) {
    return (size + align - 1) & ~(align - 1);
}

// 生成一个操作数，标明是一个借助栈的内存操作数
static std::shared_ptr<Memory> gen_sp_mem(int offset, bool is_real, int size, int count = 1) {
    auto sp = std::make_shared<Register>(Register::Stack);
    auto imm = std::make_shared<Immediate>(offset);
    Memory::MemType type = is_real ? Memory::Float : Memory::Int;
    return std::make_shared<Memory>(sp, imm, type, size, count);
}

static std::shared_ptr<Operand> get_arg_pos(int index, bool is_real) {
    if(index >= 8) {
        // 超过8个参数，需要通过栈传递
        auto sp = std::make_shared<Register>(Register::Frame, 0);
        // +8 是因为要跳过上一个函数的返回地址
        auto imm = std::make_shared<Immediate>(8 + index * 8);
        return std::make_shared<Memory>(sp, imm, is_real ? Memory::Float : Memory::Int, 8);
    } 

    return std::make_shared<Register>((is_real) ? Register::FloatArg : Register::IntArg, index);  
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

int64_t get_bit_pattern(double val) {
    int64_t res;
    memcpy(&res, &val, sizeof(double));
    return res;
}

int32_t get_bit_pattern(float val) {
    int32_t res;
    memcpy(&res, &val, sizeof(float));
    return res;
}


void RiscvBuilder::visit(const ir::BinaryInst* inst) {

}
void RiscvBuilder::visit(const ir::UnaryInst* inst) {

}
void RiscvBuilder::visit(const ir::CompareInst* inst) {

}
void RiscvBuilder::visit(const ir::StoreInst* inst) {

}
void RiscvBuilder::visit(const ir::LoadInst* inst) {

}
void RiscvBuilder::visit(const ir::ReadInst* inst) {

}
void RiscvBuilder::visit(const ir::WriteInst* inst) {

}
void RiscvBuilder::visit(const ir::CallInst* inst) {

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
    int int_arg_index = 0;
    int float_arg_index = 0;
    for(auto &arg : func->args_) {
        if(arg->type_->is_pointer_) {
            // 指针,类型为整数
            auto mem = get_arg_pos(int_arg_index++, false);
            current_scope_.push(arg->name_, mem);
            current_scope_.add_pointer(arg->name_, make_pointer_type(arg->type_));
            if(mem->isRegister()) {
                auto reg = std::static_pointer_cast<Register>(mem);
                current_scope_.touch_reg(reg->getUniqueId());
            }
        } else {
            // 非指针，类型为整数或者实数
            auto tid = arg->type_->get_tid();
            auto mem = get_arg_pos(tid == ir::Type::RealTID ? float_arg_index++ : int_arg_index++, tid == ir::Type::RealTID);
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
        auto convert_inst = std::make_shared<UnaryInst>(Instruction::FCVT_D_W, last_result_, reg);
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
        auto convert_inst = std::make_shared<UnaryInst>(Instruction::FCVT_D_W, last_result_, reg);
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
    out << ".globl main\n";
    for(auto &func : modules_->funcs_) {
        out << func->print() << std::endl;
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

} // namespace riscv
} // namespace builder