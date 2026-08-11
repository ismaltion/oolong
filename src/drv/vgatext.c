#include "vgatext.h"
#include "../lib/stdint.h"

#define VGATEXT_ADDR ((u8*)0xB8000)

u8 vgatext_putchar(u8 chara, u8 color, u16 column, u16 row) {
    if (column >= VGATEXT_WIDTH || row >= VGATEXT_HEIGHT)
        return 1;
    u32 offset = (row * VGATEXT_WIDTH + column) * 2;
    VGATEXT_ADDR[offset] = chara;
    VGATEXT_ADDR[offset + 1] = color;
    return 0;
}

void vgatext_clear() {
    for (u32 i = 0; i <= VGATEXT_WIDTH * VGATEXT_HEIGHT * 2; i++)
    {
        VGATEXT_ADDR[i] = 0;
    }
}