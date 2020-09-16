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

#define __KERNEL__

// Handle other includes here:
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

#define KERNEL_MODE_NORMAL		0x0
#define KERNEL_MODE_SAFE		0x1
#define KERNEL_MODE_NO_GUI		0x2

typedef struct aos_system_information
{
    /* cpu Specs */
    __kernel_byte       cpu_cores;
    __kernel_byte       cpu_temperature;
    __kernel_udword     cpu_id;
    __kernel_float      cpu_frequency;
    __kernel_string     cpu_manufacturer;
    __kernel_string     cpu_name;

    /* memory Specs */
    __kernel_udword     memory_installed;
    __kernel_udword     memory_available;
    __kernel_byte       memory_speed;

    /* Other Info */
    __kernel_long       up_time;
} system_info_t;

// Declare the global functions used by the kernel:
EXTERN  __kernel_void kernel_run(__kernel_void);									// The kernel's init function for startup.

#endif	// !ADAMANTINE_KERNEL
