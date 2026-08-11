#include "../lib/stdint.h"
#include "../drv/vgatext.h"

#include "memory.h"
#include "idt.h"

void kmain(u8 memory_map_location) {
    memory_init(memory_map_location);
    idt_init();
}