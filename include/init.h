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

//#define ADAMANTINE_OS_READY

#define __KERNEL__

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <system/terminal.h>
#include <drivers/vga.h>

EXTERN void sys_init(void);

static __kernel_string os_mode[] =
{
    "Normal Mode",
    "Safe Mode",
    "NoGUI Mode",
};

/*
 * Function name: init_all();
 * 
 * Usage: To initialize all of the kernel modules
 * and setup the pre-os loading.
 */
static __kernel_void _TEXT
init_all(__kernel_byte mode)
{
    /* Initialize the Terminal. */
    //TerminalInit(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
}

#endif  /* !_INIT_ */
