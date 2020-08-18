/*
 *  File: centrix.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#define CENTRIX_MODE1

#include "../include/centrix-core.h"
#include "../include/centrix.h"
#include "../include/terminal.h"
#include "../include/cpu.h"
#include "../include/vga.h"

MODULE("Centrix", "0.01a");

STRING SupportedOS[] =
{
    "CentrixOS",
    "AdamantineOS",
    "SteelOS",
};

struct CentrixCore Core;
VOID *
KernelInstall(STRING Name) {
    Core.OS_ID = NULL;
    Core.OS_Signature = NULL;

    Core.OS_Name = Name;
    return (Name);
}

DWORD 
Verify(VOID)
{
<<<<<<< HEAD
    terminal_init(SYSTEM_COLOR_GREEN, SYSTEM_COLOR_WHITE);
	terminal_clear_screen();
=======
    TerminalInit(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
	TerminalClearScreen();
>>>>>>> f17d39f86fcb43d487014e2a2e2af88ff7e7e48b

    SIZE Length = strlen(SupportedOS);
    SIZE i = 0;
    STRING OS_Name = Core.OS_Name;
    while (i < Length)
    {
        if (strcmp(OS_Name, SupportedOS[i]) == 0)
        {
<<<<<<< HEAD
            CENTRIX_INFO("\"%s\" is a valid Operating System.\n", os_name);
            CENTRIX_INFO("Starting \"%s\" OS kernel...\n\n", os_name);
=======
            TerminalPrintf("[CENTRIX]: \"%s\" is a valid Operating System.\n", OS_Name);
            TerminalPrintf("[CENTRIX]: Starting \"%s\" OS kernel...\n\n", OS_Name);
>>>>>>> f17d39f86fcb43d487014e2a2e2af88ff7e7e48b
            return (SUCCESS);
        } else {
            i++;
            if (i >= Length) 
            {
<<<<<<< HEAD
                CENTRIX_INFO("\"%s\" is not a valid Operating System...\n", os_name);
=======
                TerminalPrintf("[CENTRIX]: \"%s\" is not a valid Operating System...\n", OS_Name);
>>>>>>> f17d39f86fcb43d487014e2a2e2af88ff7e7e48b
                return (FAILURE);
            }
        }
    }
}
