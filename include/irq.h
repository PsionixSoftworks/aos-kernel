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

EXTERN BYTE (AreInterruptsEnabled(VOID));
EXTERN ULONG (IRQ_Disable(VOID));
EXTERN VOID (IRQ_Restore(ULONG Flags));
EXTERN VOID (ClearInterrupts(VOID));

#endif
