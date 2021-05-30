#ifndef _ADAMANTINE_STDIO_H
#define _ADAMANTINE_STDIO_H        1

#include <adamantine/aos-defs.h>

EXTERN int printf(const char *__restrict, ...);
EXTERN int putchar(int);
EXTERN int puts(const char *);

#endif  // !_ADAMANTINE_STDIO_H
