

#include "builder/riscv/instruction.hpp"
#include "common/log/log.hpp"
#include "builder/riscv/operand.hpp"
#include <map>
#include <set>
#include <string>

namespace builder {

namespace riscv {



std::map<Instruction::InstrType, std::string> instrTypeToString = {
    {Instruction::SLL, "sll"},
    {Instruction::SRL, "srl"},
    {Instruction::SRA, "sra"},
    {Instruction::SLLI, "slli"},
    {Instruction::SRLI, "srli"},
    {Instruction::SRAI, "srai"},
    {Instruction::SLLW, "sllw"},
    {Instruction::SRLW, "srlw"},
    {Instruction::SRAW, "sraw"},
    {Instruction::SLLIW, "slliw"},
    {Instruction::SRLIW, "srliw"},
    {Instruction::SRAIW, "sraiw"},
    {Instruction::ADD, "add"},
    {Instruction::ADDI, "addi"},
    {Instruction::SUB, "sub"},
    {Instruction::LUI, "lui"},
    {Instruction::AUIPC, "auipc"},
    {Instruction::ADDW, "addw"},
    {Instruction::ADDIW, "addiw"},
    {Instruction::SUBW, "subw"},
    {Instruction::XOR, "xor"},
    {Instruction::XORI, "xori"},
    {Instruction::OR, "or"},
    {Instruction::ORI, "ori"},
    {Instruction::AND, "and"},
    {Instruction::ANDI, "andi"},
    {Instruction::SLT, "slt"},
    {Instruction::SLTI, "slti"},
    {Instruction::SLTU, "sltu"},
    {Instruction::SLTIU, "sltiu"},
    {Instruction::BEQ, "beq"},
    {Instruction::BNE, "bne"},
    {Instruction::BLT, "blt"},
    {Instruction::BGE, "bge"},
    {Instruction::BLTU, "bltu"},
    {Instruction::BGEU, "bgeu"},
    {Instruction::J, "j"},
    {Instruction::JAL, "jal"},
    {Instruction::JALR, "jalr"},
    {Instruction::LB, "lb"},
    {Instruction::LH, "lh"},
    {Instruction::LW, "lw"},
    {Instruction::LBU, "lbu"},
    {Instruction::LHU, "lhu"},
    {Instruction::LD, "ld"},
    {Instruction::LWU, "lwu"},
    {Instruction::SB, "sb"},
    {Instruction::SH, "sh"},
    {Instruction::SW, "sw"},
    {Instruction::SD, "sd"},
    {Instruction::ECALL, "ecall"},
    {Instruction::EBREAK, "ebreak"},
    {Instruction::MRET, "mret"},
    {Instruction::SRET, "sret"},
    {Instruction::URET, "uret"},
    {Instruction::WFI, "wfi"},
    {Instruction::SFENCE_VMA, "sfence_vma"},
    {Instruction::CSRRW, "csrrw"},
    {Instruction::CSRRS, "csrrs"},
    {Instruction::CSRRC, "csrrc"},
    {Instruction::CSRRWI, "csrrwi"},
    {Instruction::CSRRSI, "csrrsi"},
    {Instruction::CSRRCI, "csrrci"},
    {Instruction::FENCE, "fence"},
    {Instruction::FENCE_I, "fence_i"},
    {Instruction::MUL, "mul"},
    {Instruction::MULH, "mulh"},
    {Instruction::MULHSU, "mulhsu"},
    {Instruction::MULHU, "mulhu"},
    {Instruction::DIV, "div"},
    {Instruction::DIVU, "divu"},
    {Instruction::REM, "rem"},
    {Instruction::REMU, "remu"},
    {Instruction::MULW, "mulw"},
    {Instruction::DIVW, "divw"},
    {Instruction::DIVUW, "divuw"},
    {Instruction::REMW, "remw"},
    {Instruction::FMV_W_X, "fmv_w_x"},
    {Instruction::FMV_X_W, "fmv_x_w"},
    {Instruction::FMV_D_X, "fmv_d_x"},
    {Instruction::FMV_X_D, "fmv_x_d"},
    {Instruction::FLW, "flw"},
    {Instruction::FLD, "fld"},
    {Instruction::FSW, "fsw"},
    {Instruction::FSD, "fsd"},
    {Instruction::FCVT_S_W, "fcvt_s_w"},
    {Instruction::FCVT_S_WU, "fcvt_s_wu"},
    {Instruction::FCVT_D_W, "fcvt_d_w"},
    {Instruction::FCVT_D_WU, "fcvt_d_wu"},
    {Instruction::FCVT_W_S, "fcvt_w_s"},
    {Instruction::FCVT_WU_S, "fcvt_wu_s"},
    {Instruction::FCVT_W_D, "fcvt_w_d"},
    {Instruction::FCVT_WU_D, "fcvt_wu_d"},
    {Instruction::FCVT_L_S, "fcvt_l_s"},
    {Instruction::FCVT_LU_S, "fcvt_lu_s"},
    {Instruction::FCVT_L_D, "fcvt_l_d"},
    {Instruction::FCVT_LU_D, "fcvt_lu_d"},
    {Instruction::FCVT_S_L, "fcvt_s_l"},
    {Instruction::FCVT_S_LU, "fcvt_s_lu"},
    {Instruction::FCVT_D_L, "fcvt_d_l"},
    {Instruction::FCVT_D_LU, "fcvt_d_lu"},
    {Instruction::FNEG_S, "fneg_s"},
    {Instruction::FNEG_D, "fneg_d"},
    {Instruction::FADD_S, "fadd_s"},
    {Instruction::FSUB_S, "fsub_s"},
    {Instruction::FMUL_S, "fmul_s"},
    {Instruction::FDIV_S, "fdiv_s"},
    {Instruction::FSQRT_S, "fsqrt_s"},
    {Instruction::FADD_D, "fadd_d"},
    {Instruction::FSUB_D, "fsub_d"},
    {Instruction::FMUL_D, "fmul_d"},
    {Instruction::FDIV_D, "fdiv_d"},
    {Instruction::FSQRT_D, "fsqrt_d"},
    {Instruction::FMADD_S, "fmadd_s"},
    {Instruction::FMSUB_S, "fmsub_s"},
    {Instruction::FNMADD_S, "fnmadd_s"},
    {Instruction::FNMSUB_S, "fnmsub_s"},
    {Instruction::FMADD_D, "fmadd_d"},
    {Instruction::FMSUB_D, "fmsub_d"},
    {Instruction::FNMADD_D, "fnmadd_d"},
    {Instruction::FNMSUB_D, "fnmsub_d"},
    {Instruction::FEQ_S, "feq_s"},
    {Instruction::FLT_S, "flt_s"},
    {Instruction::FLE_S, "fle_s"},
    {Instruction::FEQ_D, "feq_d"},
    {Instruction::FLT_D, "flt_d"},
    {Instruction::FLE_D, "fle_d"},
    {Instruction::FMIN_S, "fmin_s"},
    {Instruction::FMAX_S, "fmax_s"},
    {Instruction::FMIN_D, "fmin_d"},
    {Instruction::FMAX_D, "fmax_d"},
    {Instruction::FSGNJ_S, "fsgnj_s"},
    {Instruction::FSGNJN_S, "fsgnjn_s"},
    {Instruction::FSGNJX_S, "fsgnjx_s"},
    {Instruction::FSGNJ_D, "fsgnj_d"},
    {Instruction::FSGNJN_D, "fsgnjn_d"},
    {Instruction::FSGNJX_D, "fsgnjx_d"}
};

Instruction::Instruction(InstrType type, int op_nums)
: type_(type), op_nums_(op_nums) {
    operands_.resize(op_nums);
}

void Instruction::setOperand(int index, std::shared_ptr<Operand> operand) {
    if (index < 0 || index >= op_nums_) {
        LOG_FATAL("Instruction setOperand index error, index %d, op_nums %d", index, op_nums_);
    }
    operands_[index] = operand;
}

NoOperandInst::NoOperandInst(InstrType type)
: Instruction(type, 0)
{
    // 进行指令检查
    if (type == ECALL || type == EBREAK || type == MRET || type == SRET ||
         type == URET || type == WFI || type == SFENCE_VMA) {
        type_ = type;
    } else {
        LOG_FATAL("NoOperandInst type error, %s not a NoOperandInst", instrTypeToString[type].c_str());
    }
}

UnaryInst::UnaryInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> op1)
: Instruction(type, 1)
{
    // 进行指令检查
    if ((type >= FMV_W_X && type <= FMV_X_D)|| (type >= FCVT_S_W && type <= FNEG_D)) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register) {
            type_ = type;
            operands_[0] = op1;
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str());
            LOG_FATAL("UnaryInst type error, dest and op1 should be Register");
        }
    } else if(type_ == LUI || type ==AUIPC) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Immediate) {
            type_ = type;
            operands_[0] = op1;
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str());
            LOG_FATAL("UnaryInst type error, dest should be Register, op1 should be Immediate");
        }
    } else if (type == FSQRT_S || type == FSQRT_D) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register) {
            type_ = type;
            operands_[0] = op1;
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str());
            LOG_FATAL("UnaryInst type error, dest should be Register, op1 should be Register");
        }
    } else {
        LOG_FATAL("UnaryInst type error, %s not a UnaryInst", instrTypeToString[type].c_str());
    }
    dest_ = dest;
}

