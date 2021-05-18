/*
 *  File: system.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/system/system.h>
#include <kernel/system/terminal.h>
#include <kernel/cpu.h>
#include <string.h>

struct system_logger
{
    char                    *message[1024];
    uint8_t                 exit;
};

static uint16_t idx = 0;
struct system_logger *logger;

static inline void
log_warning(char *msg)
{
    logger->message[idx++] = msg;
    logger->exit = 0;
}

static inline void
log_error(char *msg)
{
    logger->message[idx++] = msg;
    logger->exit = 1;
}

void
system_init(void)
{
    memset(logger->message, 0, 1024);
}

void
handle_dispatched_message(uint8_t severity, char *msg)
{
    if (severity == SOME_SEVERITY)
        log_warning(msg);
    if (severity == FULL_SEVERITY)
        log_error(msg);
    
    if (logger->exit)
    {
        terminal_printf("System has reached a fatal error and cannot continue execution of the kernel.\n");
        terminal_printf("We are sorry for the inconvenience.\n");

        cpu_halt();
    }
}

char *
get_system_log(uint32_t index)
{
    if (logger->message[index] == NULL)
        return "";
    if (index >= 1024)
    {
        terminal_printf("Error: Logger cannot be a null pointer  (i.e. less than 0 or exceed 1024) or\nexceed 1024 entries at a time...\n");
        return "";
    }
    return (logger->message[index]);
}
