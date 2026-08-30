#include "bugcheck.h"
#include "console.h"

#include "../lib/stddef.h"
#include "../lib/string.h"

char permanent_buffer[16];

void KBUGCHK_get_string_reason(const enum KBUGCHK_REASONS reason, char* buffer) {
    switch (reason)
    {
    case KBUGCHK_DOUBLE_FAULT:
        strncpy(buffer, "DOUBLE_FAULT", 32);
        return;
    case KBUGCHK_INSUFFICIENT_KERNEL_MEMORY:
        strncpy(buffer, "INSUFFICIENT_KERNEL_MEMORY", 32);
        return;
    case KBUGCHK_MANUALLY_TRIGGERED:
        strncpy(buffer, "MANUALLY_TRIGGERED", 32);
        return;
    default:
        strncpy(buffer, "UNKNOWN", 32);
        return;
    }
}

void KBUGCHK(const enum KBUGCHK_REASONS reason) {
    __asm__ volatile("cli;");
    char reason_str[32];
    KBUGCHK_get_string_reason(reason, reason_str);
        
    printc("\n\n[!] --- System bug check --- [!]\n", 0x04);
    printc("A critical system error has occurred: ", 0x06);
    printc(reason_str, 0x0f);
    printc("\nSystem has halted. Shut it down or reboot manually.\nESP: 0x", 0x06);

    void *esp_val;

    __asm__ __volatile__(
        "movl %%esp, %0"
        : "=r" (esp_val)
    );

    printc(itoa_hex((u32)esp_val, permanent_buffer), 0x06);
    __asm__ volatile("hlt;");
}