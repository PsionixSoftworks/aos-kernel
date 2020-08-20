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

typedef struct AOS_TSS_Entry
{
    UDWORD              PreviousTSS;
    UDWORD              ESP0;
    UDWORD              SS0;
    UDWORD              ESP1;
    UDWORD              SS1;
    UDWORD              ESP2;
    UDWORD              SS2;
    UDWORD              CR3;
    UDWORD              EIP;
    UDWORD              EFLAGS;
    UDWORD              EAX;
    UDWORD              ECX;
    UDWORD              EDX;
    UDWORD              EBX;
    UDWORD              ESP;
    UDWORD              EBP;
    UDWORD              ESI;
    UDWORD              EDI;
    UDWORD              ES;
    UDWORD              CS;
    UDWORD              SS;
    UDWORD              DS;
    UDWORD              FS;
    UDWORD              GS;
    UDWORD              LDTR;
    UWORD               IOMapBase;
} TSS_t PACKED;

EXTERN VOID (SwitchToUserMode(VOID));
EXTERN VOID (ReenableInterrupts(VOID));
EXTERN VOID (SetKernelStack(UDWORD Stack));

#endif
