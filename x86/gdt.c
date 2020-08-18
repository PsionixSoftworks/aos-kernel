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
#include "../include/tss.h"
#include "../include/terminal.h"
#include "../include/mem-util.h"

MODULE("GlobalDescriptorTable", "0.01a");

EXTERN SET_VOID(GDT_Flush(UDWORD));
EXTERN SET_VOID(TSS_Flush(VOID));

static SET_VOID(WriteTSS(DWORD Number, UWORD SS0, UDWORD ESP0));

GDT_Entry_t GDT_Entries[6];
PGDT_t PGDT;
TSS_t TSS_Entry;

SET_VOID(GDT_SetGate(DWORD, UDWORD, UDWORD, UBYTE, UBYTE));

VOID 
GDT_Init(VOID) 
{
	PGDT.Limit = (sizeof(GDT_Entry_t) * 6) - 1;	// Learn to understand this...
	PGDT.Base = (UDWORD)&GDT_Entries;
	
	GDT_SetGate(0, 0, 0, 0, 0);
	GDT_SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	GDT_SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	GDT_SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	GDT_SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	WriteTSS(5, 0x10, 0x0);

	GDT_Flush((UDWORD)&PGDT);
	TSS_Flush();

	INFO("GDT is initialized!");
}

static VOID 
WriteTSS(DWORD Number, UWORD SS0, UDWORD ESP0)
{
	UDWORD Base = (UDWORD)&TSS_Entry;
	UDWORD Limit = Base + sizeof(TSS_Entry);

	GDT_SetGate(Number, Base, Limit, 0x89, 0x40);

	TSS_Entry.SS0 = SS0;
	TSS_Entry.ESP0 = ESP0;

	TSS_Entry.CS = 0x0B;
	TSS_Entry.SS = TSS_Entry.DS = TSS_Entry.ES = TSS_Entry.FS = TSS_Entry.GS = 0x13;
}

VOID 
SetKernelStack(UDWORD Stack)
{
	TSS_Entry.ESP0 = Stack;
}

VOID 
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
