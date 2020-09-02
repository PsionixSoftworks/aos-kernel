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

#include "types.h"
#include "aos-defs.h"

typedef struct AOS_TSS_Entry TSS_t;
struct AOS_TSS_Entry
{
    UDWORD              previous_tss;
    UDWORD              esp0;
    UDWORD              ss0;
    UDWORD              esp1;
    UDWORD              ss1;
    UDWORD              esp2;
    UDWORD              ss2;
    UDWORD              cr3;
    UDWORD              eip;
    UDWORD              eflags;
    UDWORD              eax;
    UDWORD              ecx;
    UDWORD              edx;
    UDWORD              ebx;
    UDWORD              esp;
    UDWORD              ebp;
    UDWORD              esi;
    UDWORD              edi;
    UDWORD              es;
    UDWORD              cs;
    UDWORD              ss;
    UDWORD              ds;
    UDWORD              fs;
    UDWORD              gs;
    UDWORD              ldt;
    UWORD               trap;
    UWORD               iomap_base;
} PACKED;

EXTERN VOID (SwitchToUserMode(VOID));
EXTERN VOID (ReenableInterrupts(VOID));
EXTERN VOID (SetKernelStack(UDWORD Stack));

#endif
