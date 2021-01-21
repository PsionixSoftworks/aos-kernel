#ifndef _AOS_STDLIB_H
#define _AOS_STDLIB_H       1

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t new_size);
void free(void *ptr);
void * aligned_alloc(size_t alignment, size_t size);

char *itoa(int value, char * str, int base);

#if defined(__cplusplus)
}
#endif

#endif  // !_AOS_STDLIB_H
