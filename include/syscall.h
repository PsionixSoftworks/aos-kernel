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

#include "types.h"

extern void initialize_syscalls(void);

#define DECL_SYSCALL0(fn)                       int syscall_##fn();
#define DECL_SYSCALL1(fn, p1)                   int syscall_##fn(p1);
#define DECL_SYSCALL2(fn, p1, p2)               int syscall_##fn(p1, p2);
#define DECL_SYSCALL3(fn, p1, p2, p3)           int syscall_##fn(p1, p2, p3);
#define DECL_SYSCALL4(fn, p1, p2, p3, p4)       int syscall_##fn(p1, p2, p3, p4);
#define DECL_SYSCALL4(fn, p1, p2, p3, p4, p5)   int syscall_##fn(p1, p2, p3, p4, p5);

#define DEFN_SYSCALL0(fn, num)                                                          \
int syscall_##fn()                                                                      \
{                                                                                       \
    int a;                                                                              \
    asm volatile("int $0x80" : "=a" (a) : "0" (num));                                   \
    return (a);                                                                         \
}

#define DEFN_SYSCALL1(fn, num, P1)                                                      \
int syscall_##fn(P1 p1)                                                                 \
{                                                                                       \
    int a;                                                                              \
    asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1));                    \
    return (a);                                                                         \
}

#define DEFN_SYSCALL2(fn, num, P1, P2)                                                  \
int syscall_##fn(P1 p1, P2 p2)                                                          \
{                                                                                       \
    int a;                                                                              \
    asm volatile("int $0x80" : "=a" (a) : "0" (num), "b", ((int)p1)), "c" ((int)p2);    \
    return (a);                                                                         \
}

DECL_SYSCALL1(terminal_print, string);
DECL_SYSCALL1(terminal_print_hex, string);
DECL_SYSCALL1(terminal_print_dec, string);

#endif
