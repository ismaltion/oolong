#include "../lib/stdint.h"
#include "../drv/vgatext.h"
#include "../lib/string.h"

#include "heap.h"
#include "console.h"
#include "dev.h"
#include "idt.h"
#include "bugcheck.h"
#include "paging.h"

void kmain(u8 memory_map_location) {
    setup_paging();
    memory_init(memory_map_location);
    idt_init();
    console_init();
    devices_init();

    u32 terminal_id = create_terminal(80, 25);
    u32 monitor_id = register_device(DEV_TYPE_MONITOR, CONN_TYPE_VGA);
    monitor_change_current_terminal(monitor_id, terminal_id);

    print("If you can see this, then the Oolong OS kernel works correctly as it should.\nEnjoy the text I guess, also note this bug: the cursor can't be seen anywhere,\nit should be here ->\n");
    

    u32 random_number = 989123;
    char string[20];
    
    print("itoa test: ");
    print(itoa(random_number, string, 5));

    KBUGCHK(KBUGCHK_MANUALLY_TRIGGERED);
}