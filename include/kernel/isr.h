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

#ifndef _ADAMANTINE_ISR_H
#define _ADAMANTINE_ISR_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <stdint.h>

/* Set the maximum number of interrupts we can use */
#define MAX_INTERRUPTS		256

/* Manually trigger an interrupt */
#ifndef intn
#define intn(n) __asm__ volatile ("int $" #n);
#endif

/* Define the register struct. They contain assembly registers in C */
typedef struct registers 
{
	uint32_t 				ds;                  					// data segment selector
   	uint32_t 				edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   	uint32_t 				int_no, err_code;    					// Interrupt number and error code (if applicable)
   	uint32_t 				eip, cs, eflags, useresp, ss;			// Pushed by the CPU automatically
} registers_t;

/* Define the Interrupt Service Routine type */
typedef void(*isr_t)(registers_t);

/* Function Templates */
extern void register_interrupt_handler(uint8_t, isr_t);				// Register a new interrupt handler using the IRQ's (defined above)

#endif	// !_ADAMANTINE_ISR_H
