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

#ifndef _ADAMANTINE_KERNEL_H
#define _ADAMANTINE_KERNEL_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <kernel/system/types.h>
#include <stdint.h>

#include <compiler.h>

#if !defined(KERNEL_API)
#if !defined(KERNEL_STDCALL)
#define KERNEL_API      __cdecl
#else
#define KERNEL_API      __stdcall
#endif
#endif

/* Define the system info struct */
typedef struct aos_system_information
{
    /* cpu Specs */
    uint8_t                 cpu_cores;                  // The number of CPU cores the CPU has
    uint8_t                 cpu_temperature;            // The temperature in degrees F/C
    uint32_t                cpu_id;                     // ??? Isn't this already defined?
    float                   cpu_frequency;              // The CPU frequency in (Hz)
    char                    *cpu_manufacturer;          // ??
    char                    *cpu_name;                  // ??

    /* memory Specs */
    uint32_t                memory_installed;           // The amount of RAM installed in (MB)
    uint32_t                memory_available;           // Is this really needed?
    uint8_t                 memory_speed;               // Not crucial, but memory speed in (Hz)

    /* Other Info */
    time_t                  up_time;                    // The time since the computer was turned on.
} system_info_t;

#endif	// !_ADAMANTINE_KERNEL_H
