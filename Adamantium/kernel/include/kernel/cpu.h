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

#ifndef _ADAMANTINE_CPU_H
#define _ADAMANTINE_CPU_H

#include "cpuid.h"
#include <stdint.h>

struct cpu
{
	char* vendor_string;
};

extern void cpu_init(void);								// Initialize the CPU.
extern void cpu_halt(void);								// Halts the CPU from C.
extern void cpu_suspend(void);							// Suspends the CPU from C.
extern void cpu_clear_interrupts(void);					// Disable interrupts
extern void cpu_set_interrupts(void);					// Enable interrupts
extern char *cpu_vendor_string(void);					// Gets the CPU vendor in char * format.
extern uint32_t cpu_check_is_supported(void);			// Checks if the current CPU architecture is supported.
extern void cpu_print(void);

#endif	// !_ADAMANTINE_CPU_H
