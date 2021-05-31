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
#include <kernel/cpu.h>
#include <adamantine/tty.h>
#include <compiler.h>

#include <string.h>
#include <stddef.h>

/* Define the system logger struct */
struct system_logger
{
    char                    *message[1024];             // Message to store in the array.
    uint8_t                 exit;                       // Exit status
};

/* Declare static varibles */
static uint16_t idx = 0;                                // The message index
struct system_logger *logger;                           // Pointer to the logger struct

/* Logs a warning then exits */
static inline void
log_warning(char *msg)
{
    logger->message[idx++] = msg;
    logger->exit = 0;
}

/* Logs an error then exits */
static inline void
log_error(char *msg)
{
    logger->message[idx++] = msg;
    logger->exit = 1;
}

/* Initialize the system */
void
system_init(void)
{
    /* Clear messages to zero */
    memset(logger->message, 0, 1024);
}

/* Handle the dispatched message */
void
handle_dispatched_message(uint8_t severity, char *msg)
{
    if (severity == SOME_SEVERITY)                      // If we're logging a warning,
        log_warning(msg);                               // print it as a warning
    if (severity == FULL_SEVERITY)                      // If we're logging an error,
        log_error(msg);                                 // print it as an error
    
    /* If we received an exit */
    if (logger->exit)
    {
        /* Log to the terminal a fatal error */
        tty_printf("System has reached a fatal error and cannot continue execution of the kernel.\n");
        tty_printf("We are sorry for the inconvenience.\n");

        /* Halt the CPU to prevent any damage or loss of data */
        cpu_halt();
    }
}

/* Get a log at a specified index */
char *
get_system_log(uint32_t index)
{
    if (logger->message[index] == NULL)                 // Make sure the entry is valid
        return "";
    if (index >= 1024)                                  // Keep it within the bounds of the array
    {
        tty_printf("Error: Logger cannot be a null pointer  (i.e. less than 0 or exceed 1024) or\nexceed 1024 entries at a time...\n");
        return "";
    }
    return (logger->message[index]);
}
