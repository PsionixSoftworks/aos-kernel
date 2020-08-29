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

MODULE("CPU", "0.01a");

EXTERN int cpuid_supported(void);

static inline UDWORD 
ProcessorIndex(VOID)
{
	int x = cpuid_supported();
	return (x);
}

static inline VOID 
CPU_SetActive(VOID)
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

inline VOID
CPU_Init(VOID)
{
	BOOL is_supported = (cpuid_supported() > 0);
	if (!is_supported)
		return;
	INFO("CPU is initialized!");
	TerminalPrintf("CPU Manufacturer: %s.\n", CPU_VendorString());
}

inline VOID
CPU_Halt(void) 
{
	TerminalPrint("System halted...\n");
	__asm__ volatile("CLI \n\t"	"HLT \n\t");
}

inline VOID
CPU_Suspend(void) 
{
	__asm__ volatile("HLT \n\t");
}

inline UDWORD
CPUID(VOID)
{
	int x = cpuid_supported();
	asm volatile
	(
		"MOV $0x0, %EAX\n\t"
		"CPUID\n\t"
	);
	return (x);
}

inline UDWORD 
CPUID_String(UDWORD Code, UDWORD *Location) 
{
	__asm__ volatile("cpuid":"=a"(*Location), "=b"(*(Location + 0)), "=d"(*(Location + 1)), "=c"(*(Location + 2)):"a"(Code));
	return ((int)Location[0]);
}

inline STRING
CPU_VendorString(VOID)
{
	static CHAR Str[16];
	CPUID_String(0x00000000, (UDWORD *)(Str));
	return (Str);
}

inline UDWORD
CPU_CheckIsSupported(VOID)
{
	return (cpuid_supported());
}
