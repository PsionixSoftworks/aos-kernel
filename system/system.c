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

#include "../include/system.h"
#include "../include/io.h"
#include "../include/adamantine.h"
#include "../include/vga.h"
#include "../include/aos-defs.h"

MODULE("system", "0.01a");

void 
enable_cursor(uint8_t cursor_start, uint8_t cursor_end) 
{
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, (read_portb(0x3D5) & 0xC0) | cursor_start);
	
	write_portb(0x3D4, 0x0B);
	write_portb(0x3D5, (read_portb(0x3D5) & 0xE0) | cursor_end);
}

void 
disable_cursor() 
{
	write_portb(0x3D4, 0x0A);
	write_portb(0x3D5, 0x20);
}

void 
update_cursor(uint32_t x, uint32_t y) 
{
	uint16_t pos = y * VGA_WIDTH + x;
	
	write_portb(0x3D4, 0x0F);
	write_portb(0x3D5, (uint8_t)(pos & 0xFF));
	write_portb(0x3D4, 0x0E);
	write_portb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

uint16_t 
get_cursor_position(void) 
{
	uint16_t pos = 0;
	write_portb(0x3D4, 0x0F);
	pos |= read_portb(0x3D5);
	write_portb(0x3D4, 0x0E);
	pos |= ((uint16_t)read_portb(0x3D5)) << 8;
	return (pos);
}
