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

uint32_t tick;

static void 
timer_callback(registers_t regs) 
{
	tick++;
	terminal_printf("tick: %d\n", tick);

}

void 
pit_init(uint32_t frequency) 
{
	register_interrupt_handler(IRQ0, &timer_callback);
	
	uint32_t divisor = 0x1234DC / frequency;
	write_portb(0x43, 0x36);
	
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 0x8) & 0xFF);
	
	write_portb(0x40, l);
	write_portb(0x40, h);

	terminal_printf("PIT is initialized!\n");
}
