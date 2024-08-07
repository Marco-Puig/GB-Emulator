#include <instructions.h>
#include <cpu.h>

Instruction instructions[0x100] = {
    {NOP, IMP}, // 0x00
    {},
    {},
    {},
    {},          // 0x01 - 0x04
    {DEC, R, B}, // 0x05
    {},
    {},
    {},
    {},
    {},
    {},
    {},               // 0x06 - 0x0D
    {LD, R_D8, RT_C}, // 0x0E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x0F - 0x1E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x1F - 0x2E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x2F - 0x3E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x3F - 0x4E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x4F - 0x5E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x5F - 0x6E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x6F - 0x7E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x7F - 0x8E
    {},
    {},
    {},
    {},
    {},
    {},
    {}, // 0x8F - 0x9E
    {},
    {},
    {},
    {},
    {},
    {},
    {},          // 0x9F - 0xAE
    {XOR, R, A}, // 0xAF
    {},
    {},
    {},
    {},
    {},
    {},
    {},        // 0xB0 - 0xC2
    {JP, D16}, // 0xC3
    {},
    {},
    {},
    {},
    {},
    {},
    {},       // 0xC4 - 0xF2
    {DI, IMP} // 0xF3
};

Instruction *instruction_by_opcode(u8 opcode)
{
    return &instructions[opcode];
}

char *inst_lookup[] = {
    "<NONE>",
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "POP",
    "JP",
    "PUSH",
    "RET",
    "CB",
    "CALL",
    "RETI",
    "LDH",
    "JPHL",
    "DI",
    "EI",
    "RST",
    "IN_ERR",
    "IN_RLC",
    "IN_RRC",
    "IN_RL",
    "IN_RR",
    "IN_SLA",
    "IN_SRA",
    "IN_SWAP",
    "IN_SRL",
    "IN_BIT",
    "IN_RES",
    "IN_SET"};

char *inst_name(InType t)
{
    return inst_lookup[t];
}