#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <kernel/drivers/keys.h>
#include <kernel/drivers/i8042.h>
#include <stdbool.h>
#include <stdint.h>

/* Function Templates */
extern bool keyboard_init(void);						// Initalize the keyboard driver
extern unsigned char keyboard_read_scancode(void);		// Read a scancode from the data port

#endif  // !_ADAMANTINE_KEYBOARD_H
