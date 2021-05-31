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
#include <kernel/irq.h>
#include <kernel/cpu.h>
#include <adamantine/tty.h>
#include <kernel/system/ioctrl.h>

/* Number of ticks since startup */
uint32_t tick = 0;

/* The timer callback function */
static void
timer_callback(registers_t regs)
{
	/* Make sure we're not getting an error code */
	if (!regs.err_code)
	{
		/* Prints the ticks (debug only!) */
		//tty_printf("Ticks: %d\n", tick++);
	}
}

/* Initialize the Programmable Interval Timer */
void
pit_init(uint32_t freq)
{
	cpu_set_interrupts();								// Make sure interrupts are enabled (won't work otherwise)
	register_interrupt_handler(IRQ0, &timer_callback);	// Assign IRQ0 to the PIT callback function
	uint32_t divisor = PIT_BASE_FREQ / freq;			// Set the PIT divisor
	outb(PIT_CMD_PORT, 0x36);							// TODO: Figure this out...

	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

	outb(PIT_CHANNEL_0, l);
	outb(PIT_CHANNEL_0, h);

	tty_puts("[INFO]: PIT is initialized!\n");
}
