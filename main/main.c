/*
 *  File: main.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/main.h"
#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"
#include "../include/centrix.h"
#include "../include/pit.h"

#include "../include/x86/gdt.h"
#include "../include/x86/idt.h"
#include "../include/syscall.h"
#include "../include/tss.h"
#include "../include/vga.h"

MODULE("Main", "0.01a");

VOID _TEXT 
KMain(VOID) 
{
	TerminalInit(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
	TerminalClearScreen();

	GDT_Init();
	IDT_Init();

	int a = 1 / 0;
}
