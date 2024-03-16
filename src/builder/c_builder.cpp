#include "builder/c_builder.hpp"
#include "ir/ir.hpp"
#include "ir/ir_gen.hpp"
#include <unordered_set>
namespace builder
{
    std::unordered_set<std::shared_ptr<ir::BasicBlock>> processed_bbs;
// 处理基本块,这里的参数是传引用还是
void HandleBasicBlock(std::shared_ptr<ir::BasicBlock> bb, std::ofstream& out)
{

    // 检查是否已经处理过该基本块
    if (processed_bbs.find(bb) != processed_bbs.end())
    {
        return;
    }
    // 判断基本块是否为空
    if (bb->instructions_.empty())
    {
        return;
    }

    // 标记为已处理
    processed_bbs.insert(bb);

    // 1. 判断基本块有无前驱基本块，如果有，加入左大括号
    if (bb->pre_bbs_.size() > 0)
        out << "{ \n";
    // 2. 遍历基本块中指令列表,建立栈
    std::vector<std::shared_ptr<ir::Instruction>> stack;
    for (int k = 0; k < bb->instructions_.size(); k++)
    {
        std::shared_ptr<ir::Instruction> inst = bb->instructions_[k];
        // 2.1 遍历指令操作数，检查栈顶元素是否是当前指令的某个操作数，如果是则弹栈，否则入栈
        for (const auto &operand : inst->operands_)
        {
            // 将 std::weak_ptr<ir::Value> 转换为 std::shared_ptr<ir::Instruction>
            auto operandInstruction = std::dynamic_pointer_cast<ir::Instruction>(operand.lock());
            // 检查转换后的操作数是否为空
            if (operandInstruction)
            {
                while (!stack.empty() && stack.back() == operandInstruction)
                {
                    stack.pop_back();
                }
            }
        }
        stack.push_back(inst);
    }
    // 2.2 弹栈，从栈底开始弹出元素并输出到stream中,注意分号和大括号
    std::vector<std::shared_ptr<ir::Instruction>> tempStackVector;
        while (!stack.empty())
        {
            tempStackVector.push_back(stack.back());
            stack.pop_back();
        }

        while (!tempStackVector.empty())
        {
            std::shared_ptr<ir::Instruction> inst = tempStackVector.back();
            out << inst->print() << "\n";
            tempStackVector.pop_back();
        }

        // 3. 遍历后续基本块
    for (int k = 0; k < bb->succ_bbs_.size(); k++)
    {
        std::weak_ptr<ir::BasicBlock> nextBlock = bb->succ_bbs_[k];
        std::shared_ptr<ir::BasicBlock> nextBlockShared = nextBlock.lock();
        if (nextBlockShared)
        {
            HandleBasicBlock(nextBlockShared,out);
        }
    }
    // 4. 加入右大括号
    out << "} \n";
}

void CBuilder::build(ir::Module &program)
{
    // 1. 初始化 stream
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
        std::weak_ptr<ir::Function> func = program.functions_[i];
        // 4.1 加入函数头
        out << func.lock()->print() << "\n";
        // 4.2 加入函数左大括号
        out << "{\n";
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
            if (local->is_const_ && !isFuncParam )
            {
                out << local->type_->print() << " " << local->name_ << " = " << local->init_val_->print() << ";\n";
            }
            else
            {
                if (!isFuncParam )
                {
                    out << local->type_->print() << " " << local->name_ << ";\n";
                }
            }
        }
        // 4.4 遍历基本块
        for (int j = 0; j < func.lock()->basic_blocks_.size(); j++)
        {
            std::shared_ptr<ir::BasicBlock> bb = func.lock()->basic_blocks_[j];
            HandleBasicBlock(bb,out);
        }
        // 4.5 加入函数右大括号（main函数，需要特判）
        if (func.lock()->print() == "int main()")
        {
            out << "return 0;\n";
        }
        out << "}\n";
    }
}
void CBuilder::output(std::ofstream &out)
{
}

}
