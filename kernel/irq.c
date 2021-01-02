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

#include <kernel/irq.h>

uint8_t 
are_interrupts_enabled(void) 
{
    unsigned long flags;
    asm volatile 
    ( 
        "PUSHF\n\t"
        "POP %0"
        : "=g"(flags) 
    );

    return flags & (0x1 << 0x9);
}

unsigned long
irq_disable(void) 
{
    unsigned long flags;
    asm volatile
    (
        "PUSHF\n\tCLI\n\tPOP %0" : "=r"(flags) : : "memory"
    );

    return (flags);
}

void 
irq_restore(unsigned long flags) {
    asm volatile
    (
        "PUSH %0\n\tPOPF" : : "rm"(flags) : "memory", "cc"
    );
}

void
clear_interrupts(void) 
{
    asm volatile
    (
        "CLI\n\t"
    );
}
