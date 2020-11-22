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

#include <adamantine/aos-core.h>
#include <kernel/drivers/keyboard.h>

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

static inline __kernel_void
start_modules(__kernel_void)
{
	init_descriptor_tables();
	pit_init(50);
	mm_init((uint32_t)&kernel_end);
	initialize_paging();
}

static inline __kernel_void
stop_modules(__kernel_void)
{
	return;
}

static inline kernel_t
kernel_setup(__kernel_void)
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
}

static inline kernel_t
kernel_start(__kernel_void)
{
	start_modules();
}

static inline kernel_t
kernel_stop(__kernel_void)
{
	stop_modules();
}

static aos_base_t aos;

static inline void
aos_init(void)
{
	aos.kernel_setup = &kernel_setup;
	aos.kernel_start = &kernel_start;
	aos.kernel_stop = &kernel_stop;
}

#include <kernel/system/io.h>

kernel_t __sys_entry
kernel_sys_entry(__kernel_void)
{
	/* Initialize the kernel */
	aos_init();

	/* Call kernel_setup & kernel_start */
	aos.kernel_setup();
	aos.kernel_start();
	
	terminal_printf("Done! Preparing for next phase...\n\n");
	
	aos.kernel_stop();

	return;
}

static inline void
write_aos_message(void)
{
	for (size_t i = 0; i < 16; ++i)
	{
		terminal_printf(msg[i], OS_VERSION_STRING);
	}
}
