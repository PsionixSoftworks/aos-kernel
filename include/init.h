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

#include "../include/aos-defs.h"
#include "../include/types.h"
#include "../include/terminal.h"
#include "../include/vga.h"

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
    /* Initialize the Terminal. */
    TerminalInit(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
}

#endif  /* !_INIT_ */
