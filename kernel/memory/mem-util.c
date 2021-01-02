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
#include <string.h>

#define MAX_PAGE_ALLOCS		32

extern uint32_t kernel_end;
uint32_t placement_address 	= (uint32_t)&kernel_end;

void 
mm_init(uint32_t kernel_end) 
{
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = 0x400000;
	pheap_begin = pheap_end - (MAX_PAGE_ALLOCS * 4096);
	heap_end = pheap_begin;
	memset((char *)heap_begin, 0, heap_end - heap_begin);
	pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALLOCS);

	terminal_printf("[INFO]: Memory Module is initialized!\n");
	terminal_printf("[INFO]: Kernel heap begins at 0x%x\n", last_alloc);
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
