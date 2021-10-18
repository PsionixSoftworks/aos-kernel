/*
 *  File: io.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _SYSTEM_PORTIO_H
#define _SYSTEM_PORTIO_H

// Include files go here:
#include <stdint.h>

/* Write to an 8-bit port */
static inline void
outb(uint16_t port, uint8_t value)
{
	__asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/* Write to a 16-bit port */
static inline void
outw(uint16_t port, uint16_t value)
{
	__asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

/* Write to a 32-bit port */
static inline void
outl(uint16_t port, uint32_t value)
{
	__asm__ volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

/* Read from an 8-bit port */
static inline uint8_t
inb(uint16_t port)
{
	uint8_t value = 0;
	__asm__ volatile ("inb %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

/* Read from a 16-bit port */
static inline uint16_t
inw(uint16_t port) 
{
	uint16_t value = 0;
	__asm__ volatile ("inw %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

/* Read from a 32-bit port */
static inline uint32_t
inl(uint16_t port)
{
	uint32_t value = 0;
	__asm__ volatile ("inl %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

/* Check if IRQ's are enabled (defined in "idt.h") */
#ifndef IRQS_ENABLED

/* Wait on an IO port */
static inline void 
io_wait(void) 
{
	__asm__ volatile ( 	"JMP 1f\n\t" 
						"1:JMP 2f\n\t" 
						"2:" );
}
#else
static inline void
io_wait(void)
{
	__asm__ volatile ( 	"outb %%al, $0x80" : : "a"(0) );
}
#endif	// !IRQS_ENABLED
#endif	// !_ADAMANTINE_IOCTRL_H
