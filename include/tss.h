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
#include "x86/gdt.h"

typedef struct AOS_TSS_Entry TSS_t;
struct AOS_TSS_Entry
{
    uint32_t            previous_tss:16;
    uint32_t            esp0;
    uint32_t            ss0:16;
    uint32_t            esp1;
    uint32_t            ss1:16;
    uint32_t            esp2;
    uint32_t            ss2:16;
    uint32_t            cr3;
    uint32_t            eip;
    uint32_t            eflags;
    uint32_t            eax, ecx, edx, ebx;
    uint32_t            esp, ebp, esi, edi;
    uint32_t            es:16;
    uint32_t            cs:16;
    uint32_t            ss:16;
    uint32_t            ds:16;
    uint32_t            fs:16;
    uint32_t            gs:16;
    uint32_t            ldt:16;
    uint16_t            trap, iomap_base;
} PACKED;

EXTERN VOID TSS_Init(VOID);
EXTERN VOID SwitchToUserMode(VOID);
EXTERN VOID ReenableInterrupts(VOID);
EXTERN VOID SetKernelStack(UDWORD Stack);

#endif
