#include "dev.h"
#include "../lib/stddef.h"
#include "memory.h"
#include "../drv/vgatext.h"

extern struct terminal output_terminals[MAX_TERMINALS];

void devices_init() {
    memset(devices, 0, sizeof(devices));
}

u32 register_device(enum device_type type, enum connection_type con_type) {
    if (total_devices >= MAX_DEVICES) return 0xEEEE0001;
    devices[total_devices].dtype = type;
    devices[total_devices].ctype = con_type;
    devices[total_devices].in_use = true;
    switch (type)
    {
    case DEV_TYPE_MONITOR:
    {
        struct monitor_properties* monitor_properties = kmalloc(sizeof(struct monitor_properties));
        memset(monitor_properties, 0, sizeof(struct monitor_properties));
        devices[total_devices].device_properties = monitor_properties;
        break;
    }
    default:
        devices[total_devices].device_properties = NULL;
        break;
    }
    return total_devices++;
}

u8 monitor_refresh(u32 device_id) {
    struct monitor_properties* mproperties = devices[device_id].device_properties;
    u32 terminal_id = mproperties->current_terminal;
    switch (devices[device_id].ctype)
    {
    case CONN_TYPE_VGA:
    {
        vgatext_load(output_terminals[terminal_id].content);
        vgatext_update_cursor(output_terminals[terminal_id].cursor_x, output_terminals[terminal_id].cursor_y);
        return 0;
    }
    default:
        return 4;
    }
}

u8 monitor_change_current_terminal(u32 device_id, u32 terminal_id) {
    if (device_id >= MAX_DEVICES || !devices[device_id].in_use) return 1;
    if (devices[device_id].dtype != DEV_TYPE_MONITOR) return 2;
    if (terminal_id >= MAX_TERMINALS || !output_terminals[terminal_id].in_use) return 3;

    struct monitor_properties* mproperties = devices[device_id].device_properties;
    mproperties->current_terminal = terminal_id;

    monitor_refresh(device_id);
    return 0;
}