#define __DEBUG__		1

#include <drivers/keyboard.h>
#include <drivers/keys.h>
#include <drivers/i8042.h>
#include <drivers/vga.h>
#include <system/portio.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/pic.h>
#include <compiler.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <debug.h>
#include <stdio.h>

#include <drivers/driver.h>

#define OUTPUT_BUFFER_STATUS        0x00
#define INPUT_BUFFER_STATUS         0x01
#define SYSTEM_FLAG                 0x02
#define COMMAND_DATA                0x03

extern void system_restart_safe(void);

__LOCAL KERNEL_API void keyboard_callback(void);
static bool ctl_down = false;
static bool alt_down = false;
static bool del_down = false;
static bool sft_down = false;

// Define for normal keys:
static const char keys_normal[MAX_KEYS] = 
{
	0x00, 0x00,				                                            // <None>, <Escape>,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',					// 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	'-', '=', '\b', '\t',												// -, =, <Backspace>, <Tab>,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	// Q, W, E, R, T, Y, U, I, O, P, [, ], <Enter>,
	0x00,  										                        // <Control>,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',				// A, S, D, F, G, H, J, K, L, ;, ',
	'`', 0x00, '\\',    						                        // `, <Left Shift>, \,
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0x00,				// Z, X, C, V, B, N, m, ',', ., /, <Right Shift>, <Alt>
	'*', 0x00, ' ', 0x00,											    // *, <Alt>, <Space Bar>, <Caps Lock>,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,			// F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	0x00, 																// <Numlock (On?)>,
	0x00,																// <Scroll Lock>,
	'7', '8', '9',	    												// Numpad 7, Numpad 8, Numpad 9
	'-', 																// Numpad -,
    '4', '5', '6',  													// Numpad 4, Numpad 5, Numpad 6,
	'+',																// Numpad +,
	'1', '2', '3',  													// Numpad 1, Numpad 2, Numpad 3,
	'0', 0x00, 															// Numpad 0, Numpad Del,
	0x00, 0x00,	0x00,													// <NONE>, <NONE>, "<NONE>"
	0x00, 0x00,															// <Windows key>, <Windows key>,
};

// Define for keys when shift is held:
static const char keys_caps[MAX_KEYS] = 
{
	0x00, 0x00, 														// <None>, <Escape>,
	'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',					// 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	'_', '+', '\b', '\t',												// -, =, <Backspace>, <Tab>,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	// Q, W, E, R, T, Y, U, I, O, P, [, ], <Enter>,
	0x00,																// <Control>,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',				// A, S, D, F, G, H, J, K, L, ;, ',
	'~', 0x00, '|',														// `, <Left Shift>, \,
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0x00,				// Z, X, C, V, B, N, m, ',', ., /, <Right Shift>, <Alt>
	'*', 0x00, ' ', 0x00,												// *, <Alt>, <Space Bar>, <Caps Lock>,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,			// F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	0x00, 																// <Numlock (On?)>,
	0x00,																// <Scroll Lock>,
	'7', '8', '9',														// Numpad 7, Numpad 8, Numpad 9
	'-', 																// Numpad -,
	'4', '5', '6',														// Numpad 4, Numpad 5, Numpad 6,
	'+',																// Numpad +,
	'1', '2', '3',														// Numpad 1, Numpad 2, Numpad 3,
	'0', '.',															// Numpad 0, Numpad Del,
	0x00, 0x00, 0x00,													// <NONE>, <NONE>, "<NONE>"
	0x00, 0x00,													        // <Windows key>, <Windows key>,
};

char key_buffer[256];

static inline uint8_t
ps2_controller_test(void)
{
	outb(I8042_COMMAND, 0xAA);
	return inb(I8042_DATA);
}

static inline bool
ps2_port_success(void)
{
	outb(I8042_COMMAND, 0xAB);
	return (inb(I8042_DATA) == 0x00);
}

bool
keyboard_initialize(void)
{
	memset(key_buffer, 0, sizeof(char) * 40);
	register_interrupt_handler(IRQ1, (isr_t)&keyboard_callback);
#if defined(VERBOSE_FLAGS) && (VERBOSE_FLAGS == 1)
	print_verbose_message("Keyboard driver installed and initialized.", INFO);
#endif
	return true;
}

int
keyboard_acknowledge(void)
{
	return 0;
}

unsigned char
keyboard_read_scancode(void)
{
	uint8_t status;
	unsigned char c;

	status = i8042_read_status_register();
	c = 0;

	if ((status & 0x01) == 1)
		c = i8042_read_data();
	return c;
}

__LOCAL KERNEL_API void
keyboard_callback(void)
{
	static unsigned char sc;
	sc = keyboard_read_scancode();

	if (sc != KEYBOARD_KEY_DOWN_NONE)
	{
		if (sc == KEYBOARD_KEY_DOWN_CONTROL)
            ctl_down = true;
        else if (sc == KEYBOARD_KEY_UP_CONTROL)
            ctl_down = false;

		if (sc == KEYBOARD_KEY_DOWN_ALT)
			alt_down = true;
		else if (sc == KEYBOARD_KEY_UP_ALT)
			alt_down = false;

		if (sc == KEYBOARD_KEY_DOWN_DELETE)
			del_down = true;
		else if (sc == KEYBOARD_KEY_UP_DELETE)
			del_down = false;

		if ((sc == KEYBOARD_KEY_DOWN_LEFT_SHIFT) || (sc == KEYBOARD_KEY_DOWN_RIGHT_SHIFT))
			sft_down = true;
		else if ((sc == KEYBOARD_KEY_UP_LEFT_SHIFT) || (sc == KEYBOARD_KEY_UP_RIGHT_SHIFT))
			sft_down = false;

		if ((ctl_down) && (alt_down) && (del_down))
			system_restart_safe();
		else
		{
			unsigned char c = 0;

			if (!sft_down)
			{
				c = keys_normal[(unsigned char)sc];
				char str[2] = {c, '\0'};
				puts(str);
			}
			else
			{
				c = keys_caps[(unsigned char)sc];
				char str[2] = {c, '\0'};
				puts(str);
			}
		}
	}
}