#include "opt/const_expr.hpp"

#include "common/log/log.hpp"
#include "ir/ir.hpp"
#include <memory>


namespace opt {

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
            for(auto &inst: bb.lock()->instructions_) {
                if (inst->is_expr()) {
                    if(inst->is_binary_inst()) {
                        // 二元表达式, 试着将操作数转换为常数
                        auto result = opt_binary_inst(std::dynamic_pointer_cast<ir::BinaryInst>(inst));
                        if(result) {
                            // 替换原指令
                            inst = result;
                        }
                    }
                }
            }
        }
    }
}

}