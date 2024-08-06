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

typedef struct
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
} rom_header;

bool cart_load(std::ifstream &file);

#endif
