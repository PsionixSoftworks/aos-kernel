#define KERNEL32    1

#include "../include/syscall.h"
#include "../include/isr.h"
#include "../include/terminal.h"

static void syscall_handler(registers_t *regs);

static void *syscalls[3] =
{
    &terminal_print,
    &terminal_print_value,
};
uint32_t num_syscalls = 3;

void 
initialize_syscalls(void)
{
    register_interrupt_handler(0x80, &syscall_handler);
}

void
syscall_handler(registers_t *regs)
{
    if (regs->eax >= num_syscalls)
        return;
    
    void *location = syscalls[regs->eax];

    int ret;
   asm volatile (" \
     push %1; \
     push %2; \
     push %3; \
     push %4; \
     push %5; \
     call *%6; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
   " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
    regs->eax = ret;
}
