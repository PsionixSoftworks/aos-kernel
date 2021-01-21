#include <kernel/system/cursor.h>
#include <kernel/system/io.h>
#include <kernel/drivers/vga.h>

void
cursor_enable(uint8_t start, uint8_t end)
{
	const uint8_t start_address = inb(0x3D5);
	outb(0x3D4, 0x0A);
	outb(0x3D5, (start_address & 0xC0) | start);

	const uint8_t end_address = inb(0x3D5);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (end_address & 0xE0) | end);
}

void
cursor_disable(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void
cursor_update(uint32_t x, uint32_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));

	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

uint16_t
cursor_get_pos(void)
{
	uint16_t pos = 0;

	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);

	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;

	return (pos);
}
