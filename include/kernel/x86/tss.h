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

struct tss {
    unsigned long link;
    unsigned long esp0, ss0;
    unsigned long esp1, ss1;
    unsigned long esp2, ss2;
    unsigned long cr3;
    unsigned long eip;
    unsigned long eflags;
    unsigned long eax, ecx, edx, ebx, esp, ebp;
    unsigned long esi, edi;
    unsigned long es, cs, ss, ds, fs, gs;
    unsigned long ldt;
    unsigned long iomap;
};

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
