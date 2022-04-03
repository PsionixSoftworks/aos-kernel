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

#include <adamantine/adamantine.h>
#include <system/types.h>
#include <compiler.h>
#include <errno.h>                  // Once the decision is made whether or not this OS is POSIX compliant,
                                    // it will become crucial to either define the remaining errno's or define
                                    // a proprietary system for error code handling.

#ifndef AOS_BIT_MASK
#define AOS_BIT_MASK    (0xFF >> 16) | 0x20;
#else
#define AOS_BIT_MASK
#endif

#if !defined(KERNEL_API)
#if !defined(KERNEL_CDECL)
#define KERNEL_API      
#else
#define KERNEL_API      __cdecl__
#endif
#endif

#define IS_ERR_VALUE(x)     ((unsigned long)(void *)(x) >= (unsigned long)-MAX_ERRNO)
#define IS_ERR(x)           IS_ERR_VALUE((unsigned long)x)

struct kconfig
{
    char *kernel_signature;
    const char *product_key;
    const char *computer_name;

    
};

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
    //time_t                  up_time;                    // The time since the computer was turned on.
} system_info_t;

void kconfig_defaults(struct kconfig *) __section(".text");

#endif	// !_ADAMANTINE_KERNEL_H
