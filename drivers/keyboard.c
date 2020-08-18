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

MODULE("keyboard", "0.01a");

/* Define the keyboard. */
keyboard_t keyboard;

// Declare local functions:
static void keyboard_irq(void);						// Keyboard IRQ.
static void keyboard_read(void);					// Read the keyboard on key press.

/* Define all mutexes here. */
//DEFINE_MUTEX(m_get_key);

/* Initialize the keyboard */
void 
keyboard_init(void) 
{
	keyboard.keymap = (string)malloc(256);
	memset(keyboard.keymap, 0, 256);
	
	register_interrupt_handler(33, (isr_t)keyboard_irq);
	keyboard.initialized = true;
	INFO("Keyboard initialized!");
}

/* Free the keyboard. */
void 
keyboard_free(void) 
{
	free(keyboard.keymap);
}

/* Checks if the keyboard is initialized */
bool 
keyboard_is_enabled(void) 
{
	keyboard.key_last = KEYBOARD_KEY_DOWN_NONE;
	return (keyboard.initialized);
}

/* Get the key as a character */
string 
keyboard_get_key(void) 
{
	keyboard_read();
	if ((keyboard.key_last != KEYBOARD_KEY_DOWN_NONE) || (keyboard.key_last != KEYBOARD_KEY_DOWN_ENTER)) 
	{
		return (keys_normal[keyboard.key_last]);
	} else 
	{
		return (KEYBOARD_KEY_DOWN_NONE);
	}
}

/* Get the key code */
int8_t
keyboard_get_keycode(void) 
{
	keyboard_read();
	if (keyboard.key_last == KEYBOARD_KEY_DOWN_NONE) 
	{
		return (keyboard.key_last);
	}
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the numeric last key pressed. */
uint8_t keyboard_get_keylast(void) 
{
	return (keyboard.key_last);
}

/* Set the keyboard interrupt */
static void 
keyboard_irq(void) 
{
	
}

/* Read keys as they're pressed */
static void keyboard_read(void) 
{
	keyboard.status = read_portb(KEYBOARD_PORT);
	keyboard.key_last = KEYBOARD_KEY_DOWN_NONE;
	if ((keyboard.status & 0x01) == 1) 
	{
		keyboard.key_last = read_portb(KEYBOARD_DATA);
	}
}

/* Get the keyboard string (last string of characters typed before <ENTER> key is pressed). */
string keyboard_get_string(void) 
{
	return (keyboard.buffer);
}
