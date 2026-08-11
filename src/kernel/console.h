#ifndef CONSOLE_H
#define CONSOLE_H

#define MAX_TERMINALS 32

#include "../lib/stddef.h"

struct cell {
    u8 character;
    u8 color;
};

struct terminal {
    u16 cols;
    u16 rows;
    u16 cursor_x;
    u16 cursor_y;
    bool in_use;
    struct cell* content;
};

struct terminal output_terminals[MAX_TERMINALS];

void console_init();
u32 create_terminal(u16 cols, u16 rows);
void delete_terminal(u32 id);
u8 terminal_clear(u32 id);

#endif