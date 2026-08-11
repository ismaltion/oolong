#include "console.h"
#include "../drv/vgatext.h"
#include "../lib/stddef.h"
#include "memory.h"

struct terminal output_terminals[MAX_TERMINALS];

// Init

void console_init() {
    memset(output_terminals, 0, sizeof(output_terminals));
}


// Terminal management

u32 create_terminal(u16 cols, u16 rows) {
    if (cols > 400 || rows > 400 || cols == 0 || rows == 0) return 0xEEEE0001;
    u32 id = 1;
    while (output_terminals[id].in_use) {
        id++;
        if (id >= MAX_TERMINALS) return 0xEEEE0002;
    }
    output_terminals[id].content = kmalloc(cols * rows * sizeof(struct cell));
    if (!output_terminals[id].content) return 0;
    output_terminals[id].cols = cols;
    output_terminals[id].rows = rows;
    output_terminals[id].cursor_x = 0;
    output_terminals[id].cursor_y = 0;
    output_terminals[id].in_use = true;

    memset(output_terminals[id].content, 0, cols * rows * sizeof(struct cell));
    return id;
}

void delete_terminal(u32 id) {
    if (id >= MAX_TERMINALS || !output_terminals[id].in_use) return;
    kfree(output_terminals[id].content);
    memset(&output_terminals[id], 0, sizeof(struct terminal));
}

// Terminal utils

u8 terminal_clear(u32 id) {
    if (id >= MAX_TERMINALS || !output_terminals[id].in_use) return 1;
    memset(output_terminals[id].content, 0, output_terminals[id].cols * output_terminals[id].rows * sizeof(struct cell));
    output_terminals[id].cursor_x = 0;
    output_terminals[id].cursor_y = 0;
    return 0;
}

