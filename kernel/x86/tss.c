/*
 *  File: tss.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */


#include <kernel/x86/tss.h>
#include <kernel/memory/mm.h>

tss_t tss_entry __attribute__((aligned(4096)));

/* 0x23 = 35: user Mode data selector. */
/* 0x1B = 27: CS selector value. */
EXTERN uint32_t jump_usermode(void);

static char irq_stack[4096];

void
tss_user_mode_switch(void)
{
    jump_usermode();
}

void
test_user_function(void)
{
	udword a = 0;
}
