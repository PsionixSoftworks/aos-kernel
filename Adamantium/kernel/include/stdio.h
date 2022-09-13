#ifndef _ADAMANTINE_STDIO_H
#define _ADAMANTINE_STDIO_H        1

#include <adamantium/aos-defs.h>

#ifdef __cplusplus
extern "C" {
#endif

void putchar(char);
void puts(const char*);
void printf(const char *__restrict, ...);
char getchar(void);
char *gets(char *);

#ifdef __cplusplus
}
#endif
#endif  // !_ADAMANTINE_STDIO_H
