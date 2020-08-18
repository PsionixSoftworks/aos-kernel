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
#include "../include/init.h"

#if defined(ADAMANTINE_OS_READY)
#include "../AOS/Include/Adamantine.h"
using namespace PsionixSoftworks;
#endif

/* Tell the kernel what module and version we are using. */
MODULE("Kernel", "0.04-2a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

/* Locate external references here. */
EXTERN "C" SET_UDWORD(kernel_end);
EXTERN "C" SET_UDWORD(kernel_base);

/* Declare the kernel structure. */
Kernel_t Kernel;
AdamantineOS *AOS;

EXTERN "C" VOID _TEXT
KernelInit(UBYTE Mode)
{
	InitAll(Mode);
	/* After in user mode. */
	
	AOS->SystemStartup();
	Kernel.Running = TRUE;
}

/* Update the kernel. */
EXTERN "C" VOID _TEXT 
KernelUpdate(void) 
{
	
}

/* Quit the kernel on shutdown. */
EXTERN "C" VOID _TEXT
KernelQuit(UBYTE Status) 
{
	Kernel.ExitStatus = Status;
}

/* Check if the kernel is running. */
EXTERN "C" BOOL _TEXT
KernelIsRunning(void) 
{
	return (Kernel.Running);
}
