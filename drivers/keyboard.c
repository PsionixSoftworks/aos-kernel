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
Keyboard_t Keyboard;

// Declare local functions:
static SET_VOID(KeyboardIRQ(VOID));									// Keyboard IRQ.
static SET_VOID(KeyboardRead(VOID));								// Read the keyboard on key press.

/* Initialize the keyboard */
VOID 
KeyboardInit(VOID) 
{
	Keyboard.KeyMap = (STRING)Malloc(256);
	MemSet(Keyboard.KeyMap, 0, 256);
	
	RegisterInterruptHandler(33, (ISR_t)&KeyboardIRQ);
	Keyboard.Initialized = TRUE;
	INFO("Keyboard initialized!");
}

/* Free the keyboard. */
VOID
KeyboardFree(VOID) 
{
	Free(Keyboard.KeyMap);
}

/* Checks if the keyboard is initialized */
BOOL
keyboard_is_enabled(VOID) 
{
	Keyboard.KeyLast = KEYBOARD_KEY_DOWN_NONE;
	return (Keyboard.Initialized);
}

/* Get the key as a character */
STRING 
KeyboardGetKey(VOID) 
{
	KeyboardRead();
	if ((Keyboard.KeyLast != KEYBOARD_KEY_DOWN_NONE)) 
		return (KeysNormal[Keyboard.KeyLast]);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the key code */
UBYTE
KeyboardGetKeycode(VOID) 
{
	KeyboardRead();
	if (Keyboard.KeyLast > KEYBOARD_KEY_DOWN_NONE) 
		return (Keyboard.KeyLast);
	return (KEYBOARD_KEY_DOWN_NONE);
}

/* Get the numeric last key pressed. */
UBYTE 
KeyboardGetKeyLast(void) 
{
	return (Keyboard.KeyLast);
}

/* Set the keyboard interrupt */
static VOID 
KeyboardIRQ(void) 
{
	return;
}

/* Read keys as they're pressed */
static VOID 
KeyboardRead(VOID) 
{
	Keyboard.Status = ReadPortB(KEYBOARD_PORT);
	Keyboard.KeyLast = KEYBOARD_KEY_DOWN_NONE;
	if ((Keyboard.Status & 0x01) == 1) 
		Keyboard.KeyLast = ReadPortB(KEYBOARD_DATA);
}

/* Get the keyboard string (last string of characters typed before <ENTER> key is pressed). */
STRING
KeyboardGetString(void) 
{
	return (Keyboard.Buffer);
}
