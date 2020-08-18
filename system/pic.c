/*
 *  File: pic.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/pic.h"
#include "../include/irq.h"
#include "../include/io.h"

MODULE("ProgrammableInterruptController", "0.01a");

VOID 
PIC_SendEOI(UBYTE IRQ) 
{
	if (IRQ >= 0x8) 
	{
		WritePortB(PIC2_COMMAND, PIC_EOI);
	}
	WritePortB(PIC1_COMMAND, PIC_EOI);
}

VOID 
PIC_Remap(VOID) 
{
	WritePortB(0x20, 0x11);
	WritePortB(0xA0, 0x11);
	WritePortB(0x21, 0x20);
	WritePortB(0xA1, 0x28);
	WritePortB(0x21, 0x04);
	WritePortB(0xA1, 0x02);
	WritePortB(0x21, 0x01);
	WritePortB(0xA1, 0x01);
	WritePortB(0x21, 0x0);
	WritePortB(0xA1, 0x0);
}

VOID 
IRQ_SetMask(UBYTE IRQ_Line) 
{
	UWORD Port;
	UBYTE Value;
	
	if (IRQ_Line < 0x8) 
	{
		Port = PIC1_DATA;
	} 
	else 
	{
		Port = PIC2_DATA;
		IRQ_Line -= 0x8;
	}
	Value = ReadPortB(Port) | (1 << IRQ_Line);
	WritePortB(Port, Value);
}

VOID 
IRQ_ClearMask(UBYTE IRQ_Line) 
{
	UWORD Port;
	UBYTE Value;
	
	if (IRQ_Line < 0x8) 
	{
		Port = PIC1_DATA;
	} 
	else 
	{
		Port = PIC2_DATA;
		IRQ_Line -= 0x8;
	}
	Value = ReadPortB(Port) | ~(1 << IRQ_Line);
	WritePortB(Port, Value);
}

UWORD
PIC_GetIRR(VOID) 
{
	return (PIC_GetIRQRegister(PIC_READ_IRR));
}

UWORD
PIC_GetISR(VOID) 
{
	return (PIC_GetIRQRegister(PIC_READ_ISR));
}

UWORD PIC_GetIRQRegister(DWORD OCW3) 
{
	WritePortB(PIC1_COMMAND, OCW3);
	WritePortB(PIC2_COMMAND, OCW3);
	
	return ((ReadPortB(PIC2_COMMAND) << 0x8) | ReadPortB(PIC1_COMMAND));
}
