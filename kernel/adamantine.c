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

#define _

#include <adamantine/adamantine.h>

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
	init_descriptor_tables();
	pit_init(50);
	mm_init((uint32_t)&kernel_end);
	initialize_paging();
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
}

static inline kernel_t
kernel_start(void)
{
	start_modules();
}

static inline kernel_t
kernel_stop(void)
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

extern uint32_t get_num(int);

typedef struct file FILE;

kernel_t
kernel_sys_entry(unsigned int *MultiBootHeaderStruct)
{
	/* Initialize the kernel */
	aos_init();

	/* Call kernel_setup & kernel_start */
	aos.kernel_setup();
	aos.kernel_start();

	terminal_printf("Done! Preparing for next phase...\n\n");
	
	struct filesystem *vfs;
	char *filename = "test.txt";
	vfs_init(&vfs);
	terminal_printf("Creating a new file called \"%s\".\n", filename);
	FILE *f = vfs_file_open(filename, FS_WRITE);
	vfs_file_write(&f, "Testing123");
	vfs_file_close(&f);
	
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
