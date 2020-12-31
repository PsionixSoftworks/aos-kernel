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
#include <stdint.h>
#include <kernel/system/io.h>

typedef struct aos_system system_t;

struct 
aos_system
{
	io_t io;
};

#if defined(__cplusplus)
extern "C" {
#endif

// Declare global functions:
void system_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);  // Enable the cursor in the terminal.
void system_disable_cursor(void);							// Disable the terminal cursor.
void system_update_cursor(uint32_t x, uint32_t y);			// Update the cursor position.
void system_set_cursor_type(uint8_t type);					// Set the cursor type (UNUSED).
uint16_t system_get_cursor_position(void);					// Get the cursor position.

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_SYSTEM
