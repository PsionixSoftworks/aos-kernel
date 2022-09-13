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
#include <macros.h>

#define outb(_port, _value)		__outb(_port, _value)
#define outw(_port, _value)		__outw(_port, _value)
#define outl(_port, _value)		__outl(_port, _value)
#define inb(_port)				__inb(_port)
#define inw(_port)				__inw(_port)
#define inl(_port)				__inl(_port)
#define io_wait(void)			__io_wait()

__GLOBAL KERNEL_API void 		__outb(uint16_t _port, uint8_t _value);
__GLOBAL KERNEL_API void 		__outw(uint16_t _port, uint16_t _value);
__GLOBAL KERNEL_API void 		__outl(uint16_t _port, uint32_t _value);
__GLOBAL KERNEL_API uint8_t 	__inb(uint16_t _port);
__GLOBAL KERNEL_API uint16_t 	__inw(uint16_t _port);
__GLOBAL KERNEL_API uint32_t 	__inl(uint16_t _port);
__GLOBAL KERNEL_API void 		__io_wait(void);

#endif	// !_ADAMANTINE_IOCTRL_H
