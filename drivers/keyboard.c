#define __DEBUG__		1

#include <drivers/keyboard.h>
#include <drivers/keys.h>
#include <drivers/i8042.h>
#include <drivers/vga.h>
#include <system/portio.h>
#include <adamantine/tty.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/pic.h>
#include <compiler.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <debug.h>

#include <drivers/driver.h>

#define OUTPUT_BUFFER_STATUS        0x00
#define INPUT_BUFFER_STATUS         0x01
#define SYSTEM_FLAG                 0x02
#define COMMAND_DATA                0x03

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
	outb(I8042_COMMAND_WRITE, 0xAA);
	return inb(I8042_DATA_BYTE);
}

static inline bool
ps2_port_success(void)
{
	outb(I8042_COMMAND_WRITE, 0xAB);
	return (inb(I8042_DATA_BYTE) == 0x00);
}

__LOCAL KERNEL_API void
keyboard_callback(void)
{
	
}

bool
keyboard_initialize(void)
{
	if ((ps2_controller_test() == KEYBOARD_CONTROLLER_STATUS_OK) && (ps2_port_success()))
	{
	#if defined(__DEBUG__) && __DEBUG__ == 1
		show_debug_info("Keyboard Controller initialized!");
	#endif
		register_interrupt_handler(IRQ1, &keyboard_callback);
		return true;
	}
	return false;
}

int
keyboard_acknowledge(void)
{

}

unsigned char
keyboard_read_scancode(void)
{
	
}
