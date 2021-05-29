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

#ifndef _ADAMANTINE_IOCTRL_H
#define _ADAMANTINE_IOCTRL_H

// Include files go here:
#include <stdint.h>

static inline void
outb(uint16_t port, uint8_t value)
{
	__asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline void
outw(uint16_t port, uint16_t value)
{
	__asm__ volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

static inline void
outl(uint16_t port, uint32_t value)
{
	__asm__ volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t 
inb(uint16_t port)
{
	uint8_t value = 0;
	__asm__ volatile ("inb %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

static inline uint16_t
inw(uint16_t port) 
{
	uint16_t value = 0;
	__asm__ volatile ("inw %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

static inline uint32_t
inl(uint16_t port)
{
	uint32_t value = 0;
	__asm__ volatile ("inl %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

#ifndef IRQS_ENABLED

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
	__asm__ volatile ( 	"outb %%al, $0x80" : : "a"(0) )
}

#endif

#endif	// !_ADAMANTINE_IOCTRL_H
