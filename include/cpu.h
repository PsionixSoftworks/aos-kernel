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

#include "aos-defs.h"
#include "types.h"

// Declare function templates:
EXTERN void cpu_init(void);                                     // Initialize the CPU.
//EXTERN void CPU_Register(struct CPU, dword ID);
EXTERN void cpu_halt(void);									    // Halts the CPU from C.
EXTERN void cpu_suspend(void);									// Suspends the CPU from C.
EXTERN dword cpu_broke_a_sweat(void);                             // Checks CPU performance against heat rating.
EXTERN string cpu_vendor_string(void);                           // Gets the CPU vendor in string format.
EXTERN udword cpu_check_is_supported(void);                       // Checks if the current CPU architecture is supported.

#endif	// !ADAMANTINE_CPU
