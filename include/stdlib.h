#ifndef _ADAMANTINE_STDLIB_H
#define _ADAMANTINE_STDLIB_H       1

#include <stdint.h>
#include <adamantine/aos-defs.h>

/* Function Templates */
EXTERN void *malloc(size_t);							// Allocate memory
EXTERN void *calloc(size_t, size_t);					// Calllocate memory?
EXTERN void *realloc(void *, size_t);					// Re-allocate memory?
//EXTERN void free(void *);								// Free memory
EXTERN void * aligned_alloc(size_t, size_t);			// ??
EXTERN char *itoa(int, char *, int);					// Convert an integer to a string
EXTERN void *memchr(register const void *str, int c, size_t n);
EXTERN int memcmp(const void *str1, const void *str2, size_t n);
EXTERN void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size);
EXTERN void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);

#endif  // !_ADAMANTINE_STDLIB_H
