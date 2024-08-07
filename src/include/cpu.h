#ifndef CPU_H
#define CPU_H

#include <common.h>
#include <iostream>
#include <instructions.h>
#include <bus.h>
#include <emu.h>
#include <iomanip>

// CPU Registers for the Gameboy CPU
struct cpu_registers
{
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;

    // serve as special fuctional registers
    u16 sp;
    u16 pc;
};

// Implicate CPU aspects for the Gameboy CPU
struct cpu_context
{
    cpu_registers regs;
    u16 fetched_data;
    u16 mem_dest;
    bool dest_is_mem;
    u8 cur_opcode;
    Instruction *cur_inst;

    bool halted;
    bool stepping;

    bool int_master_enabled;
};

void cpu_init();
bool cpu_step();

typedef void (*IN_PROC)(cpu_context *);

IN_PROC inst_get_processor(InType type);

#define CPU_FLAG_Z BIT(ctx->regs.f, 7)
#define CPU_FLAG_C BIT(ctx->regs.f, 4)

u16 reverse(u16 n);
u16 cpu_read_reg(RegType rt);

#endif
