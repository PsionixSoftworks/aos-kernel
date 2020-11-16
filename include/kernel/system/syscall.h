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

#define DECL_SYSCALL0(fn)                       uint32_t syscall_##fn();
#define DECL_SYSCALL1(fn, p1)                   uint32_t syscall_##fn(p1);
#define DECL_SYSCALL2(fn, p1, p2)               uint32_t syscall_##fn(p1, p2);
#define DECL_SYSCALL3(fn, p1, p2, p3)           uint32_t syscall_##fn(p1, p2, p3);
#define DECL_SYSCALL4(fn, p1, p2, p3, p4)       uint32_t syscall_##fn(p1, p2, p3, p4);
#define DECL_SYSCALL5(fn, p1, p2, p3, p4, p5)   uint32_t syscall_##fn(p1, p2, p3, p4, p5);

#define DEFN_SYSCALL0(fn, num)                                                          \
uint32_t syscall_##fn()                                                                      \
{                                                                                       \
    uint32_t a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num));                                   \
    return (a);                                                                         \
}

#define DEFN_SYSCALL1(fn, num, P1)                                                      \
uint32_t syscall_##fn(P1 p1)                                                                 \
{                                                                                       \
    uint32_t a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num), "b" ((uint32_t)p1));                    \
    return (a);                                                                         \
}

#define DEFN_SYSCALL2(fn, num, P1, P2)                                                  \
uint32_t syscall_##fn(P1 p1, P2 p2)                                                          \
{                                                                                       \
    uint32_t a;                                                                              \
    asm volatile("INT $0x96" : "=a" (a) : "0" (num), "b", ((uint32_t)p1)), "c" ((uint32_t)p2);    \
    return (a);                                                                         \
}

DECL_SYSCALL1(terminal_print, string);
DECL_SYSCALL1(terminal_print_hex, string);
DECL_SYSCALL1(terminal_print_dec, string);

#if defined(__cplusplus)
extern "C" {
#endif

void syscall_init(void);

#if defined(__cplusplus)
}
#endif

#endif
