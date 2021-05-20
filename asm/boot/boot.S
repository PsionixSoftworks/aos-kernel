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

/* The .multiboot section is used to initalize GRUB and start the kernel. */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.set ALIGN,     (1 << 0)
.set MEM_INFO,  (1 << 1)
.set GFX_MODE,  (1 << 2)
.set FLAGS,     ALIGN | MEM_INFO #| GFX_MODE
.set MAGIC,     (0x1BADB002)
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.long  MAGIC
.long FLAGS
.long CHECKSUM

.long 0
.long 0
.long 0
.long 0
.long 0

.long 0
.long 800
.long 600
.long 32

/* Declare the .text section for the entry point and other functions. */
.section .text
.globl _start
.type _start @function
_start:
    mov $stack_top, %esp
    mov $0xB8000, %eax
    push %eax
    call k_main
    pop %eax
1:  hlt
    jmp 1b
.size _start, . - _start

/* Declare the stack pointer info. */
.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
