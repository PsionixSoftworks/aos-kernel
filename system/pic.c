#define KERNEL32	1

#include "../include/pic.h"
#include "../include/irq.h"
#include "../include/io.h"
#include "../include/aos-defs.h"

MODULE("programmable-interrupt-controller", "0.01a");

void 
pic_send_eoi(uint8_t irq) 
{
	if (irq >= 8) 
	{
		write_portb(PIC2_COMMAND, PIC_EOI);
	}
	write_portb(PIC1_COMMAND, PIC_EOI);
}

void 
pic_remap(void) 
{
	write_portb(0x20, 0x11);
	write_portb(0xA0, 0x11);
	write_portb(0x21, 0x20);
	write_portb(0xA1, 0x28);
	write_portb(0x21, 0x04);
	write_portb(0xA1, 0x02);
	write_portb(0x21, 0x01);
	write_portb(0xA1, 0x01);
	write_portb(0x21, 0x0);
	write_portb(0xA1, 0x0);
}

void 
irq_set_mask(uint8_t irq_line) 
{
	uint16_t port;
	uint8_t value;
	
	if (irq_line < 8) 
	{
		port = PIC1_DATA;
	} 
	else 
	{
		port = PIC2_DATA;
		irq_line -= 8;
	}
	value = read_portb(port) | (1 << irq_line);
	write_portb(port, value);
}

void 
irq_clear_mask(uint8_t irq_line) 
{
	uint16_t port;
	uint8_t value;
	
	if (irq_line < 8) 
	{
		port = PIC1_DATA;
	} 
	else 
	{
		port = PIC2_DATA;
		irq_line -= 8;
	}
	value = read_portb(port) | ~(1 << irq_line);
	write_portb(port, value);
}

uint16_t pic_get_irr(void) 
{
	return (__pic_get_irq_register(PIC_READ_IRR));
}

uint16_t pic_get_isr(void) 
{
	return (__pic_get_irq_register(PIC_READ_ISR));
}

uint16_t __pic_get_irq_register(int ocw3) 
{
	write_portb(PIC1_COMMAND, ocw3);
	write_portb(PIC2_COMMAND, ocw3);
	
	return ((read_portb(PIC2_COMMAND) << 8) | read_portb(PIC1_COMMAND));
}
