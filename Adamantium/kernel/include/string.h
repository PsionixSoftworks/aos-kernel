#ifndef _ADAMANTINE_STRING_H
#define _ADAMANTINE_STRING_H       1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL	((void*)0)
#endif

/* Function Templates */
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
void append(char s[], char n);
size_t strlen(const char *s);
size_t str_backspace(char *str, char c);
size_t strsplit(char *str, char delim);
char *strtok(char *string, const char *delim);
size_t strspn(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif
#endif  // !_ADAMANTINE_STRING_H
