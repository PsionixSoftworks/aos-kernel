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

#include "aos-defs.h"
#include "types.h"

#if defined(__cplusplus)
extern "C" {
#endif

EXTERN SET_BYTE(AreInterruptsEnabled(void));
EXTERN SET_ULONG(IRQ_Disable(void));
EXTERN SET_VOID(IRQ_Restore(unsigned long flags));
EXTERN SET_VOID(ClearInterrupts(void));

#if defined(__cplusplus)
}
#endif
#endif
