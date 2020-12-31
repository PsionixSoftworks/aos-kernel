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

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

void pit_init(uint32_t Frequency);

#if defined(__cplusplus)
}
#endif

#endif	// !SYSTEM_TIMER
