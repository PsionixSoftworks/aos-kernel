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

MODULE("ProgrammableIntervalTimer", "0.01a");

udword tick;

static void 
timer_callback(registers_t registers) 
{
	tick++;
	terminal_printf("tick: %d\n", tick);
}

void 
pit_init(udword frequency) 
{
	register_interrupt_handler(IRQ0, &timer_callback);
	
	udword divisor = 0x1234DC / frequency;
	write_portb(0x43, 0x36);
	
	ubyte l = (ubyte)(divisor & 0xFF);
	ubyte h = (ubyte)((divisor >> 0x8) & 0xFF);
	
	write_portb(0x40, l);
	write_portb(0x40, h);

	terminal_printf("PIT is initialized!");
}
