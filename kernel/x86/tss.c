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


#include <adamantine/adamantine.h>

struct tss tss_entry __attribute__((aligned(4096)));

/* 0x23 = 35: user Mode data selector. */
/* 0x1B = 27: CS selector value. */
EXTERN uint32_t jump_usermode(void);

void
tss_user_mode_switch(void)
{
    jump_usermode();
}

void
test_user_function(void)
{
	
}
