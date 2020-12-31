#ifndef _ADAMANTINE_DESCRIPTOR_TABLES_H
#define _ADAMANTINE_DESCRIPTOR_TABLES_H

#include <stdint.h>

struct gdt_entry_struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} PACKED;
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
} PACKED;
typedef struct gdt_ptr_struct gdt_ptr_t;

struct ldt_entry_struct
{
    uint8_t table;
    uint8_t rpl;
} PACKED;
typedef struct ldt_entry_struct ldt_entry_t;

struct ldt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
} PACKED;
typedef struct ldt_ptr_struct ldt_ptr_t;

struct idt_entry_struct
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} PACKED;
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
} PACKED;
typedef struct idt_ptr_struct idt_ptr_t;

#if defined(__cplusplus)
extern "C" {
#endif

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

void init_descriptor_tables(void);

#if defined(__cplusplus)
}
#endif

#endif
