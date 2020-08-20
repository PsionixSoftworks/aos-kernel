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
#include "cpuid.h"

struct CPU 
{
	UDWORD 				NodeID;
};

// Declare function templates:
EXTERN STRUCT CPU CPU_Init(VOID);
EXTERN VOID (CPU_Register(struct CPU, DWORD ID));
EXTERN VOID (CPU_Halt(VOID));									// Halts the CPU from C.
EXTERN VOID (CPU_Suspend(VOID));									// Suspends the CPU from C.
EXTERN DWORD (CPU_BrokeASweat(VOID));

EXTERN UDWORD (CPUID(VOID));
EXTERN STRING (CPUID_ISSupported(VOID));

#endif	// !ADAMANTINE_CPU
