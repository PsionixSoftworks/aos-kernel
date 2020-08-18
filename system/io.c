/*
 *  File: io.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

// Includes go here:
#include "../include/io.h"

MODULE("Input-Output", "0.01a");

// Write to the io port :
VOID 
WritePortB(UWORD Port, UBYTE Value) 
{
	asm volatile("OUTB %0, %1" : : "a"(Value), "Nd"(Port));
}

VOID
WritePortW(UWORD Port, UWORD Value)
{
	asm volatile("OUTW %0, %1" : : "a"(Value), "Nd"(Port));
}

VOID
WritePortDW(UWORD Port, UDWORD Value)
{
	asm volatile("OUTL %0, %1" : : "a"(Value), "Nd"(Port));
}

// Read from the io port:
UBYTE 
ReadPortB(UWORD Port)
{
	UBYTE Value = 0;
	asm volatile("INB %1, %0" : "=a"(Value) : "dN"(Port));

	return (Value);
}

UWORD 
ReadPortW(UWORD Port) 
{
	UWORD Value = 0;
	asm volatile("INW %1, %0" : "=a" (Value) : "dN" (Port));

	return (Value);
}

UDWORD
ReadPortDW(UWORD Port)
{
	UDWORD Value = 0;
	asm volatile("INL %1, %0" : "=a"(Value) : "dN"(Port));

	return (Value);
}

// Tell the io port to wait:
VOID 
IO_Wait(VOID) 
{
	asm volatile("JMP 1f\n\t" "1:JMP 2f\n\t" "2:");
}
