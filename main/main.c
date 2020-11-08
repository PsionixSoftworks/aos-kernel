/*
 *  File: main.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

//#include <kernel/kernel.h>
#include <system/terminal.h>
#include <drivers/vga.h>

typedef void(*kernel_t)(void);

kernel_t
kernel_sys_entry(__kernel_void)
{
	terminal_init();
	uint8_t bgcol = terminal_get_background_color();
	uint8_t fgcol = terminal_get_foreground_color();
	if (bgcol != SYSTEM_COLOR_BLUE)
		bgcol = SYSTEM_COLOR_BLUE;
	if (fgcol != SYSTEM_COLOR_WHITE)
		fgcol = SYSTEM_COLOR_WHITE;
	terminal_set_background_color(bgcol);
	terminal_set_foreground_color(fgcol);
	terminal_clear();

	

	return 0x0;
}
