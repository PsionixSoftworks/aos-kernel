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
#include <kernel/system/terminal.h>
#include <stdbool.h>

extern uint32_t cpuid_supported(void);
extern uint32_t cpuid_get_property(uint32_t);

static void cpu_check_features(void);

void
cpu_init(void)
{
	bool is_supported = (cpuid_supported() > 0);
	if (!is_supported)
		return;
	terminal_printf("[INFO]: CPU is initialized!\n");
	terminal_printf("[INFO]: CPU Manufacturer: %s.\n", cpu_vendor_string());

	cpu_check_features();
}

inline void
cpu_halt(void) 
{
	terminal_printf("System halted...\n");
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
		terminal_printf("[ERROR]: CPUID is not supported!\n");
	return (result);
}

static void
cpu_check_features(void)
{
	if (!cpuid_get_property(CPUID_FEAT_ECX_SSE3))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_SSE3 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_PLCMUL))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_PLCMUL is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_DTES64))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_DTES64 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_MONITOR))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_MONITOR is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_DS_CPL))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_DS_CPL is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_VMX))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_VMX is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_SMX))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_SMX is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_EST))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_EST is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_TM2))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_TM2 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_SSSE3))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_SSSE3 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_CID))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_CID is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_FMA))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_FMA is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_CX16))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_CX16 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_ETPRD))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_ETPRD is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_PDCM))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_PDCM is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_PCIDE))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_PCIDE is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_DCA))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_DCA is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_SSE4_1))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_SSE4_1 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_SSE4_2))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_SSE4_2 is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_x2APIC))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_x2APIC is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_MOVBE))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_MOVBE is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_POPCNT))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_POPCNT is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_AES))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_AES is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_XSAVE))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_XSAVE is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_OSXSAVE))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_OSXSAVE is not supported...\n");
	if (!cpuid_get_property(CPUID_FEAT_ECX_AVX))
		terminal_printf("[WARNING]: CPUID_FEAT_ECX_AVX is not supported...\n");	
}
