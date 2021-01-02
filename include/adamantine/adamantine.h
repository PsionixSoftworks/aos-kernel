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

#ifndef _ADAMANTINE_H
#define _ADAMANTINE_H

// Includes go here:
#if !defined( __AOS64__ )
#include <adamantine/adamantine-x86.h>
#else
#include <adamantine/adamantine-x64.h>
#endif

#include <adamantine/aos-defs.h>
#include <adamantine/version.h>

#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ADAMANTINE
#define ADAMANTINE  1
#endif

#if defined( USING_CENTRIX_CORE )   // Here's a hint: We're not... Yet...
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
