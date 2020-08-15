#ifndef _AOS_KEYBOARD_
#define _AOS_KEYBOARD_

// Include files here:
#include "types.h"
#include "string.h"
#include "driver.h"

#if KERNEL32

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
extern void set_key_code(uint8_t *key, byte code);				// Set keycodes for each key (UNUSED).
extern void keyboard_init(void);								// Initialize the basic keyboard driver.
extern void keyboard_free(void);								// Free memory associated with the keyboard driver.
extern void keyboard_wait(void);								// Give the keyboard a wait instruction.
extern bool keyboard_is_enabled(void);							// Checks whether the keyboard is initialized or not.
extern string keyboard_get_key(void);							// Gets the value of a key pressed.
extern int8_t keyboard_get_keycode(void);						// Gets the value of the keycode pressed.
extern uint8_t keyboard_get_keylast(void);
extern string keyboard_get_string(void);

// Declare the keyboard type struct:
typedef struct 
{
	uint8_t key_last;											// The last key pressed.
	string keymap;												// Used to set a memory map of the keys (BROKEN).
	uint8_t status;												// The status of the keyboard key.
	bool initialized;											// The keyboard initializer.
	string buffer;
} __attribute__((packed)) keyboard_t;							// keyboard type.

#if defined(__cplusplus)
}
#endif

#endif
#endif 	// !ADAMANTINE_KEYBOARD
