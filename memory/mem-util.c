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
#include "../include/mem-util.h"
#include "../include/mutex.h"
#include "../include/types.h"
#include "../include/terminal.h"
#include "../include/io.h"
#include "../include/aos-defs.h"

MODULE("mem-util", "0.01a");

#define MAX_PAGE_ALLOCS		32

/* Define mutexes here. */
DEFINE_MUTEX(m_memcpy);

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;

void 
mm_init(uint32_t *kernel_end) 
{
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = 0x400000;
	pheap_begin = pheap_end - (MAX_PAGE_ALLOCS * 4096);
	heap_end = pheap_begin;
	memset((char *)heap_begin, 0, heap_end - heap_begin);
	pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALLOCS);

	terminal_printf("Kernel heap begins at %x\n", last_alloc);
}

void 
mm_print_out(void) 
{
	terminal_printf("Memory Used: %x bytes allocated.\n", memory_used);
}

void 
free(void *mem) 
{
	alloc_t *alloc = (mem - sizeof(alloc_t));
	memory_used -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}

void 
pfree(void *mem) 
{
	if ((mem < pheap_begin) || (mem > pheap_end)) 
		return;

	uint32_t ad = (uint32_t)mem;
	ad -= pheap_begin;
	ad /= 4096;

	pheap_desc[ad] = 0;

	return;
}

char *
pmalloc(size_t size) 
{
	for (int i = 0; i < MAX_PAGE_ALLOCS; i++) 
	{
		if (pheap_desc[i]) 
			continue;
		pheap_desc[i] = 1;
		terminal_print("PAllocated from ");
		terminal_print_value(pheap_begin + i * 4096, 16);
		terminal_print(" to ");
		terminal_print_value(pheap_begin + (i + 1) * 4096, 16);
		terminal_print("\n");

		return ((char *)(pheap_begin + i * 4096));
	}
	terminal_print("pmalloc: FATAL: failure!\n");
	return 0;
}

char *
malloc(size_t size) 
{
	if (!size) return;
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

			terminal_print("RE:Allocated ");
			terminal_print_value(size, 10);
			terminal_print(" bytes from ");
			terminal_print_value(mem + sizeof(alloc_t), 16);
			terminal_print(" to ");
			terminal_print_value(mem + sizeof(alloc_t) + size, 16);

			memset(mem + sizeof(alloc_t), 0, size);
			memory_used += size + sizeof(alloc_t);
			return ((char *)(mem + sizeof(alloc_t)));
		}
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

	nalloc:;
	if (last_alloc + size + sizeof(alloc_t) >= heap_end) 
	{
		PANIC("Cannot allocate. Out of memory...", 0, 0);
	}
	alloc_t *alloc = (alloc_t *)last_alloc;
	alloc->status = 1;
	alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(alloc_t);
	last_alloc += 4;

	memory_used += size + 4 + sizeof(alloc_t);
	memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
	mm_print_out();

	return ((char *)((uint32_t)alloc + sizeof(alloc_t)));
}

void *
memcpy(const void *dest, const void *src, size_t count) 
{
	mutex_lock(&m_memcpy);
	char *dst8 = (char *)dest;
	char *src8 = (char *)src;

	if (count & 1) 
	{
		dst8[0] = src8[0];
		dst8++;
		src8++;
	}

	count /= 2;
	while (count--) 
	{
		dst8[0] = src8[0];
		dst8[1] = src8[1];

		dst8 += 2;
		src8 += 2;
	}
	mutex_unlock(&m_memcpy);
	return ((void *)dest);
}

void *
memset16(void *ptr, uint16_t value, size_t num) 
{
	uint16_t *p = ptr;
	while (num--)
		*p++ = value;
	return (ptr);
}

void *
memset(void *ptr, int value, size_t num) 
{
	unsigned char *p = ptr;
	while (num--)
		*p++ = (unsigned char)value;
	return (ptr);
}
