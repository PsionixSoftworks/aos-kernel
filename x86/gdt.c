#define KERNEL32	1

#include "../include/x86/gdt.h"
#include "../include/tss.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"
#include "../include/mem_util.h"

MODULE("global-descriptor-table", "0.01a");

extern void gdt_flush(uint32_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

extern tss_t tss_entry;

void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

void 
gdt_init(void) 
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;	// Learn to understand this...
	gdt_ptr.base = (uint32_t)&gdt_entries;
	
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	gdt_flush((uint32_t)&gdt_ptr);

	INFO("GDT is initialized!");
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