BinaryInst::BinaryInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> op1, std::shared_ptr<Operand> op2)
: Instruction(type, 2)
{

    static const std::set<Instruction::InstrType> vaild_int_types = {
        ADD, SUB, SLT, SLTU, XOR, OR, AND, ANDI, MUL, MULH, MULHSU, 
        MULHU, DIV, DIVU, REM, REMU, MULW, DIVW, DIVUW, REMW
    };

    static const std::set<Instruction::InstrType> valid_float_types = {
        FADD_S, FSUB_S, FMUL_S, FDIV_S, FADD_D, FSUB_D, FMUL_D, FDIV_D,
        FSGNJ_S, FSGNJN_S, FSGNJX_S, FSGNJ_D, FSGNJN_D, FSGNJX_D
    };

    if (vaild_int_types.count(type) > 0) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register && op2->type_ == Operand::Register) {
            auto reg1 = std::dynamic_pointer_cast<Register>(op1);
            auto reg2 = std::dynamic_pointer_cast<Register>(op2);
            if(reg1->is_real() || reg2->is_real()) {
                LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str());
                LOG_FATAL("BinaryInst type error, dest, op1 and op2 should be Register");
            }
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str());
            LOG_FATAL("BinaryInst type error, dest, op1 and op2 should be Register");
        }
    } else if (valid_float_types.count(type) > 0) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register && op2->type_ == Operand::Register) {
            auto reg1 = std::dynamic_pointer_cast<Register>(op1);
            auto reg2 = std::dynamic_pointer_cast<Register>(op2);
            if(!reg1->is_real() || !reg2->is_real()) {
                LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str());
                LOG_FATAL("BinaryInst type error, dest, op1 and op2 should be Register");
            }
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str());
            LOG_FATAL("BinaryInst type error, dest, op1 and op2 should be Register");
        }
    } else {
        LOG_FATAL("BinaryInst type error, %s not a BinaryInst", instrTypeToString[type].c_str());
    }


    type_ = type;
    operands_[0] = op1;
    operands_[1] = op2;
    dest_ = dest;
}

