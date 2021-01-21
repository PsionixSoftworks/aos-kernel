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

#ifndef _AOS_KERNEL_H
#define _AOS_KERNEL_H

// Handle other includes here:
#include <stdint.h>

#define KERNEL_MODE_NORMAL		0x0
#define KERNEL_MODE_SAFE		0x1
#define KERNEL_MODE_NO_GUI		0x2

typedef struct aos_system_information
{
    /* cpu Specs */
    uint8_t                 cpu_cores;
    uint8_t                 cpu_temperature;
    uint32_t                cpu_id;
    float                   cpu_frequency;
    char                    *cpu_manufacturer;
    char                    *cpu_name;

    /* memory Specs */
    uint32_t                memory_installed;
    uint32_t                memory_available;
    uint8_t                 memory_speed;

    /* Other Info */
    long                    up_time;
} system_info_t;

// Declare the global functions used by the kernel:
void kernel_run(void);						                // The kernel's init function for startup.

#endif	// !_AOS_KERNEL_H
