#include "paging.h"
#include "../lib/stddef.h"

void define_page_directory_entry(struct page_directory_entry* pg_entry) {
    pg_entry->present = 1;
    
};