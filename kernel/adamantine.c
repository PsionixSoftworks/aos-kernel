/*
 *  File: kernel.c
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

#include <adamantine/adamantine.h>
#include <kernel/system/terminal.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/memory/mm.h>
#include <kernel/memory/paging.h>
#include <kernel/drivers/keyboard.h>

#include <filesys/vfs.h>
#include <assert.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>

extern uint32_t kernel_end;

static inline void write_aos_message(void);
static char *msg[] = {
	"              AAAAAAAAAAAAA      OOOOOOOOOOOO              SSSSSSSSSSSSSS     \n",
	"             AAAAAAAAAAAAAA    OOOOOOOOOOOOOOOO         SSSSSSSSSSSSSSSSSSSS  \n",
	"            AAAA    AAAA      OOOO          OOOO      SSSSSSSS        SSSSSSSS\n",
	"           AAAA     AAAA     OOOO            OOOO     SSSSSS              SSSS\n",
	"          AAAA      AAAA     OOOO            OOOO     SSSS                SSSS\n",
	"         AAAA       AAAA     OOOO            OOOO     SSSSSS                  \n",
	"        AAAA        AAAA     OOOO            OOOO       SSSSSSSSSSSSSSSS      \n",
	"       AAAAAAAAAAAAAAAAA     OOOO            OOOO           SSSSSSSSSSSSSS    \n",
	"      AAAAAAAAAAAAAAAAAA     OOOO            OOOO               SSSSSSSSSSSS  \n",
	"     AAAA           AAAA     OOOO            OOOO     SSSS                SSSS\n",
	"    AAAA           AAAA      OOOO            OOOO     SSSS                SSSS\n",
	"   AAAA            AAAA      OOOO            OOOO     SSSS              SSSSSS\n",
	"  AAAA             AAAA       OOOO          OOOO      SSSSSSSS        SSSSSSSS\n",
	"AAAAAAAA         AAAAAAAAA     OOOOOOOOOOOOOOOO         SSSSSSSSSSSSSSSSSSSS  \n",
	"AAAAAAAA         AAAAAAAAA       OOOOOOOOOOOO              SSSSSSSSSSSSSS     \n\n",

	"=============================[Version: v%s]==============================\n",
};

static inline void
start_modules(void)
{
	
	//mm_init((uint32_t)&kernel_end);
	//initialize_paging();
}

static inline void
stop_modules(void)
{
	return;
}

static inline kernel_t
kernel_setup(void)
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

	write_aos_message();

	return (SUCCESS);
}

static inline kernel_t
kernel_start(void)
{
	start_modules();
	return (SUCCESS);
}

static inline kernel_t
kernel_stop(void)
{
	stop_modules();
	return (SUCCESS);
}

static aos_base_t aos;

static inline void
aos_init(void)
{
	aos.kernel_setup = &kernel_setup;
	aos.kernel_start = &kernel_start;
	aos.kernel_stop = &kernel_stop;
}

void
kernel_sys_entry(void)
{
	terminal_init();
	terminal_clear();
	
	init_descriptor_tables();
	cpu_init();

	cpu_set_interrupts();
	pit_init(50);
}

static inline void
write_aos_message(void)
{
	for (size_t i = 0; i < 16; ++i)
	{
		terminal_printf(msg[i], OS_VERSION_STRING);
	}
}
