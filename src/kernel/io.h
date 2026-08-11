#ifndef IO_H
#define IO_H

#include "../lib/stddef.h"

void io_wait();
u8 inb(u16 port);
void outb(u16 port, u8 value);
u16 inw(u16 port);
void outw(u16 port, u16 value);

#endif