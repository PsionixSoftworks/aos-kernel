/*
 *  File: idt.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_INTERRUPT_DESCRIPTOR_TABLE
#define ADAMANTINE_INTERRUPT_DESCRIPTOR_TABLE

// Includes go here:
#include "../types.h"

#ifndef INTERRUPT_DESCRIPTOR
#define INTERRUPT_DESCRIPTOR
#endif

#if defined(__cplusplus)
extern "C" {
#endif

struct idt_entry_struct 
{
	uint16_t base_low;
	uint16_t selector;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct 
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

extern void 
	idt_load(uint32_t),
	isr0(void),
 	isr1(void),
	isr2(void),
	isr3(void),
	isr4(void),
	isr5(void),
	isr6(void),
 	isr7(void),
	isr8(void),
 	isr9(void),
	isr10(void),
 	isr11(void),
 	isr12(void),
 	isr13(void),
	isr14(void),
	isr15(void),
	isr16(void),
	isr17(void),
	isr18(void),
	isr19(void),
	isr20(void),
	isr21(void),
	isr22(void),
	isr23(void),
 	isr24(void),
 	isr25(void),
 	isr26(void),
	isr27(void),
 	isr28(void),
	isr29(void),
 	isr30(void),
	isr31(void);

extern void 
	irq0(void),
	irq1(void),
	irq2(void),
	irq3(void),
	irq4(void),
	irq5(void),
	irq6(void),
	irq7(void),
	irq8(void),
	irq9(void),
	irq10(void),
	irq11(void),
	irq12(void),
	irq13(void),
	irq14(void),
	irq15(void);

extern void idt_init(void);
extern void idt_free(void);

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_INTERRUPT_DESCRIPTOR_TABLE
