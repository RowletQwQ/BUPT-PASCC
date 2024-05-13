#include "opt/const_expr.hpp"

#include "common/log/log.hpp"
#include "ir/ir.hpp"
#include <memory>


namespace opt {

const int MAX_DEPTH = 100;
ir::Module *prog = nullptr;

// 执行一元运算
std::shared_ptr<ir::Literal> compute(std::shared_ptr<ir::Literal> l1, ir::Instruction::OpID op, bool is_real) {
    if (is_real) {
        double val = l1->get_real();
        switch(op) {
            case ir::Instruction::OpID::Sub:
                return ir::Literal::make_literal(-val);
            case ir::Instruction::OpID::Null:
                return ir::Literal::make_literal(val);
            default:
                LOG_WARN("Unexpected Computation: %s %f", ir::Instruction::op_to_string(op).c_str(), val);
                LOG_WARN("OpID: %d", op);
                break; // 无法优化
        }
    } else {
        long val = l1->get_int();
        switch(op) {
            case ir::Instruction::OpID::Minus:
                return ir::Literal::make_literal(-val);
            case ir::Instruction::OpID::Not: case ir::Instruction::OpID::BitReverse:
                return ir::Literal::make_literal(~val);
            case ir::Instruction::OpID::Null:
                return ir::Literal::make_literal(val);
            default:
                LOG_ERROR("Unknown Operator ID: %d", op);
                break; // 无法优化
        }
    }
    return nullptr;

}

std::shared_ptr<ir::Literal> compute(std::shared_ptr<ir::Literal> l1, std::shared_ptr<ir::Literal> l2, ir::Instruction::OpID op, bool is_real) {
    if (is_real) {
        double lval = l1->get_real();
        double rval = l2->get_real();
        switch(op) {
            case ir::Instruction::OpID::Add:
                return ir::Literal::make_literal(lval + rval);
            case ir::Instruction::OpID::Sub:
                return ir::Literal::make_literal(lval - rval);
            case ir::Instruction::OpID::Mul:
                return ir::Literal::make_literal(lval * rval);
            case ir::Instruction::OpID::Div:
                return ir::Literal::make_literal(lval / rval);
            default:
                LOG_WARN("Unexpected Computation: %f %s %f", lval, ir::Instruction::op_to_string(op).c_str(), rval);
                break; // 无法优化
        }
    } else {
        long lval = l1->get_int();
        long rval = l2->get_int();
        switch(op) {
            case ir::Instruction::OpID::Add:
                return ir::Literal::make_literal(lval + rval);
            case ir::Instruction::OpID::Sub:
                return ir::Literal::make_literal(lval - rval);
            case ir::Instruction::OpID::Mul:
                return ir::Literal::make_literal(lval * rval);
            case ir::Instruction::OpID::Div:
                return ir::Literal::make_literal(lval / rval);
            case ir::Instruction::OpID::Mod:
                return ir::Literal::make_literal(lval % rval);
            case ir::Instruction::OpID::And: case ir::Instruction::OpID::AndThen:
                return ir::Literal::make_literal(lval && rval);
            case ir::Instruction::OpID::Or: case ir::Instruction::OpID::OrElse:
                return ir::Literal::make_literal(lval || rval);
            case ir::Instruction::OpID::Eq:
                return ir::Literal::make_literal(lval == rval);
            case ir::Instruction::OpID::Ne:
                return ir::Literal::make_literal(lval != rval);
            case ir::Instruction::OpID::Gt:
                return ir::Literal::make_literal(lval > rval);
            case ir::Instruction::OpID::Ge:
                return ir::Literal::make_literal(lval >= rval);
            case ir::Instruction::OpID::Lt:
                return ir::Literal::make_literal(lval < rval);
            case ir::Instruction::OpID::Le:
                return ir::Literal::make_literal(lval <= rval);
            default:
                LOG_ERROR("Unknown Operator ID: %d", op);
                break;
        }
    }
    return nullptr;
}


std::shared_ptr<ir::Value> opt_arith_inst(std::shared_ptr<ir::Instruction> inst, int depth) {
    if (!inst->is_arith_inst() || depth > MAX_DEPTH) {
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
                auto result = opt_arith_inst(lhs_inst, depth + 1);
                if(result) {
                    inst->set_operand(0, result);
                    prog->all_values_.emplace_back(result);
                }
            }
        }
        if(rhs->is_inst()) {
            auto rhs_inst = std::dynamic_pointer_cast<ir::Instruction>(rhs);
            if(rhs_inst->is_arith_inst()) {
                auto result = opt_arith_inst(rhs_inst, depth + 1);
                if(result) {
                    inst->set_operand(1, result);
                    prog->all_values_.emplace_back(result);
                }
            }
        }
        lhs = inst->get_operand(0).lock();
        rhs = inst->get_operand(1).lock();
        if (lhs->is_literal() && rhs->is_literal()) {
            auto lval = std::dynamic_pointer_cast<ir::Literal>(lhs);
            auto rval = std::dynamic_pointer_cast<ir::Literal>(rhs);
            auto result = compute(lval, rval, inst->get_op_id(), inst->is_real());
            return result;
        }
    } else if (inst->is_unary_inst()) {
        auto operand = inst->get_operand(0).lock();
        if(inst->op_id_ == ir::Instruction::OpID::Bracket) {
            // 括号表达式，进入内部
            opt_arith_inst(std::dynamic_pointer_cast<ir::Instruction>(operand), depth + 1);
        }
        if(operand->is_inst()) {
            auto operand_inst = std::dynamic_pointer_cast<ir::Instruction>(operand);
            if(operand_inst->is_arith_inst()) {
                auto result = opt_arith_inst(operand_inst, depth + 1);
                if(result) {
                    inst->set_operand(0, result);
                    prog->all_values_.emplace_back(result);
                }
            }
        }
        operand = inst->get_operand(0).lock();
        if (operand->is_literal()) {
            auto val = std::dynamic_pointer_cast<ir::Literal>(operand);
            auto result = compute(val, inst->get_op_id(), inst->is_real());
            return result;
        }
    }
    return inst;
}

