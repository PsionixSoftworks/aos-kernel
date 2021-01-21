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

#ifndef _AOS_PIC_H
#define _AOS_PIC_H

// Includes go here:
#include <stdint.h>

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
#define PIC_READ_isr		0x0B
#endif

// Declare global functions:
void pic_send_eoi(uint8_t irq);					                // Send the end of instruction to the PIC.
void pic_remap(void);		                                    // Remap PIC.
void irq_set_mask(uint8_t irq_Line);			                // Set the irq mask.
void irq_clear_mask(uint8_t irq_Line);			                // Clear the irq mask.
uint16_t pic_get_irr(void);						                // Get (IRR?).
uint16_t pic_get_isr(void);						                // Get the interrupt service routine.
uint16_t pic_get_irq_register(int8_t ocw3);				        // Get the irq registers.

#endif	// !_AOS_PIC_H
