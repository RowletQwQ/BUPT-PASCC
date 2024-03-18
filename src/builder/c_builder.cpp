#include "builder/c_builder.hpp"
#include "common/log/log.hpp"
#include "ir/ir.hpp"
#include "ir/ir_gen.hpp"
#include <unordered_set>
#include <sstream>
namespace builder
{
    std::stringstream output;
    std::unordered_set<const ir::BasicBlock *>processed_bbs;
// 处理基本块
void HandleBasicBlock(std::string prefix, std::shared_ptr<ir::BasicBlock> bb, std::stringstream& out)
{
    // 检查是否已经处理过该基本块
    if (processed_bbs.find(bb.get()) != processed_bbs.end())
    {
        return;
    }
    // 判断基本块是否为空
    if (bb->instructions_.empty())
    {
        if (bb->name_ == "body_basic_block" || bb->name_=="then_basic_block") {
            out << "{}";
        }
        return;
    }
    // 标记为已处理
    processed_bbs.insert(bb.get());

    if(bb->name_=="body_basic_block" || bb->name_=="then_basic_block" || bb->name_ == "body_begin_basic_block"){
        out<< prefix <<"{\n";
    }
    if(bb->name_=="else_basic_block"){
        out<< prefix <<"else {\n";
    }
    // 2. 遍历基本块中指令列表
    for (int k = 0; k < bb->instructions_.size(); k++)
    {
        std::shared_ptr<ir::Instruction> inst = bb->instructions_[k];
        if(inst->op_id_== ir::Instruction::OpID::Br){
            out << prefix << inst->print() << "\n";
        }
        else{
            out << prefix <<inst->print() << ";\n";
        }


    }

    // 3. 遍历后续基本块
    for (int k = 0; k < bb->succ_bbs_.size(); k++)
    {
        std::weak_ptr<ir::BasicBlock> nextBlock = bb->succ_bbs_[k];
        std::shared_ptr<ir::BasicBlock> nextBlockShared = nextBlock.lock();
        if (nextBlockShared)
        {
            HandleBasicBlock(prefix + "\t", nextBlockShared, out);
        }
    }
    if(bb->name_=="body_basic_block"||bb->name_=="then_basic_block"|| bb->name_=="else_basic_block" || bb->name_ == "body_end_basic_block"){
        out<< prefix <<"}\n";
    }
}

void CBuilder::build(ir::Module &program)
{
    // 1. 初始化 stream
    std::stringstream out;
//    std::ofstream out("G_SETTINGS.output_file");
    // 2. 加上 C 语言的头文件
    out << "#include <stdio.h>\n";
    out << "#include <stdlib.h>\n";
    out << "#include <signal.h>\n";
    out << "#include <unistd.h>\n";
    // 2.1 注册一个超时处理函数
    out << "void timeout_handler(int sig) {\n";
    out << "\tprintf(\"Timeout!\\n\");\n";
    out << "\texit(0);\n";
    out << "}\n";

    // 3. 加上全局变量和常量
    for (const auto &global : program.global_identifiers_)
    {
        if (global->is_const_)
        {
            out << "const " + global->type_->print() << " " << global->name_ << " = " << global->init_val_->print()
                << ";\n";
        }
        else
        {
            std::string s = global->type_->print();
            int ps = s.find(" ");
            if (ps == std::string::npos)
            {
                out << global->type_->print() << " " << global->name_ << ";\n";
            }
            else
            {
                out << s.substr(0, ps) << " " << global->name_ << s.substr(ps + 1) << ";\n";
            }
        }
    }
    // 4. 遍历函数
    for (int i = 0; i < program.functions_.size(); i++)
    {
        std::weak_ptr<ir::Function> func = program.functions_[i];
        // 4.1 加入函数头
        out << func.lock()->print() << "\n";
        // 4.2 加入函数左大括号
        out << "{\n";
        if (func.lock()->print() == "int main()") {
            // 如果是 main 函数，注册超时处理函数
            out << "\tsignal(SIGALRM, timeout_handler);\n";
            out << "\talarm(1);\n";
        }
        // 4.3 加入局部标识符
        // 一上来先先加上代表函数的一个变量, 这个变量名字是函数名加上下划线
        if (func.lock()->func_type_.lock()->result_->tid_ != ir::Type::VoidTID) { // 如果不是 procedure
            std::string typeStr = func.lock()->func_type_.lock()->result_->print();
            out << typeStr << " " << func.lock()->name_ << "_;\n";
        }

        for (const auto &local : func.lock()->local_identifiers_)
        {
            // 遍历函数参数列表，排除函数参数
            bool isFuncParam = false;
            for (const auto &local_args : func.lock()->args_)
            {
                if (local->name_ == local_args->name_)
                {
                    isFuncParam = true;
                    break;
                }
            }
            if (local->is_const_ && !isFuncParam )
            {
                out << "const " + local->type_->print() << " " << local->name_ << " = " << local->init_val_->print() << ";\n";
            }
            else
            {
                if (!isFuncParam)
                {
                    std::string s = local->type_->print();
                    int ps = s.find(" ");
                    if (ps == std::string::npos)
                    {
                        out << local->type_->print() << " " << local->name_ << ";\n";
                    }
                    else
                    {
                        out << s.substr(0, ps) << " " << local->name_ << s.substr(ps + 1) << ";\n";
                    }
                }
            }
        }
        // 4.4 遍历基本块
        for (int j = 0; j < func.lock()->basic_blocks_.size(); j++)
        {
            std::shared_ptr<ir::BasicBlock> bb = func.lock()->basic_blocks_[j];
            HandleBasicBlock("", bb, out);
        }
        // 4.5 加入函数右大括号（main函数，需要特判）
        if (func.lock()->print() == "int main()")
        {
            out << "return 0;\n";
        } else if (func.lock()->func_type_.lock()->result_->tid_ != ir::Type::VoidTID) {
            out << "return " + func.lock()->name_ + "_;\n"; 
        }
        out << "}\n";
    }
    code_ = out.str();
    LOG_DEBUG("CBuilder: code generated");
}
void CBuilder::output(std::ofstream &out)
{
    out << code_;
}

}
