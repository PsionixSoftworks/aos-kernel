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
#include <kernel/drivers/keyboard.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/system/io.h>

/* Define the keyboard. */
keyboard_t keyboard;

// Declare local functions:
static inline int Keyboard_irq(void);							// keyboard irq.
static inline void keyboard_read(void);								// read the keyboard on key press.

/* Initialize the keyboard */
inline void 
keyboard_init(void) 
{
	keyboard.key_map = (char *)malloc(256);
	memset(keyboard.key_map, 0, 256);
	
	//register_interrupt_handler(33, (isr_t)&Keyboard_irq);
	keyboard.is_initialized = TRUE;
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
inline char * 
keyboard_get_key(void) 
{
	keyboard_read();
	if ((keyboard.key_last != KEYBOARD_KEY_DOWN_NONE)) 
		return (keys_normal[keyboard.key_last]);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the key code */
inline uint8_t
keyboard_get_keycode(void) 
{
	keyboard_read();
	if (keyboard.key_last > KEYBOARD_KEY_DOWN_NONE) 
		return (keyboard.key_last);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the numeric last key pressed. */
inline uint8_t 
keyboard_get_key_last(void) 
{
	return (keyboard.key_last);
}

/* Set the keyboard interrupt */
static inline int
Keyboard_irq(void) 
{
	return 0;
}

/* read keys as they're pressed */
static inline void 
keyboard_read(void) 
{
	keyboard.status = inb(KEYBOARD_PORT);
	keyboard.key_last = KEYBOARD_KEY_DOWN_NONE;
	if ((keyboard.status & 0x01) == 1) 
		keyboard.key_last = inb(KEYBOARD_DATA);
}

/* Get the keyboard char * (last char * of characters typed before <ENTER> key is pressed). */
inline char *
keyboard_get_string(void) 
{
	return (keyboard.buffer);
}
