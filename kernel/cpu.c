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
#include <system/terminal.h>

MODULE("CPU", "0.02a");

EXTERN udword cpuid_supported(void);

static inline udword
ProcessorIndex(void)
{
	udword x = cpuid_supported();
	return (x);
}

static inline void 
CPU_SetActive(void)
{
	__asm__ volatile
	(
		"/* Figure out what to do here... */"
	);

#ifdef CPU_CONFIG
	CPU_ConfigSetup();
	CPU_ConfigName();
	CPU_ConfigGetName();
#endif
}

inline void
cpu_init(void)
{
	bool is_supported = (cpuid_supported() > 0);
	if (!is_supported)
		return;
	//_INFO("CPU is initialized!");
	//terminal_printf("CPU Manufacturer: %s.\n", cpu_vendor_string());
	//system_logf(INFORMATION, "CPU is initialized!\n");
	//system_logf(INFORMATION, "Manufacturer: [%s]\n", cpu_vendor_string());
}

inline void
cpu_halt(void) 
{
	terminal_printf("System halted...\n");
	__asm__ volatile(
		"CLI \n\t"	
		"HLT \n\t"
	);
}

inline void
cpu_suspend(void) 
{
	__asm__ volatile(
		"HLT \n\t"
	);
}

inline udword
cpuid(void)
{
	udword x = cpuid_supported();
	asm volatile
	(
		"MOV $0x0, %EAX\n\t"
		"cpuid\n\t"
	);
	return (x);
}

inline udword 
cpuid_string(udword code, udword *Location) 
{
	__asm__ volatile(
		"cpuid":
		"=a"(*Location), 
		"=b"(*(Location + 0)), 
		"=d"(*(Location + 1)), 
		"=c"(*(Location + 2)):
		"a"(code)
	);
	return ((udword)Location[0]);
}

inline string
cpu_vendor_string(void)
{
	static char Str[16];
	cpuid_string(0x00000000, (udword *)(Str));
	return (Str);
}

inline bool
cpu_check_is_supported(void)
{
	bool result = cpuid_supported();
	if (result == FAILURE){}
		//system_logf(ERROR, "CPUID is not supported on this machine.\n");

	return (result);
}
