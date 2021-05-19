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

#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <adamantine/aos-defs.h>
#include <adamantine/tty.h>
#include <stdbool.h>

extern uint32_t cpuid_supported(void);
extern uint32_t cpuid_get_property(uint32_t);

void
cpu_init(void)
{
	bool is_supported = (cpuid_supported() > 0);
	if (!is_supported)
		return;
	tty_puts("[INFO]: CPU is initialized!\n");
	tty_puts("[INFO]: CPU Manufacturer: ");
	tty_puts(cpu_vendor_string());
	tty_puts("\n");
}

inline void
cpu_halt(void) 
{
	tty_puts("System halted...\n");
	asm volatile(
		"cli\n\t"	
		"hlt\n\t"
	);
}

inline void
cpu_suspend(void) 
{
	asm volatile(
		"hlt\n\t"
	);
}

/* Sets the interrupt flag (IF) to 0. */
void
cpu_clear_interrupts(void)
{
	asm volatile
	(
		"cli\n\t"
	);
}

/* Sets the interrupt flag (IF) to 1. */
void
cpu_set_interrupts(void)
{
	asm volatile
	(
		"sti\n\t"
	);
}

inline uint32_t
cpuid(void)
{
	uint32_t x = cpuid_supported();
	asm volatile
	(
		"mov $0x0, %eax\n\t"
		"cpuid\n\t"
	);
	return (x);
}

inline uint32_t 
cpuid_string(uint32_t code, uint32_t *Location) 
{
	__asm__ volatile(
		"cpuid":
		"=a"(*Location), 
		"=b"(*(Location + 0)), 
		"=d"(*(Location + 1)), 
		"=c"(*(Location + 2)):
		"a"(code)
	);
	return ((uint32_t)Location[0]);
}

inline char *
cpu_vendor_string(void)
{
	static char Str[16];
	cpuid_string(0x00000000, (uint32_t *)(Str));
	return (Str);
}

inline bool
cpu_check_is_supported(void)
{
	bool result = cpuid_supported();
	if (result == false)
		tty_puts("[ERROR]: CPUID is not supported!\n");
	return (result);
}
