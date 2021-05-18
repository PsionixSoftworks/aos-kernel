#ifndef _AOS_KEYBOARD_H
#define _AOS_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA       0x60    // Read/Write
#define KEYBOARD_STATUS     0x64    // Read
#define KEYBOARD_CMD    	0x64    // Write

void keyboard_init(void);
unsigned char keyboard_read_scancode(void);
bool keyboard_key_down(uint8_t key);
bool keyboard_key_up(uint8_t key);
bool keyboard_key_press(uint8_t key);

#endif  // !_AOS_KEYBOARD_H
