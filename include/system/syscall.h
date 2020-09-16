/*
 *  File: syscall.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _SYSCALL_
#define _SYSCALL_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

#define DECL_SYSCALL0(fn)                       udword syscall_##fn();
#define DECL_SYSCALL1(fn, p1)                   udword syscall_##fn(p1);
#define DECL_SYSCALL2(fn, p1, p2)               udword syscall_##fn(p1, p2);
#define DECL_SYSCALL3(fn, p1, p2, p3)           udword syscall_##fn(p1, p2, p3);
#define DECL_SYSCALL4(fn, p1, p2, p3, p4)       udword syscall_##fn(p1, p2, p3, p4);
#define DECL_SYSCALL4(fn, p1, p2, p3, p4, p5)   udword syscall_##fn(p1, p2, p3, p4, p5);

#define DEFN_SYSCALL0(fn, num)                                                          \
udword syscall_##fn()                                                                      \
{                                                                                       \
    udword a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num));                                   \
    return (a);                                                                         \
}

#define DEFN_SYSCALL1(fn, num, P1)                                                      \
udword syscall_##fn(P1 p1)                                                                 \
{                                                                                       \
    udword a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num), "b" ((udword)p1));                    \
    return (a);                                                                         \
}

#define DEFN_SYSCALL2(fn, num, P1, P2)                                                  \
udword syscall_##fn(P1 p1, P2 p2)                                                          \
{                                                                                       \
    udword a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num), "b", ((udword)p1)), "c" ((udword)p2);    \
    return (a);                                                                         \
}

DECL_SYSCALL1(terminal_print, string);
DECL_SYSCALL1(terminal_print_hex, string);
DECL_SYSCALL1(terminal_print_dec, string);

EXTERN  SET_VOID(syscall_init(void));

#endif
