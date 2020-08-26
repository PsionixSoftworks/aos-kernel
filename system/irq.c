/*
 *  File: irq.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/irq.h"

MODULE("InterruptRequest", "0.01a");

BYTE 
AreInterruptsEnabled(VOID) 
{
    ULONG Flags;
    asm volatile 
    ( 
        "PUSHF\n\t"
        "POP %0"
        : "=g"(Flags) 
    );

    return Flags & (0x1 << 0x9);
}

ULONG
IRQ_Disable(VOID) 
{
    ULONG Flags;
    asm volatile
    (
        "PUSHF\n\tCLI\n\tPOP %0" : "=r"(Flags) : : "memory"
    );
}

VOID 
IRQ_Restore(ULONG Flags) {
    asm volatile
    (
        "PUSH %0\n\tPOPF" : : "rm"(Flags) : "memory", "cc"
    );
}

VOID
ClearInterrupts(VOID) 
{
    asm volatile
    (
        "CLI\n\t"
    );
}
