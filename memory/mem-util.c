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
#include <memory/mm.h>
#include <adamantine/mutex.h>
#include <adamantine/aos-types.h>
#include <system/terminal.h>
#include <system/io.h>

MODULE("Memory-Util", "0.01a");

#define MAX_PAGE_ALLOCS		32

/* Define mutexes here. */
DEFINE_mutex(m_memcpy);

udword last_alloc 	= 0;
udword heap_end		= 0;
udword heap_begin 	= 0;
udword pheap_begin 	= 0;
udword pheap_end 	= 0;
udword memory_used 	= 0;
ubyte *pheap_desc 	= 0;

EXTERN udword kernel_end;
udword placement_address = (udword)&kernel_end;

void 
mm_init(udword kernel_end) 
{
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = 0x400000;
	pheap_begin = pheap_end - (MAX_PAGE_ALLOCS * 4096);
	heap_end = pheap_begin;
	memset((string)heap_begin, 0, heap_end - heap_begin);
	pheap_desc = (ubyte *)malloc(MAX_PAGE_ALLOCS);

	//_INFO("memory Module is initialized!");
	//terminal_printf("Kernel heap begins at 0x%x\n", last_alloc);
	//system_logf(INFORMATION, "Memory Heap is initialized!\n");
	//system_logf(INFORMATION, "Kenel Heap starts at 0x%x.\n", last_alloc);
}

void
MM_PrintOut(void) 
{
	//system_logf(INFORMATION, "Memory Used: %x bytes allocated.\n", memory_used);
}

void 
free(void *mem) 
{
	Alloc_t *Alloc = (mem - sizeof(Alloc_t));
	memory_used -= Alloc->size + sizeof(Alloc_t);
	Alloc->status = 0;
}

void 
pfree(void *mem) 
{
	if ((mem < pheap_begin) || (mem > pheap_end)) 
		return;

	udword ad = (udword)mem;
	ad -= pheap_begin;
	ad /= 4096;

	pheap_desc[ad] = 0;

	return;
}

void *
pmalloc(size_t size) 
{
	for (size_t i = 0; i < MAX_PAGE_ALLOCS; i++) 
	{
		if (pheap_desc[i]) 
			continue;
		pheap_desc[i] = 1;
		terminal_printf("PAllocated from %X to %X.\n", pheap_begin + i * 4096, pheap_begin + (i + 1) * 4096);

		return ((string)(pheap_begin + i * 4096));
	}
	terminal_printf("pmalloc: FATAL: failure!\n");
	return (0);
}

void *
malloc(size_t size) 
{
	if (!size) return;
	ubyte *mem = (ubyte *)heap_begin;
	while ((udword)mem < last_alloc) 
	{
		Alloc_t *a = (Alloc_t *)mem;
		if (!a->size)
			goto nalloc;
		if (a->status) 
		{
			mem += a->size;
			mem += sizeof(Alloc_t);
			mem += 4;
			continue;
		}

		if (a->size >= size) 
		{
			a->status = 1;

			terminal_printf("RE:Allocated %d bytes from %d to %d...\n", size, mem + sizeof(Alloc_t), mem + sizeof(Alloc_t) + size);

			memset(mem + sizeof(Alloc_t), 0, size);
			memory_used += size + sizeof(Alloc_t);
			return ((void *)(mem + sizeof(Alloc_t)));
		}
		mem += a->size;
		mem += sizeof(Alloc_t);
		mem += 4;
	}

	nalloc:;
	if (last_alloc + size + sizeof(Alloc_t) >= heap_end) 
	{
		//_PANIC("Cannot allocate. Out of memory...");
	}
	Alloc_t *Alloc = (Alloc_t *)last_alloc;
	Alloc->status = 1;
	Alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(Alloc_t);
	last_alloc += 4;

	memory_used += size + 4 + sizeof(Alloc_t);
	memset((void *)((udword)Alloc + sizeof(Alloc_t)), 0, size);
	//MM_PrintOut();

	return ((void *)((udword)Alloc + sizeof(Alloc_t)));
}

void *
memcpy(const void *destination, const void *source, size_t Count) 
{
	mutex_lock(&m_memcpy);
	string DST8 = (string)destination;
	string SRC8 = (string)source;

	if (Count & 1) 
	{
		DST8[0] = SRC8[0];
		DST8++;
		SRC8++;
	}

	Count /= 2;
	while (Count--) 
	{
		DST8[0] = SRC8[0];
		DST8[1] = SRC8[1];

		DST8 += 2;
		SRC8 += 2;
	}
	mutex_unlock(&m_memcpy);
	return ((void *)destination);
}

void *
memset16(void *pointer,  udword value, size_t size)
{
	uword *p = pointer;
	while (size--)
		*p++ = value;
	return (pointer);
}

void *
memset(void *pointer, dword value, size_t Number) 
{
	ubyte *p = pointer;
	while (Number--)
		*p++ = (ubyte)value;
	return (pointer);
}

/* James Molloy... */
udword
kmalloc_int(udword size, udword align, udword *physical_address)
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
	udword Temp = placement_address;
	placement_address += size;
	return (Temp);
}

udword
kmalloc_a(udword size)
{
	return (kmalloc_int(size, 1, 0));
}

udword
kmalloc_p(udword size, udword *physical_address)
{
	return (kmalloc_int(size, 0, physical_address));
}

udword
kmalloc_ap(udword size, udword *physical_address)
{
	return (kmalloc_int(size, 1, physical_address));
}

udword
kmalloc(udword size)
{
	return (kmalloc_int(size, 0, 0));
}
