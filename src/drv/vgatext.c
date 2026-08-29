#include "vgatext.h"
#include "../lib/stdint.h"
#include "../lib/memory.h"
#include "../kernel/io.h"

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
    for (u32 i = 0; i <= VGATEXT_WIDTH * VGATEXT_HEIGHT * 2; i++) {
        VGATEXT_ADDR[i] = 0;
    }
}

void vgatext_load(void* target) {
    memcpy(VGATEXT_ADDR, target, VGATEXT_WIDTH * VGATEXT_HEIGHT * 2);
}

void vgatext_update_cursor(u8 cx, u8 cy) {
    u32 cursor_pos = cy * 80 + cx;

    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);

    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((cursor_pos >> 8) & 0xFF));

    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(cursor_pos & 0xFF));
}
