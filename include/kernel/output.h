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

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

void write_portb(uint16_t port, uint8_t value);	                /* Writes to an 8-Bit port. */
void write_portw(uint16_t port, uint16_t value);	            /* Writes to a 16-Bit port. */
void write_portdw(uint16_t port, uint32_t value);	            /* Writes to a 32-Bit port. */

#if defined(__cplusplus)
}
#endif

#endif