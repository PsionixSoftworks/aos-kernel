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
#include "../include/init.h"

#if defined(ADAMANTINE_OS_READY)
#include "../AdamantineOS/Include/Adamantine.h"
using namespace PsionixSoftworks;
#endif

/* Tell the kernel what module and version we are using. */
MODULE("kernel", "0.04-2a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

/* Locate external references here. */
extern "C" uint32_t kernel_end;
extern "C" uint32_t kernel_base;
extern "C" void video_service_init(void);
extern "C" void disk_service_init(void);

/* Declare the kernel structure. */
Kernel_t kernel;
extern "C" AdamantineOS AOS;

extern "C" void __initcall
kernel_init(uint8_t mode)
{
	init_all();

	/* After in user mode. */
	AOS.SystemStartup();
	kernel.running = true;
}

/* Update the kernel. */
extern "C" void __initcall 
kernel_update(void) 
{
	
}

/* Quit the kernel on shutdown. */
extern "C" void __initcall kernel_quit(uint8_t status) 
{
	kernel.exit_status = status;
}

/* Check if the kernel is running. */
extern "C" bool __initcall
kernel_is_running(void) 
{
	return (kernel.running);
}
