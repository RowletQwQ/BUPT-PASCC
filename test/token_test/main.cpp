#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>

#include "../../src/token/token.hpp"

extern Token token;
extern int yylex();  // 在生成的 lex.yy.c 中定义的词法分析函数
extern void yy_scan_string(const char *str);  // 在生成的 lex.yy.c 中定义的字符串输入函数

int main() {
    // 遍历文件夹中的文件
    const std::string folderPath = "../../../open_set"; 
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
    // 输入数字 0 - 69 分别对应 70 个文件
    int fileIndex;
    std::cout << "Please input the index of the file you want to analyze: ";
    std::cin >> fileIndex;
    if (fileIndex < 0 || fileIndex >= files.size()) {
        std::cerr << "ERROR : Invalid index." << std::endl;
        return 1;
    }

    std::string fileName = files[fileIndex];
    std::ifstream ifs(folderPath + "/" + fileName);
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string content = ss.str();
    std::cout << "File: " << fileName << std::endl;
    
    // 词法分析
    yy_scan_string(content.c_str());
    // 定义 输出文件流
    int tokenType;
    while ((tokenType = yylex()) != 0) {
        std::cout << token.to_string() << std::endl;    
    }
    return 0;
}
