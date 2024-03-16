cmake_minimum_required(VERSION 3.10)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILECOMMANDS ON)


# 当所有函数都写完时，打开这个编译选项
# add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -fsanitize=address)
add_compile_options(-O2)
project(PASCC)


set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

SET(MAIN_SRC ${PROJECT_SOURCE_DIR}/src/main.cpp)

SET(LIBEVENT_STATIC_LINK TRUE)


# 指定文件输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
MESSAGE(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
MESSAGE(STATUS "SRC_PATH: " ${SRC_PATH})

ADD_EXECUTABLE(pascc ${SRC_FILES} ${MAIN_SRC})

target_include_directories(pascc PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(pascc -fsanitize=address -pthread)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/bison_test)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/ir_test)
# add_subdirectory(${PROJECT_SOURCE_DIR}/test/token_test)

# 启动CTest
enable_testing()

# 添加可执行文件
add_test(NAME test_bison COMMAND ${PROJECT_SOURCE_DIR}/bin/BISON_TEST ${PROJECT_SOURCE_DIR}/open_set)
add_test(NAME test_ir COMMAND ${PROJECT_SOURCE_DIR}/bin/IR_TEST --i ${PROJECT_SOURCE_DIR}/open_set -d 4)