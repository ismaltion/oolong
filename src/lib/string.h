#ifndef STRING_H
#define STRING_H

#include "stddef.h"

u32 strlen(const char* string); // Returns the length of an array of characters.
void strcpy(char* string_dest, const char* string_src); // Copies an array of characters to somewhere.
void strncpy(char* string_dest, const char* string_src, u32 limit); // Copies an array of characters to somewhere but with a length limit.
void strcat(char* dest, const char* src); // Concatenates two strings.
void strncat(char* dest, const char* src, u32 limit); // Concatenates two strings but with a length limit.
bool streq(const char* string_1, const char* string_2); // Returns true if two strings are equal, or false if they aren't.
bool strneq(const char* string_1, const char* string_2, u32 limit); // Same as streq but with a length limit.
char* itoa(u32 num, char* string_1, u32 size); // Converts u32 to array of chars.
char* itoa_hex(u32 num, char *string_1); // Converts a u32 to a hexadecimal string.
u32 atoi(const char *string_1); // Converts an array of chars to u32.
u32 atoi_hex(const char *string_1);

#endif