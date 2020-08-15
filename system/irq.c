#include "../include/irq.h"
#include "../include/aos-defs.h"

MODULE("interrupt-request", "0.01a");

bool 
are_interrupts_enabled() 
{
    unsigned long flags;
    asm volatile 
    ( 
        "pushf\n\t"
        "pop %0"
        : "=g"(flags) 
    );

    return flags & (1 << 9);
}

unsigned long 
save_irqdisable(void) 
{
    unsigned long flags;
    asm volatile
    (
        "pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory"
    );
}

void irq_restore(unsigned long flags) {
    asm volatile
    (
        "push %0\n\tpopf" : : "rm"(flags) : "memory", "cc"
    );
}

void
clear_interrupts(void) 
{
    asm volatile
    (
        "cli\n\t"
    );
}
