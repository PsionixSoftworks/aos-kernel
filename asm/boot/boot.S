/*
 *  File: boot.S
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "crti.S"
#include "crtn.S"

.CODE32
/* The .multiboot section is used to initalize GRUB and start the kernel. */
.SECTION .multiboot
.ALIGN 4
.LONG MAGIC
.LONG FLAGS
.LONG CHECKSUM

/* Declare the .text section for the entry point and other functions. */
.SECTION .text
.GLOBAL _start
.TYPE _start @function
_start:
    MOV $stack_top, %esp
    CALL kmain
    CLI
1:  HLT
    JMP 1b
.SIZE _start, . - _start

/* Initialize static functions that will not change during runtime. */
.SECTION .data

/* Special section for read-only data. */
.SECTION .special

/* Place the Multiboot stuff in read-only data because it'll never change. */
.SECTION .rodata
.SET ALIGN,      (1 << 0)
.SET MEMINFO,    (1 << 1)
.SET FLAGS,      (ALIGN | MEMINFO)
.SET MAGIC,      (0x1BADB002)
.SET CHECKSUM,   -(MAGIC + FLAGS)

/* Declare the stack pointer info. */
.SECTION .bss
.ALIGN 16
stack_bottom:
    .SKIP 16384
stack_top:
