#ifndef _ADAMANTINE_STDIO_H
#define _ADAMANTINE_STDIO_H        1

#include <adamantine/aos-defs.h>

/* Function Templates */
EXTERN int getchar(void);
EXTERN char *gets(char *);
EXTERN int printf(const char *__restrict, ...);			// Print formatted string
EXTERN int putchar(int);								// Print single character
EXTERN int puts(const char *);							// Print string

#endif  // !_ADAMANTINE_STDIO_H
