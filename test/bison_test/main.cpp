#include <iostream>
#include "ast/stmt.hpp"
extern int code_parse(const char * code_str, ProgramStmt * program);
int main() {
  code_parse("const my_name = 123; xi = 7;", nullptr);
  return 0;
}