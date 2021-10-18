#ifndef _AOS_STRING_H
#define _AOS_STRING_H

#define _USES_MACROS

#include <common.h>
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
__GLOBAL int memcmp(const void *, const void *, size_t);
__GLOBAL void *memcpy(void *__restrict, const void *__restrict, size_t);
__GLOBAL void *memmove(void *, const void *, size_t);
__GLOBAL void *memset(void *, int, size_t);
__GLOBAL char *strcat(char *dest, char *src);
__GLOBAL char *strchr(const char *str, int c);
__GLOBAL int strcmp(const char *str1, const char *str2);   
__GLOBAL char *strcpy(char *dest, char *src);
__GLOBAL char *itoa(int value, char *str, int base);
__GLOBAL void to_lower(char *str);
__GLOBAL void to_upper(char *str);
__GLOBAL void append(char s[], char n);
__GLOBAL size_t strlen(const char *s);
__GLOBAL size_t str_backspace(char *str, char c);
__GLOBAL size_t strsplit(char *str, char delim);
__GLOBAL char *strtok(char *string, const char *delim);
__GLOBAL size_t strspn(const char *s1, const char *s2);
__GLOBAL size_t strcspn(const char *s1, const char *s2);

#endif
