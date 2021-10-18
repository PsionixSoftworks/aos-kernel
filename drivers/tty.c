#include <adamantine/tty.h>
#include <drivers/vga.h>
#include <system/portio.h>

#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <termios.h>

/* Declare static variables */
static const size_t TERMINAL_WIDTH		= 80;			// Weren't these defined
static const size_t TERMINAL_HEIGHT		= 25;			// somewhere else???
static inline void tty_scroll(void);					// The teletype scroll function
static tty_t tty;										// Declare the teletype

/* Define carriage return (CR | 0xD) as a function macro */
#define CARRIAGE_RETURN()	\
{							\
	tty.x=0;				\
}

/* Define newline (NL/LF | 0xA) as a function macro */
#define NEWLINE()			\
{							\
	tty.x=0;				\
	tty.y++;				\
}

/* Define tab (TAB | 0x9) as a function macro */
#define TAB()				\
{							\
	tty.x=(tty.x+5)-1;	\
}

/* Initialize the teletype */
void
tty_init(uint16_t *mode)
{
	tty.mode_addr = (uint16_t *)mode;					// The VGA address to display information to (Text Mode | Graphic Mode)
	tty.background_color = SYSTEM_COLOR_BLACK;			// Default terminal background color
	tty.foreground_color = SYSTEM_COLOR_GRAY;			// Default terminal foreground color
	tty.x = 0;											// Default starting position (x)
	tty.y = 0;											// Default starting position (y)

	tty_clear();										// Clear the screen
}

/* Clear the screen */
void
tty_clear(void)
{
	/* Declare the colors of the terminl */
	uint8_t color = tty.foreground_color | tty.background_color << 4;
	for (size_t i = 0; i < TERMINAL_HEIGHT * TERMINAL_WIDTH; ++i)
	{
		tty.mode_addr[i] = ' ' | color << 8;			// Set the terminal colors
		tty.x = 0;										// Reset the x position of the cursor
		tty.y = 0;										// Reset the y position of the cursor
	}
}

/* Put a character at the next available position */
void
tty_putchar(char c)
{
	/* Setup the current color (overrides only the next character attributes on screen) */
	uint8_t color = tty.foreground_color | tty.background_color << 4;

	/* These will likely be removed/updated... */
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
	tty_cursor_update();								// Automatically update the terminal cursor to the teletype x and y positions
	tty_scroll();										// Auto scroll the terminal when text reaches end of line
}

/* Print a string */
void
tty_puts(char *string)
{
	/* Get the length of the string to print */
	for (size_t i = 0; i < strlen(string); ++i)
	{
		/* Print the string one character at a time */
		tty_putchar(string[i]);
	}
}

/* Print a formatted string */
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
				case 's': {								// For strings
					char *__input = va_arg(ap, char *);
					tty_puts(__input);
					i++;
					continue;
				}
				case 'b': {								// For binary
					uint32_t __input = va_arg(ap, uint32_t);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 2));
					i++;
					continue;
				}
				case 'c': {								// For char
					char *__input = va_arg(ap, char *);
					tty_putchar((int)__input);
					i++;
					continue;
				}
				case 'd': {								// For decimal (numbers; only supprts int for now)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 10));
					i++;
					continue;
				}
				case 'o': {								// For octal
					long __input = va_arg(ap, long);
					char buffer[16];
					tty_puts(itoa(__input, buffer, 8));
					i++;
					continue;
				}
				case 'x': {								// For hex (lowecase)
					unsigned long __input = va_arg(ap, unsigned long);
					char buffer[16];
					char *result = itoa(__input, buffer, 16);
					to_lower(result);
					tty_puts(result);
					i++;
					continue;
				}
				case 'X': {								// For hex (uppercase)
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

/* Print a newline */
void
tty_println(void)
{
	tty_putchar('\n');
}

/* Enable Text Mode Cursor */
void
tty_cursor_enable(uint8_t a, uint8_t b)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | a);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | b);
}

/* Disable Text Mode Cursor */
void
tty_cursor_disable(void)
{
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, 0x20);
}

/* Update the cursor position (internally) */
void
tty_cursor_update(void)
{
	uint16_t pos = tty.y * TERMINAL_WIDTH + tty.x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

/* Set the cursor position (manually) */
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

/* Get the cursor position */
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

/* Set the terminal background color */
void
tty_set_background(uint8_t color)
{
	tty.background_color = color;
}

/* Set the terminal foreground color (text) */
void
tty_set_foreground(uint8_t color)
{
	tty.foreground_color = color;
}

/* Set background and foreground colors */
void
tty_set_colors(uint8_t bg, uint8_t fg)
{
	tty_set_background(bg);
	tty_set_foreground(fg);
}

// Get the terminal background color
uint8_t
tty_get_background(void)
{
	return tty.background_color;
}

// Get the terminal foreground color (text)
uint8_t
tty_get_foreground(void)
{
	return tty.foreground_color;
}

/* Tell the terminal to scroll when it reaches the end of the line */
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

void
panic(const char *message, const char *file, uint32_t line)
{
	__asm__ volatile ( "cli" );

	tty_printf("PANIC(%s) at %s:%d\n", message, file, line);
	for (;;);
}

void
panic_assert(const char *file, uint32_t line, const char *desc)
{
	__asm__ volatile ( "cli" );

	tty_printf("ASSERTION-FAILED(%s) at %s: Line %d\n", desc, file, line);
	for (;;);
}
