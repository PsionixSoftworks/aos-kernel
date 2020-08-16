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

#include "types.h"

extern uint8_t read_portb(uint16_t port);					    /* Read 8-bit port. */
extern uint16_t read_portw(uint16_t port);					    /* Read 16-bit port. */
extern uint32_t read_portl(uint16_t port);                      /* Read 32-bit port. */

#endif
