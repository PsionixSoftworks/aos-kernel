/*
 *  File: mem-util.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

// Includes go here:
#include <kernel/memory/mm.h>
#include <kernel/system/terminal.h>
#include <kernel/system/io.h>
#include <adamantine/mutex.h>
#include <adamantine/aos-types.h>

MODULE("Memory-Util", "0.01a");

#define MAX_PAGE_ALLOCS		32

uint32_t last_alloc 	= 0;
uint32_t heap_end		= 0;
uint32_t heap_begin 	= 0;
uint32_t pheap_begin 	= 0;
uint32_t pheap_end 	= 0;
uint32_t memory_used 	= 0;
uint8_t *pheap_desc 	= 0;

EXTERN uint32_t kernel_end;
uint32_t placement_address = (uint32_t)(&kernel_end);

void 
mm_init(uint32_t kernel_end) 
{
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = 0x400000;
	pheap_begin = pheap_end - (MAX_PAGE_ALLOCS * 4096);
	heap_end = pheap_begin;
	memset((string)heap_begin, 0, heap_end - heap_begin);
	pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALLOCS);

	terminal_printf("[INFO]: Memory Module is initialized!\n");
	terminal_printf("[INFO]: Kernel heap begins at 0x%x\n", last_alloc);
}

void 
free(void *mem) 
{
	alloc_t *alloc = (mem - sizeof(alloc_t));
	memory_used -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}

void *
malloc(size_t size) 
{
	if (!size) return 0;
	uint8_t *mem = (uint8_t *)heap_begin;
	while ((uint32_t)mem < last_alloc) 
	{
		alloc_t *a = (alloc_t *)mem;
		if (!a->size)
			goto nalloc;
		if (a->status) 
		{
			mem += a->size;
			mem += sizeof(alloc_t);
			mem += 4;
			continue;
		}

		if (a->size >= size) 
		{
			a->status = 1;

			//terminal_printf("RE:Allocated %d bytes from %d to %d...\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size);

			memset(mem + sizeof(alloc_t), 0, size);
			memory_used += size + sizeof(alloc_t);
			return ((void *)(mem + sizeof(alloc_t)));
		}
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

	nalloc:;
	if (last_alloc + size + sizeof(alloc_t) >= heap_end) 
	{
		PANIC("Cannot allocate. Out of memory...");
	}
	alloc_t *alloc = (alloc_t *)last_alloc;
	alloc->status = 1;
	alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(alloc_t);
	last_alloc += 4;

	memory_used += size + 4 + sizeof(alloc_t);
	memset((void *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);

	return ((void *)((uint32_t)alloc + sizeof(alloc_t)));
}

void *
memchr(register const void *str, int c, size_t n)
{
    const uint8_t *source = (const uint8_t *)str;

    while (n-- > 0)
    {
        if (*source == c)
        {
            return (void *)source;
        }
        source++;
    }
    return (NULL);
}

int
memcmp(const void *str1, const void *str2, size_t n)
{
    register const uint8_t *s1 = (const uint8_t *)str1;
    register const uint8_t *s2 = (const uint8_t *)str2;

    while (n-- > 0)
    {
        if (*s1++ != *s2++)
        {
            return (s1[-1] < s2[-1] ? -1 : 1);
        }
    }
    return (0);
}

void *
memcpy(void *dest, const void *src, size_t n) 
{
	char *d = dest;
    const char *s = src;
    while (n--)
    {
        *d++ = *s++;
    }
    return (dest);
}

void *
memmove(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    
    if (d < s)
    {
        while (n--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        const char *lasts = s + (n - 1);
        char *lastd = d + (n - 1);
        while (n--)
        {
            *lastd-- = *lasts--;
        }
    }
    return (dest);
}

void *
memset(void *dest, int c, size_t n)
{
    uint8_t *ptr = dest;
    while (n-- > 0)
    {
        *ptr++ = c;
    }
    return (dest);
}

/* James Molloy... */
uint32_t
kmalloc_int(uint32_t size, uint32_t align, uint32_t *physical_address)
{
	if ((align == 1) && (placement_address & 0xFFFFF000))
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	if (physical_address)
	{
		*physical_address = placement_address;
	}
	uint32_t Temp = placement_address;
	placement_address += size;
	return (Temp);
}

uint32_t
kmalloc_a(uint32_t size)
{
	return (kmalloc_int(size, 1, 0));
}

uint32_t
kmalloc_p(uint32_t size, uint32_t *physical_address)
{
	return (kmalloc_int(size, 0, physical_address));
}

uint32_t
kmalloc_ap(uint32_t size, uint32_t *physical_address)
{
	return (kmalloc_int(size, 1, physical_address));
}

uint32_t
kmalloc(uint32_t size)
{
	return (kmalloc_int(size, 0, 0));
}
