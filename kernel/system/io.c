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
#include <kernel/system/io.h>

MODULE("Input-Output", "0.01a");

// Write to the io port :
void 
write_portb(uint16_t port, uint8_t value) 
{
	asm volatile("OUTB %0, %1" : : "a"(value), "Nd"(port));
}

void
write_portw(uint16_t port, uint16_t value)
{
	asm volatile("OUTW %0, %1" : : "a"(value), "Nd"(port));
}

void
write_portdw(uint16_t port, uint32_t value)
{
	asm volatile("OUTL %0, %1" : : "a"(value), "Nd"(port));
}

// read from the io port:
uint8_t 
read_portb(uint16_t port)
{
	uint8_t value = 0;
	asm volatile("INB %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

uint16_t 
read_portw(uint16_t port) 
{
	uint16_t value = 0;
	asm volatile("INW %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

uint32_t
read_portdw(uint16_t port)
{
	uint32_t value = 0;
	asm volatile("INL %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

// Tell the io port to wait:
void 
io_wait(void) 
{
	asm volatile("JMP 1f\n\t" "1:JMP 2f\n\t" "2:");
}
