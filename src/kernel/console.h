#ifndef CONSOLE_H
#define CONSOLE_H

#define MAX_TERMINALS 32

#include "../lib/stddef.h"

struct cell {
    char character;
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

void console_init();
u32 create_terminal(u16 cols, u16 rows);
void delete_terminal(u32 id);

u8 terminal_clear(u32 id);
void terminal_scroll(const u32 terminal_id);
void terminal_putchar(const u32 terminal_id, const char chara, const u8 color);
u8 terminal_print(u32 terminal_id, const char* string, u8 color);
void print(const char* string);
void printc(const char* string, u8 color);

#endif