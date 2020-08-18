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
#include <stdarg.h>

#include "../include/terminal.h"
#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include "../include/mutex.h"
#include "../include/aos-defs.h"

MODULE("terminal", "0.01a");

#define EOF		(-1)

/* Define mutexes here. */
DEFINE_MUTEX(m_mprintf);

static terminal_t terminal;
static uint16_t *video_memory;
static int terminal_putchar(char c);
static void move_cursor(void);
static void scroll(void);

void 
terminal_init(uint8_t back_color, uint8_t fore_color) 
{
	video_memory = (uint16_t *)VGA_TEXT_MODE_COLOR;
	terminal.back_color = back_color;
	terminal.fore_color = fore_color;
	terminal.is_initialized = true;

	terminal_clear_screen();
}

void 
terminal_clear_screen(void) 
{
	uint8_t attribute_byte = ((terminal.back_color << 4) | (terminal.fore_color & 0x0F));
	uint16_t blank = 0x20 | (attribute_byte << 8);

	for (int i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
	{
		video_memory[i] = blank;
	}
	terminal.x = 0;
	terminal.y = 0;
	move_cursor();
}

void 
terminal_print(const char *c) 
{
	int i = 0;
	while (c[i]) 
	{
		terminal_putchar(c[i++]);
	}
}

void
terminal_print_hex(int32_t value)
{
	terminal_print_value(value, 16);
}

void
terminal_print_dec(int32_t value)
{
	terminal_print_value(value, 10);
}

static bool 
print(const char *data, size_t length) 
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++) 
	{
		if (terminal_putchar(bytes[i]) == EOF)
			return (false);
		return (true);
	}
}

static void 
__printf(const char *str, va_list ap) 
{
	mutex_lock(&m_mprintf);
	char *s = 0;
	char buffer[32768];
	for (size_t i = 0; i < strlen((string)str); i++) 
	{
		if (str[i] == '%') 
		{
			switch (str[i + 1]) 
			{
				case 's':
					s = va_arg(ap, const char *);
					terminal_print(s);
					i++;
					continue;
				case 'b': {
					int b = va_arg(ap, int);
					terminal_print(itoa(b, buffer, 2));
					i++;
					continue;
				}
				case 'o': {
					int o = va_arg(ap, int);
					terminal_print(itoa(o, buffer, 8));
					i++;
					continue;
				}
				case 'd': {
					int c = va_arg(ap, int);
					terminal_print_dec(c);
					i++;
					continue;
				}
				case 'x': {
					int c = va_arg(ap, int);
					int final_value = itoa(c, buffer, 16);
					to_lower(final_value);
					terminal_print(final_value);
					i++;
					continue;
				}
				case 'X': {
					int c = va_arg(ap, int);
					int final_value = itoa(c, buffer, 16);
					to_upper(final_value);
					terminal_print(final_value);
					i++;
					continue;
				}
			};
		} 
		else 
		{
			terminal_putchar(str[i]);
		}
	}
	mutex_unlock(&m_mprintf);
	va_end(ap);
}

int 
terminal_printf(const char *restrict format, ...) 
{
	// TODO: Implement the printf function...
	if (!format)
		return 0;
	va_list ap;
	va_start(ap, format);
	__printf((const char *)format, ap);

	return (1);
}

void 
terminal_println(void) 
{
	terminal_print("\n");
}

void 
terminal_print_value(int32_t value, uint8_t base) 
{
	char buffer[16];
	string num_to_str = itoa(value, buffer, base);
	if (base == 16)
		terminal_print("0x");
	if (base == 2)
		terminal_print("0b");
	terminal_print(num_to_str);
}

static int 
terminal_putchar(char c) 
{
	//terminal.fore_color = SYSTEM_COLOR_WHITE;

	uint8_t attribute_byte = ((terminal.back_color << 4) | (terminal.fore_color & 0x0F));
	uint16_t attribute = attribute_byte << 8;
	uint16_t *location;

	if ((c == 0x08) && (terminal.x > 16)) 
	{
		terminal_move_cursor(-1, 0);
		location = video_memory + (terminal.y * VGA_WIDTH + terminal.x);
		*location = ' ' | attribute;
	} else
	if (c == 0x09) 
	{
		terminal.x = (terminal.x + 4) & ~(4-1);
	} else
	if (c == '\r') 
	{
		terminal.x = 0;
	} else
	if (c == '\n') 
	{
		terminal.x = 0;
		terminal.y++;
	} else
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

static void 
move_cursor(void) 
{
	uint16_t cursor_location = terminal.y * VGA_WIDTH + terminal.x;
	write_portb(0x3D4, 14);
	write_portb(0x3D5, cursor_location >> 8);
	write_portb(0x3D4, 15);
	write_portb(0x3D5, cursor_location);
}

static void 
scroll(void) 
{
	uint8_t atribute_byte = ((terminal.back_color << 4) | (terminal.fore_color & 0x0F));
	uint16_t blank = 0x20 | (atribute_byte << 8);

	if (terminal.y >= VGA_HEIGHT) 
	{
		int i;
		for (i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) 
		{
			video_memory[i] = video_memory[i + VGA_WIDTH];
		}

		for (i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
		{
			video_memory[i] = blank;
		}
		terminal.y = VGA_HEIGHT - 1;
	}
}

char 
terminal_getchar(char c) 
{
	return (c);
}

char *terminal_buffer;
char *
terminal_gets(char *str) 
{
	terminal_buffer = strcpy(str, terminal_buffer);
	return (terminal_buffer);
}

void 
terminal_move_cursor(uint32_t x, uint32_t y)
{
	terminal.x += x;
	terminal.y += y;
	move_cursor();
}

uint32_t terminal_get_cursor_x()
{
	return (terminal.x);
}

uint32_t terminal_get_cursor_y()
{
	return (terminal.y);
}

void 
panic(const string message, const string file, uint32_t line) 
{
	__asm__ __volatile__("cli");
	terminal_printf("!!! PANIC(%s) at %s : %d\n", message, file, line);
	cpu_halt();
}

void panic_assert(const char *file, uint32_t line, const char *desc) 
{
	__asm__ __volatile__("cli");
	terminal_printf("!!! ASSERTION-FAILED(%s) at %s : %d.\n", desc, file, line);
	cpu_halt();
}
