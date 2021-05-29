#include <adamantine/tty.h>
#include <kernel/drivers/vga.h>
#include <kernel/system/ioctrl.h>

#include <string.h>
#include <stdarg.h>

static const size_t TERMINAL_WIDTH		= 80;
static const size_t TERMINAL_HEIGHT		= 25;
static inline void tty_scroll(void);

tty_t tty;

#define CARRIAGE_RETURN()	\
{							\
	tty.x=0;				\
}

#define NEWLINE()			\
{							\
	tty.x=0;				\
	tty.y++;				\
}

#define TAB()				\
{							\
	tty.x=(tty.x+5)-1;	\
}

void
tty_init(uint16_t *mode)
{
	tty.mode_addr = (uint16_t *)mode;
	tty.background_color = SYSTEM_COLOR_BLACK;
	tty.foreground_color = SYSTEM_COLOR_GRAY;
	tty.x = 0;
	tty.y = 0;

	tty_clear();
}

void
tty_clear(void)
{
	uint8_t color = tty.foreground_color | tty.background_color << 4;
	for (size_t i = 0; i < TERMINAL_HEIGHT * TERMINAL_WIDTH; ++i)
	{
		tty.mode_addr[i] = ' ' | color << 8;
	}
}

void
tty_putchar(char c)
{
	uint8_t color = tty.foreground_color | tty.background_color << 4;

	if (tty.x >= TERMINAL_WIDTH)	// Defined as 80...
	{
		NEWLINE();
	}
	if (c == 0x0A)					// Newline Character
	{
		NEWLINE();
	}
	else if (c == 0x0D)				// Carriage Return
	{
		CARRIAGE_RETURN();
	}
	else if (c == 0x09)				// Tab Character
	{
		TAB();
	}
	else if (c == 0x08)				// Backspace
	{
		if (tty.x > 14)
		{
			tty.x--;
			tty.mode_addr[tty.y * TERMINAL_WIDTH + tty.x] = ' ' | color << 8;
		}
	}
	else
	{
		tty.mode_addr[tty.y * TERMINAL_WIDTH + tty.x] = c | color << 8;
		tty.x++;
	}
	tty_cursor_update();
	tty_scroll();
}

void
tty_puts(char *string)
{
	for (size_t i = 0; i < strlen(string); ++i)
	{
		tty_putchar(string[i]);
	}
}

void
tty_printf(const char *restrict format, ...)
{
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
					tty_puts(__input);
					i++;
					continue;
				}
				case 'b': {
					uint32_t __input = va_arg(ap, uint32_t);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 2));
					i++;
					continue;
				}
				case 'c': {
					char *__input = va_arg(ap, char *);
					tty_putchar((int)__input);
					i++;
					continue;
				}
				case 'd': {
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'o': {
					long __input = va_arg(ap, long);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 8));
					i++;
					continue;
				}
				case 'x': {
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_lower(result);
					tty_puts(result);
					i++;
					continue;
				}
				case 'X': {
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_upper(result);
					tty_puts(result);
					i++;
					continue;
				}
			};
		}
		else
		{
			tty_putchar(format[i]);
		}
	}
	va_end(ap);
}

void
tty_cursor_enable(uint8_t a, uint8_t b)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | a);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | b);
}

void
tty_cursor_disable(void)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, 0x20);
}

void
tty_cursor_update(void)
{
	uint16_t pos = tty.y * TERMINAL_WIDTH + tty.x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

void
tty_cursor_set_pos(uint8_t x, uint8_t y)
{
	uint16_t pos = y * TERMINAL_WIDTH + x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));

	tty.x = x;
	tty.y = y;
}

uint16_t
tty_cursor_get_pos(void)
{
	uint16_t pos = 0;
	outb(CURSOR_CMD, 0x0F);
	pos |= inb(CURSOR_DATA);
	outb(CURSOR_CMD, 0x0E);
	pos |= ((uint16_t)inb(CURSOR_DATA)) << 8;

	return pos;
}

void
tty_set_background(uint8_t color)
{
	tty.background_color = color;
}

void
tty_set_foreground(uint8_t color)
{
	tty.foreground_color = color;
}

void
tty_set_colors(uint8_t bg, uint8_t fg)
{
	tty_set_background(bg);
	tty_set_foreground(fg);
}

uint8_t
tty_get_background(void)
{
	return tty.background_color;
}

uint8_t
tty_get_foreground(void)
{
	return tty.foreground_color;
}

void
tty_scroll(void)
{
	uint8_t color = tty.foreground_color | tty.background_color << 4;
	if (tty.y >= TERMINAL_HEIGHT)
	{
		for (size_t i = 0; i < (TERMINAL_HEIGHT - 1) * TERMINAL_WIDTH; i++)
		{
			tty.mode_addr[i] = tty.mode_addr[i + TERMINAL_WIDTH];
		}
		for (size_t i = (TERMINAL_HEIGHT - 1) * TERMINAL_WIDTH; i < (TERMINAL_WIDTH * TERMINAL_HEIGHT); ++i)
		{
			tty.mode_addr[i] = color << 8;
		}
		tty.y = TERMINAL_HEIGHT - 1;
	}
}