FusionInst::FusionInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> op1, 
    std::shared_ptr<Operand> op2, std::shared_ptr<Operand> op3)
: Instruction(type, 3)
{
    static const std::set<Instruction::InstrType> valid_types = {
        FMADD_S, FMSUB_S, FNMADD_S, FNMSUB_S, 
        FMADD_D, FMSUB_D, FNMADD_D, FNMSUB_D
    };

    if (valid_types.count(type) > 0) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register && 
            op2->type_ == Operand::Register && op3->type_ == Operand::Register) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s, op3 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str(), op3->print().c_str());
            LOG_FATAL("FusionInst type error, dest, op1, op2 and op3 should be Register");
        }
    } else {
        LOG_FATAL("FusionInst type error, %s not a FusionInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = op1;
    operands_[1] = op2;
    operands_[2] = op3;
    dest_ = dest;
}

BranchInst::BranchInst(InstrType type, std::shared_ptr<Operand> op1, std::shared_ptr<Operand> op2, std::shared_ptr<Operand> dest)
: Instruction(type, 2)
{
    static const std::set<Instruction::InstrType> valid_types = {
        BEQ, BNE, BLT, BGE, BLTU, BGEU
    };

    if (valid_types.count(type) > 0) {
        if (op1->type_ == Operand::Register && op2->type_ == Operand::Register && dest->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, op1 %s, op2 %s, dest %s", 
                    instrTypeToString[type].c_str(), op1->print().c_str(), op2->print().c_str(), dest->print().c_str());
            LOG_FATAL("BranchInst type error, op1, op2 should be Register, dest should be Immediate");
        }
    } else {
        LOG_FATAL("BranchInst type error, %s not a BranchInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = op1;
    operands_[1] = op2;
    dest_ = dest;
}

JumpInst::JumpInst(InstrType type, std::shared_ptr<Operand> target)
: Instruction(type, 0)
{
    if (type == Instruction::J) {
        if (target->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, target %s", 
                    instrTypeToString[type].c_str(), target->print().c_str());
            LOG_FATAL("JumpInst type error, target should be Immediate");
        }
    } else {
        LOG_FATAL("JumpInst type error, %s not a single operand JumpInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    dest_ = target;
}

JumpInst::JumpInst(InstrType type, std::shared_ptr<Operand> ret, std::shared_ptr<Operand> desc)
: Instruction(type, 1)
{
    if (type == Instruction::JAL) {
        if (ret->type_ == Operand::Register && desc->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, ret %s, desc %s", 
                    instrTypeToString[type].c_str(), ret->print().c_str(), desc->print().c_str());
            LOG_FATAL("JumpInst type error, ret should be Register, desc should be Immediate");
        }
    } else {
        LOG_FATAL("JumpInst type error, %s not a double operand JumpInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = desc;
    dest_ = ret;
}

JumpInst::JumpInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> op1, std::shared_ptr<Operand> op2)
: Instruction(type, 2)
{
    if (type == Instruction::JALR) {
        if (dest->type_ == Operand::Register && op1->type_ == Operand::Register && op2->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, op1 %s, op2 %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), op1->print().c_str(), op2->print().c_str());
            LOG_FATAL("JumpInst type error, dest should be Register, op1 should be Register, op2 should be Immediate");
        }
    } else {
        LOG_FATAL("JumpInst type error, %s not a triple operand JumpInst", instrTypeToString[type].c_str());
    }
}

std::string NoOperandInst::print() const {
    return instrTypeToString[type_];
}

std::string UnaryInst::print() const {
    return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print();
}

std::string BinaryInst::print() const {
    return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print() + 
            ", " + operands_.at(1)->print();
}

std::string FusionInst::print() const {
    return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print() + 
            ", " + operands_.at(1)->print() + ", " + operands_.at(2)->print();
}

std::string BranchInst::print() const {
    // 分支跳转指令最不正常的事情是，它的目的操作数是一个立即数，且顺序在最后
    return instrTypeToString[type_] + " " + operands_.at(0)->print() + ", " 
            + operands_.at(1)->print() + ", " + dest_->print();
}

std::string JumpInst::print() const {
    // Jump指令分成了三种情况，J, JAL, JALR
    if (type_ == J) {
        return instrTypeToString[type_] + " " + dest_->print();
    } else if (type_ == JAL) {
        return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print();
    } else {
        return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print() + 
                ", " + operands_.at(1)->print();
    }
}

LoadInst::LoadInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> base, std::shared_ptr<Operand> offset)
: Instruction(type, 2)
{
    static const std::set<Instruction::InstrType> valid_types = {
        LB, LH, LW, LBU, LHU, LD, LWU, FLW, FLD
    };

    if (valid_types.count(type) > 0) {
        if (dest->type_ == Operand::Register && base->type_ == Operand::Register && offset->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, base %s, offset %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), base->print().c_str(), offset->print().c_str());
            LOG_FATAL("LoadInst type error, dest and base should be Register, offset should be Immediate");
        }
    } else {
        LOG_FATAL("LoadInst type error, %s not a LoadInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = base;
    operands_[1] = offset;
    dest_ = dest;
}

LoadInst::LoadInst(InstrType type, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> src)
: Instruction(type, 1)
{
    static const std::set<Instruction::InstrType> valid_types = {
        LB, LH, LW, LBU, LHU, LD, LWU, FLW, FLD
    };

    if (valid_types.count(type) > 0) {
        if (dest->type_ == Operand::Register && src->type_ == Operand::Memory) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, dest %s, src %s", 
                    instrTypeToString[type].c_str(), dest->print().c_str(), src->print().c_str());
            LOG_FATAL("LoadInst type error, dest should be Register, src should be Memory");
        }
    } else {
        LOG_FATAL("LoadInst type error, %s not a LoadInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = src;
    dest_ = dest;
}

std::string LoadInst::print() const {
    if (op_nums_ == 2) {
        return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print() + 
                ", " + operands_.at(1)->print();
    } else {
        return instrTypeToString[type_] + " " + dest_->print() + ", " + operands_.at(0)->print();
    }
}

StoreInst::StoreInst(InstrType type, std::shared_ptr<Operand> src, std::shared_ptr<Operand> dest, std::shared_ptr<Operand> offset)
: Instruction(type, 3)
{
    static const std::set<Instruction::InstrType> valid_types = {
        SB, SH, SW, SD, FSW, FSD
    };

    if (valid_types.count(type) > 0) {
        if (src->type_ == Operand::Register && dest->type_ == Operand::Register && offset->type_ == Operand::Immediate) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, src %s, dest %s, offset %s", 
                    instrTypeToString[type].c_str(), src->print().c_str(), dest->print().c_str(), offset->print().c_str());
            LOG_FATAL("StoreInst type error, src and dest should be Register, offset should be Immediate");
        }
    } else {
        LOG_FATAL("StoreInst type error, %s not a StoreInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = src;
    operands_[1] = dest;
    operands_[2] = offset;
}


StoreInst::StoreInst(InstrType type, std::shared_ptr<Operand> src, std::shared_ptr<Operand> dest)
: Instruction(type, 2)
{
    static const std::set<Instruction::InstrType> valid_types = {
        SB, SH, SW, SD, FSW, FSD
    };

    if (valid_types.count(type) > 0) {
        if (src->type_ == Operand::Register && dest->type_ == Operand::Memory) {
            // 正确的指令类型和操作数类型
        } else {
            LOG_ERROR("Error Instruction: %s, src %s, dest %s", 
                    instrTypeToString[type].c_str(), src->print().c_str(), dest->print().c_str());
            LOG_FATAL("StoreInst type error, src should be Register, dest should be Memory");
        }
    } else {
        LOG_FATAL("StoreInst type error, %s not a StoreInst", instrTypeToString[type].c_str());
    }
    type_ = type;
    operands_[0] = src;
    operands_[1] = dest;
}

std::string StoreInst::print() const {
    if (op_nums_ == 3) {
        return instrTypeToString[type_] + " " + operands_.at(0)->print() + ", " + operands_.at(1)->print() + 
                ", " + operands_.at(2)->print();
    } else {
        return instrTypeToString[type_] + " " + operands_.at(0)->print() + ", " + operands_.at(1)->print();
    }
}


} // namespace riscv

} // namespace builder