#pragma once

namespace builder {

namespace riscv {

class RiscvInstruction {
public:
    enum InstrType {
        /**Shifts**/
        // RV32I
        SLL, // Shift left logical
        SRL, // Shift right logical
        SRA, // Shift right arithmetic
        SLLI, // Shift left logical immediate
        SRLI, // Shift right logical immediate
        SRAI, // Shift right arithmetic immediate
        // RV64I
        SLLW, // Shift left logical word
        SRLW, // Shift right logical word
        SRAW, // Shift right arithmetic word
        SLLIW, // Shift left logical word immediate
        SRLIW, // Shift right logical word immediate
        SRAIW, // Shift right arithmetic word immediate
        /**Arithmetic**/
        // RV32I
        ADD, // Add
        ADDI, // Add immediate
        SUB, // Subtract
        LUI, // Load upper immediate
        AUIPC, // Add upper immediate to PC
        // RV64I
        ADDW, // Add word
        ADDIW, // Add word immediate
        SUBW, // Subtract word

        /**Logical**/
        // RV32I
        XOR, // XOR
        XORI, // XOR immediate
        OR, // OR
        ORI, // OR immediate
        AND, // AND
        ANDI, // AND immediate
        
        /**Compare**/
        // RV32I
        SLT, // Set less than
        SLTI, // Set less than immediate
        SLTU, // Set less than unsigned
        SLTIU, // Set less than immediate unsigned

        /**Branch**/
        // RV32I
        BEQ, // Branch equal
        BNE, // Branch not equal
        BLT, // Branch less than
        BGE, // Branch greater than or equal
        BLTU, // Branch less than unsigned
        BGEU, // Branch greater than or equal unsigned

        /**Jump**/
        // RV32I
        JAL, // Jump and link
        JALR, // Jump and link register

        /**Load**/
        // RV32I
        LB, // Load byte
        LH, // Load halfword
        LW, // Load word
        LBU, // Load byte unsigned
        LHU, // Load halfword unsigned
        // RV64I
        LD, // Load doubleword
        LWU, // Load word unsigned

        /**Store**/
        // RV32I
        SB, // Store byte
        SH, // Store halfword
        SW, // Store word
        // RV64I
        SD, // Store doubleword

        /**Control**/
        // RV32I
        ECALL, // Environment call from U-mode
        EBREAK, // Environment break from U-mode
        MRET, // Machine return
        SRET, // Supervisor return
        URET, // User return
        WFI, // Wait for interrupt
        SFENCE_VMA, // Synchronize TLB with ASID

        /**CSR**/
        // RV32I
        CSRRW, // CSR read/write
        CSRRS, // CSR read and set
        CSRRC, // CSR read and clear
        CSRRWI, // CSR read/write immediate
        CSRRSI, // CSR read and set immediate
        CSRRCI, // CSR read and clear immediate

        /**Fence**/
        // RV32I
        FENCE, // Fence instruction
        FENCE_I, // Fence instruction (I-type)


        /**MulDiv**/
        // RV32M
        MUL, // Multiply
        MULH, // Multiply high signed
        MULHSU, // Multiply high signed/unsigned
        MULHU, // Multiply high unsigned
        DIV, // Divide
        DIVU, // Divide unsigned
        REM, // Remainder
        REMU, // Remainder unsigned
        // RV64M
        MULW, // Multiply word
        DIVW, // Divide word
        DIVUW, // Divide word unsigned
        REMW, // Remainder word

        /***Floating-Point***/
        
        /**Move**/
        // RV32F
        FMV_W_X, // Move word from X
        FMV_X_W, // Move X from word
        // RV64F
        FMV_D_X, // Move double from X
        FMV_X_D, // Move X from double
        

        /**Load**/
        // RV32F
        FLW, // Load word
        // RV64F
        FLD, // Load double

        /**Store**/
        // RV32F
        FSW, // Store word
        // RV64F
        FSD, // Store double

        /**Convert**/
        // RV32F
        FCVT_S_W, // Convert single from word
        FCVT_S_WU, // Convert single from word unsigned
        FCVT_D_W, // Convert double from word
        FCVT_D_WU, // Convert double from word unsigned
        FCVT_W_S, // Convert word from single
        FCVT_WU_S, // Convert word unsigned from single
        FCVT_W_D, // Convert word from double
        FCVT_WU_D, // Convert word unsigned from double
        // RV64F
        FCVT_L_S, // Convert long from single
        FCVT_LU_S, // Convert long unsigned from single
        FCVT_L_D, // Convert long from double
        FCVT_LU_D, // Convert long unsigned from double
        FCVT_S_L, // Convert single from long
        FCVT_S_LU, // Convert single from long unsigned
        FCVT_D_L, // Convert double from long
        FCVT_D_LU, // Convert double from long unsigned

        /**Arithmetic**/
        // RV32F
        FADD_S, // Add single
        FSUB_S, // Subtract single
        FMUL_S, // Multiply single
        FDIV_S, // Divide single
        FSQRT_S, // Square root single
        // RV64F
        FADD_D, // Add double
        FSUB_D, // Subtract double
        FMUL_D, // Multiply double
        FDIV_D, // Divide double
        FSQRT_D, // Square root double

        /**Mul-Add**/
        // RV32F 
        FMADD_S, // Multiply-add single
        FMSUB_S, // Multiply-subtract single
        FNMADD_S, // Negative multiply-add single
        FNMSUB_S, // Negative multiply-subtract single

        // RV64F
        FMADD_D, // Multiply-add double
        FMSUB_D, // Multiply-subtract double
        FNMADD_D, // Negative multiply-add double
        FNMSUB_D, // Negative multiply-subtract double

        /**Compare**/
        // RV32F
        FEQ_S, // Equal single
        FLT_S, // Less than single
        FLE_S, // Less than or equal single
        // RV64F
        FEQ_D, // Equal double
        FLT_D, // Less than double
        FLE_D, // Less than or equal double

        /**Min/Max**/
        // RV32F
        FMIN_S, // Minimum single
        FMAX_S, // Maximum single
        // RV64F
        FMIN_D, // Minimum double
        FMAX_D, // Maximum double
        
        /**Sign Inject**/
        // RV32F
        FSGNJ_S, // Sign inject single
        FSGNJN_S, // Sign inject negate single
        FSGNJX_S, // Sign inject exclusive single
        // RV64F
        FSGNJ_D, // Sign inject double
        FSGNJN_D, // Sign inject negate double
        FSGNJX_D, // Sign inject exclusive double

    };
};




} // namespace riscv
} // namespace builder