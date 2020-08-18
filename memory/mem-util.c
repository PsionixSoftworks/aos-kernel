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

MODULE("MemoryUtility", "0.01a");

#define MAX_PAGE_ALLOCS		32

/* Define mutexes here. */
DEFINE_MUTEX(m_memcpy);

UDWORD LastAlloc 	= 0;
UDWORD HeapEnd 		= 0;
UDWORD HeapBegin 	= 0;
UDWORD PHeapBegin 	= 0;
UDWORD PHeapEnd 	= 0;
UDWORD MemoryUsed 	= 0;
UBYTE *PHeapDesc 	= 0;

VOID 
MM_Init(UDWORD *kernel_end) 
{
	LastAlloc = kernel_end + 0x1000;
	HeapBegin = LastAlloc;
	PHeapEnd = 0x400000;
	PHeapBegin = PHeapEnd - (MAX_PAGE_ALLOCS * 4096);
	HeapEnd = PHeapBegin;
	MemSet((STRING)HeapBegin, 0, HeapEnd - HeapBegin);
	PHeapDesc = (UBYTE *)Malloc(MAX_PAGE_ALLOCS);

	TerminalPrintf("Kernel heap begins at %x\n", LastAlloc);
}

VOID
MM_PrintOut(VOID) 
{
	TerminalPrintf("Memory Used: %x bytes allocated.\n", MemoryUsed);
}

VOID 
Free(VOID *Mem) 
{
	Alloc_t *Alloc = (Mem - sizeof(Alloc_t));
	MemoryUsed -= Alloc->Size + sizeof(Alloc_t);
	Alloc->Status = 0;
}

VOID 
PFree(VOID *Mem) 
{
	if ((Mem < PHeapBegin) || (Mem > PHeapEnd)) 
		return;

	UDWORD ad = (UDWORD)Mem;
	ad -= PHeapBegin;
	ad /= 4096;

	PHeapDesc[ad] = 0;

	return;
}

VOID *
PMalloc(SIZE Size) 
{
	for (DWORD i = 0; i < MAX_PAGE_ALLOCS; i++) 
	{
		if (PHeapDesc[i]) 
			continue;
		PHeapDesc[i] = 1;
		TerminalPrintf("PAllocated from %X to %X.\n", PHeapBegin + i * 4096, PHeapBegin + (i + 1) * 4096);

		return ((STRING)(PHeapBegin + i * 4096));
	}
	TerminalPrint("PMalloc: FATAL: failure!\n");
	return (0);
}

VOID *
Malloc(SIZE Size) 
{
	if (!Size) return;
	UBYTE *Mem = (UBYTE *)HeapBegin;
	while ((UDWORD)Mem < LastAlloc) 
	{
		Alloc_t *a = (Alloc_t *)Mem;
		if (!a->Size)
			goto nalloc;
		if (a->Status) 
		{
			Mem += a->Size;
			Mem += sizeof(Alloc_t);
			Mem += 4;
			continue;
		}

		if (a->Size >= Size) 
		{
			a->Status = 1;

			TerminalPrintf("RE:Allocated %d bytes from %d to %d...\n", Size, Mem + sizeof(Alloc_t), Mem + sizeof(Alloc_t) + Size);

			MemSet(Mem + sizeof(Alloc_t), 0, Size);
			MemoryUsed += Size + sizeof(Alloc_t);
			return ((VOID *)(Mem + sizeof(Alloc_t)));
		}
		Mem += a->Size;
		Mem += sizeof(Alloc_t);
		Mem += 4;
	}

	nalloc:;
	if (LastAlloc + Size + sizeof(Alloc_t) >= HeapEnd) 
	{
		PANIC("Cannot allocate. Out of memory...", 0, 0);
	}
	Alloc_t *Alloc = (Alloc_t *)LastAlloc;
	Alloc->Status = 1;
	Alloc->Size = Size;

	LastAlloc += Size;
	LastAlloc += sizeof(Alloc_t);
	LastAlloc += 4;

	MemoryUsed += Size + 4 + sizeof(Alloc_t);
	MemSet((VOID *)((UDWORD)Alloc + sizeof(Alloc_t)), 0, Size);
	MM_PrintOut();

	return ((VOID *)((UDWORD)Alloc + sizeof(Alloc_t)));
}

VOID *
MemCpy(const VOID *Destination, const VOID *Source, SIZE Count) 
{
	MutexLock(&m_memcpy);
	STRING DST8 = (STRING)Destination;
	STRING SRC8 = (STRING)Source;

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
	MutexUnlock(&m_memcpy);
	return ((VOID *)Destination);
}

VOID *
MemSet16(VOID *Pointer,  UDWORD Value, SIZE Size)
{
	UWORD *p = Pointer;
	while (Size--)
		*p++ = Value;
	return (Pointer);
}

VOID *
MemSet(VOID *Pointer, DWORD Value, SIZE Number) 
{
	UBYTE *p = Pointer;
	while (Number--)
		*p++ = (UBYTE)Value;
	return (Pointer);
}
