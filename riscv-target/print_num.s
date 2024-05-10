.section .data
format: .string "%d\n"

.section .text
.globl main
main:
    # Load the address of the format string into a0
    la a0, format
    # Load the integer to print into a1
    li a1, 42
    # Call printf
    jal ra, printf
    # Exit
    li a7, 10
    li a0, 0
    ecall