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
#include "types.h"
#include "io.h"
#include "terminal.h"

// Declare global functions:
extern void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);	// Enable the cursor in the terminal.
extern void disable_cursor();															// Disable the terminal cursor.
extern void update_cursor(uint32_t x, uint32_t y);								// Update the cursor position.
extern uint16_t get_cursor_position(void);										// Get the cursor position.
extern void set_cursor_type(uint8_t type);										// Set the cursor type (UNUSED).

#endif	// !ADAMANTINE_SYSTEM
