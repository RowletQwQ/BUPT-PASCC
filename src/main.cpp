
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "builder/riscv/builder.hpp"
#include "common/thpool/thpool.hpp"
#include "common/log/log.hpp"
#include "opt/opt.hpp"
#include "ast/stmt.hpp"
#include "ir/ir_gen.hpp"
#include "common/setting/settings.hpp"
#include "builder/c/c_builder.hpp"
#include "opt/const_expr.hpp"
#include "parser/yacc_pascal.hpp"
#include "builder/c/c_builder.hpp"

int code_parse(const char *code, ProgramStmt **program_stmt);

void init_env()
{
    if (G_SETTINGS.output_file.empty())
    {
        size_t pos = G_SETTINGS.input_file.find_last_of('.');
        if (pos == std::string::npos)
        {
            if(G_SETTINGS.is_asm) {
                G_SETTINGS.output_file = G_SETTINGS.input_file + ".s";
            } else {
                G_SETTINGS.output_file = G_SETTINGS.input_file + ".c";
            }
        }
        else
        {
            if (G_SETTINGS.is_asm)
                G_SETTINGS.output_file = G_SETTINGS.input_file.substr(0, pos) + ".s";
            else
                G_SETTINGS.output_file = G_SETTINGS.input_file.substr(0, pos) + ".c";
        }
        pos = G_SETTINGS.input_file.find_last_of("/\\");
        std::string filename;
        if (pos != std::string::npos)
            filename = G_SETTINGS.input_file.substr(pos + 1);
        else
            filename = G_SETTINGS.input_file;

        

        LOG_DEBUG("Output file: %s", G_SETTINGS.output_file.c_str());
        // 检测文件是否存在
        // std::ifstream file(G_SETTINGS.output_file);
        // if (file.is_open())
        // {
        //     if (file.peek() != std::ifstream::traits_type::eof())
        //     {
        //         // 文件已经存在且不为空
        //         LOG_WARN("Non-empty output file already exists: %s", G_SETTINGS.output_file.c_str());
        //         LOG_WARN("Program exited.");
        //         exit(0);
        //     }
        // }
    }
#ifndef ONLINE_JUDGE
    switch (G_SETTINGS.log_level)
    {
        case 0:
            common::g_log = new common::Log(common::FATAL);
            break;
        case 1:
            common::g_log = new common::Log(common::ERROR);
            break;
        case 2:
            common::g_log = new common::Log(common::WARN);
            break;
        case 3:
            common::g_log = new common::Log(common::INFO);
            break;
        case 4:
            common::g_log = new common::Log(common::DEBUG);
            break;
        default:
            common::g_log = new common::Log(common::WARN);
            break;
    }
#endif
    common::g_thpool = new common::ThreadPool(G_SETTINGS.thread_num);
    
}

int main(int argc, char *argv[])
{
    // 解析命令行参数
    G_SETTINGS.parse_args(argc, argv);
    // 初始化环境
    init_env();
    // 管理线程池
    std::unique_ptr<common::ThreadPool> thpool(common::g_thpool);
    // 管理日志
    std::unique_ptr<common::Log> log(common::g_log);
    // 从输入文件中读取代码
    std::ifstream input_file(G_SETTINGS.input_file);
    if (!input_file.is_open())
    {
        LOG_FATAL("Can't open input file: %s", G_SETTINGS.input_file.c_str());
    }
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string code = buffer.str();
    input_file.close();
    // 第一步：词法分析 and 语法分析
    LOG_DEBUG("Start parsing code...");
    ProgramStmt* program_stmt;
    int ret = code_parse(code.c_str(), &program_stmt);
    if (ret != 0)
    {
        LOG_ERROR("Parsing code failed.");
        return ret;
    }
    LOG_DEBUG("Parsing code done.");
    if(!program_stmt) {
        LOG_FATAL("Program exit");
        return -1;
    }
    // 第二步: 语义分析 & 生成中间代码
    LOG_DEBUG("Start generating intermediate code...");
    std::unique_ptr<ir::IRGenerator> visitor = std::make_unique<ir::IRGenerator>();
    visitor->visit(*program_stmt);
    std::unique_ptr<ProgramStmt> program_stmt_ptr(program_stmt);
    //visitor->show_result();
    ir::Module ir = visitor->get_ir();
    LOG_DEBUG("Generating intermediate code done.");
    // 第三步: 优化
    if (G_SETTINGS.opt_level)
    {
        LOG_DEBUG("Start optimizing intermediate code...");
        // TODO
        std::vector<std::unique_ptr<opt::Optimize>> opts;
        opts.emplace_back(std::make_unique<opt::ConstExprOpt>());
        for (auto &opt : opts)
        {
            LOG_DEBUG("Optimizing with %s...", opt->get_name().c_str());
            opt->optimize(ir);
            LOG_DEBUG("Optimizing with %s done.", opt->get_name().c_str());
        }
        LOG_DEBUG("Optimizing intermediate code done.");
    }
    // 第四步: 生成目标代码
    std::ofstream output_file(G_SETTINGS.output_file);
    LOG_DEBUG("Start generating target code...");
    if(G_SETTINGS.is_asm) {
        LOG_INFO("Generating RISC-V assembly code...");
        std::unique_ptr<builder::riscv::RiscvBuilder> builder = std::make_unique<builder::riscv::RiscvBuilder>();
        builder->build(ir);
        builder->output(output_file);
    } else {
        LOG_INFO("Generating C code...");
        std::unique_ptr<builder::c::CBuilder> builder = std::make_unique<builder::c::CBuilder>();
        builder->build(ir);
        builder->output(output_file);
    }
    
    LOG_DEBUG("Generating target code done.");
    
    return 0;
}