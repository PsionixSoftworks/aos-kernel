/*
 *  File: base32.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _CENTRIX_BASE32_
#define _CENTRIX_BASE32_

#include "../aos-defs.h"
#include "../types.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct CentrixBase
{
    UWORD               Start;
    UWORD               End;
    UDWORD              *Data;
};

#if defined(__cplusplus)
}
#endif

#endif
