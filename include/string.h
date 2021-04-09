#ifndef _AOS_STRING_H
#define _AOS_STRING_H       1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

// Declare char * functions:
int memcmp(const void *, const void *, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
char *strcat(char *dest, char *src);
char *strchr(const char *str, int c);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, char *src);
char *itoa(int value, char *str, int base);
void to_lower(char *str);
void to_upper(char *str);
size_t strlen(const char *s);
size_t str_backspace(char *str, char c);
size_t strsplit(char *str, char delim);
char *strtok(char *string, const char *delim);
size_t strspn(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);

#if defined(__cplusplus)
}
#endif

#endif  // !_AOS_STRING_H
