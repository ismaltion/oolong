#ifndef PIC_H
#define PIC_H

#include "../lib/stddef.h"

void pic_remap(u8 offset_1, u8 offset_2);
void pic_eoi(u8 irq);

#endif