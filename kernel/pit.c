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
#include <system/portio.h>

/* Number of ticks since startup */
uint32_t tick = 0;

static void
play_sound(uint32_t nfreq)
{
	uint32_t div;
	uint8_t tmp;

	div = PIT_BASE_FREQ / nfreq;
	outb(0x43, 0xB6);
	outb(0x42, (uint8_t)div);
	outb(0x42, (uint8_t)(div >> 8));

	tmp = inb(0x61);
	if (tmp != (tmp | 3))
	{
		outb(0x61, tmp | 3);
	}
}

void
pit_beep_start(uint32_t freq)
{
	play_sound(freq);
}

void
pit_beep_stop(void)
{
	uint8_t tmp = inb(0x61) & 0xFC;
	outb(0x61, tmp);
}

/* The timer callback function */
static void
timer_callback(registers_t regs)
{
	/* Make sure we're not getting an error code */
	if (!regs.err_code)
	{
		// Useful for timed interrupts...
	}
}

/* Initialize the Programmable Interval Timer */
void
pit_initialize(uint32_t freq)
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
