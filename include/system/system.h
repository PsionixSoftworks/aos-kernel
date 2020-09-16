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

#ifndef ADAMANTINE_SYSTEM
#define ADAMANTINE_SYSTEM

// Includes go here:
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <system/io.h>

typedef struct aos_system system_t;

struct 
aos_system
{
	io_t io;
};

// Declare global functions:
EXTERN void (system_enable_cursor(ubyte cursor_start, ubyte cursor_end));  // Enable the cursor in the terminal.
EXTERN void (system_disable_cursor(void));							// Disable the terminal cursor.
EXTERN void (system_update_cursor(udword x, udword y));			// Update the cursor position.
EXTERN void (system_set_cursor_type(ubyte type));					// Set the cursor type (UNUSED).
EXTERN uword (system_get_cursor_position(void));					// Get the cursor position.

#endif	// !ADAMANTINE_SYSTEM
