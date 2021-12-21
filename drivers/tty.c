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

/* Declare static variables */
static const size_t TERMINAL_WIDTH		= 80;			// Weren't these defined
static const size_t TERMINAL_HEIGHT		= 25;			// somewhere else???
static inline void tty_scroll(void);					// The teletype scroll function
static struct s_tty tty;										// Declare the teletype

/* Define carriage return (CR | 0xD) as a function macro */
#define CR	tty.tty_cursor_x=0;

/* Define newline (NL/LF | 0xA) as a function macro */
#define NL	tty.tty_cursor_x=0;	\
			tty.tty_cursor_y++;

/* Define tab (TAB | 0x9) as a function macro */
#define TAB	tty.tty_cursor_x=(tty.tty_cursor_x+5)-1;

/* Initialize the teletype */
void
k_tty_initialize(uint16_t *_mode)
{
	tty.mode_addr = (uint16_t *)_mode;				// The VGA address to display information to (Text Mode | Graphic Mode)
	tty.tty_backcol = SYSTEM_COLOR_BLACK;			// Default terminal background color
	tty.tty_forecol = SYSTEM_COLOR_GRAY;			// Default terminal foreground color
	tty.tty_cursor_x = 0;							// Default starting position (x)
	tty.tty_cursor_y = 0;							// Default starting position (y)

	tty_clear();									// Clear the screen
}

/* Clear the screen */
void
k_tty_clear(void)
{
	/* Declare the colors of the terminl */
	uint8_t color = tty.tty_forecol | tty.tty_backcol << 4;
	for (size_t i = 0; i < TTY_DISPLAY_WIDTH * TTY_DISPLAY_HEIGHT; ++i)
	{
		tty.mode_addr[i] = ' ' | color << 8;			// Set the terminal colors
		tty.tty_cursor_x = 0;							// Reset the x position of the cursor
		tty.tty_cursor_y = 0;							// Reset the y position of the cursor
	}
}

/* Put a character at the next available position */
void
k_tty_putc(char c)
{
	/* Setup the current color (overrides only the next character attributes on screen) */
	uint8_t color = tty.tty_forecol | tty.tty_backcol << 4;

	/* These will likely be removed/updated... */
	if (tty.tty_cursor_x >= TTY_DISPLAY_WIDTH)	// Defined as 80...
	{
		NL;
	}
	if (c == 0x0A)					// Newline Character
	{
		NL;
	}
	else if (c == 0x0D)				// Carriage Return
	{
		CR;
	}
	else if (c == 0x09)				// Tab Character
	{
		TAB;
	}
	else if (c == 0x08)				// Backspace
	{
		if (tty.tty_cursor_x > 14)
		{
			tty.tty_cursor_x--;
			tty.mode_addr[tty.tty_cursor_y * TTY_DISPLAY_WIDTH + tty.tty_cursor_x] = ' ' | color << 8;
		}
	}
	else
	{
		tty.mode_addr[tty.tty_cursor_y * TTY_DISPLAY_WIDTH + tty.tty_cursor_x] = c | color << 8;
		tty.tty_cursor_x++;
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
		tty_putchar(_string[i]);
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
					unsigned long __input = va_arg(ap, unsigned long);
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

/* Print a newline */
void
k_tty_println(void)
{
	tty_putchar('\n');
}

/* Enable Text Mode Cursor */
void
k_tty_cursor_enable(uint8_t a, uint8_t b)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | a);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | b);
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
	uint16_t pos = tty.tty_cursor_y * TTY_DISPLAY_WIDTH + tty.tty_cursor_x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

/* Set the cursor position (manually) */
void
k_tty_cursor_set_pos(uint8_t x, uint8_t y)
{
	uint16_t pos = y * TTY_DISPLAY_WIDTH + x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));

	tty.tty_cursor_x = x;
	tty.tty_cursor_y = y;
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
	tty.tty_backcol = _color;
}

/* Set the terminal foreground color (text) */
void
k_tty_set_foreground(uint8_t _color)
{
	tty.tty_forecol = _color;
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
	return tty.tty_backcol;
}

// Get the terminal foreground color (text)
uint8_t
k_tty_get_foreground(void)
{
	return tty.tty_forecol;
}

/* Tell the terminal to scroll when it reaches the end of the line */
void
k_tty_scroll(void)
{
	uint8_t color = tty.tty_forecol | tty.tty_backcol << 4;
	if (tty.tty_cursor_y >= TERMINAL_HEIGHT)
	{
		for (size_t i = 0; i < (TTY_DISPLAY_WIDTH - 1) * TTY_DISPLAY_WIDTH; i++)
		{
			tty.mode_addr[i] = tty.mode_addr[i + TTY_DISPLAY_WIDTH];
		}
		for (size_t i = (TTY_DISPLAY_HEIGHT - 1) * TTY_DISPLAY_WIDTH; i < (TTY_DISPLAY_WIDTH * TTY_DISPLAY_HEIGHT); ++i)
		{
			tty.mode_addr[i] = color << 8;
		}
		tty.tty_cursor_y = TTY_DISPLAY_HEIGHT - 1;
	}
}

void
panic(const char *_message, const char *_file, uint32_t _line)
{
	__asm__ volatile ( "cli" );

	tty_printf("PANIC(%s) at %s:%d\n", _message, _file, _line);
	for (;;);
}

void
panic_assert(const char *_file, uint32_t _line, const char *_desc)
{
	__asm__ volatile ( "cli" );

	tty_printf("ASSERTION-FAILED(%s) at %s: Line %d\n", _desc, _file, _line);
	for (;;);
}

/** Beyond this line is for backwards compatability only. Use for Kernel Version 40 and under */
void
tty_initialize(uint16_t *mode)
{
	k_tty_initialize(mode);
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
					unsigned long __input = va_arg(ap, unsigned long);
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
tty_cursor_enable(uint8_t start, uint8_t end)
{
	k_tty_cursor_enable(start, end);
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
