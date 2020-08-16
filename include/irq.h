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

#include "types.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern bool are_interrupts_enabled(void);
extern unsigned long save_irqdisable(void);
extern void irq_restore(unsigned long flags);
extern void clear_interrupts(void);

#if defined(__cplusplus)
}
#endif

#endif
