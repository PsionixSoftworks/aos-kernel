/*
 *  File: centrix-core.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef CENTRIX_CORE
#define CENTRIX_CORE

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>

CGUARD_BEGIN

#if !defined(CENTRIX_MODE1) || !defined(CENTRIX_ALPHA)
/* We'll just ignore it for now. */
#else
#include <centrix/centrix-unit.h>
#include <centrix/base32.h>
#endif

#if defined(DEBUG_MODE)
#include <centrix/debug.h>
#endif

struct centrix_core 
{
    udword              os_id;
    udword              os_signature;
    string              os_name;
};

CGUARD_END

#endif	// !CENTRIX_CORE
