#ifndef DEVICES_H
#define DEVICES_H
#define MAX_DEVICES 64

#include "../lib/stddef.h"
#include "console.h"

enum device_type {
    UNKNOWN,
    MONITOR,
    KEYBOARD,
    DISK
};

enum connection_type {
    UNKNOWN,
    VIRTUAL,
    PS2,
    VGA,
    ATA
};

enum disk_partition_type {
    UNKNOWN,
    MBR,
    GPT
};

struct monitor_properties {
    u32 width;
    u32 height;
    bool is_text;
    u32 current_terminal;
};

struct disk_properties {
    u32 bytes_per_sector;
    u64 total_sectors;
    enum disk_partition_type partition_type;
};

struct device {
    enum device_type dtype;
    enum connection_type ctype;
    void* device_properties;
    bool in_use;
};

struct device devices[MAX_DEVICES];
u32 total_devices = 0;

u32 register_device(enum device_type type, enum connection_type con_type);

#endif