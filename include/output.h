/*
 *  File: output.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _OUTPUT_
#define _OUTPUT_

#include "aos-defs.h"
#include "types.h"

EXTERN  VOID (WritePortB(UWORD Port, UBYTE Value));	            /* Writes to an 8-Bit port. */
EXTERN  VOID (WritePortW(UWORD Port, UWORD Value));	            /* Writes to a 16-Bit port. */
EXTERN  VOID (WritePortDW(UWORD Port, UDWORD Value));	        /* Writes to a 32-Bit port. */

#endif