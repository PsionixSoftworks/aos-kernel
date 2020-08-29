/*
 *  File: mem-util.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_MEMORY_UTILITY
#define ADAMANTINE_MEMORY_UTILITY

#include "aos-defs.h"
#include "types.h"

// Declare the allocation type:
typedef struct 
{
	BYTE 				Status;
	SIZE 				Size;
} Alloc_t;

EXTERN VOID (MM_Init(UDWORD *kernel_end));
EXTERN VOID (PagingMapVirtualToPhysical(UDWORD Virtual, UDWORD Physical));

EXTERN VOID (*PMalloc(SIZE Size));
EXTERN VOID (*Malloc(SIZE Size));
EXTERN VOID (PFree(VOID *Mem));
EXTERN VOID (free(VOID *Mem));

EXTERN VOID (*MemCpy(const VOID *Destination, const VOID *Source, SIZE Size));
EXTERN VOID (*MemSet(VOID *Pointer, DWORD Value, SIZE Size));
EXTERN VOID (*MemSet16(VOID *Pointer,  UDWORD Value, SIZE Size));

UDWORD kMalloc_int(UDWORD Size, int Align, UDWORD *PhysicalAddress);
UDWORD kMalloc_a(UDWORD Size);
UDWORD kMalloc_p(UDWORD SIZE, UDWORD *PhysicalAddress);
UDWORD kMalloc_ap(UDWORD Size, UDWORD *PhysicalAddress);
UDWORD kMalloc(UDWORD Size);

#endif	// !ADAMANTINE_MEMORY_UTILITY
