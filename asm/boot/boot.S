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
.SECTION .multiboot
.ALIGN 4
.LONG MAGIC
.LONG FLAGS
.LONG CHECKSUM

.SET ALIGN,     (1 << 0)
.SET MEM_INFO,  (1 << 1)
.SET GFX_EN,    (1 << 2)
.SET FLAGS,     (ALIGN | MEM_INFO)
.SET MAGIC,     (0x1BADB002)
.SET CHECKSUM,  -(MAGIC + FLAGS)

/* Declare the .text section for the entry point and other functions. */
.SECTION .text
.TYPE _init, @function
_init:
    MOV $0x1FFF, %EAX
    MOV %EAX, %ECX
    RET

.GLOBL _start
.TYPE _start @function
_start:
    MOV $_init, %ESP
    MOV $stack_top, %ESP
    CALL kernel_sys_entry
    CLI
1:  HLT
    JMP 1b
.SIZE _start, . - _start

/* Declare the stack pointer info. */
.SECTION .bss
.ALIGN 16
stack_bottom:
    .SKIP 16384
stack_top:
