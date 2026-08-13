#ifndef STRING_H
#define STRING_H

#include "stddef.h"

u32 strlen(const char* string);
void strcpy(char* string_dest, const char* string_src);
void strncpy(char* string_dest, const char* string_src, u32 limit);
void strcat(char* dest, const char* src);
void strncat(char* dest, const char* src, u32 limit);
bool streq(const char* string_1, const char* string_2);
bool strneq(const char* string_1, const char* string_2, u32 limit);

#endif