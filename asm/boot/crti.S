/*
 *  File: crti.S
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

.SECTION .init
.GLOBL _init
.TYPE _init, @function
_init:
    PUSH %EBP
    MOVL %ESP, %EBP

.SECTION .fini
.GLOBL _fini
.TYPE _fini, @function
_fini:
    PUSH %EBP
    MOVL %ESP, %EBP