void ConstExprOpt::optimize(ir::Module &program) {
    // 遍历基本块，找到所有表达式
    prog = &program;
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
                                    auto result = opt_arith_inst(array_inst, 0);
                                    if(result) {
                                        inst_ptr->set_operand(1, result);
                                        program.all_values_.emplace_back(result);
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
                    auto rval = inst->get_operand(1).lock();
                    if (rval->is_inst()) {
                        auto inst_ptr = std::dynamic_pointer_cast<ir::Instruction>(rval);
                        if (inst_ptr->is_arith_inst()) {
                            auto result = opt_arith_inst(inst_ptr, 0);
                            if(result) {
                                inst->set_operand(1, result);
                                program.all_values_.emplace_back(result);
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
                            auto result = opt_arith_inst(inst_ptr, 0);
                            if(result) {
                                inst->set_operand(0, result);
                                program.all_values_.emplace_back(result);
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
                                auto result = opt_arith_inst(inst_ptr, 0);
                                if(result) {
                                    inst->set_operand(i, result);
                                    program.all_values_.emplace_back(result);
                                }
                            } else if (inst_ptr->is_array_visit_inst()) {
                                while (inst_ptr->is_array_visit_inst()) {
                                    // 如果是数组访问，则进行优化（第二个操作数一定是一个计算表达式）
                                    auto array_ptr = inst_ptr->get_operand(1).lock();
                                    if (array_ptr->is_inst()) {
                                        auto array_inst = std::dynamic_pointer_cast<ir::Instruction>(array_ptr);
                                        if (array_inst->is_arith_inst()) {
                                            auto result = opt_arith_inst(array_inst, 0);
                                            if(result) {
                                                inst_ptr->set_operand(1, result);
                                                program.all_values_.emplace_back(result);
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