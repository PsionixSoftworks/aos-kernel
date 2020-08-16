#ifndef ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER
#define ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER

// Includes go here:
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
extern void pic_send_eoi(uint8_t irq);					// Send the end of instruction to the PIC.
extern void pic_remap(void);		                    // Remap PIC.
extern void irq_set_mask(uint8_t irq_line);			    // Set the IRQ mask.
extern void irq_clear_mask(uint8_t irq_line);			// Clear the IRQ mask.
extern uint16_t pic_get_irr(void);						// Get (IRR?).
extern uint16_t pic_get_isr(void);						// Get the interrupt service routine.
uint16_t __pic_get_irq_register(int ocw3);				// Get the IRQ register.

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_PROGRAMMABLE_INTERRUPT_CONTROLLER
