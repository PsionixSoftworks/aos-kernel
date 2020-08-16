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

#include "../types.h"
#include "../string.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct command_line 
{
    string *cmd_list;
};
typedef struct command_line command_t;

extern void command_line_init(void);
extern void parse_command(string cmd);

#if defined(__cplusplus)
}
#endif

#endif
