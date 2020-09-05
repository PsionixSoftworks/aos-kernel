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

MODULE("Memory-Util", "0.01a");

#define MAX_PAGE_ALLOCS		32

/* Define mutexes here. */
DEFINE_mutex(m_memcpy);

udword LastAlloc 	= 0;
udword HeapEnd 		= 0;
udword HeapBegin 	= 0;
udword PHeapBegin 	= 0;
udword PHeapEnd 	= 0;
udword memoryUsed 	= 0;
ubyte *PHeapDesc 	= 0;

EXTERN udword kernel_end;
udword PlacementAddress = (udword)&kernel_end;

void 
mm_init(udword *kernel_end) 
{
	LastAlloc = kernel_end + 0x1000;
	HeapBegin = LastAlloc;
	PHeapEnd = 0x400000;
	PHeapBegin = PHeapEnd - (MAX_PAGE_ALLOCS * 4096);
	HeapEnd = PHeapBegin;
	memset((string)HeapBegin, 0, HeapEnd - HeapBegin);
	PHeapDesc = (ubyte *)malloc(MAX_PAGE_ALLOCS);

	_INFO("memory Module is initialized!");
	terminal_printf("Kernel heap begins at 0x%x\n", LastAlloc);
}

void
MM_PrintOut(void) 
{
	terminal_printf("memory Used: %x bytes allocated.\n", memoryUsed);
}

void 
free(void *mem) 
{
	Alloc_t *Alloc = (mem - sizeof(Alloc_t));
	memoryUsed -= Alloc->size + sizeof(Alloc_t);
	Alloc->status = 0;
}

void 
pfree(void *mem) 
{
	if ((mem < PHeapBegin) || (mem > PHeapEnd)) 
		return;

	udword ad = (udword)mem;
	ad -= PHeapBegin;
	ad /= 4096;

	PHeapDesc[ad] = 0;

	return;
}

void *
pmalloc(size_t size) 
{
	for (size_t i = 0; i < MAX_PAGE_ALLOCS; i++) 
	{
		if (PHeapDesc[i]) 
			continue;
		PHeapDesc[i] = 1;
		terminal_printf("PAllocated from %X to %X.\n", PHeapBegin + i * 4096, PHeapBegin + (i + 1) * 4096);

		return ((string)(PHeapBegin + i * 4096));
	}
	terminal_print("pmalloc: FATAL: failure!\n");
	return (0);
}

void *
malloc(size_t size) 
{
	if (!size) return;
	ubyte *mem = (ubyte *)HeapBegin;
	while ((udword)mem < LastAlloc) 
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
			memoryUsed += size + sizeof(Alloc_t);
			return ((void *)(mem + sizeof(Alloc_t)));
		}
		mem += a->size;
		mem += sizeof(Alloc_t);
		mem += 4;
	}

	nalloc:;
	if (LastAlloc + size + sizeof(Alloc_t) >= HeapEnd) 
	{
		_PANIC("Cannot allocate. Out of memory...");
	}
	Alloc_t *Alloc = (Alloc_t *)LastAlloc;
	Alloc->status = 1;
	Alloc->size = size;

	LastAlloc += size;
	LastAlloc += sizeof(Alloc_t);
	LastAlloc += 4;

	memoryUsed += size + 4 + sizeof(Alloc_t);
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
	if ((align == 1) && (PlacementAddress & 0xFFFFF000))
	{
		PlacementAddress &= 0xFFFFF000;
		PlacementAddress += 0x1000;
	}
	if (physical_address)
	{
		*physical_address = PlacementAddress;
	}
	udword Temp = PlacementAddress;
	PlacementAddress += size;
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
