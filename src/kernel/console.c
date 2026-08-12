#include "console.h"
#include "../drv/vgatext.h"
#include "../lib/stddef.h"
#include "memory.h"
#include "dev.h"

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

void terminal_scroll(const u32 terminal_id) {
    u32 total_chars = output_terminals[terminal_id].cols * (output_terminals[terminal_id].rows - 1);

    for (u32 i = 0; i < total_chars; i++) {
        output_terminals[terminal_id].content[i] = output_terminals[terminal_id].content[i + output_terminals[terminal_id].cols];
    }

    struct cell empty_cell;
    empty_cell.character = ' ';
    empty_cell.color = 0;
    u32 last_row_start = (output_terminals[terminal_id].rows - 1) * output_terminals[terminal_id].cols;
    for (u32 i = 0; i < output_terminals[terminal_id].cols; i++) {
        output_terminals[terminal_id].content[last_row_start + i] = empty_cell;
    }
}

void terminal_putchar(const u32 terminal_id, const char chara, const u8 color) {
    // Yes. This function can be simplified with a pointer. I'm too tired rn to do that.
    // Submit a PR if you want to clean this garbage. also yes I suddenly remembered the existence of const.
    if (chara == '\b') {
        if (output_terminals[terminal_id].cursor_x > 0) {
            output_terminals[terminal_id].cursor_x--;
        } else if (output_terminals[terminal_id].cursor_y > 0) {
            output_terminals[terminal_id].cursor_y--;
            output_terminals[terminal_id].cursor_x = output_terminals[terminal_id].cols - 1;
        }
        struct cell entry;
        entry.character = ' ';
        entry.color = color;
        u32 offset = output_terminals[terminal_id].cursor_y * output_terminals[terminal_id].cols + output_terminals[terminal_id].cursor_x;
        output_terminals[terminal_id].content[offset] = entry;
    } else if (chara == '\n') {
        output_terminals[terminal_id].cursor_x = 0;
        output_terminals[terminal_id].cursor_y++;
    } else {
        struct cell entry;
        entry.character = chara;
        entry.color = color;

        if (output_terminals[terminal_id].cursor_x > output_terminals[terminal_id].cols) {
            output_terminals[terminal_id].cursor_x = 0;
            output_terminals[terminal_id].cursor_y++;
        }
        if (output_terminals[terminal_id].cursor_y >= output_terminals[terminal_id].rows) {
            terminal_scroll(terminal_id);
            output_terminals[terminal_id].cursor_y = output_terminals[terminal_id].rows - 1;
        }

        u32 offset = output_terminals[terminal_id].cursor_y * output_terminals[terminal_id].cols + output_terminals[terminal_id].cursor_x;
        output_terminals[terminal_id].content[offset] = entry;
        output_terminals[terminal_id].cursor_x++;
    }
    if (output_terminals[terminal_id].cursor_y >= output_terminals[terminal_id].rows) {
        terminal_scroll(terminal_id);
        output_terminals[terminal_id].cursor_y = output_terminals[terminal_id].rows - 1;
    }
}

void terminal_print(u32 terminal_id, const char* string) {
    for (u32 i = 0; string[i] != 0; i++) {
        terminal_putchar(terminal_id, string[i], 0x07);
    }
}