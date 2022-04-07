#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#include <drivers/vga.h>
#else
#include <drivers/tty.h>
#endif

#include <system/portio.h>

#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <termios.h>
#include <memory/memory-util.h>
#include <math/math-util.h>

#define TAB_SIZE	5

static uint32_t x, y;
P_TTY tty;
P_VGA vga;

void
tty_setup(void)
{
	vga->init			= k_tty_initialize;
	vga->clear			= k_tty_clear;
	vga->putc			= k_tty_putc;
	vga->puts			= k_tty_puts;
	vga->printf			= k_tty_printf;
	vga->cursor_enable	= k_tty_cursor_enable;
	vga->cursor_disable	= k_tty_cursor_disable;
	vga->cursor_update	= k_tty_cursor_update;
	vga->cursor_set_pos	= k_tty_cursor_set_pos;
	vga->cursor_get_pos	= k_tty_cursor_get_pos;
	vga->set_background	= k_tty_set_background;
	vga->set_foreground = k_tty_set_foreground;
	vga->set_colors		= k_tty_set_colors;
	vga->get_background	= k_tty_get_background;
	vga->get_foreground	= k_tty_get_foreground;
	vga->scroll			= k_tty_scroll;
}

P_VGA
k_tty_get_vgahandle(void)
{
	return (vga);
}

/* Initialize the teletype */
void
k_tty_initialize(uint32_t _mode)
{
	vga->buffer = (uint16_t *)_mode;
	vga->length = 0;

	tty->background_color = SYSTEM_COLOR_BLACK;
	tty->foreground_color = SYSTEM_COLOR_GRAY;
}

/* Clear the screen */
void
k_tty_clear(void)
{
	/* Declare the colors of the terminl */
	uint8_t color = tty->foreground_color | tty->background_color << 4;
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
	{
		vga->buffer[i] = (' ' | (color << 8));			// Set the terminal colors
		tty->pos = 0;
		x = 0;
		y = 0;
	}
}

/* Put a character at the next available position */
void
k_tty_putc(char c)
{
	/* Setup the current color (overrides only the next character attributes on screen) */
	uint8_t color = tty->foreground_color | tty->background_color << 4;

	/* These will likely be removed/updated... */
	if (c == 0x0A)					// Newline Character
	{
		x = 0;
		y++;
		tty->pos = y * VGA_WIDTH + x;
	}
	else if (c == 0x09)				// Tab Character
	{
		tty->pos = (x + TAB_SIZE) - 1;
	}
	else if (c == 0x08)				// Backspace
	{
		if (x > 0)
		{
			x--;
			tty->pos--;
			vga->length--;
			vga->buffer[tty->pos] = ' ' | color << 8;
		}
	}
	else
	{
		vga->buffer[tty->pos] = c | color << 8;
		vga->length++;
		tty->pos++;
		x++;
	}
	k_tty_cursor_update();								// Automatically update the terminal cursor to the teletype x and y positions
	k_tty_scroll();										// Auto scroll the terminal when text reaches end of line
}

/* Print a string */
void
k_tty_puts(char *_string)
{
	/* Get the length of the string to print */
	for (size_t i = 0; i < strlen(_string); ++i)
	{
		/* Print the string one character at a time */
		k_tty_putc(_string[i]);
	}
}

/* Print a formatted string */
void
k_tty_printf(const char *restrict _format, ...)
{
	va_list ap;
	va_start(ap, _format);
	for (size_t i = 0; i < strlen(_format); ++i)
	{
		if (_format[i] == '%')
		{
			switch (_format[i + 1])
			{
				case 's': {								// For strings
					char *__input = va_arg(ap, char *);
					k_tty_puts(__input);
					i++;
					continue;
				}
				case 'b': {								// For binary
					uint32_t __input = va_arg(ap, uint32_t);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 2));
					i++;
					continue;
				}
				case 'c': {								// For char
					char *__input = va_arg(ap, char *);
					k_tty_putc((int)__input);
					i++;
					continue;
				}
				case 'd': {								// For decimal (numbers; only supprts int for now)
					int __input = va_arg(ap, int);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'u': {
					unsigned int __input = va_arg(ap, unsigned int);
					char buffer[256];
					k_tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'o': {								// For octal
					long __input = va_arg(ap, long);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 8));
					i++;
					continue;
				}
				case 'x': {								// For hex (lowecase)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_lower(result);
					k_tty_puts(result);
					i++;
					continue;
				}
				case 'X': {								// For hex (uppercase)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_upper(result);
					k_tty_puts(result);
					i++;
					continue;
				}
			};
		}
		else
		{
			k_tty_putc(_format[i]);
		}
	}
	va_end(ap);
}

/* Print a newline */
void
k_tty_println(void)
{
	k_tty_putc('\n');
}

/* Enable Text Mode Cursor */
void
k_tty_cursor_enable(void)
{
#if defined(CURSOR_TYPE) && (CURSOR_TYPE == 1)
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | 0);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | 15);
#else
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | 14);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | 15);
#endif
}

/* Disable Text Mode Cursor */
void
k_tty_cursor_disable(void)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, 0x20);
}

