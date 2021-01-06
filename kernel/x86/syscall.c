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

#include <kernel/system/syscall.h>
#include <kernel/isr.h>

DEFN_SYSCALL1(terminal_print, 0, char *);
DEFN_SYSCALL1(terminal_print_hex, 1, char *);
DEFN_SYSCALL1(terminal_print_dec, 2, char *);
/*
static void *Syscalls[3] =
{
    &terminal_print,
    &terminal_print_hex,
    &terminal_print_dec,
};
*/
uint32_t NumberOfSyscalls = 3;

void 
syscall_init(void)
{
    //register_interrupt_handler(0x96, (isr_t)&SyscallHandler);
}
