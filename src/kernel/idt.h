#ifndef IDT_H
#define IDT_H

#include "../lib/stdint.h"

void idt_set_gate(u32 num, u32 handler, u16 selector, u8 attributes);
void idt_init();

#endif