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

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

EXTERN  void pit_init(udword Frequency);

#endif	// !SYSTEM_TIMER
