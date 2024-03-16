#include "opt/const_expr.hpp"

#include "common/log/log.hpp"
#include "ir/ir.hpp"
#include <memory>


namespace opt {



std::shared_ptr<ir::Literal> compute(std::shared_ptr<ir::Literal> l1, std::shared_ptr<ir::Literal> l2, ir::Instruction::OpID op) {
    // ir::Type::TID l_type = l1->type_->get_tid();
    // ir::Type::TID r_type = l2->type_->get_tid();
    // auto result_type = std::max(l_type, r_type);
    // if (result_type == ir::Type::TID::RealTID) {
    //     switch (op) {
    //         case ir::Instruction::OpID::Add:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_real() + l2->get_real());
    //         case ir::Instruction::OpID::Sub:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_real() - l2->get_real());
    //         case ir::Instruction::OpID::Mul:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_real() * l2->get_real());
    //         case ir::Instruction::OpID::Div:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_real() / l2->get_real());
    //         default:
    //             break;
    //     }
    // } else {
    //     switch(op) {
    //         case ir::Instruction::OpID::Add:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_int() + l2->get_int());
    //         case ir::Instruction::OpID::Sub:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_int() - l2->get_int());
    //         case ir::Instruction::OpID::Mul:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_int() * l2->get_int());
    //         case ir::Instruction::OpID::Div:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_int() / l2->get_int());
    //         case ir::Instruction::OpID::Mod:
    //             return std::make_shared<ir::Literal>(result_type, l1->get_int() % l2->get_int());
    //         default:
    //             break;
    //     }
    // }
    return nullptr;
}

//TODO: 实现常数表达式优化
std::shared_ptr<ir::Value> try_get_value(std::shared_ptr<ir::Value> val) {
    if(val->get_val_id() == ir::Value::ValueID::Literal) {
        return val;
    }
}

std::shared_ptr<ir::Instruction> binary_comp(std::shared_ptr<ir::Value> lhs,
    std::shared_ptr<ir::Value> rhs, ir::Instruction::OpID op) {
        if(!lhs || !rhs) {
            return nullptr;
        }
        if(lhs->get_val_id() != ir::Value::ValueID::Literal ||
            rhs->get_val_id() != ir::Value::ValueID::Literal) {
                return nullptr;
        }
        throw std::runtime_error("Not implemented yet");
}

std::shared_ptr<ir::Instruction> opt_binary_inst(std::shared_ptr<ir::BinaryInst> inst) {
    std::shared_ptr<ir::Value> lhs = try_get_value(inst->get_operand(0).lock());
    std::shared_ptr<ir::Value> rhs = try_get_value(inst->get_operand(1).lock());
    if (lhs->get_val_id() == ir::Value::ValueID::Literal &&
        rhs->get_val_id() == ir::Value::ValueID::Literal) {
            // 两个操作数都是常数, 可以进行计算
            auto result = binary_comp(lhs, rhs, inst->op_id_);
            if (!result) {
                LOG_ERROR("ConstExprOpt: failed to optimize binary expression, inst: %s", 
                        inst->print().c_str());
                return nullptr;
            }
            return result;
    } else if (lhs->get_val_id() == ir::Value::ValueID::Literal) {
        // 左操作数是常数
        inst->set_operand(0, lhs);
    }
    return nullptr;

}

void ConstExprOpt::optimize(ir::Module &program) {
    // 遍历基本块，找到所有表达式
    for (auto &func : program.functions_) {
        for(auto &bb: func->basic_blocks_) {
            for(auto &inst: bb->instructions_) {
                if (inst->is_assign_inst()) {
                    
                }
            }
        }
    }
}

} // namespace opt