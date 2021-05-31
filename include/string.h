#ifndef _ADAMANTINE_STRING_H
#define _ADAMANTINE_STRING_H       1

#include <stdint.h>
#include <adamantine/aos-defs.h>

/* Function Templates */
extern int memcmp(const void *, const void *, size_t);
extern void *memcpy(void *__restrict, const void *__restrict, size_t);
extern void *memmove(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern char *strcat(char *dest, char *src);
extern char *strchr(const char *str, int c);
extern int strcmp(const char *str1, const char *str2);
extern char *strcpy(char *dest, char *src);
extern char *itoa(int value, char *str, int base);
extern void to_lower(char *str);
extern void to_upper(char *str);
extern void append(char s[], char n);
extern size_t strlen(const char *s);
extern size_t str_backspace(char *str, char c);
extern size_t strsplit(char *str, char delim);
extern char *strtok(char *string, const char *delim);
extern size_t strspn(const char *s1, const char *s2);
extern size_t strcspn(const char *s1, const char *s2);

#endif  // !_ADAMANTINE_STRING_H
