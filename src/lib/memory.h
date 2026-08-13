#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

void memset(void* dest, u8 val, u64 size);
void memcpy(void* dest, const void* src, u64 size);
bool memeq(const void *mem1, const void *mem2, u64 limit);

#endif