#ifndef _ADAMANTINE_STDLIB_H
#define _ADAMANTINE_STDLIB_H       1

#include <stdint.h>
#include <adamantine/aos-defs.h>

EXTERN void *malloc(size_t size);
EXTERN void *calloc(size_t num, size_t size);
EXTERN void *realloc(void *ptr, size_t new_size);
EXTERN void free(void *ptr);
EXTERN void * aligned_alloc(size_t alignment, size_t size);
EXTERN char *itoa(int value, char * str, int base);

#endif  // !_ADAMANTINE_STDLIB_H
