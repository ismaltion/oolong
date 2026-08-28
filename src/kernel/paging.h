#ifndef PAGING_H
#define PAGING_H

#include "../lib/stddef.h"

struct page_directory_entry {
    u32 present         : 1;
    u32 read_write      : 1;
    u32 user_supervisor : 1;
    u32 page_write_thru : 1;
    u32 page_cache_dis  : 1;
    u32 accessed        : 1;
    u32 dirty           : 1;
    u32 page_size       : 1;
    u32 available       : 4;
    u32 addr_31_12      : 20;
} __attribute__((packed));

struct page_table_entry {
    u32 present         : 1;
    u32 read_write      : 1;
    u32 user_supervisor : 1;
    u32 page_write_thru : 1;
    u32 page_cache_dis  : 1;
    u32 accessed        : 1;
    u32 dirty           : 1;
    u32 page_attribute  : 1;
    u32 global          : 1;
    u32 avl             : 3;
    u32 addr_31_12      : 20;
} __attribute__((packed));

#endif