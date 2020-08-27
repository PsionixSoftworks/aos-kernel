/*
 *  File: kernel.c
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

/* Include the initializer rather than all of the modules. */
#include "../include/kernel.h"
#include "../include/init.h"
#include "../include/x86/gdt.h"
#include "../include/x86/idt.h"
#include "../include/paging.h"
#include "../include/mem-util.h"

#if defined(ADAMANTINE_OS_READY)
#include "../AOS/Include/Adamantine.h"
using namespace PsionixSoftworks;
#endif

/* Tell the kernel what module and version we are using. */
MODULE("Kernel", "0.04-2a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

EXTERN "C" VOID KMain(VOID);

static inline VOID *
ParamTest(UDWORD _STRAIGHTEN x)
{
	VOID *Result = 0;
	if (Result == NULL)
	{
		Result = (VOID *)x;
	}
	return (Result);
}

EXTERN "C" VOID _TEXT
KernelRun(VOID)
{
	InitAll(KERNEL_MODE_NORMAL);

	TerminalPrintf("%s kernel [Version: %s] is starting up...\n", OS_NAME, OS_VERSION);
	INFO("Starting kernel modules...");
	GDT_Init();
	IDT_Init();
	PagingInit();

	uint32_t *x = (uint32_t *)ParamTest(1000000);
	MemSet(x, 0x9F, 160);
	
	TerminalPrintln();
	TerminalPrintf("Done! Starting %s in user_mode...\n", OS_NAME);
}
