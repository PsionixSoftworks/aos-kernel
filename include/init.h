/*
 *  File: init.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

#ifndef _INIT_
#define _INIT_

#define ADAMANTINE_OS_READY

#include "../include/aos-defs.h"
#include "../include/types.h"
#include "../include/kernel.h"
#include "../include/x86/gdt.h"
#include "../include/x86/idt.h"
#include "../include/terminal.h"

/* Check if we're using C++. If so, safeguard the code to C linkage. */
#if defined(__cplusplus)
extern "C" {
#endif  /* !__cplusplus */

static string OS_Mode[] =
{
    "Normal Mode",
    "Safe Mode",
    "NoGUI Mode",
};

/*
 * Function Name: init_all();
 * 
 * Usage: To initialize all of the kernel modules
 * and setup the pre-os loading.
 */
static void _TEXT
InitAll(BYTE Mode)
{
    /* Print the startup message. */
    TerminalPrintf("%s - Version: %s, Running in '%s'.\n", OS_NAME, OS_VERSION, OS_Mode[Mode]);

    /* Load up the kernel module's */
    INFO("Getting setup...");
    GDT_Init();
    IDT_Init();
}

#if defined(__cplusplus)
}
#endif  /* !__cplusplus */
#endif  /* !__cplusplus */
