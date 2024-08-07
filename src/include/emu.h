#ifndef EMU_H
#define EMU_H

#include <cart.h>

typedef struct
{
    bool paused;
    bool running;
    u64 ticks;
} emu_context;

int emu_run(std::ifstream &file);

emu_context *emu_get_context();

void emu_cycles(int cpu_cycles);

#endif
