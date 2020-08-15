#define KERNEL32	1

#include "../include/pit.h"
#include "../include/isr.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"

MODULE("programmable-interval-timer", "0.01a");

uint32_t tick;

static void 
timer_callback(registers_t regs) 
{
	tick++;
	terminal_print("Tick: ");
	terminal_print_value(tick, 10);
	terminal_println();
}

void 
timer_init(uint32_t frequency) 
{
	register_interrupt_handler(IRQ0, &timer_callback);
	
	uint32_t divisor = 1193180 / frequency;
	write_portb(0x43, 0x36);
	
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);
	
	write_portb(0x40, l);
	write_portb(0x40, h);
}

