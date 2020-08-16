/*
 *  File: pit.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef SYSTEM_TIMER
#define SYSTEM_TIMER

#include "types.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern void timer_init(uint32_t frequency);

#if defined(__cplusplus)
}
#endif

#endif	// !SYSTEM_TIMER
