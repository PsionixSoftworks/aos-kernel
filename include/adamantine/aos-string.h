#ifndef _AOS_STRING_H
#define _AOS_STRING_H

#include <stdint.h>
#include <macros.h>

#ifndef STRING_T
#define STRING_T
#if defined(__cplusplus)
typedef const char *string_t;
#else
typedef char *string_t;
#endif
#endif

/* Function Templates */
__GLOBAL KERNEL_API int memcmp(const void *, const void *, size_t);
__GLOBAL KERNEL_API void *memcpy(void *__restrict, const void *__restrict, size_t);
__GLOBAL KERNEL_API void *memmove(void *, const void *, size_t);
__GLOBAL KERNEL_API void *memset(void *, int, size_t);
__GLOBAL KERNEL_API char *strcat(char *dest, char *src);
__GLOBAL KERNEL_API char *strchr(const char *str, int c);
__GLOBAL KERNEL_API int strcmp(const char *str1, const char *str2);   
__GLOBAL KERNEL_API char *strcpy(char *dest, char *src);
__GLOBAL KERNEL_API char *itoa(int value, char *str, int base);
__GLOBAL KERNEL_API void to_lower(char *str);
__GLOBAL KERNEL_API void to_upper(char *str);
__GLOBAL KERNEL_API void append(char s[], char n);
__GLOBAL KERNEL_API size_t strlen(const char *s);
__GLOBAL KERNEL_API size_t str_backspace(char *str, char c);
__GLOBAL KERNEL_API size_t strsplit(char *str, char delim);
__GLOBAL KERNEL_API char *strtok(char *string, const char *delim);
__GLOBAL KERNEL_API size_t strspn(const char *s1, const char *s2);
__GLOBAL KERNEL_API size_t strcspn(const char *s1, const char *s2);

#endif
