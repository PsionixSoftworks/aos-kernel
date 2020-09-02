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
#include "../include/cpuid.h"
#include "../include/terminal.h"

MODULE("CPU", "0.02a");

EXTERN int cpuid_supported(void);

static inline udword
ProcessorIndex(VOID)
{
	int x = cpuid_supported();
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
CPU_Init(void)
{
	bool is_supported = (cpuid_supported() > 0);
	if (!is_supported)
		return;
	INFO("CPU is initialized!");
	TerminalPrintf("CPU Manufacturer: %s.\n", CPU_VendorString());
}

inline void
CPU_Halt(void) 
{
	TerminalPrint("System halted...\n");
	__asm__ volatile(
		"CLI \n\t"	
		"HLT \n\t"
	);
}

inline void
CPU_Suspend(void) 
{
	__asm__ volatile(
		"HLT \n\t"
	);
}

inline udword
CPUID(void)
{
	int x = cpuid_supported();
	asm volatile
	(
		"MOV $0x0, %EAX\n\t"
		"CPUID\n\t"
	);
	return (x);
}

inline udword 
CPUID_String(udword Code, udword *Location) 
{
	__asm__ volatile(
		"cpuid":
		"=a"(*Location), 
		"=b"(*(Location + 0)), 
		"=d"(*(Location + 1)), 
		"=c"(*(Location + 2)):
		"a"(Code)
	);
	return ((int)Location[0]);
}

inline string
CPU_VendorString(void)
{
	static char Str[16];
	CPUID_String(0x00000000, (udword *)(Str));
	return (Str);
}

inline udword
CPU_CheckIsSupported(void)
{
	return (cpuid_supported());
}
