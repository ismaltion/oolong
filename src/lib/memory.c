#include "memory.h"
#include "stddef.h"

void memset(void* dest, u8 val, u64 size) {
    u8* ptr = (u8*)dest;
    for (u64 i = 0; i < size; i++) {
        ptr[i] = val;   
    }
}

void memcpy(void* dest, const void* src, u64 size) {
    u8* d_ptr = (u8*)dest;
    const u8* s_ptr = (const u8*)src;
    
    for (u64 i = 0; i < size; i++) {
        d_ptr[i] = s_ptr[i];
    }
}

bool memeq(const void *mem1, const void *mem2, u64 limit) {
    if (mem1 == NULL || mem2 == NULL) {
        return mem1 == mem2;
    }

    const u8 *p1 = (const u8 *)mem1;
    const u8 *p2 = (const u8 *)mem2;

    for (u64 i = 0; i < limit; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }

    return true;
}