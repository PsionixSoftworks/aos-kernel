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
#include "../aos-defs.h"
#include "../types.h"

#ifndef INTERRUPT_DESCRIPTOR
#define INTERRUPT_DESCRIPTOR
#endif

struct idt_entry 
{
	uword 				base_lo;
	uword 				selector;
	ubyte 				always_zero;
	ubyte 				flags;
	uword 				base_hi;
} PACKED;
typedef struct idt_entry idt_entry_t;

struct pidt 
{
	uword 				limit;
	udword 				base;
} PACKED;
typedef struct pidt pidt_t;

EXTERN	void (isr_0(void));
EXTERN	void (isr_1(void));
EXTERN	void (isr_2(void));
EXTERN	void (isr_3(void));
EXTERN	void (isr_4(void));
EXTERN	void (isr_5(void));
EXTERN	void (isr_6(void));
EXTERN	void (isr_7(void));
EXTERN	void (isr_8(void));
EXTERN	void (isr_9(void));
EXTERN	void (isr_10(void));
EXTERN	void (isr_11(void));
EXTERN	void (isr_12(void));
EXTERN	void (isr_13(void));
EXTERN	void (isr_14(void));
EXTERN	void (isr_15(void));
EXTERN	void (isr_16(void));
EXTERN	void (isr_17(void));
EXTERN	void (isr_18(void));
EXTERN	void (isr_19(void));
EXTERN	void (isr_20(void));
EXTERN	void (isr_21(void));
EXTERN	void (isr_22(void));
EXTERN	void (isr_23(void));
EXTERN	void (isr_24(void));
EXTERN	void (isr_25(void));
EXTERN	void (isr_26(void));
EXTERN	void (isr_27(void));
EXTERN	void (isr_28(void));
EXTERN	void (isr_29(void));
EXTERN	void (isr_30(void));
EXTERN	void (isr_31(void));
EXTERN 	void (isr_150(void));

EXTERN	void (irq_0(void));
EXTERN	void (irq_1(void));
EXTERN	void (irq_2(void));
EXTERN	void (irq_3(void));
EXTERN	void (irq_4(void));
EXTERN	void (irq_5(void));
EXTERN	void (irq_6(void));
EXTERN	void (irq_7(void));
EXTERN	void (irq_8(void));
EXTERN	void (irq_9(void));
EXTERN	void (irq_10(void));
EXTERN	void (irq_11(void));
EXTERN	void (irq_12(void));
EXTERN	void (irq_13(void));
EXTERN	void (irq_14(void));
EXTERN	void (irq_15(void));

EXTERN 	void (idt_init(void));
EXTERN 	void (idt_free(void));

#endif	// !ADAMANTINE_INTERRUPT_DESCRIPTOR_TABLE
