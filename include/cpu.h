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
EXTERN void CPU_Init(void);                                     // Initialize the CPU.
//EXTERN VOID CPU_Register(struct CPU, dword ID);
EXTERN void CPU_Halt(void);									    // Halts the CPU from C.
EXTERN void CPU_Suspend(void);									// Suspends the CPU from C.
EXTERN dword CPU_BrokeASweat(void);                             // Checks CPU performance against heat rating.
EXTERN string CPU_VendorString(void);                           // Gets the CPU vendor in string format.
EXTERN udword CPU_CheckIsSupported(void);                       // Checks if the current CPU architecture is supported.

#endif	// !ADAMANTINE_CPU
