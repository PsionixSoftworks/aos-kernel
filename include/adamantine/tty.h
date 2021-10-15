#ifndef _ADAMANTINE_TTY_H
#define _ADAMANTINE_TTY_H

#define KERNEL_ONLY										// CAN ONLY BE ACCESSED IN KERNEL MODE!

#define _USES_MACROS

#include <common.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>
#include <termios.h>
#include <macros.h>

/* Macros for the Text Mode cursor */
#define CURSOR_CMD		0x03D4							// Cursor Command
#define CURSOR_DATA		0x03D5							// Cursor Data

/* Define macros for the Text Mode cusror */
#if defined(CURSOR_TYPE) && (CURSOR_TYPE == 0)			// This will make a block cursor, all others will be an underline (for now).
#define CURSOR_START	0xE								// Top=14
#define CURSOR_END		0xF								// Bottom=15
#else
#define CURSOR_START	0x0								// Top=0
#define CURSOR_END		0xF								// Bottom=15
#endif

/* Define the type for the teletype struct */
typedef struct TTY tty_t;
struct TTY
{
	uint16_t *mode_addr;								// VGA address to print characters at
	uint8_t background_color;							// Command line background color
	uint8_t foreground_color;							// Command line foreground color
	uint8_t x;											// Cursor x-position
	uint8_t y;											// Cursor y-position
};

/* Function templates */
__GLOBAL void tty_init(uint16_t *);	// Initialize the teletype text mode for the command line
__GLOBAL void tty_clear(void);	// Clears the screen
__GLOBAL void tty_putchar(char);	// Put a character at the next position
__GLOBAL void tty_puts(char *);	// Print a string
__GLOBAL void tty_printf(const char *__restrict, ...);	// Print a formatted string
__GLOBAL void tty_println(void);	// Print a newline
__GLOBAL void tty_cursor_enable(uint8_t, uint8_t);	// Enable Text Mode cursor
__GLOBAL void tty_cursor_disable(void);	// Disable Text Mode cursor
__GLOBAL void tty_cursor_update(void);	// Update the cursor position internally
__GLOBAL void tty_cursor_set_pos(uint8_t, uint8_t);	// Manually set the  cursor position
__GLOBAL uint16_t tty_cursor_get_pos(void);	// Get the cursor position
__GLOBAL void tty_set_background(uint8_t);	// Set the teletype background color
__GLOBAL void tty_set_foreground(uint8_t);	// Set the teletype text color
__GLOBAL void tty_set_colors(uint8_t, uint8_t);	// Set both the background and text colors
__GLOBAL uint8_t tty_get_background(void);	// Get the current background color
__GLOBAL uint8_t tty_get_foreground(void);	// Get the current foreground color

#endif	// !_ADAMANTINE_TTY_H
