#ifndef KBUGCHK_H
#define KBUGCHK_H

#include "../lib/stddef.h"

enum KBUGCHK_REASONS {
    KBUGCHK_UNKNOWN,
    KBUGCHK_MANUALLY_TRIGGERED,
    KBUGCHK_DOUBLE_FAULT,
    KBUGCHK_INSUFFICIENT_KERNEL_MEMORY
};

void KBUGCHK_get_string_reason(const enum KBUGCHK_REASONS reason, char* buffer);
void KBUGCHK(const enum KBUGCHK_REASONS reason);

#endif