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

#include "../include/main.h"
#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"

MODULE("main", "0.01a");

void _TEXT 
kmain(void) 
{
	KernelInstall(OS_NAME);
	uint32_t status = Verify();
	if (status == SUCCESS)
	{
		kernel_init(0);
		while (kernel_is_running())
		{
			kernel_update();
		}
		kernel_quit(0x0);
	} else {
		ERROR("Unable to start. Invalid OS...");
		kernel_quit(0x1);
	}
}