/* Update the cursor position (internally) */
void
k_tty_cursor_update(void)
{
	uint16_t pos = tty->pos;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

/* Set the cursor position (manually) */
void
k_tty_cursor_set_pos(uint8_t x, uint8_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));

	tty->pos = pos;
}

/* Get the cursor position */
uint16_t
k_tty_cursor_get_pos(void)
{
	uint16_t pos = 0;
	outb(CURSOR_CMD, 0x0F);
	pos |= inb(CURSOR_DATA);
	outb(CURSOR_CMD, 0x0E);
	pos |= ((uint16_t)inb(CURSOR_DATA)) << 8;

	return pos;
}

/* Set the terminal background color */
void
k_tty_set_background(uint8_t _color)
{
	tty->background_color = _color;
}

/* Set the terminal foreground color (text) */
void
k_tty_set_foreground(uint8_t _color)
{
	tty->foreground_color = _color;
}

/* Set background and foreground colors */
void
k_tty_set_colors(uint8_t _bg, uint8_t _fg)
{
	k_tty_set_background(_bg);
	k_tty_set_foreground(_fg);
}

// Get the terminal background color
uint8_t
k_tty_get_background(void)
{
	return tty->background_color;
}

// Get the terminal foreground color (text)
uint8_t
k_tty_get_foreground(void)
{
	return tty->foreground_color;
}

/* Tell the terminal to scroll when it reaches the end of the line */
void
k_tty_scroll(void)
{
	uint8_t color = tty->foreground_color | tty->background_color << 4;
	if (y >= VGA_HEIGHT)
	{
		for (size_t i = 0; i < (VGA_WIDTH - 1) * VGA_HEIGHT; i++)
		{
			vga->buffer[i] = vga->buffer[i + VGA_WIDTH];
		}
		for (size_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); ++i)
		{
			vga->buffer[i] = color << 8;
		}
		y = VGA_HEIGHT - 1;
	}
	tty->pos = y * VGA_WIDTH + x;
}

void
panic(const char *_message, const char *_file, uint32_t _line)
{
	__asm__ volatile ( "cli" );

	k_tty_printf("PANIC(%s) at %s:%d\n", _message, _file, _line);
	for (;;);
}

void
panic_assert(const char *_file, uint32_t _line, const char *_desc)
{
	__asm__ volatile ( "cli" );

	k_tty_printf("ASSERTION-FAILED(%s) at %s: Line %d\n", _desc, _file, _line);
	for (;;);
}

/** Beyond this line is for backwards compatability only. Use for Kernel Version 40 and under */
//#if (KERNEL_VERSION_NUMBER <= 40)
void
tty_initialize(uint32_t _mode)
{
	k_tty_initialize(_mode);
}

void
tty_clear(void)
{
	k_tty_clear();
}

void
tty_putchar(char c)
{
	k_tty_putc(c);
}

void
tty_puts(char *str)
{
	k_tty_puts(str);
}

void
tty_printf(const char *restrict _format, ...)
{
	va_list ap;
	va_start(ap, _format);
	for (size_t i = 0; i < strlen(_format); ++i)
	{
		if (_format[i] == '%')
		{
			switch (_format[i + 1])
			{
				case 's': {								// For strings
					char *__input = va_arg(ap, char *);
					k_tty_puts(__input);
					i++;
					continue;
				}
				case 'b': {								// For binary
					uint32_t __input = va_arg(ap, uint32_t);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 2));
					i++;
					continue;
				}
				case 'c': {								// For char
					char *__input = va_arg(ap, char *);
					k_tty_putc((int)__input);
					i++;
					continue;
				}
				case 'd': {								// For decimal (numbers; only supprts int for now)
					int __input = va_arg(ap, int);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'u': {
					unsigned int __input = va_arg(ap, int);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'o': {								// For octal
					long __input = va_arg(ap, long);
					char buffer[16];
					k_tty_puts(itoa(__input, buffer, 8));
					i++;
					continue;
				}
				case 'x': {								// For hex (lowecase)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_lower(result);
					k_tty_puts(result);
					i++;
					continue;
				}
				case 'X': {								// For hex (uppercase)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_upper(result);
					k_tty_puts(result);
					i++;
					continue;
				}
			};
		}
		else
		{
			k_tty_putc(_format[i]);
		}
	}
	va_end(ap);
}

void
tty_println(void)
{
	k_tty_println();
}

void
tty_cursor_enable(void)
{
	k_tty_cursor_enable();
}

void
tty_cursor_disable(void)
{
	k_tty_cursor_disable();
}

void
tty_cursor_update(void)
{
	k_tty_cursor_update();
}

void
tty_cursor_set_pos(uint8_t x, uint8_t y)
{
	k_tty_cursor_set_pos(x, y);
}

uint16_t
tty_cursor_get_pos(void)
{
	return k_tty_cursor_get_pos();
}

void
tty_set_background(uint8_t color)
{
	k_tty_set_background(color);
}

void
tty_set_foreground(uint8_t color)
{
	k_tty_set_foreground(color);
}

void
tty_set_colors(uint8_t bg, uint8_t fg)
{
	k_tty_set_colors(bg, fg);
}

uint8_t
tty_get_background(void)
{
	return k_tty_get_background();
}

uint8_t
tty_get_foreground(void)
{
	return k_tty_get_foreground();
}
//#endif
