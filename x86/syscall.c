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

#include "../include/syscall.h"
#include "../include/isr.h"
#include "../include/terminal.h"

static VOID SyscallHandler(Registers_t *Register);

DEFN_SYSCALL1(TerminalPrint, 0, STRING);
DEFN_SYSCALL1(TerminalPrintHex, 1, STRING);
DEFN_SYSCALL1(TerminalPrintDec, 2, STRING);

static VOID *Syscalls[3] =
{
    &TerminalPrint,
    &TerminalPrintHex,
    &TerminalPrintDec,
};
UDWORD NumberOfSyscalls = 3;

VOID 
SysCallsInit(VOID)
{
    RegisterInterruptHandler(0x80, &SyscallHandler);
}

VOID
SyscallHandler(Registers_t *Register)
{
    if (Register->EAX >= NumberOfSyscalls)
        return;
    
    VOID *Location = Syscalls[Register->EAX];

    DWORD Value = 0;
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
        " : "=a" (Value) : "r" (Register->EDI), "r" (Register->ESI), "r" (Register->EDX), "r" (Register->ECX), "r" (Register->EBX), "r" (Location)
    );
    Register->EAX = Value;
}
