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

#if defined(__cplusplus)
extern "C" {
#endif

// Declare the allocation type:
typedef struct 
{
	BYTE 				Status;
	SIZE 				Size;
} Alloc_t;

EXTERN SET_VOID(MM_Init(UDWORD *kernel_end));
EXTERN SET_VOID(PagingMapVirtualToPhysical(UDWORD Virtual, UDWORD Physical));

EXTERN SET_VOID(*PMalloc(SIZE Size));
EXTERN SET_VOID(*Malloc(SIZE Size));
EXTERN SET_VOID(PFree(VOID *Mem));
EXTERN SET_VOID(free(VOID *Mem));

EXTERN SET_VOID(*MemCpy(const VOID *Destination, const VOID *Source, SIZE Size));
EXTERN SET_VOID(*MemSet(VOID *Pointer, DWORD Value, SIZE Size));
EXTERN SET_VOID(*MemSet16(VOID *Pointer,  UDWORD Value, SIZE Size));

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_MEMORY_UTILITY
