/*
 *  File: ldt.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _LOCAL_DESCRIPTOR_TABLE_
#define _LOCAL_DESCRIPTOR_TABLE_

#include "../../include/types.h"
#include "../../include/aos-defs.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct ldt_entry_struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint16_t limit_high;
    uint16_t base_high;
    uint8_t access;
    uint8_t granularity;
} PACKED;
typedef struct ldt_entry_struct ldt_entry_t;

struct ldt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
} PACKED;
typedef struct ldt_ptr_struct ldt_ptr_t;

extern void ldt_init(void);
extern void ldt_set_gate(uint16_t num,uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#if defined(__cplusplus)
}
#endif

#endif
