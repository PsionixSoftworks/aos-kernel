/*
 *  File: pic.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/pic.h>
#include <system/portio.h>

/* Send an End Of Instruction to the Programmable Interrupt Controller */
void 
pic_send_eoi(uint8_t _irq) 
{
	if (_irq > 7) 										// Check if we're using PIC2
	{
		outb(PIC2_COMMAND, PIC_EOI);					// PIC2 EOI
	}
	outb(PIC1_COMMAND, PIC_EOI);						// Otherwise PIC1 EOI
}

/* Remap the PIC to correctly display interrups as they are received */
void 
pic_remap(void) 
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

/* Return the combined value of the cascaded PIC's IRQ request register */
uint16_t
pic_get_irr(void) 
{
	return (pic_get_irq_register(PIC_READ_IRR));
}

/* Return the combined value of the cascaded PIC's in service register */
uint16_t
pic_get_isr(void) 
{
	return (pic_get_irq_register(PIC_READ_isr));
}

/* Yeah, I'll have to figure this one out... */
uint16_t
pic_get_irq_register(int8_t _ocw3) 
{
	outb(PIC1_COMMAND, _ocw3);
	outb(PIC2_COMMAND, _ocw3);
	
	return ((inb(PIC2_COMMAND) << 0x8) | inb(PIC1_COMMAND));
}
