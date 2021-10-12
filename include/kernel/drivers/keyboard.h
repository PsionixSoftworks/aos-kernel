#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <kernel/drivers/keys.h>
#include <kernel/drivers/i8042.h>
#include <common.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

#define MAX_KEYS			256							// Max number of keybinds (shouldn't exceed 256)

/* Function Templates */
EXTERN __GLOBAL KERNEL_API _PROTO(bool keyboard_init, (void)                    );		// Initalize the keyboard driver
EXTERN __GLOBAL KERNEL_API _PROTO(unsigned char keyboard_read_scancode, (void)  );		// Read a scancode from the data port

#endif  // !_ADAMANTINE_KEYBOARD_H
