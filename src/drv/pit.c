#include "pit.h"
#include "../lib/stddef.h"
#include "../kernel/io.h"

void pit_init(u32 frequency) {
    u32 divisor = 1193182 / frequency;
    outb(0x43, 0x36);
    outb(0x40, (u8)(divisor & 0xFF));
    outb(0x40, (u8)((divisor >> 8) & 0xFF));
}