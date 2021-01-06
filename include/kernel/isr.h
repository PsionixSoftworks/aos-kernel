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

#include <stdint.h>

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
	uint32_t ds;                  // data segment selector
   	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   	uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   	uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

#if defined(__cplusplus)
extern "C" {
#endif

typedef void(*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler);

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_isr
