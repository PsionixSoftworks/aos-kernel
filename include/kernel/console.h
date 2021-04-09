#ifndef _AOS_CONSOLE_H
#define _AOS_CONSOLE_H

#include <stdint.h>

struct aos_console console;

struct aos_in
{
    char *(*readln)(void);
};

struct aos_out
{
    void (*putchar)(char c);
    void (*print)(char *str);
    void (*printf)(const char *format, ...);
};

struct aos_console
{
    struct aos_in in;
    struct aos_out out;
};

extern char *readln(void);
extern void putchar(char c);
extern void print(char *str);
extern void printf(const char *format, ...);

#endif
