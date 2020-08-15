#ifndef ADAMANTINE_MEMORY_UTILITY
#define ADAMANTINE_MEMORY_UTILITY

#include "types.h"

#if KERNEL32

#if defined(__cplusplus)
extern "C" {
#endif

// Declare the allocation type:
typedef struct 
{
	uint8_t status;
	size_t size;
} alloc_t;

extern void mm_init(uint32_t *kernel_end);
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);

extern char *pmalloc(size_t size);
extern char *malloc(size_t size);
extern void pfree(void *mem);
extern void free(void *mem);

extern void *memcpy(const void *dest, const void *src, size_t num);
extern void *memset(void *ptr, int value, size_t num);
extern void *memset16(void *ptr,  uint16_t value, size_t num);

#if defined(__cplusplus)
}
#endif

#endif
#endif	// !ADAMANTINE_MEMORY_UTILITY
