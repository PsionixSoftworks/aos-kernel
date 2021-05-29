#ifndef _ADAMANTINE_GDT_H
#define _ADAMANTINE_GDT_H

#define KERNEL_ONLY

#include <compiler.h>
#include <stdint.h>

#define GDT_MEMORY_START		0x00000000
#define GDT_MEMORY_END			0xFFFFFFFF
#define GDT_KERNEL_CODE			0b10011010
#define GDT_KERNEL_DATA			0b10010010
#define GDT_USER_CODE			0b11111010
#define GDT_USER_DATA			0b11110010
#define GDT_GRANULARITY			0b11001111

struct gdt_entry_struct
{
    uint16_t	limit_low;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} PACKED;
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
    uint16_t    limit;
    uint32_t    base;
} PACKED;
typedef struct gdt_ptr_struct gdt_ptr_t;

extern void gdt_init(void);

#endif
