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
#include "../include/aos-defs.h"

MODULE("input-output", "0.01a");

// Write to the io port :
void 
write_portb(uint16_t port, uint8_t value) 
{
	asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Read from the io port:
uint8_t 
read_portb(uint16_t port) 
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));

	return (ret);
}

uint16_t 
read_portw(uint16_t port) 
{
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));

	return (ret);
}

// Tell the io port to wait:
void 
io_wait(void) 
{
	asm volatile("jmp 1f\n\t" "1:jmp 2f\n\t" "2:");
}
