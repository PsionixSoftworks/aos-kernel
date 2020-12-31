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

#include <adamantine/adamantine.h>

isr_t interrupt_handlers[256];

char *exception_messages[] =
{
	"AOS_INTERRUPT Raised! : [Division By Zero Exception]",
	"AOS_INTERRUPT Raised! : [Single-Step Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Non-Maskable Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Breakpoint Exception]",
	"AOS_INTERRUPT Raised! : [Detected Overflow Exception]",
	"AOS_INTERRUPT Raised! : [Out Of Bounds Exception]",
	"AOS_INTERRUPT Raised! : [Invalid Opcode Exception]",
	"AOS_INTERRUPT Raised! : [No Available Coprocessor Exception]",
	"AOS_INTERRUPT Raised! : [Double Fault Exception]",
	"AOS_INTERRUPT Raised! : [Coprocessor Segment Overrun Exception]",
	"AOS_INTERRUPT Raised! : [Invalid TSS Exception]",
	"AOS_INTERRUPT Raised! : [Segment Not Present Exception]",
	"AOS_INTERRUPT Raised! : [Stack Fault Exception]",
	"AOS_INTERRUPT Raised! : [General Protection Fault Exception]",
	"AOS_INTERRUPT Raised! : [Page Fault Exception]",
	"AOS_INTERRUPT Raised! : [Reserved Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Math Fault Exception]",
	"AOS_INTERRUPT Raised! : [Alignment Check Exception]",
	"AOS_INTERRUPT Raised! : [Machine Check Exception]",
	"AOS_INTERRUPT Raised! : [SIMD Floating-Point Exception]",
	"AOS_INTERRUPT Raised! : [Virtualization Exception]",
	"AOS_INTERRUPT Raised! : [Control Protection Exception]",
};

DEPRECATED void
fault_handler(registers_t registers) 
{
	if (registers.INT_NO < 32) 
	{
		terminal_printf("%s, INT_NO: 0x%X.\n", exception_messages[registers.INT_NO], registers.INT_NO);
		if (registers.ERR_CODE)
		{
			terminal_printf("ERROR_CODE: 0x%X.\n");
			cpu_halt();
		}
	}
}

void 
register_interrupt_handler(uint8_t n, isr_t handler) 
{
	interrupt_handlers[n] = handler;
}

void
isr_handler(registers_t registers)
{
	if (interrupt_handlers[registers.INT_NO] != 0)
	{
		isr_t handler = interrupt_handlers[registers.INT_NO];
		handler(registers);
	}
	else
	{
		fault_handler(registers);
	}
}

void 
irq_handler(registers_t registers) 
{
	if (registers.INT_NO >= 40) 
	{
		write_portb(0xA0, 0x20);
	}
	write_portb(0x20, 0x20);	/* EOI */
	
	if (interrupt_handlers[registers.INT_NO] != 0) 
	{
		isr_t handler = interrupt_handlers[registers.INT_NO];
		handler(registers);
	}
}
