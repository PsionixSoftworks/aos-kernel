/*
 *  File: cmd.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _COMMAND_
#define _COMMAND_

#include "../aos-defs.h"
#include "../types.h"
#include "../string.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct CommandLine 
{
    STRING              *CMD_List;
};
typedef struct CommandLine Command_t;

EXTERN  VOID (CommandLineInit(VOID));
EXTERN  UBYTE (ParseCommand(STRING CMD));

#if defined(__cplusplus)
}
#endif

#endif
