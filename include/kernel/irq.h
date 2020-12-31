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

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

uint8_t are_interrupts_enabled(void);
unsigned long irq_disable(void);
void irq_restore(unsigned long flags);
void clear_interrupts(void);

#if defined(__cplusplus)
extern "C" {
#endif

#endif
