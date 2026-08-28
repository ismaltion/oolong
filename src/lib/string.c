#include "string.h"
#include "stddef.h"

u32 strlen(const char* string) {
    u32 length = 0;
    while (string[length] != 0) {
        length++;
    }
    return length;
}

void strcpy(char* string_dest, const char* string_src) {
    u32 i = 0;
    while (string_src[i] != 0) {
        string_dest[i] = string_src[i];
        i++;
    }
    string_dest[i] = 0;
}

void strncpy(char* string_dest, const char* string_src, u32 limit) {
    if (limit == 0) return;
    u32 i = 0;
    while (string_src[i] != 0 && i < limit) {
        string_dest[i] = string_src[i];
        i++;
    }
    while (i < limit) {
        string_dest[i++] = 0;
    }
}

void strcat(char* dest, const char* src) {
    u32 i = strlen(dest);
    u32 j = 0;
    while (src[j] != 0) {
        dest[i++] = src[j++];
    }
    dest[i] = 0;
}

void strncat(char* dest, const char* src, u32 limit) {
    u32 i = strlen(dest);
    u32 j = 0;
    while (src[j] != 0 && j < limit) {
        dest[i++] = src[j++];
    }
    dest[i] = 0;
}

bool streq(const char* string_1, const char* string_2) {
    u32 i = 0;
    while (string_1[i] != 0 && string_2[i] != 0) {
        if (string_1[i] != string_2[i]) return false;
        i++;
    }
    if (string_1[i] != string_2[i]) return false;
    return true;
}

bool strneq(const char* string_1, const char* string_2, u32 limit) {
    u32 i = 0;
    while (i < limit) {
        if (string_1[i] != string_2[i]) {
            return false;
        }
        if (string_1[i++] == 0) {
            return true;
        }
    }
    return true;
}

char itoa(u32 a, char *buf) {
    u32 pos = 11;
    buf[pos] = '\0';

    if (a == 0) {
        buf[--pos] = '0';
        return buf[pos];
    }

    bool negative = a < 0;

    if (!negative) a = -a;

    while(a < 0) {
        buf[--pos] = '0' - (a % 10);
    }

    return buf[pos];
}