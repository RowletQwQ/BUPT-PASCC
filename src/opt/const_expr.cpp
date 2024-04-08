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
    throw std::runtime_error("Not implemented");
}


std::shared_ptr<ir::Value> opt_arith_inst(std::shared_ptr<ir::Instruction> inst) {
    if (!inst->is_arith_inst()) {
        // 不是算术表达式，直接返回
        return inst;
    }
    if (inst->is_binary_inst()) {
        // 二元表达式计算优化
        auto lhs = inst->get_operand(0).lock();
        auto rhs = inst->get_operand(1).lock();
        if(lhs->is_inst()) {
            auto lhs_inst = std::dynamic_pointer_cast<ir::Instruction>(lhs);
            if(lhs_inst->is_arith_inst()) {
                auto result = opt_arith_inst(lhs_inst);
                if(result) {
                    inst->set_operand(0, result);
                }
            }
        }
        if(rhs->is_inst()) {
            auto rhs_inst = std::dynamic_pointer_cast<ir::Instruction>(rhs);
            if(rhs_inst->is_arith_inst()) {
                auto result = opt_arith_inst(rhs_inst);
                if(result) {
                    inst->set_operand(1, result);
                }
            }
        }
        lhs = inst->get_operand(0).lock();
        rhs = inst->get_operand(1).lock();
        if (lhs->is_literal() && rhs->is_literal()) {
            auto lval = std::dynamic_pointer_cast<ir::Literal>(lhs);
            auto rval = std::dynamic_pointer_cast<ir::Literal>(rhs);
            auto result = compute(lval, rval, inst->get_op_id());
            return result;
        }
    }
    throw std::runtime_error("Not implemented");
}

void ConstExprOpt::optimize(ir::Module &program) {
    // 遍历基本块，找到所有表达式
    for (auto &func : program.functions_) {
        for(auto &bb: func->basic_blocks_) {
            for(auto &inst: bb->instructions_) {
                // 之所以用这种遍历方式，是为了避免将被抛弃的表达式再度进行优化
                if (inst->is_assign_inst()) {
                    auto ptr = inst->get_operand(0).lock();
                    if (ptr->is_inst()) {
                        auto inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(ptr);
                        while (inst_ptr->is_array_visit_inst()) {
                            // 如果是数组访问，则进行优化（第二个操作数一定是一个计算表达式）
                            auto array_ptr = inst_ptr->get_operand(1).lock();
                            if (array_ptr->is_inst()) {
                                auto array_inst = std::dynamic_pointer_cast<ir::Instruction>(array_ptr);
                                if (array_inst->is_arith_inst()) {
                                    auto result = opt_arith_inst(array_inst);
                                    if(result) {
                                        inst_ptr->set_operand(1, result);
                                    }
                                }
                            }
                            ptr = inst_ptr->get_operand(0).lock();
                            if (ptr->is_inst()) {
                                inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(ptr);
                            } else {
                                break;
                            }
                        }
                    }
                } else if (inst->is_br_inst()) {
                    // 分支语句的compare条件可能可以优化
                    auto cond = inst->get_operand(0).lock();
                    if (cond->is_inst()) {
                        // 如果此处不是常数，尝试优化
                        auto inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(cond);
                        if (inst_ptr->is_arith_inst()) {
                            auto result = opt_arith_inst(inst_ptr);
                            if(result) {
                                inst->set_operand(0, result);
                            }
                        }
                    }
                } else if (inst->is_io_inst()) {
                    unsigned op_num = inst->get_num_ops();
                    for (unsigned i = 0; i < op_num; i++) {
                        auto ptr = inst->get_operand(i).lock();
                        if (ptr->is_inst()) {
                            auto inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(ptr);
                            if (inst_ptr->is_arith_inst()) {
                                auto result = opt_arith_inst(inst_ptr);
                                if(result) {
                                    inst->set_operand(i, result);
                                }
                            } else if (inst_ptr->is_array_visit_inst()) {
                                while (inst_ptr->is_array_visit_inst()) {
                                    // 如果是数组访问，则进行优化（第二个操作数一定是一个计算表达式）
                                    auto array_ptr = inst_ptr->get_operand(1).lock();
                                    if (array_ptr->is_inst()) {
                                        auto array_inst = std::dynamic_pointer_cast<ir::Instruction>(array_ptr);
                                        if (array_inst->is_arith_inst()) {
                                            auto result = opt_arith_inst(array_inst);
                                            if(result) {
                                                inst_ptr->set_operand(1, result);
                                            }
                                        }
                                    }
                                    ptr = inst_ptr->get_operand(0).lock();
                                    if (ptr->is_inst()) {
                                        inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(ptr);
                                    } else {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

} // namespace opt