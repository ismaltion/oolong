#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

void memset(void* dest, u8 val, u64 size); // Sets all bytes of a memory space to the same thing.
void memcpy(void* dest, const void* src, u64 size); // Copies all bytes of a memory space to another memory space.
bool memeq(const void *mem1, const void *mem2, u64 limit); // Returns true if two memory spaces are the same.

#endif