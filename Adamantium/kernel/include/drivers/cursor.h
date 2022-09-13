#ifndef _DRIVERS_CURSOR_H
#define _DRIVERS_CURSOR_H

#include <system/portio.h>
#include <drivers/vga.h>
#include <adamantium/aos-bool.h>
#include <stdint.h>

/* Macros for the Text Mode cursor */
#define CURSOR_CMD		0x03D4										// Cursor Command
#define CURSOR_DATA		0x03D5										// Cursor Data

/* Define macros for the Text Mode cusror */
#if defined(CURSOR_TYPE) && (CURSOR_TYPE == CR_TYPE_UNDER)			// This will make a block cursor, all others will be an underline (for now).
#define CURSOR_START	0xE											// Top=14
#define CURSOR_END		0xF											// Bottom=15
#else
#define CURSOR_START	0x0											// Top=0
#define CURSOR_END		0xF											// Bottom=15
#endif

enum cursor_type
{
	CR_TYPE_BLOCK,
	CR_TYPE_UNDER,
};

struct cursor
{
	uint32_t x;
	uint32_t y;
	uint8_t start;
	uint8_t end;
};

static int __initialized = false;

static inline void
cursor_init(struct cursor* cursor)
{
	cursor->x 		= 0;
	cursor->y 		= 0;
	cursor->start 	= CURSOR_START;
	cursor->end		= CURSOR_END;
	__initialized	= true;
}

static inline void
cursor_enable(struct cursor* cursor)
{
	if (__initialized)
	{
		outb(CURSOR_CMD, 0x0A);
		outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | cursor->start);

		outb(CURSOR_CMD, 0x0B);
		outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | cursor->end);
	}
}

static inline void
cursor_disable(void)
{
	outb(CURSOR_CMD,  0x0A);
	outb(CURSOR_DATA, 0x20);
}

static inline void
cursor_set_pos(struct cursor* cursor, int x, int y)
{
	cursor->x = x;
	cursor->y = y;
}

static inline void
cursor_update_pos(struct cursor* cursor)
{
	uint16_t pos = cursor->y * VGA_WIDTH + cursor->x;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

static inline uint16_t
cursor_get_pos(void)
{
	uint16_t pos = 0;
	outb(CURSOR_CMD, 0x0F);
	pos |= inb(CURSOR_DATA);
	outb(CURSOR_CMD, 0x0E);
	pos |= ((uint16_t)inb(CURSOR_DATA)) << 8;

	return pos;
}

#endif
