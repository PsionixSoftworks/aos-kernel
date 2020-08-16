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
#include "types.h"

#define KERNEL_MODE_NORMAL		0x10
#define KERNEL_MODE_SAFE		0x20
#define KERNEL_MODE_NO_GUI		0x30

#if defined(__cplusplus)
extern "C" {
#endif

typedef void(*kfunc_t)(uint8_t);

// Declare the global functions used by the kernel:
extern void kernel_init(uint8_t mode);					// The kernel's init function for startup.
extern void kernel_update(void);				// The kernel's update function to run the os in a constant loop.
extern void kernel_quit(uint8_t status);					// Shuts down the kernel when execution stops.
extern bool kernel_is_running(void);			// Checks to see if the kernel is running.
extern void free_system_resources(uint8_t);
extern void kernel_begin_mode(kfunc_t init_func, uint8_t mode);

// Define the kernel struct, it will control every aspect of the kernel:
typedef struct 
{
	bool running;										// This needs to be set to true in order to keep the kernel_update function running.
	uint8_t exit_status;
} Kernel_t;			// Define the kernel type.

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_KERNEL
