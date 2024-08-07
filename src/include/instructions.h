#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <common.h>

enum AddrMode // Addressing Mode for the Instruction Set Codes (how the instruction is formatted)
{
    IMP,
    R_D16,
    R_R,
    MR_R,
    R,
    R_D8,
    R_MR,
    R_HLI,
    R_HLD,
    HLI_R,
    HLD_R,
    R_A8,
    A8_R,
    HL_SPR,
    D16,
    D8,
    D16_R,
    MR_D8,
    MR,
    A16_R,
    R_A16
};

enum RegType // Register Type with loading and storing capabilities/values
{
    RT_NONE,
    A,
    F,
    B,
    RT_C, // register type c
    D,
    E,
    H,
    L,
    AF,
    BC,
    DE,
    HL,
    SP,
    PC
};

enum InType // Instruction Type (what you would see in Assembly code) - refer to Instruction Set Codes
{
    IT_NONE,
    NOP,
    LD,
    INC,
    DEC,
    RLCA,
    ADD,
    RRCA,
    STOP,
    RLA,
    JR,
    RRA,
    DAA,
    CPL,
    SCF,
    CCF,
    HALT,
    ADC,
    SUB,
    SBC,
    AND,
    XOR,
    OR,
    CP,
    POP,
    JP,
    PUSH,
    RET,
    CB,
    CALL,
    RETI,
    LDH,
    JPHL,
    DI,
    EI,
    RST,
    ERR,
    RLC,
    RRC,
    RL,
    RR,
    SLA,
    SRA,
    SWAP,
    SRL,
    BIT,
    RES,
    SET
};

enum CondType // Conditionals for the Instruction Set Codes
{
    CT_NONE,
    NZ,
    Z,
    NC,
    CT_C // condition type c
};

struct Instruction
{
    InType type;
    AddrMode mode;
    RegType reg_1;
    RegType reg_2;
    CondType cond;
    u8 param;
};

Instruction *instruction_by_opcode(u8 opcode);

char *inst_name(InType t);

#endif