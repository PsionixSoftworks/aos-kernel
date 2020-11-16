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
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/adamantine-x86.h>
#include <adamantine/version.h>

#ifndef __sys_entry
#define __sys_entry 	__kernel_only
#else
#define __sys_entry
#endif

#if defined( USING_AOSAPI ) && AOSAPI_VER > 10
#include <sys/sysapi.h>
#include <sys/input.h>
#include <sys/output.h>
#endif	// !USING_SYSAPI

#if defined( USING_CENTRIX_CORE )
#include <centrix/centrix-core.h>
#include <centrix/centrix.h>
#endif

#if defined( USING_ARBITRARY_SYSTEM )
#endif	// !USING_ARBITRARY_SYSTEM

#if !defined( __adamantine__ ) && defined( __x86_runtime__ ) || defined( __adamantine_subsystem__ )
#define __adamantine__ __binary__(__instructable inst, func_ptr);
#endif 	// !__adamantine__

typedef struct
{
    kernel_t (*kernel_setup)(void);
    kernel_t (*kernel_start)(void);
    kernel_t (*kernel_stop)(void);
} aos_base_t PACKED;

#ifndef ADAMANTINE_VER
#define ADAMANTINE_VER 	OS_VERSION_NUMBER
#endif	// !ADAMANTINE_VER
#endif	// !ADAMANTINE
