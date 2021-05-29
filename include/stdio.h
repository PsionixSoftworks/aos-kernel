#ifndef _ADAMANTINE_STDIO_H
#define _ADAMANTINE_STDIO_H        1

#if defined(__cplusplus)
extern "C" {
#endif

int printf(const char *__restrict, ...);
int putchar(int);
int puts(const char *);

#if defined(__cplusplus)
}
#endif

#endif  // !_ADAMANTINE_STDIO_H
