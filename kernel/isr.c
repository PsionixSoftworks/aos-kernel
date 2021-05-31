/*
 *  File: isr.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/isr.h>
#include <adamantine/aos-defs.h>
#include <adamantine/tty.h>
#include <kernel/system/ioctrl.h>
#include <kernel/cpu.h>
#include <kernel/pic.h>

/* Define the exception message array */
char *exception_messages[MAX_INTERRUPTS] =
{
	"AOS_INTERRUPT Raised! : [Division By Zero Exception]",				// int $0x00
	"AOS_INTERRUPT Raised! : [Single-Step Interrupt Exception]",		// int $0x01
	"AOS_INTERRUPT Raised! : [Non-Maskable Interrupt Exception]",		// int $0x02
	"AOS_INTERRUPT Raised! : [Breakpoint Exception]",					// int $0x03
	"AOS_INTERRUPT Raised! : [Detected Overflow Exception]",			// int $0x04
	"AOS_INTERRUPT Raised! : [Out Of Bounds Exception]",				// int $0x05
	"AOS_INTERRUPT Raised! : [Invalid Opcode Exception]",				// int $0x06
	"AOS_INTERRUPT Raised! : [No Available Coprocessor Exception]",		// int $0x07
	"AOS_INTERRUPT Raised! : [Double Fault Exception]",					// int $0x08
	"AOS_INTERRUPT Raised! : [Coprocessor Segment Overrun Exception]",	// int $0x09
	"AOS_INTERRUPT Raised! : [Invalid TSS Exception]",					// int $0x0A
	"AOS_INTERRUPT Raised! : [Segment Not Present Exception]",			// int $0x0B
	"AOS_INTERRUPT Raised! : [Stack Fault Exception]",					// int $0x0C
	"AOS_INTERRUPT Raised! : [General Protection Fault Exception]",		// int $0x0D
	"AOS_INTERRUPT Raised! : [Page Fault Exception]",					// int $0x0E
	"AOS_INTERRUPT Raised! : [Reserved Interrupt Exception]",			// int $0x0F
	"AOS_INTERRUPT Raised! : [Math Fault Exception]",					// int $0x10
	"AOS_INTERRUPT Raised! : [Alignment Check Exception]",				// int $0x11
	"AOS_INTERRUPT Raised! : [Machine Check Exception]",				// int $0x12
	"AOS_INTERRUPT Raised! : [SIMD Floating-Point Exception]",			// int $0x13
	"AOS_INTERRUPT Raised! : [Virtualization Exception]",				// int $0x14
	"AOS_INTERRUPT Raised! : [Control Protection Exception]",			// int $0x15
};

/* Declare the interrupt handlers */
isr_t interrupt_handlers[256];

/* Handle fault/exception messages */
static void
fault_handler(registers_t regs)
{
	/* Make sure it's within the bounds of the ISR's (0-31) */
	if (regs.int_no < 32)
	{
		tty_printf("%s, int_no: 0x%X.\n", exception_messages[regs.int_no], regs.int_no);

		/* Check if the exception is an errcode */
		if (regs.err_code)
		{
			/* If so, tell us */
			tty_printf("ERROR_CODE: 0x%X.\n");
			cpu_halt();
		}
		return;
	}
}

/* Register interrupts with callback functions */
void
register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

/* Handle Interrupt Service Routine's (called in interrupt.asm) */
void
isr_handler(registers_t regs)
{
	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
	else
	{
		fault_handler(regs);
	}
}

/* Handle Interrupt Requests (called in interrupt.asm) */
void 
irq_handler(registers_t regs) 
{
	if (interrupt_handlers[regs.int_no] != 0) 
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}

	/* Replace the old way of doing it */
	pic_send_eoi(regs.int_no);
}
