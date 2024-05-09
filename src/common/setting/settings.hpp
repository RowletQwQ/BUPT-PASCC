#pragma once

#include <string>
namespace common {


class Settings {
public:
    std::string output_file;
    std::string input_file;
    int log_level;
    int opt_level;
    int thread_num;

    Settings() : output_file(""), input_file(""), log_level(-1), opt_level(0), thread_num(4) {}

    /**
     * @brief 解析命令行参数
     * 
     * @param argc 命令行参数个数
     * @param argv 命令行参数
     */
    void parse_args(int argc,char *argv[]);


    /**
     * @brief 输出帮助信息
     */
    void say_help();

    /**
     * @brief 获取设置的单例
     * 
     * @return Settings& 
     */
    static Settings &get_instance();
};

#define G_SETTINGS common::Settings::get_instance()

} // namespace common
