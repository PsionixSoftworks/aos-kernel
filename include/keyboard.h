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
#include "aos-defs.h"
#include "types.h"
#include "string.h"
#include "driver.h"

#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER						(BASE_ADDR - 0x67)
#define KEYBOARD_DATA						(KEYBOARD_DRIVER << 2)
#define KEYBOARD_PORT						((KEYBOARD_DRIVER + 1) << 2)
#endif

// Define the max allocation size for keys:
#define MAX_ALLOC_SIZE						256

#if defined(__cplusplus)
extern "C" {
#endif

// Declare global functions:
EXTERN 	SET_VOID(SetKeyCode(BYTE *Key, BYTE Code));					// Set keycodes for each key (UNUSED).
EXTERN 	SET_VOID(KeyboardInit(void));								// Initialize the basic keyboard driver.
EXTERN 	SET_VOID(KeyboardFree(void));								// Free memory associated with the keyboard driver.
EXTERN 	SET_VOID(KeyboardWait(void));								// Give the keyboard a wait instruction.
EXTERN 	SET_BOOL(KeyboardIsEnabled(void));							// Checks whether the keyboard is initialized or not.
EXTERN 	SET_STRING(KeyboardGetKey(void));							// Gets the value of a key pressed.
EXTERN 	SET_STRING(KeyboardGetString(void));
EXTERN 	SET_UBYTE(KeyboardGetKeycode(void));						// Gets the value of the keycode pressed.
EXTERN 	SET_UBYTE(KeyboardGetKeyLast(void));

// Declare the keyboard type struct:
typedef struct AOS_Keyboard_Basic
{
	BYTE 				KeyLast;									// The last key pressed.
	BYTE 				Status;										// The status of the keyboard key.
	STRING 				KeyMap;										// Used to set a memory map of the keys (BROKEN).
	STRING 				Buffer;
	BOOL 				Initialized;								// The keyboard initializer.
} PACKED Keyboard_t;												// keyboard type.

#if defined(__cplusplus)
}
#endif
#endif 	// !ADAMANTINE_KEYBOARD
