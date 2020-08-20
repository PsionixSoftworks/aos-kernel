/*
 *  File: gdt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/gdt.h"
#include "../include/terminal.h"
#include "../include/mem-util.h"

MODULE("GlobalDescriptorTable", "0.01a");

EXTERN VOID GDT_Flush(UDWORD);

GDT_Entry_t GDT_Entries[5];
PGDT_t PGDT;

static VOID GDT_SetGate(DWORD, UDWORD, UDWORD, UBYTE, UBYTE);

VOID 
GDT_Init(VOID) 
{
	PGDT.Limit = (sizeof(GDT_Entry_t) * 5) - 1;	// Learn to understand this...
	PGDT.Base = (UDWORD)&GDT_Entries;
	
	GDT_SetGate(0, 0, 0, 0, 0);
	GDT_SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	GDT_SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	GDT_SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	GDT_SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	GDT_Flush((UDWORD)&PGDT);

	INFO("GDT is initialized!");
}

static VOID 
GDT_SetGate(DWORD Number, UDWORD Base, UDWORD Limit, UBYTE Access, UBYTE Granularity) 
{
	GDT_Entries[Number].BaseLo 		= (Base & 0xFFFF);
	GDT_Entries[Number].BaseMiddle	= (Base >> 16) & 0xFF;
	GDT_Entries[Number].BaseHi		= (Base >> 24) & 0xFF;
	
	GDT_Entries[Number].LimitLo		= (Limit & 0xFFFF);
	GDT_Entries[Number].Granularity	= (Limit >> 16) & 0x0F;
	
	GDT_Entries[Number].Granularity	|= Granularity & 0xF0;
	GDT_Entries[Number].Access		= Access;
}
