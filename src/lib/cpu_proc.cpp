#include <iostream>
#include <array>
#include <cpu.h>
#include <emu.h>

static void proc_none(cpu_context *ctx)
{
    std::cerr << "INVALID INSTRUCTION!\n";
    std::exit(-7);
}

static void proc_nop(cpu_context *ctx)
{
    // TODO: Implement NOP instruction
}

static void proc_di(cpu_context *ctx)
{
    ctx->int_master_enabled = false;
}

static void proc_ld(cpu_context *ctx)
{
    // TODO: Implement all the different types of LD instructions
}

void cpu_set_flags(cpu_context *ctx, char z, char n, char h, char c)
{
    if (z != -1)
    {
        BIT_SET(ctx->regs.f, 7, z);
    }

    if (n != -1)
    {
        BIT_SET(ctx->regs.f, 6, n);
    }

    if (h != -1)
    {
        BIT_SET(ctx->regs.f, 5, h);
    }

    if (c != -1)
    {
        BIT_SET(ctx->regs.f, 4, c);
    }
}

static void proc_xor(cpu_context *ctx)
{
    ctx->regs.a ^= ctx->fetched_data & 0xFF;
    cpu_set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}

static bool check_cond(cpu_context *ctx)
{
    bool z = CPU_FLAG_Z;
    bool c = CPU_FLAG_C;

    switch (ctx->cur_inst->cond)
    {
    case CT_NONE:
        return true;
    case CT_C:
        return c;
    case NC:
        return !c;
    case Z:
        return z;
    case NZ:
        return !z;
    }

    return false;
}

static void proc_jp(cpu_context *ctx)
{
    if (check_cond(ctx))
    {
        ctx->regs.pc = ctx->fetched_data;
        emu_cycles(1);
    }
}

using IN_PROC = void (*)(cpu_context *);
static std::array<IN_PROC, 6> processors = {
    // 6 - # of instructions
    proc_none, // IT_NONE
    proc_nop,  // IN_NOP
    proc_ld,   // IN_LD
    proc_jp,   // IN_JP
    proc_di,   // IN_DI
    proc_xor   // IN_XOR
};

IN_PROC inst_get_processor(InType type)
{
    return processors[type];
}