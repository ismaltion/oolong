#include "paging.h"
#include "../lib/memory.h"
#include "../lib/stddef.h"

#define PHYSICAL_KERNEL_ADDRESS 0x7e00

struct page_directory_entry main_page_directory[1024] __attribute__((aligned(4096)));
struct page_table_entry higher_half_page_table[1024] __attribute__((aligned(4096)));

void define_page_directory_entry(struct page_directory_entry* pg_entry, u32 address, bool is_user, bool present) {
    pg_entry->present = present;
    pg_entry->read_write = 1;
    pg_entry->user_supervisor = is_user;
    pg_entry->page_write_thru = 0;
    pg_entry->page_cache_dis = 0;
    pg_entry->accessed = 0;
    pg_entry->dirty = 0;
    pg_entry->page_size = 0;
    pg_entry->available = 0;
    pg_entry->addr_31_12 = address >> 12;
};

void define_page_table_entry(struct page_table_entry* pg_entry, u32 address, bool is_user, bool present) {
    pg_entry->present = present;
    pg_entry->read_write = 1;
    pg_entry->user_supervisor = is_user;
    pg_entry->page_write_thru = 0;
    pg_entry->page_cache_dis = 0;
    pg_entry->accessed = 0;
    pg_entry->dirty = 0;
    pg_entry->page_attribute = 0;
    pg_entry->global = 0;
    pg_entry->available = 0;
    pg_entry->addr_31_12 = address >> 12;
}

void setup_paging() {
    memset(main_page_directory, 0, sizeof(main_page_directory));
    memset(higher_half_page_table, 0, sizeof(higher_half_page_table));

    define_page_directory_entry(&main_page_directory[0], (u32)higher_half_page_table, false, true);
    define_page_directory_entry(&main_page_directory[768], (u32)higher_half_page_table, false, true);

    u32 phys_addr = 0;
    for (u32 i = 0; i <= 256; i++) {
        define_page_table_entry(&higher_half_page_table[i], phys_addr, false, true);
        phys_addr += 0x1000;
    }
    
    load_page_directory((u32*)main_page_directory);
    enable_paging();
}