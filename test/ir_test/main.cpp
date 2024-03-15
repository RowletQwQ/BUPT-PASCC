#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>



#include "common/log/log.hpp"
#include "opt/opt.hpp"
#include "ast/stmt.hpp"
#include "ir/ir_gen.hpp"
#include "common/setting/settings.hpp"
#include "parser/yacc_pascal.hpp"

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
}

int main(int argc, char *argv[])
{
    // 解析命令行参数
    G_SETTINGS.parse_args(argc, argv);
    // 初始化环境
    init_env();
    const std::string folderPath = G_SETTINGS.input_file;
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
        std::string fileName = ent->d_name;
        if (fileName != "." && fileName != "..") {
            files.push_back(fileName);
        }
        }
        closedir(dir);
    } else {
        std::cerr << "ERROR : Could not open directory." << std::endl;
        return 1;
    }

    std::sort(files.begin(), files.end());
    for (size_t i = 0; i < files.size(); i++) {
        // 识别出第fileIndex个 以 .pas 结尾的文件
        if (files[i].find(".pas") == std::string::npos) {
            files.erase(files.begin() + i);
            i--;
        }
    }

    for(auto &file: files) {
        std::string fileName = folderPath + "/" + file;
        std::ifstream ifs(fileName);
        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string content = ss.str();
        ifs.close();
        // 第一步：词法分析 and 语法分析
        LOG_DEBUG("Start parsing code..., File: %s", fileName.c_str());
        ProgramStmt *program = nullptr;
        code_parse(content.c_str(), &program);
        if (program == nullptr) {
            LOG_FATAL("ERROR : Parsing failed.");
            break;
        } else {
            LOG_INFO("File %s Parsing succeeded.", fileName.c_str());
        }
        
        LOG_DEBUG("Parsing code done. File: %s", fileName.c_str());
        // 第二步: 语义分析 & 生成中间代码
        LOG_DEBUG("Start generating intermediate code... File: %s", fileName.c_str());

        try {
            std::unique_ptr<ir::IRGenerator> visitor = std::make_unique<ir::IRGenerator>();
            visitor->visit(*program);
            visitor->show_result();
            ir::Module ir = visitor->get_ir();
        } catch (const std::exception& e) {
            delete program;
            LOG_FATAL("ERROR : %s", e.what());
            break;
        }
        delete program;
    }
    
    return 0;
}