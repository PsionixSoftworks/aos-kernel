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

#ifndef _AOS_IO_H
#define _AOS_IO_H

// Include files go here:
#include <stdint.h>

static inline void
outb(uint16_t port, uint8_t value)
{
	__asm__ __volatile__("OUTB %0, %1" : : "a"(value), "Nd"(port));
}

static inline void
outw(uint16_t port, uint16_t value)
{
	__asm__ __volatile__("OUTW %0, %1" : : "a"(value), "Nd"(port));
}

static inline void
outl(uint16_t port, uint32_t value)
{
	__asm__ __volatile__("OUTL %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t 
inb(uint16_t port)
{
	uint8_t value = 0;
	__asm__ __volatile__("INB %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

static inline uint16_t
inw(uint16_t port) 
{
	uint16_t value = 0;
	__asm__ __volatile__("INW %1, %0" : "=a" (value) : "dN" (port));

	return (value);
}

static inline uint32_t
inl(uint16_t port)
{
	uint32_t value = 0;
	__asm__ __volatile__("INL %1, %0" : "=a"(value) : "dN"(port));

	return (value);
}

static inline void 
io_wait(void) 
{
	__asm__ __volatile__("JMP 1f\n\t" "1:JMP 2f\n\t" "2:");
}

#endif	// !_AOS_IO_H
