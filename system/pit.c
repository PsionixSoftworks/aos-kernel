/*
 *  File: pit.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/pit.h"
#include "../include/isr.h"
#include "../include/terminal.h"
#include "../include/io.h"

MODULE("ProgrammableIntervalTimer", "0.01a");

UDWORD Tick;

static VOID 
TimerCallback(Registers_t Register) 
{
	Tick++;
	TerminalPrintf("Tick: %d\n", Tick);
}

VOID 
TimerInit(UDWORD Frequency) 
{
	RegisterInterruptHandler(IRQ0, &TimerCallback);
	
	UDWORD Divisor = 0x1234DC / Frequency;
	WritePortB(0x43, 0x36);
	
	UBYTE l = (UBYTE)(Divisor & 0xFF);
	UBYTE h = (UBYTE)((Divisor >> 0x8) & 0xFF);
	
	WritePortB(0x40, l);
	WritePortB(0x40, h);
}
