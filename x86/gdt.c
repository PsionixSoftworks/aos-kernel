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

MODULE("Global-Descriptor-Table", "0.01a");

#define MAX_GDT_ENTRIES		6

EXTERN void gdt_flush(udword);
EXTERN void tss_flush(void);
EXTERN tss_t tss_entry ALIGN(4096);

gdt_entry_t gdt_entries[MAX_GDT_ENTRIES];
PGDT_t pgdt;

static inline void gdt_set_base(dword index, udword base);
static inline void gdt_set_limit(dword index, udword limit);
static inline void gdt_set_granularity(dword index, ubyte granularity);
static inline void gdt_set_access(dword index, ubyte access);
static inline bool gdt_entry_used(dword index);
static inline void gdt_set_gate(dword, udword, udword, ubyte, ubyte);
static void TSS_Write(uint32_t num);

void
gdt_init(void) 
{
	pgdt.limit = (sizeof(gdt_entry_t) * MAX_GDT_ENTRIES) - 1;
	pgdt.base = (udword)&gdt_entries;
	
	uword base, limit; 
	ubyte access, granularity;

	udword i = 0;
	gdt_set_gate(i++, GDT_SEGMENT_NULL, GDT_SEGMENT_NULL, GDT_SEGMENT_NULL, GDT_SEGMENT_NULL);		// 0th index needs to be a null segment...
	gdt_set_gate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_0, ACCESS_BYTE_FLAGS);	
	gdt_set_gate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_1, ACCESS_BYTE_FLAGS);	
	gdt_set_gate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_2, ACCESS_BYTE_FLAGS);	
	gdt_set_gate(i++, MEMORY_START_REGION, MEMORY_END_REGION, ACCESS_BYTE_3, ACCESS_BYTE_FLAGS);	
	TSS_Write(i++);

	gdt_flush((udword)&pgdt);
	tss_flush();
	
	_INFO("GDT is initialized!");
}

static inline void
gdt_set_gate(dword index, udword base, udword limit, ubyte access, ubyte granularity) 
{
	/* Make sure we're not adding nothing or a used entry. */
	if ((index != NULL) && (!gdt_entry_used(index)))
	{
		/* Setup a GDT. */
		gdt_set_base(index, base);
		gdt_set_limit(index, limit);
		gdt_set_access(index, access);
		gdt_set_granularity(index, granularity);
	}
	return;
}

static inline void
gdt_set_base(dword index, udword base)
{
	gdt_entries[index].base_lo 		= (base & 0xFFFF);
	gdt_entries[index].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[index].base_hi		= (base >> 24) & 0xFF;
}

static inline void
gdt_set_limit(dword index, udword limit)
{
	gdt_entries[index].limit_lo		= (limit & 0xFFFF);
	gdt_entries[index].granularity	= (limit >> 16) & 0x0F;
}

static inline void
gdt_set_granularity(dword index, ubyte granularity)
{
	gdt_entries[index].granularity	|= granularity & 0xF0;
}

static inline void
gdt_set_access(dword index, ubyte access)
{
	gdt_entries[index].access		= access;
}

static inline bool
gdt_entry_used(dword index)
{
	return (FALSE);
}

static void
TSS_Write(uint32_t num)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = sizeof(tss_entry);

	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0 = 0x10;
	tss_entry.esp0 = 0x00;
	tss_entry.iomap_base = 0xDFFF;
	tss_entry.cs = 0x0B;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}
