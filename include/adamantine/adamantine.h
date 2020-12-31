/*
 *  File: adamantine.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE
#define ADAMANTINE

// Includes go here:
#if defined( __AOS64__ )
#include <adamantine/adamantine-x64.h
#else
#include <adamantine/adamantine-x86.h>
#endif

#include <adamantine/aos-defs.h>
#include <adamantine/mutex.h>
#include <adamantine/version.h>

#include <filesys/aos-fs.h>
#include <filesys/ext2.h>
#include <filesys/vfs.h>

#include <kernel/drivers/device.h>
#include <kernel/drivers/driver.h>
#include <kernel/drivers/vga.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/memory/mm.h>
#include <kernel/memory/ordered-array.h>
#include <kernel/memory/paging.h>
#include <kernel/system/io.h>
#include <kernel/system/system.h>
#include <kernel/system/syscall.h>
#include <kernel/system/terminal.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/x86/tss.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/kernel.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/task.h>

#include <math/math-util.h>
#include <math/simple-math.h>
#include <math/vector2f.h>

#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined( USING_CENTRIX_CORE )   // Here's a hint: We're not...
#include <centrix/centrix-core.h>
#include <centrix/centrix.h>
#endif

typedef void *kernel_t;

typedef struct
{
    kernel_t (*kernel_setup)(void);
    kernel_t (*kernel_start)(void);
    kernel_t (*kernel_stop)(void);
} aos_base_t;

#ifndef ADAMANTINE_VER
#define ADAMANTINE_VER 	OS_VERSION_NUMBER
#endif	// !ADAMANTINE_VER
#endif	// !ADAMANTINE
