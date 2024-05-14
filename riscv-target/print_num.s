.section .data
format_int: .string "%d-"
format_float: .string "%p-%f\n"
num_float: .dword 0x400921fb54442d18

.section .text
.globl main
main:
    # Load the address of the format string for integer into a0
    la a0, format_int
    # Load the integer to print into a1
    li a1, 42
    # Call printf
    jal ra, printf

    # Load the address of the format string for float into a0
    la a0, format_float
    # Load the address of the float into a2
    la a5, num_float
    fld fa2, 0(a5)
    # Load the float to print into fa0
    fmv.x.d a2, fa2
    add a1, zero, a2
    # Call printf
    jal ra, printf

    # Exit
    li a7, 10
    li a0, 0
    ecall