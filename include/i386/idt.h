#ifndef _ADAMANTINE_IDT_H
#define _ADAMANTINE_IDT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <common.h>
#include <stdint.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

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
EXTERN __GLOBAL KERNEL_API _PROTO(void idt_init, (void)              ); // Initialize the Interrupt Descriptor Table
EXTERN __GLOBAL KERNEL_API _PROTO(void isr0, (void)                  ); // Interrupt Service Routine 0, [Division By Zero]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr1, (void)                  ); // Interrupt Service Routine 1, [Debug Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr2, (void)                  ); // Interrupt Service Routine 2, [Non-Maskable Interrupt]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr3, (void)                  ); // Interrupt Service Routine 3, [Breakpoint Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr4, (void)                  ); // Interrupt Service Routine 4, [Into Detected Overflow]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr5, (void)                  ); // Interrupt Service Routine 5, [Out Of Bounds Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr6, (void)                  ); // Interrupt Service Routine 6, [Invalid Opcode Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr7, (void)                  ); // Interrupt Service Routine 7, [No Coprocessor Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr8, (void)                  ); // Interrupt Service Routine 8, [Double Fault]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr9, (void)                  ); // Interrupt Service Routine 9, [Coprocessor Segment Overrun]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr10, (void)                 ); // Interrupt Service Routine 10, [Bad TSS]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr11, (void)                 ); // Interrupt Service Routine 11, [Segment Not Present]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr12, (void)                 ); // Interrupt Service Routine 12, [Stack Fault]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr13, (void)                 ); // Interrupt Service Routine 13, [General Protection Fault]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr14, (void)                 ); // Interrupt Service Routine 14, [Page Fault]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr15, (void)                 ); // Interrupt Service Routine 15, [Unknown Interrupt Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr16, (void)                 ); // Interrupt Service Routine 16, [Coprocessor Fault]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr17, (void)                 ); // Interrupt Service Routine 17, [Alignment Check Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr18, (void)                 ); // Interrupt Service Routine 18, [Machine Check Exception]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr19, (void)                 ); // Interrupt Service Routine 19, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr20, (void)                 ); // Interrupt Service Routine 20, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr21, (void)                 ); // Interrupt Service Routine 21, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr22, (void)                 ); // Interrupt Service Routine 22, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr23, (void)                 ); // Interrupt Service Routine 23, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr24, (void)                 ); // Interrupt Service Routine 24, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr25, (void)                 ); // Interrupt Service Routine 25, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr26, (void)                 ); // Interrupt Service Routine 26, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr27, (void)                 ); // Interrupt Service Routine 27, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr28, (void)                 ); // Interrupt Service Routine 28, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr29, (void)                 ); // Interrupt Service Routine 29, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr30, (void)                 ); // Interrupt Service Routine 30, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void isr31, (void)                 ); // Interrupt Service Routine 31, [Reserved]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq0, (void)                  ); // Interrupt Request 0, [PIT 0 (System Time)]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq1, (void)                  ); // Interrupt Request 1, [Keyboard]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq2, (void)                  ); // Interrupt Request 2, [Cascade from IRQ9]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq3, (void)                  ); // Interrupt Request 3, [COM Port 2 | 4]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq4, (void)                  ); // Interrupt Request 4, [COM Port 1 | 3]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq5, (void)                  ); // Interrupt Request 5, [Parallel Port 2 (Printer) | Sound Cards]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq6, (void)                  ); // Interrupt Request 6, [Floppy Drive Controller]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq7, (void)                  ); // Interrupt Request 7, [Parallel Port 1 (Printer)]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq8, (void)                  ); // Interrupt Request 8, [Real Time Clock]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq9, (void)                  ); // Interrupt Request 9, [Video]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq10, (void)                 ); // Interrupt Request 10, [Open?]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq11, (void)                 ); // Interrupt Request 11, [Open?]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq12, (void)                 ); // Interrupt Request 12, [PS/2 Mouse]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq13, (void)                 ); // Interrupt Request 13, [Coprocessor]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq14, (void)                 ); // Interrupt Request 14, [Primary IDE Controller (HDD)]
EXTERN __GLOBAL KERNEL_API _PROTO(void irq15, (void)                 ); // Interrupt Request 15, [Secondary IDE Controller (DD)]

#define IRQS_ENABLED        1                                       // Defined for "ioctrl.h"

#endif
