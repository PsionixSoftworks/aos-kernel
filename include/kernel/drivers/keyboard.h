#ifndef _ADAMANTINE_KEYBOARD_H
#define _ADAMANTINE_KEYBOARD_H

#define KERNEL_ONLY

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA       0x60    // Read/Write
#define KEYBOARD_STATUS     0x64    // Read
#define KEYBOARD_CMD    	0x64    // Write

extern void keyboard_init(void);
extern unsigned char keyboard_read_scancode(void);
extern bool keyboard_key_down(uint8_t key);
extern bool keyboard_key_up(uint8_t key);
extern bool keyboard_key_press(uint8_t key);

#endif  // !_ADAMANTINE_KEYBOARD_H
