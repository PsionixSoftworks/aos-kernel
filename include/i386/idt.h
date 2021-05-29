#ifndef _ADAMANTINE_IDT_H
#define _ADAMANTINE_IDT_H

#define KERNEL_ONLY

#include <compiler.h>
#include <stdint.h>

struct idt_entry_struct
{
    uint16_t                base_lo;
    uint16_t                sel;
    uint8_t                 always0;
    uint8_t                 flags;
    uint16_t                base_hi;
} PACKED;
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
    uint16_t                limit;
    uint32_t                base;
} PACKED;
typedef struct idt_ptr_struct idt_ptr_t;

extern void idt_init(void);

void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
void isr8(void);
void isr9(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr15(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);
void isr20(void);
void isr21(void);
void isr22(void);
void isr23(void);
void isr24(void);
void isr25(void);
void isr26(void);
void isr27(void);
void isr28(void);
void isr29(void);
void isr30(void);
void isr31(void);

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif
