#ifndef _ADAMANTINE_STRING_H
#define _ADAMANTINE_STRING_H       1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

// Declare char * functions:
extern int memcmp(const void *, const void *, size_t);
extern void *memcpy(void *__restrict, const void *__restrict, size_t);
extern void *memmove(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern char *strcat(char *dest, char *src);
extern char *strchr(const char *str, int c);
extern int strcmp(const char *str1, const char *str2);
extern char *strcpy(char *dest, char *src);
extern char *itoa(int value, char *str, int base);
void to_lower(char *str);
void to_upper(char *str);
void append(char s[], char n);
size_t strlen(const char *s);
size_t str_backspace(char *str, char c);
size_t strsplit(char *str, char delim);
char *strtok(char *string, const char *delim);
size_t strspn(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);

#if defined(__cplusplus)
}
#endif

#endif  // !_ADAMANTINE_STRING_H
