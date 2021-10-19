#include <i386/idt.h>
#include <adamantine/tty.h>
#include <kernel/irq.h>
#include <kernel/pic.h>
#include <string.h>

/* Define the IDT enties and the pointer to the IDT */
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

/* Setup the interrupt gates (to be replaced) */
static inline void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

/* Initialize the Interrupt Descriptor Table */
void
idt_initialize(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;      // Get the size of the IDT (255)
    idt_ptr.base = (uint32_t)&idt_entries;              // Get the base of the IDT

    /* Clear the address of all entries to zero */
    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    /* Remap the PIC */
    pic_remap();

    /* Assign ISR0-31 */
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);        // Interrupt Service Routine 0, [Division By Zero]
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);        // Interrupt Service Routine 1, [Debug Exception]
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);        // Interrupt Service Routine 2, [Non-Maskable Interrupt]
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);        // Interrupt Service Routine 3, [Breakpoint Exception]
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);        // Interrupt Service Routine 4, [Into Detected Overflow]
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);        // Interrupt Service Routine 5, [Out Of Bounds Exception]
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);        // Interrupt Service Routine 6, [Invalid Opcode Exception]
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);        // Interrupt Service Routine 7, [No Coprocessor Exception]
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);        // Interrupt Service Routine 8, [Double Fault]
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);        // Interrupt Service Routine 9, [Coprocessor Segment Overrun]
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);      // Interrupt Service Routine 10, [Bad TSS]
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);      // Interrupt Service Routine 11, [Segment Not Present]
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);      // Interrupt Service Routine 12, [Stack Fault]
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);      // Interrupt Service Routine 13, [General Protection Fault]
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);      // Interrupt Service Routine 14, [Page Fault]
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);      // Interrupt Service Routine 15, [Unknown Interrupt Exception]
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);      // Interrupt Service Routine 16, [Coprocessor Fault]
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);      // Interrupt Service Routine 17, [Alignment Check Exception]
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);      // Interrupt Service Routine 18, [Machine Check Exception]
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);      // Interrupt Service Routine 19, [Reserved]
    idt_set_gate(IRQ0, (uint32_t)irq0, 0x08, 0x8E);     // Interrupt Request 0, [PIT 0 (System Time)]
    idt_set_gate(IRQ1, (uint32_t)irq1, 0x08, 0x8E);     // Interrupt Request 1, [Keyboard]
    idt_set_gate(IRQ2, (uint32_t)irq2, 0x08, 0x8E);     // Interrupt Request 2, [Cascade from IRQ9]
    idt_set_gate(IRQ3, (uint32_t)irq3, 0x08, 0x8E);     // Interrupt Request 3, [COM Port 2 | 4]
    idt_set_gate(IRQ4, (uint32_t)irq4, 0x08, 0x8E);     // Interrupt Request 4, [COM Port 1 | 3]
    idt_set_gate(IRQ5, (uint32_t)irq5, 0x08, 0x8E);     // Interrupt Request 5, [Parallel Port 2 (Printer) | Sound Cards]
    idt_set_gate(IRQ6, (uint32_t)irq6, 0x08, 0x8E);     // Interrupt Request 6, [Floppy Drive Controller]
    idt_set_gate(IRQ7, (uint32_t)irq7, 0x08, 0x8E);     // Interrupt Request 7, [Parallel Port 1 (Printer)]
    idt_set_gate(IRQ8, (uint32_t)irq8, 0x08, 0x8E);     // Interrupt Request 8, [Real Time Clock]
    idt_set_gate(IRQ9, (uint32_t)irq9, 0x08, 0x8E);     // Interrupt Request 9, [Video]
    idt_set_gate(IRQ10, (uint32_t)irq10, 0x08, 0x8E);   // Interrupt Request 10, [Open?]
    idt_set_gate(IRQ11, (uint32_t)irq11, 0x08, 0x8E);   // Interrupt Request 11, [Open?]
    idt_set_gate(IRQ12, (uint32_t)irq12, 0x08, 0x8E);   // Interrupt Request 12, [PS/2 Mouse]
    idt_set_gate(IRQ13, (uint32_t)irq13, 0x08, 0x8E);   // Interrupt Request 13, [Coprocessor]
    idt_set_gate(IRQ14, (uint32_t)irq14, 0x08, 0x8E);   // Interrupt Request 14, [Primary IDE Controller (HDD)]
    idt_set_gate(IRQ15, (uint32_t)irq15, 0x08, 0x8E);   // Interrupt Request 15, [Secondary IDE Controller (DD)]
    
    /* Load the IDT into memory */
    __asm__ volatile ( "lidt (%0)" : : "m"(idt_ptr) );
}

/* Tell the IDT how the interrups work */
static inline void
idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo    = base & 0xFFFF;        // BaseBaseBaseBaseBaseBase
    idt_entries[num].base_hi    = (base >> 16) & 0xFFFF;// See if we can merge ^

    idt_entries[num].sel        = sel;
    idt_entries[num].always0    = 0;

    idt_entries[num].flags      = flags | 0x60;         // TODO: Figure out what 0x60 does here...
}
