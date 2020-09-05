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

#include "aos-defs.h"
#include "types.h"
#include "string.h"

#define irq0		32
#define irq1		33
#define irq2		34
#define irq3		35
#define irq4		36
#define irq5		37
#define irq6		38
#define irq7		39
#define irq8		40
#define irq9		41
#define irq10		42
#define irq11		43
#define irq12		44
#define irq13		45
#define irq14		46
#define irq15		47

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
