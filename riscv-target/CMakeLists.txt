# 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 指定项目的名称和使用的语言
project(assembly_project ASM)

# 找到目录下的所有 .s 文件
file(GLOB SOURCES "*.s")

# 为每个 .s 文件生成一个可执行文件
foreach(source ${SOURCES})
    get_filename_component(executable ${source} NAME_WE)
    add_executable(${executable} ${source})
endforeach()

# 指定编译器和 QEMU 的路径
set(CMAKE_ASM_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_LINKER riscv64-unknown-elf-ld)
set(QEMU qemu-riscv64)

# 为每个可执行文件生成一个 .out 文件
foreach(source ${SOURCES})
    get_filename_component(executable ${source} NAME_WE)
    add_custom_command(TARGET ${executable} POST_BUILD
        COMMAND ${CMAKE_LINKER} -o ${executable}.out $<TARGET_FILE:${executable}>
        COMMENT "Linking ${executable}"
    )
endforeach()