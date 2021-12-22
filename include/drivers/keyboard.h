#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#include <drivers/keys.h>
#include <drivers/i8042.h>
#include <macros.h>

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

#define MAX_KEYS			            256							// Max number of keybinds (shouldn't exceed 256)
#define KEYBOARD_CONTROLLER_STATUS_OK   0x55

#define KB_DATA                         0x60
#define KB_STATUS                       0x64
#define KB_COMMAND                      0x64

/* Function Templates */
__GLOBAL KERNEL_API bool keyboard_initialize(void);		            // Initalize the keyboard driver
__GLOBAL KERNEL_API int keyboard_acknowledge(void);                 // Acknowledge keyboard inputs
__GLOBAL KERNEL_API unsigned char keyboard_read_scancode(void);		// Read a scancode from the data port

#endif  // !_ADAMANTINE_KEYBOARD_H
