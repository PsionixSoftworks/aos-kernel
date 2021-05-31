#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <stdint.h>
#include <stdbool.h>

/* Define keyboard port macros */
#define KEYBOARD_DATA       0x60    					// Read/Write
#define KEYBOARD_STATUS     0x64    					// Read
#define KEYBOARD_CMD    	0x64    					// Write

/* Function Templates */
extern void keyboard_init(void);						// Initalize the keyboard driver
extern unsigned char keyboard_read_scancode(void);		// Read a scancode from the data port
extern bool keyboard_key_down(uint8_t key);				// Check if a key is down (Unused?)
extern bool keyboard_key_up(uint8_t key);				// Check if a key is up (Unused?)
extern bool keyboard_key_press(uint8_t key);			// Check if a key is pressed (Unused?)

#endif  // !_ADAMANTINE_KEYBOARD_H
