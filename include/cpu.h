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
EXTERN SET_STRUCT(CPU CPU_Init(VOID));
EXTERN SET_VOID(CPU_Register(struct CPU, DWORD ID));
EXTERN SET_VOID(CPU_Halt(VOID));									// Halts the CPU from C.
EXTERN SET_VOID(CPU_Suspend(VOID));									// Suspends the CPU from C.
EXTERN SET_DWORD(CPU_BrokeASweat(VOID));

EXTERN SET_UDWORD(CPUID(VOID));
EXTERN SET_STRING(CPUID_ISSupported(VOID));

#endif	// !ADAMANTINE_CPU
