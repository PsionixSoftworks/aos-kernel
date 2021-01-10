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
#include <kernel/cpu.h>
#include <kernel/system/terminal.h>
#include <kernel/system/io.h>

uint32_t tick = 0;

static void
timer_callback(registers_t regs)
{
	//terminal_printf("Ticks: %d\n", tick);
	if (tick == 100)
		terminal_printf("PIT reached 100!\n");
	tick++;
}

void
pit_init(uint32_t freq)
{
	terminal_printf("[INFO]: PIT is initialized!\n");
	cpu_set_interrupts();
	register_interrupt_handler(IRQ0, &timer_callback);
	uint32_t divisor = 1193180 / freq;
	outb(PIT_CMD_PORT, 0x36);

	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

	outb(PIT_CHANNEL_0, l);
	outb(PIT_CHANNEL_0, h);
}
