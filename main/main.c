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
#include "../include/vga.h"
#include "../include/kernel.h"
#include "../include/terminal.h"
#include "../include/math/math-util.h"

MODULE("Main", "0.01a");

struct Test
{
	uint32_t a;
} PACKED;
typedef struct Test Test_t;

inline VOID CheckKernelSignature(VOID);

VOID _TEXT 
KMain(VOID) 
{
	TerminalInit(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
	TerminalClearScreen();

	double a = 13.49;
	int b = round(a);

	TerminalPrintf("%d\n", b);

	return;
}
