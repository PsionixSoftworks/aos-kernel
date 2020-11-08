/*
 *  File: syscall.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <system/syscall.h>
#include <kernel/isr.h>
#include <system/terminal.h>

static void SyscallHandler(registers_t *registers);

DEFN_SYSCALL1(terminal_print, 0, string);
DEFN_SYSCALL1(terminal_print_hex, 1, string);
DEFN_SYSCALL1(terminal_print_dec, 2, string);
/*
static void *Syscalls[3] =
{
    &terminal_print,
    &terminal_print_hex,
    &terminal_print_dec,
};
*/
udword NumberOfSyscalls = 3;

void 
syscall_init(void)
{
    register_interrupt_handler(0x96, &SyscallHandler);
}

void
SyscallHandler(registers_t *registers)
{
    if (registers->EAX >= NumberOfSyscalls)
        return;
    
    //void *Location = Syscalls[registers->EAX];
    /*
    dword value = 0;
    asm volatile ("     \
        PUSH %1;        \
        PUSH %2;        \
        PUSH %3;        \
        PUSH %4;        \
        PUSH %5;        \
        CALL *%6;       \
        POP %%EBX;      \
        POP %%EBX;      \
        POP %%EBX;      \
        POP %%EBX;      \
        POP %%EBX;      \
        " : "=a" (value) : "r" (registers->EDI), "r" (registers->ESI), "r" (registers->EDX), "r" (registers->ECX), "r" (registers->EBX), "r" (Location)
    );
    registers->EAX = value;
    */
}
