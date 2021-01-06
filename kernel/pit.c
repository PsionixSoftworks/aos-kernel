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

#include <kernel/pit.h>
#include <kernel/isr.h>
#include <kernel/system/terminal.h>
#include <kernel/system/io.h>

uint32_t tick;

void 
timer_callback(registers_t *regs) 
{
	tick++;
	terminal_printf("tick: %d\n", tick);
}

void 
pit_init(uint32_t frequency) 
{	
	uint32_t divisor = 1193180 / frequency;
	outb(PIT_CMD_PORT, 0x36);
	outb(PIT_CHANNEL_0, divisor & 0xFF);
	outb(PIT_CHANNEL_0, divisor >> 8);

	register_interrupt_handler(0, timer_callback);
}
