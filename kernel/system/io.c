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

// Write to the io port :
void 
outb(uint16_t port, uint8_t value) 
{
	__asm__ __volatile__("OUTB %0, %1" : : "a"(value), "Nd"(port));
}

void
outw(uint16_t port, uint16_t value)
{
	__asm__ __volatile__("OUTW %0, %1" : : "a"(value), "Nd"(port));
}

void
outl(uint16_t port, uint32_t value)
{
	__asm__ __volatile__("OUTL %0, %1" : : "a"(value), "Nd"(port));
}

// read from the io port:
uint8_t 
inb(uint16_t port)
{
	uint8_t value = 0;
	__asm__ __volatile__("INB %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

uint16_t 
inw(uint16_t port) 
{
	uint16_t value = 0;
	__asm__ __volatile__("INW %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

uint32_t
inl(uint16_t port)
{
	uint32_t value = 0;
	__asm__ __volatile__("INL %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

// Tell the io port to wait:
void 
io_wait(void) 
{
	__asm__ __volatile__("JMP 1f\n\t" "1:JMP 2f\n\t" "2:");
}
