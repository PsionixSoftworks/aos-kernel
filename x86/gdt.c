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
#include "../include/x86/ldt.h"
#include "../include/tss.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"
#include "../include/mem-util.h"

MODULE("global-descriptor-table", "0.01a");

extern void gdt_flush(uint32_t);
extern void tss_flush(void);

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0);

gdt_entry_t gdt_entries[6];
gdt_ptr_t gdt_ptr;
tss_t tss_entry;

void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

void 
gdt_init(void) 
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;	// Learn to understand this...
	gdt_ptr.base = (uint32_t)&gdt_entries;
	
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	write_tss(5, 0x10, 0x0);

	gdt_flush((uint32_t)&gdt_ptr);
	tss_flush();

	INFO("GDT is initialized!");
}

static void 
write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

	gdt_set_gate(num, base, limit, 0x89, 0x40);

	tss_entry.ss0 = ss0;
	tss_entry.esp0 = esp0;

	tss_entry.cs = 0x0B;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}

void 
set_kernel_stack(uint32_t stack)
{
	tss_entry.esp0 = stack;
}

void 
gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) 
{
	gdt_entries[num].base_low 		= (base & 0xFFFF);
	gdt_entries[num].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[num].base_high		= (base >> 24) & 0xFF;
	
	gdt_entries[num].limit_low		= (limit & 0xFFFF);
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;
	
	gdt_entries[num].granularity	|= granularity & 0xF0;
	gdt_entries[num].access			= access;
}
