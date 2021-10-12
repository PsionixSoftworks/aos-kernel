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
EXTERN __GLOBAL _PROTO(int memcmp, (const void *, const void *, size_t)                 );
EXTERN __GLOBAL _PROTO(void *memcpy, (void *__restrict, const void *__restrict, size_t) );
EXTERN __GLOBAL _PROTO(void *memmove, (void *, const void *, size_t)                    );
EXTERN __GLOBAL _PROTO(void *memset, (void *, int, size_t)                              );
EXTERN __GLOBAL _PROTO(char *strcat, (char *dest, char *src)                            );
EXTERN __GLOBAL _PROTO(char *strchr, (const char *str, int c)                           );
EXTERN __GLOBAL _PROTO(int strcmp, (const char *str1, const char *str2)                 );   
EXTERN __GLOBAL _PROTO(char *strcpy, (char *dest, char *src)                            );
EXTERN __GLOBAL _PROTO(char *itoa, (int value, char *str, int base)                     );
EXTERN __GLOBAL _PROTO(void to_lower, (char *str)                                       );
EXTERN __GLOBAL _PROTO(void to_upper, (char *str)                                       );
EXTERN __GLOBAL _PROTO(void append, (char s[], char n)                                  );
EXTERN __GLOBAL _PROTO(size_t strlen, (const char *s)                                   );
EXTERN __GLOBAL _PROTO(size_t str_backspace, (char *str, char c)                        );
EXTERN __GLOBAL _PROTO(size_t strsplit, (char *str, char delim)                         );
EXTERN __GLOBAL _PROTO(char *strtok, (char *string, const char *delim)                  );
EXTERN __GLOBAL _PROTO(size_t strspn, (const char *s1, const char *s2)                  );
EXTERN __GLOBAL _PROTO(size_t strcspn, (const char *s1, const char *s2)                 );

#endif
