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
#include "../aos-defs.h"
#include "../types.h"

#ifndef GLOBAL_DESCRIPTOR
#define GLOBAL_DESCRIPTOR
#endif

#define MEMORY_START_REGION                  0x00000000
#define MEMORY_END_REGION                    0xFFFFFFFF
#define ACCESS_BYTE_0                        0x9A
#define ACCESS_BYTE_1                        0x92
#define ACCESS_BYTE_2                        0xFA
#define ACCESS_BYTE_3                        0xF2
#define ACCESS_BYTE_FLAGS                    0xCF
#define GDT_SEGMENT_NULL                     0x00

typedef struct gdt_entry gdt_entry_t;
typedef struct pgdt PGDT_t;

struct
gdt_entry
{
   uword                limit_lo;                                  // The lower 16 bits of the limit.
   uword                base_lo;                                   // The lower 16 bits of the base.
   byte                 base_middle;                               // The next 8 bits of the base.
   byte                 access;                                   // Access flags, determine what ring this segment can be used in.
   byte                 granularity;
   byte                 base_hi;                                   // The last 8 bits of the base.
} PACKED;

struct
pgdt
{
   uword limit;                                                   // The upper 16 bits of all selector limits.
   udword base;                                                   // The address of the first gdt_entry_t struct.
} PACKED;

EXTERN   void gdt_init(void);

#endif	                                                         // !ADAMANTINE_GLOBAL_DESCRIPTOR_TABLE
