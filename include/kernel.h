/*
 *  File: kernel.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_KERNEL_
#define _AOS_KERNEL_

// Handle other includes here:
#include "aos-defs.h"
#include "types.h"

#define KERNEL_MODE_NORMAL		0x0
#define KERNEL_MODE_SAFE		0x1
#define KERNEL_MODE_NO_GUI		0x2

#if defined(__cplusplus)
extern "C" {
#endif

typedef VOID(*KFunc_t)(BYTE);

// Declare the global functions used by the kernel:
EXTERN VOID (KernelRun(VOID));									// The kernel's init function for startup.

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_KERNEL
