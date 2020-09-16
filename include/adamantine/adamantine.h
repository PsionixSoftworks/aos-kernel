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

#if defined( USING_SYSAPI )
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

#if !defined( _x86_ARCHTYPE ) && !defined( _x64_ARCHTYPE )
#define _x86_ARCHTYPE		0x20
#endif	// !ARCHTYPE

#if !defined( __adamantine__ ) && defined( __x86_runtime__ ) || defined( __adamantine_subsystem__ )
#define __adamantine__ __binary__(__Instructable Inst, func_ptr);
#endif 	// !__adamantine__

#ifndef ADAMANTINE_VER
#define ADAMANTINE_VER 	100
#endif	// !ADAMANTINE_VER
#endif	// !ADAMANTINE
