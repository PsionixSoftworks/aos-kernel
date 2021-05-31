/*
 *  File: irq.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _ADAMANTINE_IRQ_H
#define _ADAMANTINE_IRQ_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <stdint.h>
#include <stdbool.h>

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

/* Function Templates */
extern bool are_interrupts_enabled(void);				// Checks if interrupts are enabled?
extern unsigned long irq_disable(void);					// Disables IRQ's temporarily?
extern void irq_restore(unsigned long);					// Restores disabled IRQ?
extern void clear_interrupts(void);						// Clear interrupt flag (NASM 'cli')
extern void set_interrupts(void);						// Set interrupt flag (NASM 'sti')

#endif  // !_ADAMANTINE_IRQ_H
