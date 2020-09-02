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
#include "../include/math/math-util.h"
#include "../include/string.h"
#include "../include/io.h"

#include "../include/keyboard.h"
#include "../include/keys.h"

#include "../include/aos-fs.h"

#include "../include/cpu.h"

#if defined(ADAMANTINE_OS_READY)
#include "../AOS/Include/Adamantine.h"
using namespace PsionixSoftworks;
#endif

/* Tell the kernel what module and version we are using. */
MODULE("Kernel", "0.04-4a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

EXTERN UDWORD kernel_end;
EXTERN VOID KMain(VOID);

EXTERN VOID _TEXT
KernelRun(VOID)
{
	InitAll(KERNEL_MODE_NORMAL);

	TerminalPrintf("%s kernel [Version: %s] is starting up...\n", OS_NAME, OS_VERSION);
	INFO("Starting kernel modules...");
	GDT_Init();
	IDT_Init();
	MM_Init(&kernel_end);

	PagingInit();
	if (CPU_CheckIsSupported() == FAILURE)
		asm("INT $0x12");
	CPU_Init();

	KeyboardInit();

	TerminalPrintln();
	//TerminalPrintf("Done! Starting %s in user_mode...\n", OS_NAME);
	TerminalPrintf("You may type below:\n");
	TerminalPrintf("~%s >>> ", AOS_ROOT_DIRNAME);

	while (1)
	{
		string keystr = KeyboardGetKey();
		if (keystr > KEYBOARD_KEY_DOWN_NONE)
		{
			TerminalPrintf(keystr);
			if (KeyboardGetKeyLast() == KEYBOARD_KEY_DOWN_ENTER)
			{
				TerminalPrintf("~%s >>> ", AOS_ROOT_DIRNAME);
			}
			if (KeyboardGetKeyLast() == KEYBOARD_KEY_DOWN_ESCAPE)
			{
				//WritePortB(0x0CF9, 0x0E);
			}
		}
	}
}
