/*
 *  File: centrix.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef CENTRIX
#define CENTRIX

#include "aos-defs.h"
#include "centrix-core.h"
#include "types.h"
#include "mem-util.h"
#include "terminal.h"

#if CENTRIX_VERSION <= 100

<<<<<<< HEAD
#define CENTRIX_INFO(...)	terminal_print("[CENTRIX_INFO]: ");	\
							terminal_printf( __VA_ARGS__ );

static uint32_t *
BEGIN_PROC_ANALYZER(void)
{
	uint32_t *proctest = (uint32_t *)malloc(256);
	int x = (int)memset(proctest, 0xFF, 0xFF);

	terminal_printf("Result of x: %x\n", x);

	return (proctest);
}

static void 
FREE_PROC_ANALYZER(uint32_t *proc)
{
	free(proc);
}

#endif
=======
EXTERN  SET_VOID(*KernelInstall(STRING Name));
EXTERN SET_DWORD(Verify(VOID));
>>>>>>> f17d39f86fcb43d487014e2a2e2af88ff7e7e48b

#endif	/* !CENTRIX_VERSION */
#endif	/* !CENTRIX */
