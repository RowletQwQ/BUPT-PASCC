cmake_minimum_required(VERSION 3.12)
project(TOKEN_TEST)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

#../src/parser/lex_pascal.l
FLEX_TARGET(lexer ../../src/parser/lex_pascal.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)


# 将main token 以及生成的lex.yy.cpp编译成一个可执行文件 main.cpp 依赖 token.cpp flex依赖token.cpp 
add_executable(TOKEN_TEST main.cpp ${FLEX_lexer_OUTPUTS} ../../src/token/token.hpp ../../src/token/token.cpp)
# 
target_include_directories(TOKEN_TEST PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/token/)

target_link_libraries(TOKEN_TEST ${FLEX_LIBRARIES} ${BISON_LIBRARIES} )