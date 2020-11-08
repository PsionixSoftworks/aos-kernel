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

//#include <aos-core.h>
#include <adamantine/adamantine.h>
#include <adamantine/aos-defs.h>
#include <drivers/vga.h>
#include <system/terminal.h>
#include <x86/descriptor-tables.h>

/* Tell the kernel what module and version we are using. */
MODULE("Kernel", "0.04-4a");

/* Run the kernel module */
EXTERN __kernel_void _TEXT
kernel_run(__kernel_void)
{
	//system_log_begin();
	//system_logf(NONE, "%s kernel [Version: %s] is starting up...\n", OS_NAME, OS_VERSION);
	init_descriptor_tables();
	//system_log_end();
}
