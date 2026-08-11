#include "memory.h"
#include "../lib/stddef.h"

#define MEMORY_MAP_ADDR 0x500
#define MIN_BLOCK_SIZE 8

extern u8 kernel_end;

struct mmap_entry {
    u64 address;
    u64 size;
    u32 type;
    u32 attributes;
} __attribute__((packed));

struct block {
    u64 size;
    bool free;
    struct block* next;
};

u64 heap_start = 0;
u64 heap_end = 0;
u64 heap_size = 0;
u64 available_memory = 0;
struct mmap_entry* memory_map = (struct mmap_entry*)MEMORY_MAP_ADDR;

struct block* free_list;


// --- Memory utils ---

void memset(void* dest, u8 val, u64 size) {
    u8* ptr = (u8*)dest;
    for (u64 i = 0; i < size; i++)
    {
        ptr[i] = val;   
    }
}

void memcpy(void* dest, const void* src, u64 size) {
    u8* d_ptr = (u8*)dest;
    const u8* s_ptr = (const u8*)src;
    
    for (u64 i = 0; i < size; i++)
    {
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


// --- Actual memory management ---

u8 memory_init(u16 mmap_length) {
    for (u64 i = 0; i < mmap_length; i++) {
        if (memory_map[i].type == 1 && memory_map[i].size > available_memory && memory_map[i].address + memory_map[i].size > (u64)&kernel_end) {
            heap_start = memory_map[i].address;
            heap_end = heap_start + memory_map[i].size;
            available_memory = memory_map[i].size;
        }
    }

    if (heap_start < (u64)&kernel_end) {
        heap_start = (u64)&kernel_end;
        available_memory = heap_end - heap_start;
    }

    if (available_memory == 0) return 1;

    heap_size = heap_end - heap_start;
    free_list = (struct block*)heap_start;
    free_list->size = heap_size - sizeof(struct block);
    free_list->free = true;
    free_list->next = NULL;

    return 0;
}

void split(struct block* block, u64 size) {
    u8* end = (u8*)(block + 1) + size;
    struct block* new_block = (struct block*)end;

    new_block->size = block->size - size - sizeof(struct block);
    new_block->free = true;
    new_block->next = block->next;
    block->size = size;
    block->next = new_block;
}

struct block* find_block(u64 size) {
    struct block* current = free_list;

    while (current) {
        if (current->free && current->size >= size)
            return current;

        current = current->next;
    }

    return NULL;
}

void* kmalloc(u64 size) {
    if (size == 0) return NULL;
    struct block* block = find_block(size = (size + 7) & ~7ULL);

    if (!block) return NULL;
    if (block->size >= size + sizeof(struct block) + MIN_BLOCK_SIZE) split(block, size);

    block->free = false;
    available_memory -= block->size;
    return block + 1;
}

void coalesce() {
    struct block* current = free_list;

    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += sizeof(struct block) + current->next->size;
            current->next = current->next->next;
        }
        else {
            current = current->next;
        }
    }
}

void kfree(void* ptr) {
    if (!ptr) return;
    struct block* block = ((struct block*)ptr - 1);
    if (block-> free) return;
    block->free = true;
    available_memory += block->size;
    coalesce();
}

void *krealloc(void* ptr, u64 size) {
    size = (size + 7) & ~7ULL;
    if (!ptr) return kmalloc(size);
    if (size == 0) { kfree(ptr); return NULL; }

    struct block* block = ((struct block*)ptr ) - 1;
    if (block->size >= size) {
        if (block->size >= size + sizeof(struct block) + MIN_BLOCK_SIZE) split(block, size);
        return ptr;
    }
    if (block->next && block->next->free && block->size + sizeof(struct block) + block->next->size >= size) {
        block->size += sizeof(struct block) + block->next->size;
        block->next = block->next->next;
        if (block->size >= size + sizeof(struct block) + MIN_BLOCK_SIZE) split(block, size);
        return ptr;
    }

    void* new_ptr = kmalloc(size);
    if (!new_ptr) return NULL;
    memcpy(new_ptr, ptr, block->size);
    kfree(ptr);

    return new_ptr;
}