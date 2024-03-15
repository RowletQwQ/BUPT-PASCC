#include "builder/c_builder.hpp"
#include "ir.hpp"
#include "ir_gen.hpp"
namespace builder
{
// 这里传引用函数传值？，参数问题
void HandleBasicBlock(std::shared_ptr<BasicBlock> &bb)
{

    // 1. 判断基本块有无前驱基本块，如果有，加入左大括号
    if (bb->pre_bbs_.size() > 0)
        out << "{ \n";
    // 2. 遍历基本块中指令列表,建立栈
    std::vector<std::shared_ptr<Instruction>> stack;
    for (int k = 0; k < bb->instructions_.size(); k++)
    {
        std::shared_ptr<Instruction> inst = bb->instructions_[k];
        // 遍历指令操作数，检查栈顶元素是否是当前指令的某个操作数，如果是则弹栈
        for (const auto &operand : inst->operands_)
        {
            while (!stack.empty() && stack.back() == operand)
            {
                stack.pop_back();
            }
        }
        // 将当前指令压入栈
        stack.push_back(inst->print());
    }
    // 3.
    // 弹栈，输出到ofstream中。注意，应该是，如果有后续基本块，最后一条语句不输出分号，但是如果遇到空白后继块呢？if语句和while语句没有分号，赋值语句后面应该有分号
    while (!stack.empty())
    {
        auto inst = stack.pop_back();
        out << inst->print() << ";\n";
        stack.pop_back();
    }
    // 4. 遍历基本块的后继基本块
    for (int k = 0; k < bb->succ_bbs_.size(); k++)
    {
        std::weak_ptr<BasicBlock> nextBlock = bb->succ_bbs_[k];
        HandleBasicBlock(nextBlock);
    }
    // 4.3.5 加入基本块右大括号
    out << "} \n";
}

void CBuilder::build(ir::Module &program)
{
    // 1. 初始化 ofstream
    std::ofstream out("G_SETTINGS.output_file");
    // 2. 加上 C 语言的头文件
    out << "#include <stdio.h>";
    out << "\n";
    // 3. 加上全局变量和常量
    for (const auto &global : program.global_identifiers_)
    {
        if (global->is_const_)
        {
            out << "const " + global->type_->print() << " " << global->name_ << " = " << global->init_val_->print()
                << "\n";
        }
        else
        {
            std::string s = global->type_->print();
            int ps = s.find(" ");
            if (ps == std::string::npos)
            {
                out << global->type_->print() << " " << global->name_ << "\n";
            }
            else
            {
                out << s.substr(0, ps) << " " << global->name_ << s.substr(ps + 1) << "\n";
            }
        }
    }
    // 4. 遍历函数
    for (int i = 0; i < program.functions_.size(); i++)
    {
        std::weak_ptr<Function> func = program.functions_[i];
        // 4.1 加入函数头
        out << func.lock()->print() << "\n";
        // 4.2 加入函数左大括号
        out << "{\n"
            // 4.3 加入局部标识符
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
            if (local->is_const_ && isFuncParam == false)
            {
                out << local->type_->print() << " " << local->name_ << " = " << local->init_val_->print() << ";\n";
            }
            else
            {
                if (isFuncParam == false)
                {
                    out << local->type_->print() << " " << local->name_ << ";\n";
                }
            }
        }
        // 4.3 遍历基本块
        for (int j = 0; j < func.lock()->basic_blocks_.size(); j++)
        {
            std::shared_ptr<BasicBlock> bb = func.lock()->basic_blocks_[j];
            HandleBasicBlock(bb);
        }
    }
}
void CBuilder::output(std::ofstream &out)
{
}
} // namespace builder
