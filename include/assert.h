#ifndef _ADAMANTINE_ASSERT_H
#define _ADAMANTINE_ASSERT_H

#include <stdint.h>

/*
#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

/* Define the assert function *
#ifndef assert
#define assert(msg)     __assert(msg, __FILE__, __LINE__);
#endif

/* Function Templates *
extern void __assert(char *msg, char *filename, unsigned int lineno);
*/

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b));

extern void panic(const char *message, const char *file, uint32_t line);
extern void panic_assert(const char *file, uint32_t line, const char *desc);

#endif  // !_ADAMANTINE_ASSERT_H
