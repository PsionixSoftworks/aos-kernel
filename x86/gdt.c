/*
 *  File: gdt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/gdt.h"
#include "../include/tss.h"
#include "../include/terminal.h"
#include "../include/mem-util.h"

MODULE("GlobalDescriptorTable", "0.01a");

EXTERN VOID GDT_Flush(UDWORD);
EXTERN VOID TSS_Flush(VOID);
EXTERN TSS_t tss_entry;

GDT_Entry_t GDT_Entries[6];
PGDT_t PGDT;

static inline VOID GDT_SetBase(DWORD Index, UDWORD Base);
static inline VOID GDT_SetLimit(DWORD Index, UDWORD Limit);
static inline VOID GDT_SetGranularity(DWORD Index, UBYTE Granularity);
static inline VOID GDT_SetAccess(DWORD Index, UBYTE Access);
static inline BOOL GDT_EntryUsed(DWORD Index);
static inline VOID GDT_SetGate(DWORD, UDWORD, UDWORD, UBYTE, UBYTE);
static inline VOID TSS_Write(uint32_t num);

VOID
GDT_Init(VOID) 
{
	PGDT.Limit = (sizeof(GDT_Entry_t) * 5) - 1;	// Learn to understand this...
	PGDT.Base = (UDWORD)&GDT_Entries;
	
	UWORD Base, Limit; 
	UBYTE Access, Granularity;

	int i = 0;
	GDT_SetGate(i++, NULL, NULL, NULL, NULL);	// 0th index needs to be a null segment...
	GDT_SetGate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_0, ACCESS_BYTE_FLAGS);
	GDT_SetGate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_1, ACCESS_BYTE_FLAGS);
	GDT_SetGate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_2, ACCESS_BYTE_FLAGS);
	GDT_SetGate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_3, ACCESS_BYTE_FLAGS);
	TSS_Write(i++);

	GDT_Flush((UDWORD)&PGDT);
	//TSS_Flush();
	
	INFO("GDT is initialized!");
}

static inline VOID
GDT_SetGate(DWORD Index, UDWORD Base, UDWORD Limit, UBYTE Access, UBYTE Granularity) 
{
	/* Make sure we're not adding nothing or a used entry. */
	if ((Index != NULL) && (!GDT_EntryUsed(Index)))
	{
		/* Setup a GDT. */
		GDT_SetBase(Index, Base);
		GDT_SetLimit(Index, Limit);
		GDT_SetAccess(Index, Access);
		GDT_SetGranularity(Index, Granularity);
	}
	return;
}

static inline VOID
GDT_SetBase(DWORD Index, UDWORD Base)
{
	GDT_Entries[Index].BaseLo 		= (Base & 0xFFFF);
	GDT_Entries[Index].BaseMiddle	= (Base >> 16) & 0xFF;
	GDT_Entries[Index].BaseHi		= (Base >> 24) & 0xFF;
}

static inline VOID
GDT_SetLimit(DWORD Index, UDWORD Limit)
{
	GDT_Entries[Index].LimitLo		= (Limit & 0xFFFF);
	GDT_Entries[Index].Granularity	= (Limit >> 16) & 0x0F;
}

static inline VOID
GDT_SetGranularity(DWORD Index, UBYTE Granularity)
{
	GDT_Entries[Index].Granularity	|= Granularity & 0xF0;
}

static inline VOID
GDT_SetAccess(DWORD Index, UBYTE Access)
{
	GDT_Entries[Index].Access		= Access;
}

static inline BOOL
GDT_EntryUsed(DWORD Index)
{
	return (FALSE);
}

static inline VOID
TSS_Write(uint32_t num)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = sizeof(tss_entry);

	GDT_SetGate(num, base, limit, 0xE9, 0x00);

	tss_entry.ss0 = 0x10;
	tss_entry.esp0 = 0x00;
	tss_entry.cs = 0x0B;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}
