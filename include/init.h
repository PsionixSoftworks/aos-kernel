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

#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/x86/gdt.h"
#include "../include/x86/ldt.h"     /* WIP * */
#include "../include/x86/idt.h"

#define __initcall      _TEXT

/* Check if we're using C++. If so, safeguard the code to C linkage. */
#if defined(__cplusplus)
extern "C" {
#endif  /* !__cplusplus */

/*
 * Function Name: init_all();
 * 
 * Usage: To initialize all of the kernel modules
 * and setup the pre-os loading.
 */
static void __initcall
init_all(void) 
{
    /* Print the startup message. */
    terminal_printf("%s - Version: %s, Running in 'NoGUI Mode'.\n", OS_NAME, OS_VERSION);

    /* Load up the kernel module's */
    INFO("Getting setup...");
    gdt_init();
    ldt_init();
    idt_init();

    
}

#if defined(__cplusplus)
}
#endif  /* !__cplusplus */

#endif  /* !__cplusplus */
