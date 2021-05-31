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

/* Define the IRQ numbers. They are taechnically ISR 32-47 */
#define IRQ0		32									// Interrupt Request 0, [PIT 0 (System Time)]
#define IRQ1		33									// Interrupt Request 1, [Keyboard]
#define IRQ2		34									// Interrupt Request 2, [Cascade from IRQ9]
#define IRQ3		35									// Interrupt Request 3, [COM Port 2 | 4]
#define IRQ4		36									// Interrupt Request 4, [COM Port 1 | 3]
#define IRQ5		37									// Interrupt Request 5, [Parallel Port 2 (Printer) | Sound Cards]
#define IRQ6		38									// Interrupt Request 6, [Floppy Drive Controller]
#define IRQ7		39									// Interrupt Request 7, [Parallel Port 1 (Printer)]
#define IRQ8		40									// Interrupt Request 8, [Real Time Clock]
#define IRQ9		41									// Interrupt Request 9, [Video]
#define IRQ10		42									// Interrupt Request 10, [Open?]
#define IRQ11		43									// Interrupt Request 11, [Open?]
#define IRQ12		44									// Interrupt Request 12, [PS/2 Mouse]
#define IRQ13		45									// Interrupt Request 13, [Coprocessor]
#define IRQ14		46									// Interrupt Request 14, [Primary IDE Controller (HDD)]
#define IRQ15		47									// Interrupt Request 15, [Secondary IDE Controller (DD)]

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
