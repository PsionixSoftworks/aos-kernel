/*
 *  File: ldt.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/x86/ldt.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"

void _TEXT
ldt_init(void)
{
    
    INFO("LDT is initialized!");
}
