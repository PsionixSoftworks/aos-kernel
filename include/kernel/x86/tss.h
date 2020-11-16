/*
 *  File: tss.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_TASK_STATE_SEGMENT_
#define _AOS_TASK_STATE_SEGMENT_

#define KERNEL32    1

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <kernel/x86/descriptor-tables.h>

#define REPLACE_KERNEL_DATA_SEGMENT 0x18
#define REPLACE_KERNEL_STACK_ADDR   0x20

typedef struct aos_tss_entry tss_t;

struct aos_tss_entry
{
    uint32_t            previous_tss;
    uint32_t            esp0;
    uint32_t            ss0;
    uint32_t            esp1;
    uint32_t            ss1;
    uint32_t            esp2;
    uint32_t            ss2;
    uint32_t            cr3;
    uint32_t            eip;
    uint32_t            eflags;
    uint32_t            eax, ecx, edx, ebx;
    uint32_t            esp, ebp, esi, edi;
    uint32_t            es;
    uint32_t            cs;
    uint32_t            ss;
    uint32_t            ds;
    uint32_t            fs;
    uint32_t            gs;
    uint32_t            ldt;
    uint16_t            trap, iomap_base;
} PACKED;

#if defined(__cplusplus)
extern "C" {
#endif

void tss_init(void);
void tss_user_mode_switch(void);
void tss_reenable_interrupts(void);
void tss_set_kernel_stack(uint32_t stack);

#if defined(__cplusplus)
}
#endif

#endif
