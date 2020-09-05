/*
 *  File: keyboard.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

/* Includes go here: */
#include "../include/keyboard.h"
#include "../include/keys.h"
#include "../include/terminal.h"
#include "../include/mem-util.h"
#include "../include/x86/idt.h"
#include "../include/isr.h"
#include "../include/mutex.h"
#include "../include/pic.h"
#include "../include/irq.h"
#include "../include/aos-defs.h"
#include "../include/io.h"

MODULE("Keyboard", "0.01a");

/* Define the keyboard. */
keyboard_t keyboard;

// Declare local functions:
static inline SET_VOID(Keyboard_irq(void));									// keyboard irq.
static inline SET_VOID(keyboard_read(void));								// read the keyboard on key press.

/* Initialize the keyboard */
inline void 
keyboard_init(void) 
{
	keyboard.key_map = (string)malloc(256);
	memset(keyboard.key_map, 0, 256);
	
	register_interrupt_handler(33, (isr_t)&Keyboard_irq);
	keyboard.is_initialized = TRUE;
	//_INFO("keyboard initialized!");
}

/* free the keyboard. */
inline void
keyboard_free(void) 
{
	free(keyboard.key_map);
}

/* Checks if the keyboard is initialized */
inline bool
keyboard_is_enabled(void) 
{
	keyboard.key_last = KEYBOARD_KEY_DOWN_NONE;
	return (keyboard.is_initialized);
}

/* Get the key as a character */
inline string 
keyboard_get_key(void) 
{
	keyboard_read();
	if ((keyboard.key_last != KEYBOARD_KEY_DOWN_NONE)) 
		return (KeysNormal[keyboard.key_last]);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the key code */
inline ubyte
keyboard_get_keycode(void) 
{
	keyboard_read();
	if (keyboard.key_last > KEYBOARD_KEY_DOWN_NONE) 
		return (keyboard.key_last);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the numeric last key pressed. */
inline ubyte 
keyboard_get_key_last(void) 
{
	return (keyboard.key_last);
}

/* Set the keyboard interrupt */
static inline void
Keyboard_irq(void) 
{
	return;
}

/* read keys as they're pressed */
static inline void 
keyboard_read(void) 
{
	keyboard.status = read_portb(KEYBOARD_PORT);
	keyboard.key_last = KEYBOARD_KEY_DOWN_NONE;
	if ((keyboard.status & 0x01) == 1) 
		keyboard.key_last = read_portb(KEYBOARD_DATA);
}

/* Get the keyboard string (last string of characters typed before <ENTER> key is pressed). */
inline string
keyboard_get_string(void) 
{
	return (keyboard.buffer);
}
