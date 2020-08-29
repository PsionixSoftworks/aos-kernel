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

// Declare global functions:
EXTERN 	VOID (SetKeyCode(BYTE *Key, BYTE Code));					// Set keycodes for each key (UNUSED).
EXTERN 	VOID (KeyboardInit(void));								// Initialize the basic keyboard driver.
EXTERN 	VOID (KeyboardFree(void));								// Free memory associated with the keyboard driver.
EXTERN 	VOID (KeyboardWait(void));								// Give the keyboard a wait instruction.
EXTERN 	BOOL (KeyboardIsEnabled(void));							// Checks whether the keyboard is initialized or not.
EXTERN 	STRING (KeyboardGetKey(void));							// Gets the value of a key pressed.
EXTERN 	STRING (KeyboardGetString(void));
EXTERN 	UBYTE (KeyboardGetKeycode(void));						// Gets the value of the keycode pressed.
EXTERN 	UBYTE (KeyboardGetKeyLast(void));

// Declare the keyboard type struct:
typedef struct AOS_Keyboard_Basic
{
	BYTE 				KeyLast;									// The last key pressed.
	BYTE 				Status;										// The status of the keyboard key.
	STRING 				KeyMap;										// Used to set a memory map of the keys (BROKEN).
	STRING 				Buffer;
	BOOL 				Initialized;								// The keyboard initializer.
} PACKED Keyboard_t;												// keyboard type.

#endif 	// !ADAMANTINE_KEYBOARD
