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
#include <system/io.h>

MODULE("Input-Output", "0.01a");

// Write to the io port :
void 
write_portb(uword port, ubyte value) 
{
	asm volatile("OUTB %0, %1" : : "a"(value), "Nd"(port));
}

void
write_portw(uword port, uword value)
{
	asm volatile("OUTW %0, %1" : : "a"(value), "Nd"(port));
}

void
write_portdw(uword port, udword value)
{
	asm volatile("OUTL %0, %1" : : "a"(value), "Nd"(port));
}

// read from the io port:
ubyte 
read_portb(uword port)
{
	ubyte value = 0;
	asm volatile("INB %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

uword 
read_portw(uword port) 
{
	uword value = 0;
	asm volatile("INW %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

udword
read_portdw(uword port)
{
	udword value = 0;
	asm volatile("INL %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

// Tell the io port to wait:
void 
io_wait(void) 
{
	asm volatile("JMP 1f\n\t" "1:JMP 2f\n\t" "2:");
}
