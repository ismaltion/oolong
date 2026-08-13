#ifndef HEAP_H
#define HEAP_H

#include "../lib/stddef.h"

u8 memory_init(u16 mmap_length);
void* kmalloc(u64 size);
void kfree(void* ptr);
void *krealloc(void* ptr, u64 size);

#endif