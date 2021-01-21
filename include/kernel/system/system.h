/*
 *  File: system.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_SYSTEM_H
#define _AOS_SYSTEM_H

// Includes go here:
#include <stdint.h>

#if defined(__x86_SYSTEM_CORE__)
#endif

void system_init(void);
void handle_dispatched_message(uint8_t severity, char *msg);
char *get_system_log(uint32_t index);

#endif	// !_AOS_SYSTEM_H
