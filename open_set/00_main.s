.data
: .word 3
__PLACEHOLDER__main_bb_0_0: .string "%d"
.bss
a: .space 4
.text
.globl main
main:
	addi sp, sp, -8
	sd s0, 0(sp)
	add s0, sp, zero
	addi sp, sp, 0
main_bb_0:
	la t0, a
	lw t0, 0(t0)
	add t1, zero, t0
	addi t2, zero, 3
	sw t2, 0(t1)
	addi sp, sp, -72
	sd s2, 0(sp)
	sd s3, 8(sp)
	sd s4, 16(sp)
	sd s5, 24(sp)
	sd s6, 32(sp)
	sd s7, 40(sp)
	sd s8, 48(sp)
	sd s9, 56(sp)
	sd s10, 64(sp)
	sd s11, 72(sp)
	add s2, zero, a0
	add s3, zero, a1
	add s4, zero, a2
	add s5, zero, a3
	add s6, zero, a4
	add s7, zero, a5
	add s8, zero, a6
	add s9, zero, a7
	la a0, __PLACEHOLDER__main_bb_0_0
	la t3, a
	lw t3, 0(t3)
	add a1, zero, t3
	jal ra, printf
	add a0, zero, s2
	add a1, zero, s3
	add a2, zero, s4
	add a3, zero, s5
	add a4, zero, s6
	add a5, zero, s7
	add a6, zero, s8
	add a7, zero, s9
	ld s2, 0(sp)
	ld s3, 8(sp)
	ld s4, 16(sp)
	ld s5, 24(sp)
	ld s6, 32(sp)
	ld s7, 40(sp)
	ld s8, 48(sp)
	ld s9, 56(sp)
	ld s10, 64(sp)
	ld s11, 72(sp)
	addi sp, sp, 72
	xor a0, zero, zero
	addi sp, sp, 0
	ld s0, 0(s0)
	jalr zero, ra, 0
