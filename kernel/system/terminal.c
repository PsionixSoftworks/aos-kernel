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
#include <kernel/system/terminal.h>
#include <kernel/drivers/vga.h>
#include <kernel/system/io.h>
#include <kernel/cpu.h>
#include <adamantine/version.h>
#include <stdarg.h>

#if (OS_VERSION_NUMBER >= 50)

static uint16_t *video_buffer;
static uint8_t background_color;
static uint8_t foreground_color;
static uint32_t x;
static uint32_t y;

static inline void terminal_putchar(char c);
static inline void terminal_kprintf(string restrict format, va_list ap);
static inline void terminal_scroll(void);

static inline void cursor_enable(uint8_t start, uint8_t end);
static inline void cursor_disable(void);
static inline void cursor_update(int x, int y);
static inline uint16_t cursor_get_pos(void);

void
terminal_init(void)
{
	video_buffer = (uint16_t *)VGA_TEXT_MODE_COLOR;
	background_color = DEFAULT_BACKGROUND_COLOR;
	foreground_color = DEFAULT_FOREGROUND_COLOR;
	x = 0;
	y = 0;

	terminal_clear();
	cursor_enable(0x0, 0xF);
}

void
terminal_clear(void)
{
	uint8_t color = ((background_color << 0x4) | (foreground_color & 0x0F));
	uint16_t blank = (color << 0x8);

	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
	{
		video_buffer[i] = blank;
	}
	x = 0;
	y = 0;
	cursor_update(x, y);
}

void
terminal_set_background_color(uint8_t color)
{
	background_color = color;
}

void
terminal_set_foreground_color(uint8_t color)
{
	foreground_color = color;
}

void
terminal_reset_background_color(void)
{
	background_color = DEFAULT_BACKGROUND_COLOR;
}

void
terminal_reset_foreground_color(void)
{
	foreground_color = DEFAULT_FOREGROUND_COLOR;
}

uint8_t
terminal_get_background_color(void)
{
	return (background_color);
}

uint8_t
terminal_get_foreground_color(void)
{
	return (foreground_color);
}

void
terminal_print(string str)
{
	for (size_t i = 0; i < strlen(str); ++i)
	{
		terminal_putchar(str[i]);
	}
}

void
terminal_printf(string restrict format, ...)
{
	char buffer[256];
	va_list ap;
	va_start(ap, format);
	for (size_t i = 0; i < strlen(format); ++i)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
				case 's': {
					string __input = va_arg(ap, string);
					terminal_print(__input);
					i++;
					continue;
				}
				case 'b': {
					int32_t __input = va_arg(ap, int32_t);
					terminal_print(itoa(__input, buffer, 2));
					i++;
					continue;
				}
				case 'c': {
					string __input = va_arg(ap, string);
					terminal_putchar(__input);
					i++;
					continue;
				}
				case 'd': {
					uint32_t __input = va_arg(ap, uint32_t);
					terminal_print(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'o': {
					int32_t __input = va_arg(ap, int32_t);
					terminal_print(itoa(__input, buffer, 8));
					i++;
					continue;
				}
				case 'x': {
					int32_t __input = va_arg(ap, int32_t);
					string result = itoa(__input, buffer, 16);
					to_lower(result);
					terminal_print(result);
					i++;
					continue;
				}
				case 'X': {
					int32_t __input = va_arg(ap, int32_t);
					string result = itoa(__input, buffer, 16);
					to_upper(result);
					terminal_print(result);
					i++;
					continue;
				}
			};
		}
		else
		{
			terminal_putchar(format[i]);
		}
	}
	va_end(ap);
}

static inline void
terminal_putchar(char c)
{
	uint8_t color = ((background_color << 0x4) | (foreground_color & 0x0F));
	const uint16_t attrib = color << 0x8;

	if (x >= VGA_WIDTH)
	{
		x = 0;
		y++;
	}
	if (c == '\n')
	{
		x = 0;
		y++;
	}
	else if (c == '\t')
	{
		x = (x + 5) - 1;
	}
	else
	{
		video_buffer[y * VGA_WIDTH + x] = c | attrib;
		x++;
	}
	cursor_update(x, y);
	terminal_scroll();
}

static inline void
terminal_scroll(void)
{
	const uint8_t color = ((background_color << 0x4) | (foreground_color & 0x0F));
	const uint16_t attrib = color << 0x8;

	if (y >= VGA_HEIGHT)
	{
		for (size_t i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++)
		{
			video_buffer[i] = video_buffer[i + VGA_WIDTH];
		}
		for (size_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); ++i)
		{
			video_buffer[i] = attrib;
		}
		y = VGA_HEIGHT - 1;
	}
}

static inline void
cursor_enable(uint8_t start, uint8_t end)
{
	const uint8_t start_address = read_portb(0x3D5);
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, (start_address & 0xC0) | start);

	const uint8_t end_address = read_portb(0x3D5);
	write_portb(0x3D4, 0x0B);
	write_portb(0x3D5, (end_address & 0xE0) | end);
}

