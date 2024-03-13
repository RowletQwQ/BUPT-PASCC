#include <algorithm>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <dirent.h>

#include "ast/stmt.hpp"
#include "ast/stmt_test.hpp"
#include "common/log/log.hpp"

extern int code_parse(const char * code_str, ProgramStmt ** program);

void single_point_test(const std::string folderPath , std::vector<std::string> files){
    // 输入数字 0 - 69 分别对应 70 个文件
  size_t fileIndex;
  std::cout << "Please input the index of the file you want to analyze: ";
  std::cin >> fileIndex;
  if (fileIndex >= files.size()) {
      LOG_FATAL("ERROR : Invalid index.");
  }
  std::string fileName = files[fileIndex];
  std::ifstream ifs(folderPath + "/" + fileName);
  std::stringstream ss;
  ss << ifs.rdbuf();
  std::string content = ss.str();
  LOG_INFO("File: %s",fileName.c_str());
  ProgramStmt * program = nullptr;
  code_parse(content.c_str(), &program);
  
  if(program == nullptr) {
      LOG_FATAL("ERROR : Parsing failed.");
  }else{
      LOG_INFO("File %s Parsing succeeded.", fileName.c_str());
      //std::cout<<program_stmt_str(program, 0)<<std::endl;
      delete program;
  }
}

void batch_test(int beginIndex,const std::string folderPath , std::vector<std::string> files){
    for(size_t i = beginIndex; i < files.size(); i++) {
        std::string fileName = files[i];
        std::ifstream ifs(folderPath + "/" + fileName);
        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string content = ss.str();
        ProgramStmt * program = nullptr;
        code_parse(content.c_str(), &program);
        if(program == nullptr) {
            LOG_FATAL("ERROR : Parsing failed.");
            break;
        }else{
            LOG_INFO("File %s Parsing succeeded.",  fileName.c_str());
        }
        delete program;
        //std::cout<<program_stmt_str(program, 0)<<std::endl;
    }
}


int main() {
  
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
  
  std::sort(files.begin(), files.end());
  for(size_t i = 0; i < files.size(); i++) {
      // 识别出第fileIndex个 以 .pas 结尾的文件
      if (files[i].find(".pas") == std::string::npos) {
          files.erase(files.begin() + i);
          i--;
      }
  }
    // 
    common::g_log = new common::Log(common::DEBUG);
    // batch_test(58,folderPath,files);
//     common::g_log = new common::Log(common::FATAL);
//     batch_test(57,folderPath,files);
    // single_point_test(folderPath,files);
    batch_test(0,folderPath,files);
    //single_point_test(folderPath,files);
    delete common::g_log;
    return 0;
}