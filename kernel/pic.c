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
#include <kernel/system/ioctrl.h>

void 
pic_send_eoi(uint8_t irq) 
{
	if (irq > 7) 
	{
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);
}

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

void 
irq_set_mask(uint8_t irq_Line) 
{
	uint16_t port;
	uint8_t value;
	
	if (irq_Line < 0x8) 
	{
		port = PIC1_DATA;
	} 
	else 
	{
		port = PIC2_DATA;
		irq_Line -= 0x8;
	}
	value = inb(port) | (1 << irq_Line);
	outb(port, value);
}

void 
irq_clear_mask(uint8_t irq_Line) 
{
	uint16_t port;
	uint8_t value;
	
	if (irq_Line < 0x8) 
	{
		port = PIC1_DATA;
	} 
	else 
	{
		port = PIC2_DATA;
		irq_Line -= 0x8;
	}
	value = inb(port) | ~(1 << irq_Line);
	outb(port, value);
}

uint16_t
pic_get_irr(void) 
{
	return (pic_get_irq_register(PIC_READ_IRR));
}

uint16_t
pic_get_isr(void) 
{
	return (pic_get_irq_register(PIC_READ_isr));
}

uint16_t pic_get_irq_register(int8_t ocw3) 
{
	outb(PIC1_COMMAND, ocw3);
	outb(PIC2_COMMAND, ocw3);
	
	return ((inb(PIC2_COMMAND) << 0x8) | inb(PIC1_COMMAND));
}
