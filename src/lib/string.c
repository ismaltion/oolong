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
char *itoa(u32 num, char *string_1, u32 base) {
    u32 i = 0;

    bool negative = false;

    if (num == 0) {
        string_1[i++] = '0';
        string_1[i] = '\0';
        return string_1;
    }

    if (num < 0 && base == 10) {
        negative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        string_1[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (negative == true) string_1[i++] = '-';

    string_1[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        swap((string_1 + start), (string_1 + end));
        start++;
        end--;
    }

    return string_1;
}

u32 atoi(const char *s) {
    u32 i, n;

    for (i = 0; s[i] == ' ' || (unsigned)s[i]-'\t' < 5; i++);

    u32 sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (n = 0; (unsigned)s[i]-'0' < 10; i++)
        n = 10 * n + (s[i] - '0');

    return sign * n;
}