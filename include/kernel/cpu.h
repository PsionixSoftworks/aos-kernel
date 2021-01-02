/*
 *  File: cpu.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_CPU
#define ADAMANTINE_CPU

#include <stdint.h>

void cpu_init(void);                        // Initialize the CPU.
void cpu_halt(void);						// Halts the CPU from C.
void cpu_suspend(void);					    // Suspends the CPU from C.
void cpu_clear_interrupts(void);
void cpu_set_interrupts(void);
int32_t cpu_broke_a_sweat(void);            // Checks CPU performance against heat rating.
char *cpu_vendor_string(void);              // Gets the CPU vendor in char * format.
uint32_t cpu_check_is_supported(void);      // Checks if the current CPU architecture is supported.

#endif	// !ADAMANTINE_CPU
