# 指定编译器和 QEMU 的路径
AS = riscv64-unknown-linux-gnu-as
LD = riscv64-unknown-linux-gnu-ld
QEMU = qemu-riscv64

# 找到目录下的所有 .s 文件
SOURCES = $(wildcard *.s)
# 将 .s 文件转换为 .o 文件
OBJECTS = $(SOURCES:.s=.o)
# 将 .s 文件转换为可执行文件
EXECUTABLES = $(SOURCES:.s=)

# 默认目标：编译所有的 .s 文件并运行
all: $(EXECUTABLES)
    for exe in $(EXECUTABLES); do \
        $(QEMU) $$exe > $$exe.out; \
    done

# 规则：如何从 .s 文件生成可执行文件
%: %.o
    $(LD) -o $@ $<

# 规则：如何从 .s 文件生成 .o 文件
%.o: %.s
    $(AS) -o $@ $<

# 清理目标：删除所有生成的 .o 文件和可执行文件
clean:
    rm -f $(OBJECTS) $(EXECUTABLES)