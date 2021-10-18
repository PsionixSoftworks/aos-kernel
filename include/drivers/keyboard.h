#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#include <drivers/keys.h>
#include <drivers/i8042.h>
#include <common.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

#define MAX_KEYS			256							                    // Max number of keybinds (shouldn't exceed 256)

/* Function Templates */
__GLOBAL KERNEL_API bool keyboard_initialize(void);		            // Initalize the keyboard driver
__GLOBAL KERNEL_API int keyboard_acknowledge(void);                 // Acknowledge keyboard inputs
__GLOBAL KERNEL_API unsigned char keyboard_read_scancode(void);		// Read a scancode from the data port

#endif  // !_ADAMANTINE_KEYBOARD_H
