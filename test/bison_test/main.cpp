#include <iostream>
#include "ast/stmt.hpp"
#include "common/log/log.hpp"
extern int code_parse(const char * code_str, ProgramStmt * program);
int main() {
  common::g_log = new common::Log(common::DEBUG);
  code_parse("-34 - -23", nullptr);
  return 0;
}