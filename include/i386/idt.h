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
} __packed;

/* Define the IDT ptr struct */
struct idt_ptr_struct
{
    uint16_t                limit;                      // IDT size max
    uint32_t                base;                       // IDT base
} __packed;

/* Function Templates */
__GLOBAL KERNEL_API void idt_init(void);         // Initialize the Interrupt Descriptor Table
__GLOBAL KERNEL_API void isr0(void);             // Interrupt Service Routine 0, [Division By Zero]
__GLOBAL KERNEL_API void isr1(void);             // Interrupt Service Routine 1, [Debug Exception]
__GLOBAL KERNEL_API void isr2(void);             // Interrupt Service Routine 2, [Non-Maskable Interrupt]
__GLOBAL KERNEL_API void isr3(void);             // Interrupt Service Routine 3, [Breakpoint Exception]
__GLOBAL KERNEL_API void isr4(void);             // Interrupt Service Routine 4, [Into Detected Overflow]
__GLOBAL KERNEL_API void isr5(void);             // Interrupt Service Routine 5, [Out Of Bounds Exception]
__GLOBAL KERNEL_API void isr6(void);             // Interrupt Service Routine 6, [Invalid Opcode Exception]
__GLOBAL KERNEL_API void isr7(void);             // Interrupt Service Routine 7, [No Coprocessor Exception]
__GLOBAL KERNEL_API void isr8(void);             // Interrupt Service Routine 8, [Double Fault]
__GLOBAL KERNEL_API void isr9(void);             // Interrupt Service Routine 9, [Coprocessor Segment Overrun]
__GLOBAL KERNEL_API void isr10(void);            // Interrupt Service Routine 10, [Bad TSS]
__GLOBAL KERNEL_API void isr11(void);            // Interrupt Service Routine 11, [Segment Not Present]
__GLOBAL KERNEL_API void isr12(void);            // Interrupt Service Routine 12, [Stack Fault]
__GLOBAL KERNEL_API void isr13(void);            // Interrupt Service Routine 13, [General Protection Fault]
__GLOBAL KERNEL_API void isr14(void);            // Interrupt Service Routine 14, [Page Fault]
__GLOBAL KERNEL_API void isr15(void);            // Interrupt Service Routine 15, [Unknown Interrupt Exception]
__GLOBAL KERNEL_API void isr16(void);            // Interrupt Service Routine 16, [Coprocessor Fault]
__GLOBAL KERNEL_API void isr17(void);            // Interrupt Service Routine 17, [Alignment Check Exception]
__GLOBAL KERNEL_API void isr18(void);            // Interrupt Service Routine 18, [Machine Check Exception]
__GLOBAL KERNEL_API void isr19(void);            // Interrupt Service Routine 19, [Reserved]
__GLOBAL KERNEL_API void isr20(void);            // Interrupt Service Routine 20, [Reserved]
__GLOBAL KERNEL_API void isr21(void);            // Interrupt Service Routine 21, [Reserved]
__GLOBAL KERNEL_API void isr22(void);            // Interrupt Service Routine 22, [Reserved]
__GLOBAL KERNEL_API void isr23(void);            // Interrupt Service Routine 23, [Reserved]
__GLOBAL KERNEL_API void isr24(void);            // Interrupt Service Routine 24, [Reserved]
__GLOBAL KERNEL_API void isr25(void);            // Interrupt Service Routine 25, [Reserved]
__GLOBAL KERNEL_API void isr26(void);            // Interrupt Service Routine 26, [Reserved]
__GLOBAL KERNEL_API void isr27(void);            // Interrupt Service Routine 27, [Reserved]
__GLOBAL KERNEL_API void isr28(void);            // Interrupt Service Routine 28, [Reserved]
__GLOBAL KERNEL_API void isr29(void);            // Interrupt Service Routine 29, [Reserved]
__GLOBAL KERNEL_API void isr30(void);            // Interrupt Service Routine 30, [Reserved]
__GLOBAL KERNEL_API void isr31(void);            // Interrupt Service Routine 31, [Reserved]
__GLOBAL KERNEL_API void irq0(void);             // Interrupt Request 0, [PIT 0 (System Time)]
__GLOBAL KERNEL_API void irq1(void);             // Interrupt Request 1, [Keyboard]
__GLOBAL KERNEL_API void irq2(void);             // Interrupt Request 2, [Cascade from IRQ9]
__GLOBAL KERNEL_API void irq3(void);             // Interrupt Request 3, [COM Port 2 | 4]
__GLOBAL KERNEL_API void irq4(void);             // Interrupt Request 4, [COM Port 1 | 3]
__GLOBAL KERNEL_API void irq5(void);             // Interrupt Request 5, [Parallel Port 2 (Printer) | Sound Cards]
__GLOBAL KERNEL_API void irq6(void);             // Interrupt Request 6, [Floppy Drive Controller]
__GLOBAL KERNEL_API void irq7(void);             // Interrupt Request 7, [Parallel Port 1 (Printer)]
__GLOBAL KERNEL_API void irq8(void);             // Interrupt Request 8, [Real Time Clock]
__GLOBAL KERNEL_API void irq9(void);             // Interrupt Request 9, [Video]
__GLOBAL KERNEL_API void irq10(void);            // Interrupt Request 10, [Open?]
__GLOBAL KERNEL_API void irq11(void);            // Interrupt Request 11, [Open?]
__GLOBAL KERNEL_API void irq12(void);            // Interrupt Request 12, [PS/2 Mouse]
__GLOBAL KERNEL_API void irq13(void);            // Interrupt Request 13, [Coprocessor]
__GLOBAL KERNEL_API void irq14(void);            // Interrupt Request 14, [Primary IDE Controller (HDD)]
__GLOBAL KERNEL_API void irq15(void);            // Interrupt Request 15, [Secondary IDE Controller (DD)]

#define IRQS_ENABLED        1                                       // Defined for "ioctrl.h"

#endif
