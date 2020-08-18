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

MODULE("interrupt-service-routine", "0.01a");

ISR_t InterruptHandlers[256];

STRING ExceptionMessages[] = 
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

VOID
FaultHandler(Registers_t *Register) 
{
	if (Register->INT_No < 32) 
	{
		ERROR(ExceptionMessages[Register->INT_No]);
		CPU_Halt();
		TerminalPrint("System halted!");
	}
}

VOID 
RegisterInterruptHandler(UBYTE n, ISR_t Handler) 
{
	InterruptHandlers[n] = Handler;
}

VOID
ISR_Handler(Registers_t Register) 
{
	if (InterruptHandlers[Register.INT_No] != 0) 
	{
		ISR_t Handler = InterruptHandlers[Register.INT_No];
		Handler(Register);
	} 
	else 
	{
		FaultHandler(&Register);
	}
}

VOID 
IRQ_Handler(Registers_t Register) 
{
	if (Register.INT_No >= 40) 
	{
		WritePortB(0xA0, 0x20);
	}
	WritePortB(0x20, 0x20);
	
	if (InterruptHandlers[Register.INT_No] != 0) 
	{
		ISR_t Handler = InterruptHandlers[Register.INT_No];
		Handler(Register);
	}
}
