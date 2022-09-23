#include <drivers/device.h>
#include <drivers/cursor.h>
#include <drivers/tty.h>
#include <drivers/vga.h>
#include <compiler.h>
#include <stdio.h>

static enum vga_color default_background = SYSTEM_COLOR_BLACK;
static enum vga_color default_foreground = SYSTEM_COLOR_GRAY;
struct cursor cr;
struct device tty_device;
struct tty tty;
struct vga vga;

uint8_t tty_init(uint16_t *mode __unused)
{
	if (device_init(&tty_device, "TTY Module", DT_TTY, IOT_ASYNC) == DEVICE_SUCCESS)
	{
		if (tty_device.port == (uint16_t*)VGA_ADDRESS)
			vga.buffer = device_get_address(&tty_device);
		vga.length = 0;

		cursor_init(&cr);
		cursor_enable(&cr);

		tty.background = default_background;
		tty.foreground = default_foreground;
		tty.width = VGA_WIDTH;
		tty.height = VGA_HEIGHT;

		tty_clear();

		return DEVICE_SUCCESS;
	}
	return DEVICE_FAILURE;
}

void tty_clear(void)
{
	uint8_t color = tty.foreground | tty.background << 4;
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		vga.buffer[i] = ' ' | color << 8;
		cursor_set_pos(&cr, 0, 0);
	}
	cursor_update_pos(&cr);
}

void tty_set_background(uint8_t background)
{
	tty.background = background;
}

void tty_set_foreground(uint8_t foreground)
{
	tty.foreground = foreground;
}

void tty_set_colors(uint8_t background, uint8_t foreground)
{
	tty.background = background;
	tty.foreground = foreground;
}

uint8_t
tty_get_background(void)
{
	return tty.background;
}

uint8_t
tty_get_foreground(void)
{
	return tty.foreground;
}

void tty_scroll(void)
{
	uint8_t color = tty.foreground | tty.background << 4;
	if (cr.y >= VGA_HEIGHT)
	{
		for (size_t i = 0; i < (VGA_WIDTH - 1) * VGA_WIDTH; i++)
		{
			vga.buffer[i] = vga.buffer[i + VGA_WIDTH];
		}
		for (size_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); ++i)
		{
			vga.buffer[i] = color << 8;
		}
		cr.y = VGA_HEIGHT - 1;
	}
}
