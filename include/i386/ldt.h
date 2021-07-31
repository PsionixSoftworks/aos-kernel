#ifndef _ADAMANTINE_LDT_H
#define _ADAMANTINE_LDT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <compiler.h>
#include <stdint.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

/* Define the types for the LDT */
typedef struct ldt_entry_struct ldt_entry_t;            // The physical LDT type
typedef struct ldt_ptr_struct ldt_ptr_t;                // The ptr to the end-start of the LDT

/* Define the LDT struct */
struct ldt_entry_struct
{
    uint8_t                 table;                      // Does what exactly???
    uint8_t                 rpl;                        // Ring Privelage Level
} PACKED;

/* Define the LDT ptr struct */
struct ldt_ptr_struct
{
    uint16_t                limit;                      // LDT size max
    uint32_t                base;                       // LDT base
} PACKED;

/* Function Templates */
EXTERN KERNEL_API void ldt_init(void);                             // Initialize the Local Descriptor Table

#endif  // !_ADAMANTINE_LDT_H
