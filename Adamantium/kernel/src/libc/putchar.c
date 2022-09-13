#include <drivers/cursor.h>
#include <drivers/tty.h>
#include <drivers/vga.h>
#include <stdio.h>
#include <stdint.h>

static uint32_t x = 0;
static uint32_t y = 0;

extern struct tty tty;
extern struct vga vga;
extern struct cursor cr;

void
putchar(char c)
{
	uint8_t color = tty.foreground | tty.background << 4;

	if (x >= tty.width)
	{
		vga.length++;
		x = 0;
		y++;
	}
	else if (c == '\n')
	{
		vga.length++;
		x = 0;
		y++;
	}
	else if (c == '\r')
	{
		x = 0;
	}
	else if (c == '\t')
	{
		vga.length += 4;
		x = (x + 5) - 1;
	}
	else if (c == '\b')
	{
		if (x > 0)
		{
			x--;
			vga.buffer[y * VGA_WIDTH + x] = ' ' | color << 8;
			vga.length--;
		}
	}
	else
	{
		vga.buffer[y * VGA_WIDTH + x] = c | color << 8;
		vga.length++;
		x++;
	}
	cursor_set_pos(&cr, x, y);
	cursor_update_pos(&cr);
	tty_scroll();
}
