#ifndef DRV_VGATEXT_H
#define DRV_VGATEXT_H

#define VGATEXT_WIDTH   80
#define VGATEXT_HEIGHT  25

#include "../lib/stdint.h"

u8 vgatext_putchar(u8 chara, u8 color, u16 column, u16 row);

#endif