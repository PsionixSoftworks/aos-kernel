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

/* Include the initializer rather than all of the modules. */
/*
#include "../include/kernel.h"
#include "../include/x86/gdt.h"
#include "../include/x86/idt.h"
#include "../include/paging.h"
#include "../include/mem-util.h"
#include "../include/math/math-util.h"
#include "../include/string.h"
#include "../include/io.h"
#include "../include/task.h"
#include "../include/tss.h"
#include "../include/pit.h"

#include "../include/device.h"

#include "../include/keyboard.h"
#include "../include/keys.h"

#include "../include/aos-fs.h"

#include "../include/cpu.h"
*/

#define __KERNEL__

#include "../include/aos-core.h"

/* Tell the kernel what module and version we are using. */
MODULE("Kernel", "0.04-4a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

#if defined(ADAMANTINE_OS_READY)
#include "../../AdamantineOS Desktop/include/adamantine.h"
using namespace PsionixSoftworks;
#endif

EXTERN __kernel_udword kernel_end;

static inline __kernel_string cpu_supported_names[] =
{
    /* Intel */
    "Pentium Pro",
	"Pentium II",
	"Pentium II Xeon"
	"Pentium III",
	"Pentium III Xeon"
	"Pentium M",
	"Celeron",
	"Celeron M",
	"Intel Core Duo",
	"Intel Core Solo",
	"Pentium 4",
	"Core i3",
	"Core i5",
	"Core i7",

    /* AMD */
	
};

EXTERN __kernel_udword memoryUsed;

EXTERN __kernel_void
_test_user_function(void)
{
	uint32_t a = 100;
}

system_t system;

EXTERN __kernel_void _TEXT
kernel_run(__kernel_void)
{
	system_log_begin();
	system_logf(NONE, "Testing%d...\n", 123);
	system_log_end();
	/*init_all(KERNEL_MODE_NORMAL);
	terminal_printf("%s kernel [Version: %s] is starting up...\n", OS_NAME, OS_VERSION);
	INFO("Starting kernel modules...");
	gdt_init();
	idt_init();
	mm_init(&kernel_end);

	paging_init();
	if (cpu_check_is_supported() == FAILURE)
		asm("INT $0x12");
	cpu_init();

	keyboard_init();
	terminal_printf("Total memory Used: %dKB.\n", memoryUsed);
	terminal_println();

	terminal_printf("Done! Switching %s to user_mode (hopefully)...\n", OS_NAME);
	
	//tss_init();
	tss_user_mode_switch();
	/* Perform a syscall to terminal_printf if successful. */

	/*
	terminal_printf("You may type below:\n");
	terminal_printf("~%s >>> ", AOS_ROOT_DIRNAME);

	while (1)
	{
		string keystr = keyboard_get_key();
		if (keystr > KEYBOARD_KEY_DOWN_NONE)
		{
			terminal_printf(keystr);
			if (keyboard_get_key_last() == KEYBOARD_KEY_DOWN_ENTER)
			{
				terminal_printf("~%s >>> ", AOS_ROOT_DIRNAME);
			}
			if (keyboard_get_key_last() == KEYBOARD_KEY_DOWN_ESCAPE)
			{
				/* Trigger reset... *
				//write_portb(0x0CF9, 0x04);
			}
		}
	}
	*/
}
