/*
 *  File: input.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _INPUT_
#define _INPUT_

#include "aos-defs.h"
#include "types.h"

#if defined(__cplusplus)
EXTERN "C" {
#endif

EXTERN UBYTE (ReadPortB(UWORD Port));					        /* Read 8-bit port. */
EXTERN UWORD (ReadPortW(UWORD Port));					        /* Read 16-bit port. */
EXTERN UDWORD (ReadPortDW(UWORD Port));                          /* Read 32-bit port. */

#if defined(__cplusplus)
}
#endif
#endif
