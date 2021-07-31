#ifndef _AOS_STRING_H
#define _AOS_STRING_H

#include <stdint.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

#ifndef STRING_T
#define STRING_T
#if defined(__cplusplus)
typedef const char *string_t;
#else
typedef char *string_t;
#endif
#endif

/* Function Templates */
EXTERN int memcmp(const void *, const void *, size_t);
EXTERN void *memcpy(void *__restrict, const void *__restrict, size_t);
EXTERN void *memmove(void *, const void *, size_t);
EXTERN void *memset(void *, int, size_t);
EXTERN char *strcat(char *dest, char *src);
EXTERN char *strchr(const char *str, int c);
EXTERN int strcmp(const char *str1, const char *str2);
EXTERN char *strcpy(char *dest, char *src);
EXTERN char *itoa(int value, char *str, int base);
EXTERN void to_lower(char *str);
EXTERN void to_upper(char *str);
EXTERN void append(char s[], char n);
EXTERN size_t strlen(const char *s);
EXTERN size_t str_backspace(char *str, char c);
EXTERN size_t strsplit(char *str, char delim);
EXTERN char *strtok(char *string, const char *delim);
EXTERN size_t strspn(const char *s1, const char *s2);
EXTERN size_t strcspn(const char *s1, const char *s2);

#endif
