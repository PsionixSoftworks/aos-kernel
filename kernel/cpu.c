/*
 *  File: cpu.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/cpu.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"

MODULE("cpu", "0.01a");

static inline uint32_t processor_index(void)
{
	return (0x00);
}

static inline void cpu_set_active(void)
{
	asm volatile
	(
		"/* Figure out what to do here... */"
	);

#ifdef CPU_CONFIG
__cpu_config_setup();
__cpu_config_name();
__cpu_config_get_name();
#endif
}

void _TEXT
cpu_halt(void) 
{
	terminal_print("System halted...\n");
	__asm__ __volatile__("cli \n\t"	"hlt \n\t");
}

void _TEXT
cpu_suspend(void) 
{
	__asm__ __volatile__("hlt \n\t");
}

int _TEXT
cpuid(void)
{
	asm volatile
	(
		"mov $0x0, %eax\n\t"
		"cpuid\n\t"
	);
	return (0);
}
