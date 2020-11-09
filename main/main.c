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
#include <kernel/pit.h>
#include <kernel/memory/paging.h>
#include <kernel/memory/mm.h>

extern uint32_t kernel_end;
typedef void(*kernel_t)(void);

/*
static void
do_page_fault(void)
{
	uint32_t *ptr = (uint32_t *)0xA0000000;
	uint32_t page_fault = *ptr;
}
*/

static void
start_modules(void)
{
	init_descriptor_tables();
	pit_init(50);
	mm_init((uint32_t)&kernel_end);
	initialize_paging();
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

	start_modules();

	terminal_printf("Done! Preparing for next phase...\n\n");

	return 0x0;
}
