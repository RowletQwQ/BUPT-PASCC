cmake_minimum_required(VERSION 3.12)
project(PASCC_TEST)
add_compile_options(-g -fsanitize=address)
set(CMAKE_CXX_STANDARD 17)


find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)



# 生成词法分析器
FLEX_TARGET(FLEX ../../src/parser/lex_pascal.l  ${CMAKE_CURRENT_BINARY_DIR}/lex_pascal.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lex_pascal.hpp)

# 生成语法分析器
BISON_TARGET(BISON ../../src/parser/yacc_pascal.y ${CMAKE_CURRENT_BINARY_DIR}/yacc_pascal.cpp)

# 包含主项目src目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)

# 包含构建出的词法分析器和语法分析器
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(AST_SOURCE_FILES
    ../../src/ast/stmt.cpp
    ../../src/ast/stmt_test.cpp
)

set(LOG_SOURCE_FILES
    ../../src/common/log/log.cpp
)

add_executable(PASCC_TEST
    main.cpp
    ${FLEX_FLEX_OUTPUTS}
    ${BISON_BISON_OUTPUTS}
    ${AST_SOURCE_FILES}
    ${LOG_SOURCE_FILES}
)

target_link_libraries(PASCC_TEST ${BISON_LIBRARIES} -fsanitize=address)
# 项目架构 
# |---src
#          |---token
#                   |---token.hpp
#                   |---token.cpp
#          |---ast
#                 |---stmt.hpp
#                 |---stmt.cpp
#                 |---stmt_test.cpp
# |---test
#        |---bison_test
#                  |---CMakeLists.txt
#                  |---src
#                         |---lex_pascal.l
#                         |---yacc_pascal.y
#                         |---main.cpp