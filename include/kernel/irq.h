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

/* Function Templates */
extern bool are_interrupts_enabled(void);				// Checks if interrupts are enabled?
extern unsigned long irq_disable(void);					// Disables IRQ's temporarily?
extern void irq_restore(unsigned long);					// Restores disabled IRQ?
extern void clear_interrupts(void);						// Clear interrupt flag (NASM 'cli')
extern void set_interrupts(void);						// Set interrupt flag (NASM 'sti')

#endif  // !_ADAMANTINE_IRQ_H
