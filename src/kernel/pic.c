#include "pic.h"
#include "../lib/stddef.h"
#include "io.h"

#define PIC1        0x20
#define PIC2        0xA0

void pic_remap(u8 offset_1, u8 offset_2) {
    outb(PIC1, 0x10 | 1);
    io_wait();
    outb(PIC2, 0x10 | 1);
    io_wait();

    outb(PIC1 + 1, offset_1);
    io_wait();
    outb(PIC2 + 1, offset_2);
    io_wait();

    outb(PIC1 + 1, 4);
    io_wait();
    outb(PIC2 + 1, 2);
    io_wait();

    outb(PIC1 + 1, 1);
    io_wait();
    outb(PIC2 + 1, 1);
    io_wait();

    outb(PIC1 + 1, 0);
    outb(PIC2 + 1, 0);
}

void pic_eoi(u8 irq) {
    if (irq >= 8) outb(PIC2, 0x20);
    outb(PIC1, 0x20);
}