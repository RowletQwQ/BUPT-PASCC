.section .data
format: .asciz "%d\n"

.section .text
.globl main
.globl add

# 定义add函数
add:
    # a0和a1寄存器分别存储参数a和b
    # 将a和b相加，结果存储在a0寄存器中
    add a0, a0, a1
    # 返回到调用者
    ret

main:
    # 将要相加的两个数加载到a0和a1寄存器中
    li a0, 2
    li a1, 3
    # 调用add函数
    jal ra, add
    # 此时，a0寄存器中的值就是5（2+3）

    # 以下是打印和退出的代码
    la a1, format
    mv a2, a0
    jal ra, printf
    li a7, 10
    li a0, 0
    ecall