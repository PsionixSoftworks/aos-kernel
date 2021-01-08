#ifndef _AOS_KEYBOARD_H
#define _AOS_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA       0x60
#define KEYBOARD_STATUS     0x64
#define KEYBOARD_COMMAND    0x64

void keyboard_init(void);
unsigned char keyboard_read_scancode(void);

#endif
