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

#if defined(__cplusplus)
extern "C" {
#endif

#include "aos-defs.h"
#include "types.h"
#include "string.h"

#if !defined(CENTRIX_MODE1) || !defined(CENTRIX_ALPHA)
/* We'll just ignore it for now. */
#else
#include "centrix/centrix_unit.h"
#include "centrix/base32.h"

#endif

#if defined(DEBUG_MODE)
#include "centrix/debug.h"
#endif

struct CentrixCore 
{
    UDWORD              OS_ID;
    UDWORD              OS_Signature;
    STRING              OS_Name;
};

void *KernelInstall(string name);
int32_t Verify(void);

#if defined(__cplusplus)
}
#endif

#endif	// !CENTRIX_CORE
