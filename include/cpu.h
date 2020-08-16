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

#include "types.h"
#include "cpuid.h"

struct cpu 
{
	uint32_t node_id;
};

// Declare function templates:
extern struct cpu cpu_init(void);
extern void cpu_register(struct cpu, int id);
extern void cpu_halt(void);											// Halts the CPU from C.
extern void cpu_suspend(void);										// Suspends the CPU from C.
extern int cpu_broke_a_sweat(void);

extern int cpuid(void);
extern char *cpuid_supported(void);

#endif	// !ADAMANTINE_CPU
