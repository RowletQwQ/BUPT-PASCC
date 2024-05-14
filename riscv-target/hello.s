.data
    .align 2
hello: .string "Hello, World!\n"

.text
    .globl main
main:
    la a1, hello       
    li a7, 64          
    li a0, 1           
    li a2, 14         
    ecall              
        
    li a0, 0           
    ret          