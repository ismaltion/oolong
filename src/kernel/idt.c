#include "../lib/stdint.h"
#include "../drv/vgatext.h"
#include "../drv/pit.h"
#include "idt.h"
#include "pic.h"

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8  something;
    u8  attributes;
    u16 offset_high;
};

struct idt_pointer {
    u16 limit;
    u32 base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_pointer idtp;

extern void load_idt(void *);
extern void default_irq_stub();
extern void timer_stub();

extern u64 timer_ticks;

void idt_set_gate(u32 num, u32 handler, u16 selector, u8 attributes) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = selector;
    idt[num].something = 0;
    idt[num].attributes = attributes;
    idt[num].offset_high = handler >> 16;
}

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (u32)&idt;

    pic_remap(0x20, 0x28);

    for (u16 i = 0; i < 256; i++)
        idt_set_gate(i, (u64)default_irq_stub, 0x08, 0b10001110);

    idt_set_gate(32, (u64)timer_stub, 0x08, 0b10001110);

    pit_init(1000);

    load_idt(&idtp);
}