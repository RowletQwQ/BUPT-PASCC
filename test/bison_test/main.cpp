#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>

#include "ast/stmt.hpp"
#include "ast/stmt_test.hpp"
#include "common/log/log.hpp"
extern int code_parse(const char * code_str, ProgramStmt ** program);

void single_point_test(const std::string folderPath , std::vector<std::string> files){
    // 输入数字 0 - 69 分别对应 70 个文件
  int fileIndex;
  std::cout << "Please input the index of the file you want to analyze: ";
  std::cin >> fileIndex;
  if (fileIndex < 0 || fileIndex >= files.size()) {
      std::cerr << "ERROR : Invalid index." << std::endl;
  }
  std::string fileName = files[fileIndex];
  std::ifstream ifs(folderPath + "/" + fileName);
  std::stringstream ss;
  ss << ifs.rdbuf();
  std::string content = ss.str();
  std::cout << "File: " << fileName << std::endl;
  ProgramStmt * program = nullptr;
  code_parse(content.c_str(), &program);
  
  if(program == nullptr) {
      std::cerr << "ERROR : Parsing failed." << std::endl;
  }else{
      std::cout << "Parsing succeeded." << std::endl;
  }
  std::cout<<program_stmt_str(program, 0)<<std::endl;
}

void batch_test(int beginIndex,const std::string folderPath , std::vector<std::string> files){
    for(int i = beginIndex; i < files.size(); i++) {
        std::string fileName = files[i];
        std::ifstream ifs(folderPath + "/" + fileName);
        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string content = ss.str();
        ProgramStmt * program = nullptr;
        code_parse(content.c_str(), &program);
        if(program == nullptr) {
            std::cout << fileName << " : Parsing failed." << std::endl;
        }else{
            std::cout << fileName << " : Parsing succeeded." << std::endl;
        }
    }
}


int main() {
  common::g_log = new common::Log(common::FATAL);
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
  
  
  for(int i = 0; i < files.size(); i++) {
      // 识别出第fileIndex个 以 .pas 结尾的文件
      if (files[i].find(".pas") == std::string::npos) {
          files.erase(files.begin() + i);
          i--;
      }
  }
    // 
    batch_test(0,folderPath,files);
    // single_point_test(folderPath,files);
  
  return 0;
}