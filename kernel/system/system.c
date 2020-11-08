/*
 *  File: system.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/system/system.h>
#include <kernel/system/io.h>
#include <kernel/drivers/vga.h>
#include <adamantine/adamantine.h>

MODULE("System", "0.01a");

void 
system_enable_cursor(ubyte cursor_start, ubyte cursor_end) 
{
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, (read_portb(0x3D5) & 0xC0) | cursor_start);
	
	write_portb(0x3D4, 0x0B);
	write_portb(0x3D5, (read_portb(0x3D5) & 0xE0) | cursor_end);
}

void 
system_disable_cursor(void) 
{
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, 0x20);
}

void 
system_update_cursor(udword x, udword y) 
{
	uword position = y * VGA_WIDTH + x;
	
	write_portb(0x3D4, 0x0F);
	write_portb(0x3D5, (ubyte)(position & 0xFF));
	write_portb(0x3D4, 0x0E);
	write_portb(0x3D5, (ubyte)((position >> 8) & 0xFF));
}

uword 
system_get_cursor_position(void)
{
	uword position = 0;
	write_portb(0x3D4, 0x0F);
	position |= read_portb(0x3D5);
	write_portb(0x3D4, 0x0E);
	position |= ((uword)read_portb(0x3D5)) << 8;
	return (position);
}
