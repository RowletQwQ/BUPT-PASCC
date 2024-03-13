#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>



#include "common/log/log.hpp"
#include "opt/opt.hpp"
#include "ast/stmt.hpp"
#include "ir/ir_gen.hpp"
#include "common/setting/settings.hpp"
#include "parser/yacc_pascal.hpp"
#include "builder/c_builder.hpp"

void code_parse(const char *code, ProgramStmt **program_stmt);

void init_env()
{
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
    if (G_SETTINGS.output_file.empty())
    {
        size_t pos = G_SETTINGS.input_file.find_last_of('.');
        if (pos == std::string::npos)
        {
            G_SETTINGS.output_file = G_SETTINGS.input_file + ".c";
        }
        else
        {
            G_SETTINGS.output_file = G_SETTINGS.input_file.substr(0, pos) + ".c";
        }

        LOG_DEBUG("Output file: %s", G_SETTINGS.output_file.c_str());
    }

    
    
}

int main(int argc, char *argv[])
{
    // 解析命令行参数
    G_SETTINGS.parse_args(argc, argv);
    // 初始化环境
    init_env();

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
    code_parse(code.c_str(), &program_stmt);
    LOG_DEBUG("Parsing code done.");
    // 第二步: 语义分析 & 生成中间代码
    LOG_DEBUG("Start generating intermediate code...");
    
    std::unique_ptr<ir::IRGenerator> visitor = std::make_unique<ir::IRGenerator>();

    visitor->visit(*program_stmt);
    visitor->show_result();
    ir::Module ir = visitor->get_ir();


    
    LOG_DEBUG("Generating intermediate code done.");
    // 第三步: 优化
    if (G_SETTINGS.opt_level)
    {
        LOG_DEBUG("Start optimizing intermediate code...");
        // TODO
        std::vector<opt::Optimize> opts;

        for (auto &opt : opts)
        {
            opt.optimize(ir);
        }
        LOG_DEBUG("Optimizing intermediate code done.");
    }

    // TODO: 删除
    return 0;
    // 第四步: 生成目标代码
    std::ofstream output_file(G_SETTINGS.output_file);
    // TODO
    LOG_DEBUG("Start generating target code...");
    std::unique_ptr<builder::CBuilder> builder = std::make_unique<builder::CBuilder>();
    builder->build(ir);
    builder->output(output_file);
    LOG_DEBUG("Generating target code done.");

    return 0;
}