static inline void
cursor_disable(void)
{
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, 0x20);
}

static inline void
cursor_update(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	write_portb(0x3D4, 0x0F);
	write_portb(0x3D5, (uint8_t)(pos & 0xFF));

	write_portb(0x3D4, 0x0E);
	write_portb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static inline uint16_t
cursor_get_pos(void)
{
	uint16_t pos = 0;

	write_portb(0x3D4, 0x0F);
	pos |= read_portb(0x3D5);

	write_portb(0x3D4, 0x0E);
	pos |= ((uint16_t)read_portb(0x3D5)) << 8;

	return (pos);
}

void 
panic(const string msg, const string file, udword line) 
{
	__asm__ __volatile__("CLI");
	terminal_printf("!!! PANIC(%s) in file \"%s\" : Line: %d\n", msg, file, line);
	cpu_halt();
}

void
panic_assert(const string file, udword line, const string description)
{
	__asm__ __volatile__("CLI");
	terminal_printf("!!! ASSERTION-FAILED(%s) in file \"%s\" : Line: %d.\n", description, file, line);
	cpu_halt();
}

#else
#define __KERNEL__

#include <system/terminal.h>
#include <drivers/vga.h>
#include <system/io.h>
#include <drivers/keyboard.h>
#include <adamantine/mutex.h>
#include <stdarg.h>
#include <adamantine.h>

#define EOF		(-1)

/* Define mutexes here. */
DEFINE_mutex(m_mprintf);

static const ubyte default_back_color = SYSTEM_COLOR_BLACK;
static const ubyte default_fore_color = SYSTEM_COLOR_WHITE;

static terminal_t terminal;
static uword *video_buffer;
static string terminal_buffer;
static inline dword terminal_putchar(char c);
static inline void move_cursor(void);
static inline void scroll(void);
static bool is_initialized;
static ubyte fore_color;
static ubyte back_color;
static udword x;
static udword y;

DEPRECATED static inline dword 
terminal_putchar(char c) 
{
	ubyte color_byte = ((terminal.back_color << 0x04) | (terminal.fore_color & 0x0F));
	uword attribute = color_byte << 0x08;
	uword *location;

	if ((c == 0x08) && (terminal.x > 0x10)) 
	{
		terminal_move_cursor(-1, 0);
		location = video_buffer + (terminal.y * VGA_WIDTH + terminal.x);
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
		location = video_buffer + (terminal.y * VGA_WIDTH + terminal.x);
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
	video_buffer 	= (uword *)VGA_TEXT_MODE_COLOR;
	back_color 		= default_back_color;
	fore_color 		= default_fore_color;
	is_initialized 	= TRUE;

	/* Clear the screen and set the whole screen to default. */
	system_log_clear();
}

inline void
system_log_end(void)
{
	video_buffer	= NULL;
	is_initialized 	= FALSE;
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
		system_log_set_fore_col(SYSTEM_COLOR_LT_GREEN);
		terminal_print("[INFO]: ");
		printf((const string)format, ap);
		system_log_reset_fore_col();
	}
	else if (severity == WARNING)
	{
		system_log_set_fore_col(SYSTEM_COLOR_YELLOW);
		terminal_print("[WARNING]: ");
		printf((const string)format, ap);
		system_log_reset_fore_col();
	}
	else if (severity == ERROR)
	{
		system_log_set_fore_col(SYSTEM_COLOR_RED);
		terminal_printf("[ERROR]: ");
		printf((const string)format, ap);
		system_log_reset_fore_col();
		cpu_halt();
	}
	else
	{
		printf((const string)format, ap);
	}

	return (TRUE);
}

inline void
system_log_set_back_col(ubyte col)
{
	back_color = col;
}

inline void
system_log_set_fore_col(ubyte col)
{
	fore_color = col;
}

inline void
system_log_reset_back_col(void)
{
	back_color = default_back_color;
}

inline void
system_log_reset_fore_col(void)
{
	fore_color = default_fore_color;
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
		video_buffer[i] = blank;
	}
}

inline void
system_log_clear(void)
{
	/* Clear the screen and set the whole screen to default. */
	ubyte color_byte;
	uword blank;

	/* Set the color properties (for background and text). */
	color_byte 				= ((back_color << 0x04) | (fore_color & 0x0F));
	blank 					= 0x20 | (color_byte << 0x08);

	/* Fill the terminal blank (black is default) */
	for (size_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
	{
		video_buffer[i] = blank;
	}

	/* Set the terminal cursor x and y positions */
	x = 0;
	y = 0;
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
			video_buffer[i] = video_buffer[i + VGA_WIDTH];
		}

		for (i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
		{
			video_buffer[i] = Blank;
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
	video_buffer = (uword *)VGA_TEXT_MODE_COLOR;
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
		video_buffer[i] = Blank;
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

#endif
