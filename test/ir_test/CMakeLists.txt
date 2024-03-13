cmake_minimum_required(VERSION 3.10)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src/ast)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src/common)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src/ir)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src/parser)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../src/token)
MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILECOMMANDS ON)


# 当所有函数都写完时，打开这个编译选项

add_compile_options(-g)
#add_compile_options(-g -fsanitize=address)

# add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -fsanitize=address)

project(BISON_TEST)

SET(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

MESSAGE(STATUS "PROJECT_DIR: " ${PROJECT_DIR})

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE SRC_FILES ${PROJECT_DIR}/src/ast/*.cpp ${PROJECT_DIR}/src/common/*.cpp ${PROJECT_DIR}/src/ir/*.cpp
${PROJECT_DIR}/src/parser/*.cpp ${PROJECT_DIR}/src/token/*.cpp)

SET(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

SET(LIBEVENT_STATIC_LINK TRUE)

SET(pthread)
# 指定文件输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR}/bin)
MESSAGE(STATUS "PROJECT_DIR: " ${PROJECT_DIR})
set(SRC_PATH ${PROJECT_DIR}/src)
MESSAGE(STATUS "SRC_PATH: " ${SRC_PATH})

ADD_EXECUTABLE(IR_TEST ${SRC_FILES} ${MAIN_SRC})

#target_link_libraries(IR_TEST -fsanitize=address)

