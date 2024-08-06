#include <emu.h>

/*
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/

static emu_context ctx;

emu_context *emu_get_context()
{
    return &ctx;
}

void delay(u32 ms)
{
    SDL_Delay(ms);
}

int emu_run(std::ifstream &file)
{
    if (!cart_load(file)) // file reading error already within cart_load function
    {
        return -2;
    }

    std::cout << "Cart loaded.." << std::endl;

    SDL_Init(SDL_INIT_VIDEO);
    std::cout << "SDL Active" << std::endl;
    TTF_Init();
    std::cout << "TTF Active" << std::endl;

    // cpu_init(); // need to create cpu functionality

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while (ctx.running)
    {
        if (ctx.paused)
        {
            delay(10);
            continue;
        }

        //  if (!cpu_step()) // need to create cpu functionality
        //  {
        std::cout << "CPU Stopped" << std::endl;
        return -3;
        //  }

        ctx.ticks++;
    }

    return 0;
}
