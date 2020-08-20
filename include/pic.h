/*
 *  File: pic.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER
#define ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER

// Includes go here:
#include "aos-defs.h"
#include "types.h"

// Check if the PIC devices have been defined:
#ifndef PIC_DEVICE
#define PIC1				0x20
#define PIC2				0xA0
#define PIC1_COMMAND		PIC1
#define PIC1_DATA			(PIC1 + 1)
#define PIC2_COMMAND		PIC2
#define PIC2_DATA			(PIC2 + 1)

#define PIC_EOI				0x20

#define ICW1_ICW4			0x01
#define ICW1_SINGLE			0x02
#define ICW1_INTERVAL4		0x04
#define ICW1_LEVEL			0x08
#define ICW1_INIT			0x10

#define ICW4_8086			0x01
#define ICW4_AUTO			0x02
#define ICW4_BUF_SLAVE	    0x04
#define ICW4_BUF_MASTER	    0x08
#define ICW4_SFNM			0x10

#define PIC_READ_IRR		0x0A
#define PIC_READ_ISR		0x0B
#endif

#if defined(__cplusplus)
extern "C" {
#endif

// Declare global functions:
EXTERN  VOID (PIC_SendEOI(UBYTE IRQ));					        // Send the end of instruction to the PIC.
EXTERN  VOID (PIC_Remap(VOID));		                            // Remap PIC.
EXTERN  VOID (IRQ_SetMask(UBYTE IRQ_Line));			            // Set the IRQ mask.
EXTERN  VOID (IRQ_ClearMask(UBYTE IRQ_Line));			            // Clear the IRQ mask.
EXTERN  UWORD (PIC_GetIRR(VOID));						        // Get (IRR?).
EXTERN  UWORD (PIC_GetISR(VOID));						        // Get the interrupt service routine.
EXTERN  UWORD (PIC_GetIRQRegister(DWORD OCW3));				    // Get the IRQ register.

#if defined(__cplusplus)
}
#endif
#endif	// !ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER
