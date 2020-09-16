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

#define __KERNEL__

#include <kernel/kernel.h>
#include <system/terminal.h>

MODULE("Main", "0.01a");

__kernel_void _TEXT 
kernel_sys_entry(__kernel_void)
{
	kernel_run();
	return;
}
