/*
 *  File: idt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/idt.h"
#include "../include/terminal.h"
#include "../include/io.h"
#include "../include/mem-util.h"
#include "../include/pic.h"

MODULE("Interrupt-Descriptor-Table", "0.01a");

EXTERN void idt_flush(udword);

idt_entry_t idt_entries[256];
pidt_t pidt;

static inline void idt_set_gate(ubyte number, udword base, uword selector, ubyte flags);

void
idt_init(void)
{
	pidt.limit = sizeof(idt_entry_t) * 256 - 1;
	pidt.base = (udword)&idt_entries;
	
	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);
	
    pic_remap();
	
	idt_set_gate( 0, (udword)isr_0, 0x08, 0x8E);
    idt_set_gate( 1, (udword)isr_1, 0x08, 0x8E);
    idt_set_gate( 2, (udword)isr_2, 0x08, 0x8E);
    idt_set_gate( 3, (udword)isr_3, 0x08, 0x8E);
    idt_set_gate( 4, (udword)isr_4, 0x08, 0x8E);
    idt_set_gate( 5, (udword)isr_5, 0x08, 0x8E);
    idt_set_gate( 6, (udword)isr_6, 0x08, 0x8E);
    idt_set_gate( 7, (udword)isr_7, 0x08, 0x8E);
    idt_set_gate( 8, (udword)isr_8, 0x08, 0x8E);
    idt_set_gate( 9, (udword)isr_9, 0x08, 0x8E);
    idt_set_gate(10, (udword)isr_10, 0x08, 0x8E);
    idt_set_gate(11, (udword)isr_11, 0x08, 0x8E);
    idt_set_gate(12, (udword)isr_12, 0x08, 0x8E);
    idt_set_gate(13, (udword)isr_13, 0x08, 0x8E);
    idt_set_gate(14, (udword)isr_14, 0x08, 0x8E);
    idt_set_gate(15, (udword)isr_15, 0x08, 0x8E);
    idt_set_gate(16, (udword)isr_16, 0x08, 0x8E);
    idt_set_gate(17, (udword)isr_17, 0x08, 0x8E);
    idt_set_gate(18, (udword)isr_18, 0x08, 0x8E);
    idt_set_gate(19, (udword)isr_19, 0x08, 0x8E);
    idt_set_gate(20, (udword)isr_20, 0x08, 0x8E);
    idt_set_gate(21, (udword)isr_21, 0x08, 0x8E);
    idt_set_gate(22, (udword)isr_22, 0x08, 0x8E);
    idt_set_gate(23, (udword)isr_23, 0x08, 0x8E);
    idt_set_gate(24, (udword)isr_24, 0x08, 0x8E);
    idt_set_gate(25, (udword)isr_25, 0x08, 0x8E);
    idt_set_gate(26, (udword)isr_26, 0x08, 0x8E);
    idt_set_gate(27, (udword)isr_27, 0x08, 0x8E);
    idt_set_gate(28, (udword)isr_28, 0x08, 0x8E);
    idt_set_gate(29, (udword)isr_29, 0x08, 0x8E);
    idt_set_gate(30, (udword)isr_30, 0x08, 0x8E);
    idt_set_gate(31, (udword)isr_31, 0x08, 0x8E);
	idt_set_gate(128, (udword)isr_150, 0x08, 0x8E);
	
    idt_set_gate(32, (udword)irq_0, 0x08, 0x8E);
    idt_set_gate(33, (udword)irq_1, 0x08, 0x8E);
    idt_set_gate(34, (udword)irq_2, 0x08, 0x8E);
    idt_set_gate(35, (udword)irq_3, 0x08, 0x8E);
    idt_set_gate(36, (udword)irq_4, 0x08, 0x8E);
    idt_set_gate(37, (udword)irq_5, 0x08, 0x8E);
    idt_set_gate(38, (udword)irq_6, 0x08, 0x8E);
    idt_set_gate(39, (udword)irq_7, 0x08, 0x8E);
    idt_set_gate(40, (udword)irq_8, 0x08, 0x8E);
    idt_set_gate(41, (udword)irq_9, 0x08, 0x8E);
    idt_set_gate(42, (udword)irq_10, 0x08, 0x8E);
    idt_set_gate(43, (udword)irq_11, 0x08, 0x8E);
    idt_set_gate(44, (udword)irq_12, 0x08, 0x8E);
    idt_set_gate(45, (udword)irq_13, 0x08, 0x8E);
    idt_set_gate(46, (udword)irq_14, 0x08, 0x8E);
    idt_set_gate(47, (udword)irq_15, 0x08, 0x8E);
	
	idt_flush((udword)&pidt);

    //_INFO("IDT is initialized!");
    system_logf(INFORMATION, "IDT is initialized!\n");
}

static inline void
idt_set_gate(ubyte number, udword base, uword selector, ubyte flags)
{
	idt_entries[number].base_lo     = base & 0xFFFF;
    idt_entries[number].base_hi     = (base >> 16) & 0xFFFF;
	
	idt_entries[number].selector    = selector;
	idt_entries[number].always_zero = 0;
	
	idt_entries[number].flags       = flags | 0x60;
}

void
idt_free(void) 
{
    free(idt_entries);
}
