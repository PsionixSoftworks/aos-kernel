/*
 *  File: idt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/idt.h"
#include "../include/terminal.h"
#include "../include/io.h"
#include "../include/mem-util.h"
#include "../include/pic.h"

MODULE("InterruptDescriptorTable", "0.01a");

IDT_Entry_t IDT_Entries[256];
PIDT_t PIDT;

static VOID
IDT_SetGate(UBYTE Number, UDWORD Base, UWORD Selector, UBYTE Flags) 
{
	IDT_Entries[Number].BaseLo = Base & 0xFFFF;
    IDT_Entries[Number].BaseHi = (Base >> 16) & 0xFFFF;
	
	IDT_Entries[Number].Selector = Selector;
	IDT_Entries[Number].AlwaysZero = 0;
	
	IDT_Entries[Number].Flags = Flags | 0x60;
}

VOID
IDT_Init(VOID)
{
	PIDT.Limit = sizeof(IDT_Entry_t) * 0x100 - 0x1;
	PIDT.Base = (UDWORD)&IDT_Entries;
	
	MemSet(&IDT_Entries, 0, sizeof(IDT_Entry_t) * 0x100);
	
    PIC_Remap();
	
	IDT_SetGate( 0, (UDWORD)ISR_0, 0x08, 0x8E);
    IDT_SetGate( 1, (UDWORD)ISR_1, 0x08, 0x8E);
    IDT_SetGate( 2, (UDWORD)ISR_2, 0x08, 0x8E);
    IDT_SetGate( 3, (UDWORD)ISR_3, 0x08, 0x8E);
    IDT_SetGate( 4, (UDWORD)ISR_4, 0x08, 0x8E);
    IDT_SetGate( 5, (UDWORD)ISR_5, 0x08, 0x8E);
    IDT_SetGate( 6, (UDWORD)ISR_6, 0x08, 0x8E);
    IDT_SetGate( 7, (UDWORD)ISR_7, 0x08, 0x8E);
    IDT_SetGate( 8, (UDWORD)ISR_8, 0x08, 0x8E);
    IDT_SetGate( 9, (UDWORD)ISR_9, 0x08, 0x8E);
    IDT_SetGate(10, (UDWORD)ISR_10, 0x08, 0x8E);
    IDT_SetGate(11, (UDWORD)ISR_11, 0x08, 0x8E);
    IDT_SetGate(12, (UDWORD)ISR_12, 0x08, 0x8E);
    IDT_SetGate(13, (UDWORD)ISR_13, 0x08, 0x8E);
    IDT_SetGate(14, (UDWORD)ISR_14, 0x08, 0x8E);
    IDT_SetGate(15, (UDWORD)ISR_15, 0x08, 0x8E);
    IDT_SetGate(16, (UDWORD)ISR_16, 0x08, 0x8E);
    IDT_SetGate(17, (UDWORD)ISR_17, 0x08, 0x8E);
    IDT_SetGate(18, (UDWORD)ISR_18, 0x08, 0x8E);
    IDT_SetGate(19, (UDWORD)ISR_19, 0x08, 0x8E);
    IDT_SetGate(20, (UDWORD)ISR_20, 0x08, 0x8E);
    IDT_SetGate(21, (UDWORD)ISR_21, 0x08, 0x8E);
    IDT_SetGate(22, (UDWORD)ISR_22, 0x08, 0x8E);
    IDT_SetGate(23, (UDWORD)ISR_23, 0x08, 0x8E);
    IDT_SetGate(24, (UDWORD)ISR_24, 0x08, 0x8E);
    IDT_SetGate(25, (UDWORD)ISR_25, 0x08, 0x8E);
    IDT_SetGate(26, (UDWORD)ISR_26, 0x08, 0x8E);
    IDT_SetGate(27, (UDWORD)ISR_27, 0x08, 0x8E);
    IDT_SetGate(28, (UDWORD)ISR_28, 0x08, 0x8E);
    IDT_SetGate(29, (UDWORD)ISR_29, 0x08, 0x8E);
    IDT_SetGate(30, (UDWORD)ISR_30, 0x08, 0x8E);
    IDT_SetGate(31, (UDWORD)ISR_31, 0x08, 0x8E);
	
    IDT_SetGate(32, (UDWORD)IRQ_0, 0x08, 0x8E);
    IDT_SetGate(33, (UDWORD)IRQ_1, 0x08, 0x8E);
    IDT_SetGate(34, (UDWORD)IRQ_2, 0x08, 0x8E);
    IDT_SetGate(35, (UDWORD)IRQ_3, 0x08, 0x8E);
    IDT_SetGate(36, (UDWORD)IRQ_4, 0x08, 0x8E);
    IDT_SetGate(37, (UDWORD)IRQ_5, 0x08, 0x8E);
    IDT_SetGate(38, (UDWORD)IRQ_6, 0x08, 0x8E);
    IDT_SetGate(39, (UDWORD)IRQ_7, 0x08, 0x8E);
    IDT_SetGate(40, (UDWORD)IRQ_8, 0x08, 0x8E);
    IDT_SetGate(41, (UDWORD)IRQ_9, 0x08, 0x8E);
    IDT_SetGate(42, (UDWORD)IRQ_10, 0x08, 0x8E);
    IDT_SetGate(43, (UDWORD)IRQ_11, 0x08, 0x8E);
    IDT_SetGate(44, (UDWORD)IRQ_12, 0x08, 0x8E);
    IDT_SetGate(45, (UDWORD)IRQ_13, 0x08, 0x8E);
    IDT_SetGate(46, (UDWORD)IRQ_14, 0x08, 0x8E);
    IDT_SetGate(47, (UDWORD)IRQ_15, 0x08, 0x8E);
	
	IDT_Load((UDWORD)&PIDT);

    INFO("IDT is initialized!");
}

VOID
IDT_Free(VOID) 
{
    Free(IDT_Entries);
}
