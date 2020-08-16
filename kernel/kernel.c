/*
 *  File: kernel.c
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

/* Include the initializer rather than all of the modules. */
#include "../include/init.h"

/* Tell the kernel what module and version we are using. */
MODULE("kernel", "0.04-2a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

/* Locate external references here. */
extern uint32_t kernel_end;
extern uint32_t kernel_base;
extern void video_service_init(void);
extern void disk_service_init(void);

/* Declare the kernel structure. */
Kernel_t kernel;

void __initcall
kernel_init(uint8_t mode)
{
	init_all();
	kernel.running = true;
}

/* Update the kernel. */
void __initcall 
kernel_update(void) 
{
	
}

/* Quit the kernel on shutdown. */
void __initcall kernel_quit(uint8_t status) 
{
	kernel.exit_status = status;
}

/* Check if the kernel is running. */
bool __initcall
kernel_is_running(void) 
{
	return (kernel.running);
}
