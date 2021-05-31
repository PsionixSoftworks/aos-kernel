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

/* Checks if interrupts are enabled? */
bool 
are_interrupts_enabled(void) 
{
    unsigned long flags;
    asm volatile 
    (
        "PUSHF\n\t"
        "POP %0"
        : "=g"(flags)
    );

    return flags & 0x200;
}

/* Temporarily disable IRQ's */
unsigned long
irq_disable(void) 
{
    unsigned long flags;
    asm volatile
    (
        "pushf\n\tCLI\n\tpop %0" : "=r"(flags) : : "memory"
    );

    return (flags);
}

/* Restore temporarily disabled IRQ's */
void 
irq_restore(unsigned long flags) {
    asm volatile
    (
        "push %0\n\tpopf" : : "rm"(flags) : "memory", "cc"
    );
}

/* Clear interrupts (again?) */
void
clear_interrupts(void) 
{
    asm ( "cli\n\t" );
}

/* Set interrupts (again?) */
void
set_interrupts(void)
{
    asm ( "sti\n\t" );
}
