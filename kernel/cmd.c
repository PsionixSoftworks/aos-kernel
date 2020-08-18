/*
 *  File: cmd.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/cmd/cmd.h"
#include "../include/terminal.h"

MODULE("Command", "0.01a");

Command_t Command;

VOID 
CommandLineInit(VOID) 
{
    Command.CMD_List[0] = "test";
}

UBYTE
ParseCommand(STRING CMD) 
{
    for (UBYTE i = 0; i < sizeof(UBYTE); i++) 
    {
        if (CMD == Command.CMD_List[i])
            return (1);
    }
    return (0);
}
