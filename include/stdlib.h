#ifndef _ADAMANTINE_STDLIB_H
#define _ADAMANTINE_STDLIB_H       1

#include <stdint.h>
#include <adamantine/aos-defs.h>

/* Function Templates */
EXTERN void *malloc(size_t);							// Allocate memory
EXTERN void *calloc(size_t, size_t);					// Calllocate memory?
EXTERN void *realloc(void *, size_t);					// Re-allocate memory?
EXTERN void free(void *);								// Free memory
EXTERN void * aligned_alloc(size_t, size_t);			// ??
EXTERN char *itoa(int, char *, int);					// Convert an integer to a string

#endif  // !_ADAMANTINE_STDLIB_H
