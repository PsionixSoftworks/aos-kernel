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

#define __KERNEL__              1

// Handle other includes here:
#include "aos-defs.h"
#include "types.h"

#define KERNEL_MODE_NORMAL		0x0
#define KERNEL_MODE_SAFE		0x1
#define KERNEL_MODE_NO_GUI		0x2

typedef struct AOS_SystemInformation
{
    /* CPU Specs */
    BYTE CPU_Cores;
    BYTE CPU_Temperature;
    UDWORD CPU_ID;
    FLOAT CPU_Frequency;
    STRING CPU_Manufacturer;
    STRING CPU_Name;

    /* Memory Specs */
    ULONG MemoryInstalled;
    ULONG MemoryAvailable;
    BYTE MemorySpeed;

    /* Other Info */
    LONG UpTime;
} SystemInfo_t;

// Declare the global functions used by the kernel:
EXTERN VOID (KernelRun(VOID));									// The kernel's init function for startup.


#endif	// !ADAMANTINE_KERNEL
