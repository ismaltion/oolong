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

// function made by cedkechat01
char* itoa(u32 num, char* string_1, u32 size) {
    // end of string pointer
    int index = size - 1;
    string_1[index] = '\0';

    // handle zero case
    if (num == 0) {
        index = index - 1;
        string_1[index] = '0';
        return &string_1[index];
    }

    // unsigned types cant be negative
    bool negative = false;

    if (num < 0) {
        negative = true;
        num = -num;
    }

    // extract digits right-to-left
    while (num > 0) {
        u32 digit = num % 10; //get last digit
        index = index - 1;    // move left in buffer
        string_1[index] = '0' + digit; // convert to ASCII
        num = num / 10;       // remove last digit
    }

    // add minus sign if needed
    if (negative == true) {
        index = index - 1;
        string_1[index] = '-';
    }

    // return start of string
    return &string_1[index];
}