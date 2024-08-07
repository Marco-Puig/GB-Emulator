#include <cpu.h>

/*
CPU Registers:
16-bit	Hi	Lo	Name/Function
AF	A	-	Accumulator & Flags
BC	B	C	BC
DE	D	E	DE
HL	H	L	HL
SP	-	-	Stack Pointer
PC	-	-	Program Counter/Pointer
*/

extern cpu_context ctx; // extern keyword is used to declare a variable that is defined again in this file

// Reversing the 16-bit value because of the little-endian architecture of the CPU
u16 reverse(u16 n)
{
    return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}

// Reading the register value from the CPU
u16 cpu_read_reg(RegType rt)
{
    switch (rt)
    {
    case A:
        return ctx.regs.a;
    case F:
        return ctx.regs.f;
    case B:
        return ctx.regs.b;
    case RT_C:
        return ctx.regs.c;
    case D:
        return ctx.regs.d;
    case E:
        return ctx.regs.e;
    case H:
        return ctx.regs.h;
    case L:
        return ctx.regs.l;

    case AF:
        return reverse(*((u16 *)&ctx.regs.a));
    case BC:
        return reverse(*((u16 *)&ctx.regs.b));
    case DE:
        return reverse(*((u16 *)&ctx.regs.d));
    case HL:
        return reverse(*((u16 *)&ctx.regs.h));

    case PC:
        return ctx.regs.pc;
    case SP:
        return ctx.regs.sp;
    default:
        return 0;
    }
}

// Initialize the CPU context
cpu_context ctx = {0};

// Initialize the CPU registers
void cpu_init()
{
    ctx.regs.pc = 0x100;
    ctx.regs.a = 0x01;
}

// Reading the register value from the CPU
static void fetch_instruction()
{
    ctx.cur_opcode = bus_read(ctx.regs.pc++);
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);
}

// Fetching data from the CPU, parsing the data for to later execute the instruction
static void fetch_data()
{
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    if (ctx.cur_inst == NULL)
    {
        return;
    }

    switch (ctx.cur_inst->mode)
    {
    case IMP:
        return;

    case R:
        ctx.fetched_data = cpu_read_reg(ctx.cur_inst->reg_1);
        return;

    case R_D8:
        ctx.fetched_data = bus_read(ctx.regs.pc);
        emu_cycles(1);
        ctx.regs.pc++;
        return;

    case D16:
    {
        u16 lo = bus_read(ctx.regs.pc);
        emu_cycles(1);

        u16 hi = bus_read(ctx.regs.pc + 1);
        emu_cycles(1);

        ctx.fetched_data = lo | (hi << 8);

        ctx.regs.pc += 2;

        return;
    }

    default:
        printf("Unknown Addressing Mode! %d (%02X)\n", ctx.cur_inst->mode, ctx.cur_opcode);
        exit(-7);
        return;
    }
}

// Execute the instruction based on the opcode
static void execute()
{
    IN_PROC proc = inst_get_processor(ctx.cur_inst->type);

    if (!proc)
    {
        std::cerr << "Unknown Instruction Processor or Not yet developed this functionality! " << inst_name(ctx.cur_inst->type) << std::endl;
    }

    proc(&ctx);
}

bool cpu_step()
{
    if (!ctx.halted)
    {
        u16 pc = ctx.regs.pc;

        fetch_instruction(); // get data and instruction
        fetch_data();

        // Debugging the CPU instructions to ensure the instruction set has been implemented correctly
        std::cout << std::hex << std::setw(4) << std::setfill('0') << pc << ": "
                  << std::left << std::setw(7) << inst_name(ctx.cur_inst->type) << " ("
                  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ctx.cur_opcode) << " "
                  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus_read(pc + 1)) << " "
                  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus_read(pc + 2)) << ") "
                  << "A: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ctx.regs.a) << " "
                  << "B: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ctx.regs.b) << " "
                  << "C: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ctx.regs.c) << std::endl;

        if (ctx.cur_inst == NULL)
        {
            std::cout << "Unknown Instruction!" << ctx.cur_opcode << std::endl;
            exit(-7);
        }

        execute();
    }

    return true;
}
