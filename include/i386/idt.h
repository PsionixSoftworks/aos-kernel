#ifndef _ADAMANTINE_IDT_H
#define _ADAMANTINE_IDT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <compiler.h>
#include <stdint.h>

typedef struct idt_entry_struct idt_entry_t;            // The physical IDT type
typedef struct idt_ptr_struct idt_ptr_t;                // The ptr to the end-start of the IDT

/* Define the IDT struct */
struct idt_entry_struct
{
    uint16_t                base_lo;                    // Lower limit of the IDT base
    uint16_t                sel;                        // Kernel segment selector
    uint8_t                 always0;                    // This must always be zero
    uint8_t                 flags;                      // Flags for the IDT
    uint16_t                base_hi;                    // Top of the IDT base
} PACKED;

/* Define the IDT ptr struct */
struct idt_ptr_struct
{
    uint16_t                limit;                      // IDT size max
    uint32_t                base;                       // IDT base
} PACKED;

/* Function Templates */
extern void idt_init(void);                             // Initialize the Interrupt Descriptor Table
extern void isr0(void);                                 // Interrupt Service Routine 0, [Division By Zero]
extern void isr1(void);                                 // Interrupt Service Routine 1, [Debug Exception]
extern void isr2(void);                                 // Interrupt Service Routine 2, [Non-Maskable Interrupt]
extern void isr3(void);                                 // Interrupt Service Routine 3, [Breakpoint Exception]
extern void isr4(void);                                 // Interrupt Service Routine 4, [Into Detected Overflow]
extern void isr5(void);                                 // Interrupt Service Routine 5, [Out Of Bounds Exception]
extern void isr6(void);                                 // Interrupt Service Routine 6, [Invalid Opcode Exception]
extern void isr7(void);                                 // Interrupt Service Routine 7, [No Coprocessor Exception]
extern void isr8(void);                                 // Interrupt Service Routine 8, [Double Fault]
extern void isr9(void);                                 // Interrupt Service Routine 9, [Coprocessor Segment Overrun]
extern void isr10(void);                                // Interrupt Service Routine 10, [Bad TSS]
extern void isr11(void);                                // Interrupt Service Routine 11, [Segment Not Present]
extern void isr12(void);                                // Interrupt Service Routine 12, [Stack Fault]
extern void isr13(void);                                // Interrupt Service Routine 13, [General Protection Fault]
extern void isr14(void);                                // Interrupt Service Routine 14, [Page Fault]
extern void isr15(void);                                // Interrupt Service Routine 15, [Unknown Interrupt Exception]
extern void isr16(void);                                // Interrupt Service Routine 16, [Coprocessor Fault]
extern void isr17(void);                                // Interrupt Service Routine 17, [Alignment Check Exception]
extern void isr18(void);                                // Interrupt Service Routine 18, [Machine Check Exception]
extern void isr19(void);                                // Interrupt Service Routine 19, [Reserved]
extern void isr20(void);                                // Interrupt Service Routine 20, [Reserved]
extern void isr21(void);                                // Interrupt Service Routine 21, [Reserved]
extern void isr22(void);                                // Interrupt Service Routine 22, [Reserved]
extern void isr23(void);                                // Interrupt Service Routine 23, [Reserved]
extern void isr24(void);                                // Interrupt Service Routine 24, [Reserved]
extern void isr25(void);                                // Interrupt Service Routine 25, [Reserved]
extern void isr26(void);                                // Interrupt Service Routine 26, [Reserved]
extern void isr27(void);                                // Interrupt Service Routine 27, [Reserved]
extern void isr28(void);                                // Interrupt Service Routine 28, [Reserved]
extern void isr29(void);                                // Interrupt Service Routine 29, [Reserved]
extern void isr30(void);                                // Interrupt Service Routine 30, [Reserved]
extern void isr31(void);                                // Interrupt Service Routine 31, [Reserved]
extern void irq0(void);                                 // Interrupt Request 0, [PIT 0 (System Time)]
extern void irq1(void);                                 // Interrupt Request 1, [Keyboard]
extern void irq2(void);                                 // Interrupt Request 2, [Cascade from IRQ9]
extern void irq3(void);                                 // Interrupt Request 3, [COM Port 2 | 4]
extern void irq4(void);                                 // Interrupt Request 4, [COM Port 1 | 3]
extern void irq5(void);                                 // Interrupt Request 5, [Parallel Port 2 (Printer) | Sound Cards]
extern void irq6(void);                                 // Interrupt Request 6, [Floppy Drive Controller]
extern void irq7(void);                                 // Interrupt Request 7, [Parallel Port 1 (Printer)]
extern void irq8(void);                                 // Interrupt Request 8, [Real Time Clock]
extern void irq9(void);                                 // Interrupt Request 9, [Video]
extern void irq10(void);                                // Interrupt Request 10, [Open?]
extern void irq11(void);                                // Interrupt Request 11, [Open?]
extern void irq12(void);                                // Interrupt Request 12, [PS/2 Mouse]
extern void irq13(void);                                // Interrupt Request 13, [Coprocessor]
extern void irq14(void);                                // Interrupt Request 14, [Primary IDE Controller (HDD)]
extern void irq15(void);                                // Interrupt Request 15, [Secondary IDE Controller (DD)]

#define IRQS_ENABLED                            1       // Defined for "ioctrl.h"

#endif
