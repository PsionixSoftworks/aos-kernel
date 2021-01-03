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
#include <stdarg.h>

#if (OS_VERSION_NUMBER <= 150)

static uint16_t *video_buffer;
static uint8_t background_color;
static uint8_t foreground_color;
static uint32_t x;
static uint32_t y;

static inline void terminal_putchar(char c);
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
terminal_print(char *str)
{
	for (size_t i = 0; i < strlen(str); ++i)
	{
		terminal_putchar(str[i]);
	}
}

void
terminal_printf(const char *restrict format, ...)
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
					char *__input = va_arg(ap, char *);
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
					char *__input = va_arg(ap, char *);
					terminal_putchar((int)__input);
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
					char *result = itoa(__input, buffer, 16);
					to_lower(result);
					terminal_print(result);
					i++;
					continue;
				}
				case 'X': {
					int32_t __input = va_arg(ap, int32_t);
					char *result = itoa(__input, buffer, 16);
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
panic(const char *msg, const char *file, uint32_t line) 
{
	__asm__ __volatile__("CLI");
	terminal_printf("!!! PANIC(%s) in file \"%s\" : Line: %d\n", msg, file, line);
	cpu_halt();
}

#endif