

#include "builder.hpp"
#include "ir/ir.hpp"
#include "common/thpool/thpool.hpp"
#include "operand.hpp"

#include <future>
#include <memory>
#include <vector>
namespace builder {
namespace riscv {

// 声明线程唯一变量
thread_local std::shared_ptr<BasicBlock> cur_bb_;
thread_local std::shared_ptr<Function> cur_func_;
thread_local std::vector<std::shared_ptr<GlobalConst>> tmp_consts_;
thread_local std::shared_ptr<Operand> last_result_;

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

}
void RiscvBuilder::visit(const ir::BreakInst* inst) {

}
void RiscvBuilder::visit(const ir::ContinueInst* inst) {

}
void RiscvBuilder::visit(const ir::ContinueIncInst* inst) {

}
void RiscvBuilder::visit(const ir::BranchInst* inst) {

}
void RiscvBuilder::visit(const ir::Module* module) {

}
void RiscvBuilder::visit(const ir::BasicBlock* bb) {

}
void RiscvBuilder::visit(const ir::Function* func) {

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
    auto global_const = std::make_shared<GlobalConst>(literal->get_real(), literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralInt* literal) {
    auto global_const = std::make_shared<GlobalConst>(literal->get_int(), literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralString* literal) {
    auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralChar* literal) {
    auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
}

void RiscvBuilder::visit(const ir::LiteralBool* literal) {
    auto global_const = std::make_shared<GlobalConst>(literal->val_, literal->name_);
    modules_->add_const(global_const);
    tmp_consts_.emplace_back(global_const);
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
    auto global_const = std::make_shared<GlobalConst>(literal->get_real(), literal->name_);
    modules_->add_const(global_const);
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