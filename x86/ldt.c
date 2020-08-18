/*
 *  File: ldt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/ldt.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"

MODULE("local-descriptor-table", "0.01a");

extern void ldt_flush(uint32_t);

ldt_entry_t ldt_entries[8192];
ldt_ptr_t ldt_ptr;

void _TEXT
ldt_init(void)
{
    ldt_ptr.limit = (sizeof(ldt_entry_t)) - 1;
    ldt_ptr.base = (uint32_t)&ldt_entries;
    ldt_set_gate(0, 0, 0, 0, 0);
    ldt_set_gate(1, 0x00000000, 0xFFFFFFFF, 0x9A, 0xCF);
    ldt_set_gate(2, 0x00000000, 0xFFFFFFFF, 0x92, 0xCF);
    ldt_set_gate(3, 0x00000000, 0xFFFFFFFF, 0x9A, 0xCF);
    ldt_set_gate(4, 0x00000000, 0xFFFFFFFF, 0x92, 0xCF);
    ldt_flush((uint32_t)&ldt_ptr);

    INFO("LDT is initialized!");
}

void
ldt_set_gate(uint16_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    ldt_entries[num].base_low       = (base & 0xFFFF);
    ldt_entries[num].base_high      = (base >> 32) & 0xFF;

    ldt_entries[num].limit_low      = (limit & 0xFFFF);
    ldt_entries[num].limit_high     = (limit >> 16) & 0x0F;

    ldt_entries[num].access         = access;
    ldt_entries[num].granularity	= granularity;
}
