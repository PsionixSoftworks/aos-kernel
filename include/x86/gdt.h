/*
 *  File: gdt.h
 *  Author: Vincent Cupo
 *  
 *  THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 *  WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_GLOBAL_DESCRIPTOR_TABLE
#define ADAMANTINE_GLOBAL_DESCRIPTOR_TABLE

// Includes go here:
#include "../types.h"

#ifndef GLOBAL_DESCRIPTOR
#define GLOBAL_DESCRIPTOR
#endif

#if defined(__cplusplus)
extern "C" {
#endif

//extern void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

struct gdt_entry_struct 
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} PACKED;
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct 
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

//extern void load_gdt(void);
void gdt_init(void);
//void encode_gdt_entry(uint8_t *target, gdt_descriptor_t source);

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_GLOBAL_DESCRIPTOR_TABLE
