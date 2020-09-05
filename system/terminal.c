/*
 *  File: terminal.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

/* Include anything the terminal requires here */
#define __KERNEL__

#include "../include/terminal.h"
#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include "../include/mutex.h"

#include <stdarg.h>

MODULE("terminal", "0.01a");

#define EOF		(-1)

/* Define mutexes here. */
DEFINE_mutex(m_mprintf);

static const ubyte default_back_color = SYSTEM_COLOR_BLACK;
static const ubyte default_fore_color = SYSTEM_COLOR_WHITE;

static terminal_t terminal;
static uword *video_memory;
static string terminal_buffer;
static inline dword terminal_putchar(char c);
static inline void move_cursor(void);
static inline void scroll(void);

DEPRECATED static inline dword 
terminal_putchar(char c) 
{
	ubyte color_byte = ((terminal.back_color << 0x04) | (terminal.fore_color & 0x0F));
	uword attribute = color_byte << 0x08;
	uword *location;

	if ((c == 0x08) && (terminal.x > 0x10)) 
	{
		terminal_move_cursor(-1, 0);
		location = video_memory + (terminal.y * VGA_WIDTH + terminal.x);
		*location = ' ' | attribute;
	} 
	else
	if (c == 0x09) 
	{
		terminal.x = (terminal.x + 0x04) & ~(0x04-0x01);
	} 
	else
	if (c == '\r') 
	{
		terminal.x = 0;
	} 
	else
	if (c == '\n') 
	{
		terminal.x = 0;
		terminal.y++;
	} 
	else
	if (c >= ' ') 
	{
		location = video_memory + (terminal.y * VGA_WIDTH + terminal.x);
		*location = c | attribute;
		terminal.x++;
	}

	if (terminal.x >= VGA_WIDTH) {
		terminal.x = 0;
		terminal.y++;
	}
	scroll();
	move_cursor();
}

inline void 
system_log_begin(void)
{
	/* Setup the initial terminal buffer. */
	video_memory 			= (uword *)VGA_TEXT_MODE_COLOR;
	terminal.back_color 	= default_back_color;
	terminal.fore_color 	= default_fore_color;
	terminal.is_initialized = TRUE;

	/* Clear the screen and set the whole screen to default. */
	system_log_clear();
}

inline void
system_log_end(void)
{
	video_memory			= NULL;
	terminal.is_initialized = FALSE;
}

static void 
printf(const string Str, va_list ap)
{
	mutex_lock(&m_mprintf);
	string s = 0;
	char buffer[512];
	for (size_t i = 0; i < strlen((string)Str); i++)
	{
		if (Str[i] == '%') 
		{
			switch (Str[i + 1]) 
			{
				case 's':
					s = va_arg(ap, const string);
					terminal_print(s);
					i++;
					continue;
				case 'b': {
					dword b = va_arg(ap, dword);
					terminal_print(itoa(b, buffer, 2));
					i++;
					continue;
				}
				case 'o': {
					dword o = va_arg(ap, dword);
					terminal_print(itoa(o, buffer, 8));
					i++;
					continue;
				}
				case 'd': {
					dword c = va_arg(ap, dword);
					terminal_print_dec(c);
					i++;
					continue;
				}
				case 'x': {
					dword c = va_arg(ap, dword);
					dword FinalValue = itoa(c, buffer, 16);
					terminal_print(FinalValue);
					i++;
					continue;
				}
				case 'X': {
					dword c = va_arg(ap, dword);
					dword FinalValue = itoa(c, buffer, 0x10);
					to_upper(FinalValue);
					terminal_print(FinalValue);
					i++;
					continue;
				}
			};
		} 
		else 
		{
			terminal_putchar(Str[i]);
		}
	}
	mutex_unlock(&m_mprintf);
	va_end(ap);
}

inline bool
system_logf(ubyte severity, string restrict format, ...)
{
	if (!format)
		return (FALSE);
	va_list ap;
	va_start(ap, format);
	if (severity == INFORMATION)
	{
		terminal_print("[INFO]: ");
	}
	if (severity == WARNING)
	{
		terminal_print("[WARNING]: ");
	}
	if (severity == ERROR)
	{
		terminal_printf("[ERROR]: ");
		printf((const string)format, ap);
		cpu_halt();
	}
	printf((const string)format, ap);

	return (TRUE);
}

inline void
system_log_set_back_col(ubyte col)
{
	terminal.back_color = col;
}

inline void
system_log_set_fore_col(ubyte col)
{
	terminal.fore_color = col;
}

inline void
system_log_reset_back_col(void)
{
	terminal.back_color = default_back_color;
}

inline void
system_log_reset_fore_col(void)
{
	terminal.fore_color = default_fore_color;
}

