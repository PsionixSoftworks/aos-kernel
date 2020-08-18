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

MODULE("CPU", "0.01a");

static inline UDWORD 
ProcessorIndex(void)
{
	return (0x00);
}

static inline VOID 
CPU_SetActive(VOID)
{
	asm volatile
	(
		"/* Figure out what to do here... */"
	);

#ifdef CPU_CONFIG
CPU_ConfigSetup();
CPU_ConfigName();
CPU_ConfigGetName();
#endif
}

VOID _TEXT
CPU_Halt(void) 
{
	TerminalPrint("System halted...\n");
	__asm__ __volatile__("CLI \n\t"	"HLT \n\t");
}

VOID _TEXT
CPU_Suspend(void) 
{
	__asm__ __volatile__("HLT \n\t");
}

UDWORD _TEXT
CPUID(VOID)
{
	asm volatile
	(
		"MOV $0x0, %EAX\n\t"
		"CPUID\n\t"
	);
	return (0);
}
