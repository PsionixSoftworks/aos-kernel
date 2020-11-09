/*
 *  File: isr.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_isr
#define ADAMANTINE_isr

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>

#define IRQ0		32
#define IRQ1		33
#define IRQ2		34
#define IRQ3		35
#define IRQ4		36
#define IRQ5		37
#define IRQ6		38
#define IRQ7		39
#define IRQ8		40
#define IRQ9		41
#define IRQ10		42
#define IRQ11		43
#define IRQ12		44
#define IRQ13		45
#define IRQ14		46
#define IRQ15		47

typedef struct aos_registers 
{
	udword DS;                  // data segment selector
   	udword EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX; // Pushed by pusha.
   	udword INT_NO, ERR_CODE;    // Interrupt number and error code (if applicable)
   	udword EIP, CS, EFLAGS, USERESP, SS;
} registers_t;

typedef void(*isr_t)(registers_t);
EXTERN	void register_interrupt_handler(ubyte n, isr_t handler);

#endif	// !ADAMANTINE_isr
