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


struct GDT_Entry 
{
   UWORD                LimitLo;                                  // The lower 16 bits of the limit.
   UWORD                BaseLo;                                   // The lower 16 bits of the base.
   BYTE                 BaseMiddle;                               // The next 8 bits of the base.
   BYTE                 Access;                                   // Access flags, determine what ring this segment can be used in.
   BYTE                 Granularity;
   BYTE                 BaseHi;                                   // The last 8 bits of the base.
} PACKED;
typedef struct GDT_Entry GDT_Entry_t;

struct PGDT 
{
   UWORD Limit;                                                   // The upper 16 bits of all selector limits.
   UDWORD Base;                                                   // The address of the first gdt_entry_t struct.
} PACKED;
typedef struct PGDT PGDT_t;

EXTERN   VOID GDT_Init(VOID);

#endif	                                                         // !ADAMANTINE_GLOBAL_DESCRIPTOR_TABLE
