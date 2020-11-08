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
#include <kernel/system/terminal.h>
#include <kernel/drivers/vga.h>
#include <kernel/x86/descriptor-tables.h>

typedef void(*kernel_t)(void);

static void
start_modules(void)
{
	init_descriptor_tables();
}

kernel_t
kernel_sys_entry(__kernel_void)
{
	terminal_init();
	uint8_t bgcol = terminal_get_background_color();
	uint8_t fgcol = terminal_get_foreground_color();
	if (bgcol != DEFAULT_BACKGROUND_COLOR)
		bgcol = DEFAULT_BACKGROUND_COLOR;
	if (fgcol != DEFAULT_FOREGROUND_COLOR)
		fgcol = DEFAULT_FOREGROUND_COLOR;
	terminal_set_background_color(bgcol);
	terminal_set_foreground_color(fgcol);
	terminal_clear();	

	terminal_printf("== Adamantine OS - Version 0.1a ==\n");
	terminal_printf("Starting modules...\n");

	init_descriptor_tables();

	return 0x0;
}
