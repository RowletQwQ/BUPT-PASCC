

#include "builder/riscv/operand.hpp"
#include "common/log/log.hpp"
#include <string>
namespace builder {
namespace riscv {
    

Register::Register(Register::RegType reg_type, int reg_id /* = -1*/) 
: Operand(Operand::Register), reg_type_(reg_type)
{
    // 判断reg_id是否在范围内
    if(reg_type == RegType::Temp && (reg_id < 0 || reg_id > 6)) {
        LOG_FATAL("There is no t%d register in RISC-V", reg_id);
    } else if (reg_type == Saved && (reg_id < 0 || reg_id > 11)) {
        LOG_FATAL("There is no s%d register in RISC-V", reg_id);
    } else if (reg_type == IntArg || reg_type == FloatArg && (reg_id < 0 || reg_id > 7)) {
        LOG_FATAL("There is no a%d register in RISC-V", reg_id);
    } else if (reg_type == Float && (reg_id < 8 || reg_id > 31)) {
        if(reg_id < 0 || reg_id > 7) {
            LOG_FATAL("Trying to use args register as a universal reg");
        } else {
            LOG_FATAL("There is no f%d register in RISC-V", reg_id);
        }
    }
    reg_id_ = reg_id;
    switch(reg_type_) {
        case RegType::Zero:
            reg_unique_id_ = 0;
            break;
        case RegType::Return:
            reg_unique_id_ = 1;
            break;
        case RegType::Stack:
            reg_unique_id_ = 2;
            break;
        case RegType::Thread:
            reg_unique_id_ = 3;
            break;
        case RegType::Temp:
            reg_unique_id_ = 5 + reg_id_;
            break;
        case RegType::Frame:
            reg_unique_id_ = 8;
            break;
        case RegType::Saved:
            reg_unique_id_ = 8 + reg_id_;
            break;
        case RegType::IntArg:
            reg_unique_id_ = 10 + reg_id_;
            break;
        case RegType::FloatArg:
            reg_unique_id_ = 33 + reg_id_;
            break;
        case RegType::Float:
            reg_unique_id_ = 32 + reg_id_;
            break;
        default:
            LOG_FATAL("Unknown register type");
    }
}

std::string Register::print() const {
    switch(reg_type_) {
        case RegType::Zero:
            return "zero";
        case RegType::Return:
            return "ra";
        case RegType::Stack:
            return "sp";
        case RegType::Thread:
            return "gp";
        case RegType::Temp:
            return "t" + std::to_string(reg_id_);
        case RegType::Frame:
            return "s0";
        case RegType::Saved:
            return "s" + std::to_string(reg_id_);
        case RegType::IntArg:
            return "a" + std::to_string(reg_id_);
        case RegType::Float: case RegType::FloatArg:
            return "f" + std::to_string(reg_id_);
        default:
            LOG_FATAL("Unknown register type");
    }
}

std::string Immediate::print() const {
    switch (imm_type_) {
        case ImmType::Int32:
            return std::to_string(imm_i32_);
        case ImmType::Int64:
            return std::to_string(imm_i64_);
        case ImmType::Float32:
            return std::to_string(imm_f32_);
        case ImmType::Float64:
            return std::to_string(imm_f64_);
    }
}

std::string Label::print() const {
    return name_ + ":";
}

std::string GlobalConst::print() const {
    static std::map<GlobalConst::ConstType, std::string> type2str = {
        {Word, ".word"}, {DWord, ".dword"}, {Float, ".float"}, {Double, ".double"}, {ASCIIZ, ".asciiz"}
    };
    switch(type_) {
        case Word:
            return name_ + ": .word " + std::to_string(i32_);
        case DWord:
            return name_ + ": .dword " + std::to_string(i64_);
        case Float:
            return name_ + ": .float " + std::to_string(f32_);
        case Double:
            return name_ + ": .double " + std::to_string(f64_);
        case ASCIIZ:
            return name_ + ": .asciiz \"" + str_val_ + "\"";
        case ARRAY:
            break;
        default:
            LOG_FATAL("Unknown global const type");
    }
    std::vector<std::shared_ptr<GlobalConst>> res;
    for(auto &val : array_val_) {
        if (val->type_ == ARRAY) {
            auto tmp = val->unpackArray();
            res.insert(res.end(), tmp.begin(), tmp.end());
        } else {
            res.emplace_back(val);
        }
    }
    auto type = res[0]->type_;
    std::string s = name_ + ": " + type2str[type] + " ";

    for(auto &val : res) {
        switch(type) {
            case Word:
                s += std::to_string(val->i32_) + ",";
                break;
            case DWord:
                s += std::to_string(val->i64_) + ",";
                break;
            case Float:
                s += std::to_string(val->f32_) + ",";
                break;
            case Double:
                s += std::to_string(val->f64_) + ",";
                break;
            case ASCIIZ:
                s += "\"" +val->str_val_ + "\",";
                break;
            default:
                LOG_FATAL("Unknown global const type");
        }
    }
    s.pop_back();
    return s;
}

std::vector<std::shared_ptr<GlobalConst>> GlobalConst::unpackArray() const {
    std::vector<std::shared_ptr<GlobalConst>> res;
    for(auto &val : array_val_) {
        if (val->type_ == ARRAY) {
            auto tmp = val->unpackArray();
            res.insert(res.end(), tmp.begin(), tmp.end());
        } else {
            res.emplace_back(val);
        }
    }
    return res;
}

std::string Memory::print() const {
    // 内存访问总是形如 4(x5)诸如此样
    return offset_->print() + "(" + base_->print() + ")";
}

std::string GlobalId::print() const {
    return name_ + ": .space" + std::to_string(size_);
}

// Function::Function(const std::string &name, int num_args, OpType ret_type) 
// : Label(OpType::Function, name), num_args_(num_args), ret_type_(ret_type)
// {
//     args_.resize(num_args);
// }

// void Function::setArgs(int index, std::shared_ptr<Operand> op) {
//     if(index >= num_args_ || index < 0) {
//         LOG_FATAL("Index out of range");
//     }
//     args_[index] = op;
// }

} // namespace riscv
} // namespace builder