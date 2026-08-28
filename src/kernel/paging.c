#include "paging.h"
#include "../lib/stddef.h"

void define_page_directory_entry(struct page_directory_entry* pg_entry, bool is_user, u32 address) {
    pg_entry->present = 1;
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

void define_page_table_entry(struct page_table_entry* pg_entry, bool is_user, u32 address) {
    pg_entry->present = 1;
    pg_entry->read_write = 1;
    pg_entry->user_supervisor = is_user;
    pg_entry->page_write_thru = 0;
    pg_entry->page_cache_dis = 0;
    pg_entry->accessed = 0;
    pg_entry->dirty = 0;
    pg_entry->page_attribute = 0;
}