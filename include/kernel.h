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
EXTERN VOID (KernelUpdate(VOID));								// The kernel's update function to run the os in a constant loop.
EXTERN VOID (KernelQuit(UBYTE Status));							// Shuts down the kernel when execution stops.
EXTERN VOID (FreeSystemResources(BYTE));
EXTERN VOID (KernelBeginMode(KFunc_t InitFunc, BYTE Mode));
EXTERN BOOL (KernelIsRunning(void));							// Checks to see if the kernel is running.

// Define the kernel struct, it will control every aspect of the kernel:
typedef struct AOS_Kernel
{
	BOOL 				Running;								// This needs to be set to true in order to keep the kernel_update function running.
	BYTE 				ExitStatus;
} Kernel_t;			// Define the kernel type.

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_KERNEL
