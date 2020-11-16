/*
 *  File: keyboard.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_KEYBOARD_
#define _AOS_KEYBOARD_

// Include files here:
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>
#include <kernel/drivers/driver.h>

#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER						(BASE_ADDR - 0x67)
#define KEYBOARD_DATA						(KEYBOARD_DRIVER << 2)
#define KEYBOARD_PORT						((KEYBOARD_DRIVER + 1) << 2)
#endif

// Define the max allocation size for keys:
#define MAX_ALLOC_SIZE						256

// Declare the keyboard type struct:
typedef struct aos_keyboard_basic
{
	byte 				key_last;								// The last key pressed.
	byte 				status;									// The status of the keyboard key.
	string 				key_map;								// Used to set a memory map of the keys (BROKEN).
	string 				buffer;
	bool 				is_initialized;							// The keyboard initializer.
} keyboard_t;

#if defined(__cplusplus)
extern "C" {
#endif

// Declare global functions:
void keyboard_set_key_code(byte *key, byte code);				// Set keycodes for each key (UNUSED).
void keyboard_init(void);										// Initialize the basic keyboard driver.
void keyboard_free(void);										// free memory associated with the keyboard driver.
void keyboard_wait(void);										// Give the keyboard a wait instruction.
bool keyboard_is_enabled(void);									// Checks whether the keyboard is initialized or not.
string keyboard_get_key(void);									// Gets the value of a key pressed.
string keyboard_get_string(void);
uint8_t keyboard_get_keycode(void);								// Gets the value of the keycode pressed.
uint8_t keyboard_get_key_last(void);

#if defined(__cplusplus)
}
#endif

#endif 	// !ADAMANTINE_KEYBOARD