inline void
system_log_clear_back_col(ubyte col)
{
	ubyte color_byte;
	uword blank;

	color_byte 				= ((col << 0x04) | (terminal.fore_color & 0x0F));
	blank 					= 0x20 | (color_byte << 0x08);

	for (size_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
	{
		video_memory[i] = blank;
	}
}

inline void
system_log_clear(void)
{
	/* Clear the screen and set the whole screen to default. */
	ubyte color_byte;
	uword blank;

	/* Set the color properties (for background and text). */
	color_byte 				= ((terminal.back_color << 0x04) | (terminal.fore_color & 0x0F));
	blank 					= 0x20 | (color_byte << 0x08);

	/* Fill the terminal blank (black is default) */
	for (size_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
	{
		video_memory[i] = blank;
	}

	/* Set the terminal cursor x and y positions */
	terminal.x = 0;
	terminal.y = 0;
	move_cursor();
}

static inline void 
move_cursor(void) 
{
	uword CursorLocation = terminal.y * VGA_WIDTH + terminal.x;
	write_portb(0x3D4, 14);
	write_portb(0x3D5, CursorLocation >> 8);
	write_portb(0x3D4, 15);
	write_portb(0x3D5, CursorLocation);
}

static inline void 
scroll(void) 
{
	ubyte AtributeByte = ((terminal.back_color << 0x4) | (terminal.fore_color & 0x0F));
	uword Blank = 0x20 | (AtributeByte << 0x8);

	if (terminal.y >= VGA_HEIGHT) 
	{
		dword i;
		for (i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) 
		{
			video_memory[i] = video_memory[i + VGA_WIDTH];
		}

		for (i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
		{
			video_memory[i] = Blank;
		}
		terminal.y = VGA_HEIGHT - 1;
	}
}

/* THIS BEGINS DEPRECATED FUNCTIONS */
/* THIS BEGINS DEPRECATED FUNCTIONS */
/* THIS BEGINS DEPRECATED FUNCTIONS */

DEPRECATED inline void
terminal_init(ubyte back_color, ubyte fore_color) 
{
	video_memory = (uword *)VGA_TEXT_MODE_COLOR;
	terminal.back_color = back_color;
	terminal.fore_color = fore_color;
	terminal.is_initialized = TRUE;

	terminal_clear_screen();
}

DEPRECATED inline void
terminal_clear_screen(void)
{
	ubyte color_byte = ((terminal.back_color << 0x04) | (terminal.fore_color & 0x0F));
	uword Blank = 0x20 | (color_byte << 0x08);

	for (dword i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
	{
		video_memory[i] = Blank;
	}
	terminal.x = 0;
	terminal.y = 0;
	move_cursor();
}

DEPRECATED inline void
terminal_print(const string Str) 
{
	dword i = 0;
	while (Str[i]) 
	{
		terminal_putchar(Str[i++]);
	}
}

DEPRECATED inline void
terminal_print_hex(udword value)
{
	terminal_print_value(value, 0x10);
}

DEPRECATED inline void
terminal_print_dec(dword value)
{
	terminal_print_value(value, 0x0A);
}

static inline bool 
print(const string data, size_t length) 
{
	const ubyte *Bytes = (const ubyte *)data;
	for (size_t i = 0; i < length; i++) 
	{
		if (terminal_putchar(Bytes[i]) == EOF)
			return (FALSE);
		return (TRUE);
	}
}

DEPRECATED inline dword 
terminal_printf(const string restrict Format, ...) 
{
	// TODO: Implement the printf function...
	if (!Format)
		return 0;
	va_list ap;
	va_start(ap, Format);
	printf((const string)Format, ap);

	return (1);
}

DEPRECATED inline void 
terminal_println(void) 
{
	terminal_print("\n");
}

DEPRECATED inline void 
terminal_print_value(dword value, ubyte base) 
{
	char buffer[16];
	string NumberToString = itoa(value, buffer, base);
	if (base == 0x10)
		terminal_print("0x");
	if (base == 0x2)
		terminal_print("0b");
	terminal_print(NumberToString);
}

inline char
terminal_getchar(char c) 
{
	return (c);
}

inline string
terminal_gets(string Str) 
{
	terminal_buffer = strcpy(Str, terminal_buffer);
	return (terminal_buffer);
}

inline void 
terminal_move_cursor(udword x, udword y)
{
	terminal.x += x;
	terminal.y += y;
	move_cursor();
}

udword 
terminal_get_cursor_x(void)
{
	return (terminal.x);
}

udword terminal_get_cursor_y(void)
{
	return (terminal.y);
}

void 
panic(const string Message, const string File, udword Line) 
{
	__asm__ __volatile__("CLI");
	terminal_printf("!!! PANIC(%s) at %s : %d\n", Message, File, Line);
	cpu_halt();
}

void
panic_assert(const string File, udword Line, const string Description) 
{
	__asm__ __volatile__("CLI");
	terminal_printf("!!! ASSERTION-FAILED(%s) at %s : %d.\n", Description, File, Line);
	cpu_halt();
}
