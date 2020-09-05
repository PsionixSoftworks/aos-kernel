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

EXTERN __kernel_udword memory_used;
EXTERN __kernel_udword cpuid_get_property(__kernel_ubyte);

static bool use_startup_password = FALSE;	// Enable/disable logging into system before startup.
static string user_name;					// When enabled, the username of the user.
static string user_pass;					// When enabled, the password of the user (as an encrypted hash).

/* Used when switching to user mode. */
EXTERN __kernel_void
_test_user_function(void)
{
	uint32_t a = 100;
}

static inline void
gather_user_info(void)
{
	system_logf(NONE, "Username: ");
	system_logf(NONE, "Password: ");
}

/* Run the kernel module */
EXTERN __kernel_void _TEXT
kernel_run(__kernel_void)
{
	system_log_begin();

	init_all(KERNEL_MODE_NORMAL);
	system_logf(NONE, "%s kernel [Version: %s] is starting up...\n", OS_NAME, OS_VERSION);
	gdt_init();
	idt_init();
	mm_init(&kernel_end);

	paging_init();
	cpu_check_is_supported();
	cpu_init();

	keyboard_init();
	system_logf(INFORMATION, "Total memory Used: %dKB.\n\n", memory_used);

	system_log_set_fore_col(SYSTEM_COLOR_LT_BLUE);
	system_logf(NONE, "You may type below:\n");
	system_logf(NONE, "~%s >>> ", AOS_ROOT_DIRNAME);
	system_log_reset_fore_col();

	system_log_set_fore_col(SYSTEM_COLOR_YELLOW);
	while (1)
	{
		if (use_startup_password)
		{
			gather_user_info();
		}

		string keystr = keyboard_get_key();
		if (keystr > KEYBOARD_KEY_DOWN_NONE)
		{
			system_log_set_fore_col(SYSTEM_COLOR_YELLOW);
			terminal_printf(keystr);
			if (keyboard_get_key_last() == KEYBOARD_KEY_DOWN_ENTER)
			{
				system_log_set_fore_col(SYSTEM_COLOR_LT_BLUE);
				system_logf(NONE, "~%s >>> ", AOS_ROOT_DIRNAME);
			}
		}
	}
	system_log_reset_fore_col();
	system_log_end();
}
