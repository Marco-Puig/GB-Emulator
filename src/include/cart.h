#ifndef CART_H
#define CART_H

#include <common.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <stdio.h>
#include <cpu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct rom_header
{
    u8 entry[4];
    u8 logo[0x30];

    char title[16];
    u16 new_lic_code;
    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u16 global_checksum;
};

bool cart_load(std::ifstream &file);
u8 cart_read(u16 address);
void cart_write(u16 address, u8 value);

#endif
