#include "console.h"
#include "../drv/vgatext.h"
#include "../lib/stdint.h"

struct cell {
    u8 character;
    u8 color;
};

struct terminal {
    u32 cols;
    u32 rows;
    u32 cursor_x;
    u32 cursor_y;
    struct cell* buffer;
};