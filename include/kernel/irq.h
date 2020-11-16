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

#ifndef _INTERRUPT_REQUESTS_
#define _INTERRUPT_REQUESTS_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

EXTERN 	byte are_interrupts_enabled(void);
EXTERN 	unsigned long irq_disable(void);
EXTERN 	void irq_restore(unsigned long flags);
EXTERN 	void clear_interrupts(void);

#endif
