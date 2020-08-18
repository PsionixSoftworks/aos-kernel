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

#include "../include/isr.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"

MODULE("interrupt-service-routine", "0.01a");

isr_t interrupt_handlers[256];

string exception_msgs[] = 
{
	"AOS_INTERRUPT Raised! : [Debug Exception]",
	"AOS_INTERRUPT Raised! : [Non-Maskable Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Breakpoint Exception]",
	"AOS_INTERRUPT Raised! : [Into Detected Overflow Exception]",
	"AOS_INTERRUPT Raised! : [Out Of Bounds Exception]",
	"AOS_INTERRUPT Raised! : [Invalid Opcode Exception]",
	"AOS_INTERRUPT Raised! : [No Coprocessor exception]",
	"AOS_INTERRUPT Raised! : [Double Fault Exception]",
	"AOS_INTERRUPT Raised! : [Division By Zero Exception]",
	"AOS_INTERRUPT Raised! : [Coprocessor Segment Overrun Exception]",
	"AOS_INTERRUPT Raised! : [Bad TSS Exception]",
	"AOS_INTERRUPT Raised! : [Segment Not Present Exception]",
	"AOS_INTERRUPT Raised! : [Stack Fault Exception]",
	"AOS_INTERRUPT Raised! : [General Protection Fault Exception]",
	"AOS_INTERRUPT Raised! : [Page Fault Exception]",
	"AOS_INTERRUPT Raised! : [Unknown Interrupt Exception]",
	"AOS_INTERRUPT Raised! : [Coprocessor Fault Exception]",
	"AOS_INTERRUPT Raised! : [Alignment Check Exception]",
	"AOS_INTERRUPT Raised! : [Machine Check Exception]",
};

void fault_handler(struct registers *r) 
{
	if (r->int_no < 32) 
	{
		ERROR(exception_msgs[r->int_no]);
		cpu_halt();
		terminal_print("System halted!");
	}
}

void 
register_interrupt_handler(uint8_t n, isr_t handler) 
{
	interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs) 
{
	if (interrupt_handlers[regs.int_no] != 0) 
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	} 
	else 
	{
		fault_handler(&regs);
	}
}

void 
irq_handler(registers_t regs) 
{
	if (regs.int_no >= 40) 
	{
		write_portb(0xA0, 0x20);
	}
	write_portb(0x20, 0x20);
	
	if (interrupt_handlers[regs.int_no] != 0) 
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}
