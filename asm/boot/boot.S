/*
 *  File: boot.S
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

#include "crti.S"
#include "crtn.S"

.code32
/* The .multiboot section is used to initalize GRUB and start the kernel. */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Declare the .text section for the entry point and other functions. */
.section .text
.global _start
.type _start @function
_start:
    mov $stack_top, %esp
    call kmain
    cli
1:  hlt
    jmp 1b
.size _start, . - _start

/* Initialize static functions that will not change during runtime. */
.section .data

/* Special section for read-only data. */
.section .special

/* Place the Multiboot stuff in read-only data because it'll never change. */
.section .rodata
.set ALIGN,      (1 << 0)
.set MEMINFO,    (1 << 1)
.set FLAGS,      (ALIGN | MEMINFO)
.set MAGIC,      (0x1BADB002)
.set CHECKSUM,   -(MAGIC + FLAGS)

/* Declare the stack pointer info. */
.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
