#ifndef _ADAMANTINE_GDT_H
#define _ADAMANTINE_GDT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <common.h>
#include <stdint.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

/* Define macros for the Global Descriptor Table */
#define GDT_MEMORY_START		0x00000000              // Start of memory
#define GDT_MEMORY_END			0xFFFFFFFF              // End of memory
#define GDT_KERNEL_CODE			0b10011010              // Kernel Mode Code needs to be at 0x9A
#define GDT_KERNEL_DATA			0b10010010              // Kernel Mode Data needs to be at 0x92
#define GDT_USER_CODE			0b11111010              // User Mode Code needs to be at 0xFA
#define GDT_USER_DATA			0b11110010              // User Mode Data needs to be at 0xF2
#define GDT_GRANULARITY			0b11001111              // GDT Granularity needs to be at 0xCF

#define MAX_GDT_ENTRIES         8192                    // The maximum number of GDT entries in the kernel

/* Define the types for the GDT */
typedef struct gdt_entry_struct gdt_entry_t;            // The physical GDT type
typedef struct gdt_ptr_struct gdt_ptr_t;                // The ptr to the end-start of the GDT

/* Define the GDT struct */
struct gdt_entry_struct
{
    uint16_t	limit_low;                              // Limit of the GDT data
    uint16_t    base_low;                               // Lower limit of the GDT base
    uint8_t     base_middle;                            // Middle of the GDT base
    uint8_t     access;                                 // Kernel/User Mode
    uint8_t     granularity;                            // GDT Granularity
    uint8_t     base_high;                              // Top of the GDT base
} __packed;

/* Define the GDT ptr struct */
struct gdt_ptr_struct
{
    uint16_t    limit;                                  // GDT size max
    uint32_t    base;                                   // GDT base
} __packed;

/* Function Templates */
__GLOBAL KERNEL_API void gdt_init(void);                             // Initialize the Global Descriptor Table

#endif  // !_ADAMANTINE_GDT_H
