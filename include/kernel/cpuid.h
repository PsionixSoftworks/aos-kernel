/*
 *  File: cpuid.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_CPUID_H
#define _AOS_CPUID_H

#include <stdint.h>

enum cpuid_requests 
{
	CPUID_GET_VENDOR_STRING,
	CPUID_GET_FEATURES,
	CPUID_GET_TLB,
	CPUID_GET_SERIAL,
	
	CPUID_INTEL_EXTENDED=0x80000000,
	CPUID_INTEL_FEATURES,
	CPUID_INTEL_BRAND_STRING,
	CPUID_INTEL_BRAND_STRING_MORE,
	CPUID_INTEL_BRAND_STRING_END
};

enum cpuid_features 
{
	CPUID_FEAT_ECX_SSE3			= 1 << 0,
	CPUID_FEAT_ECX_PLCMUL		= 1 << 1,
	CPUID_FEAT_ECX_DTES64		= 1 << 2,
	CPUID_FEAT_ECX_MONITOR      = 1 << 3,
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,
    CPUID_FEAT_ECX_VMX          = 1 << 5,
    CPUID_FEAT_ECX_SMX          = 1 << 6,
    CPUID_FEAT_ECX_EST          = 1 << 7,
    CPUID_FEAT_ECX_TM2          = 1 << 8,
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13,
    CPUID_FEAT_ECX_ETPRD        = 1 << 14,
    CPUID_FEAT_ECX_PDCM         = 1 << 15,
    CPUID_FEAT_ECX_PCIDE        = 1 << 17,
    CPUID_FEAT_ECX_DCA          = 1 << 18,
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19,
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20,
    CPUID_FEAT_ECX_x2APIC       = 1 << 21,
    CPUID_FEAT_ECX_MOVBE        = 1 << 22,
    CPUID_FEAT_ECX_POPCNT       = 1 << 23,
    CPUID_FEAT_ECX_AES          = 1 << 25,
    CPUID_FEAT_ECX_XSAVE        = 1 << 26,
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27,
    CPUID_FEAT_ECX_AVX          = 1 << 28,

    CPUID_FEAT_EDX_FPU          = 1 << 0,
    CPUID_FEAT_EDX_VME          = 1 << 1,
    CPUID_FEAT_EDX_DE           = 1 << 2,
    CPUID_FEAT_EDX_PSE          = 1 << 3,
    CPUID_FEAT_EDX_TSC          = 1 << 4,
    CPUID_FEAT_EDX_MSR          = 1 << 5,
    CPUID_FEAT_EDX_PAE          = 1 << 6,
    CPUID_FEAT_EDX_MCE          = 1 << 7,
    CPUID_FEAT_EDX_CX8          = 1 << 8,
    CPUID_FEAT_EDX_APIC         = 1 << 9,
    CPUID_FEAT_EDX_SEP          = 1 << 11,
    CPUID_FEAT_EDX_MTRR         = 1 << 12,
    CPUID_FEAT_EDX_PGE          = 1 << 13,
    CPUID_FEAT_EDX_MCA          = 1 << 14,
    CPUID_FEAT_EDX_CMOV         = 1 << 15,
    CPUID_FEAT_EDX_PAT          = 1 << 16,
    CPUID_FEAT_EDX_PSE36        = 1 << 17,
    CPUID_FEAT_EDX_PSN          = 1 << 18,
    CPUID_FEAT_EDX_CLF          = 1 << 19,
    CPUID_FEAT_EDX_DTES         = 1 << 21,
    CPUID_FEAT_EDX_ACPI         = 1 << 22,
    CPUID_FEAT_EDX_MMX          = 1 << 23,
    CPUID_FEAT_EDX_FXSR         = 1 << 24,
    CPUID_FEAT_EDX_SSE          = 1 << 25,
    CPUID_FEAT_EDX_SSE2         = 1 << 26,
    CPUID_FEAT_EDX_SS           = 1 << 27,
    CPUID_FEAT_EDX_HTT          = 1 << 28,
    CPUID_FEAT_EDX_TM1          = 1 << 29,
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};

#define CPUID_VENDOR_OLD_AMD		"AMDisbetter!"
#define CPUID_VENDOR_AMD			"AuthenticAMD"
#define CPUID_VENDOR_INTEL			"GenuineIntel"
#define CPUID_VENDOR_HAULS			"CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA	"TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA		"GenuineTMx86"
#define CPUID_VENDOR_CYRIX			"CyrixInstead"
#define CPUID_VENDOR_CENTAUR		"CentaurHauls"
#define CPUID_VENDOR_NEXGEN			"NexGenDriven"
#define CPUID_VENDOR_UMC			"UMC UMC UMC "
#define CPUID_VENDOR_SIS			"SiS SiS SiS "
#define CPUID_VENDOR_NSC			"Geode by NSC"
#define CPUID_VENDOR_RISE			"RiseRiseRise"
#define CPUID_VENDOR_VORTEX 		"Vortex86 SoC"
#define CPUID_VENDOR_VIA			"VIA VIA VIA "

uint32_t cpuid(void);
uint32_t cpuid_string(uint32_t code, uint32_t *Location);
char * cpuid_is_supported(void);

#endif  // !_AOS_CPUID_H
