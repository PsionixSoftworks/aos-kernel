/*
 *  File: system.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _ADAMANTINE_SYSTEM_H
#define _ADAMANTINE_SYSTEM_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

// Includes go here:
#include <stdint.h>

/* Define message dispatcher severities */
enum msg_severity
{
    NO_SEVERITY,                                        // In other words, info
    SOME_SEVERITY,                                      // In other words, warning
    FULL_SEVERITY,                                      // In other words, error
};

/* Function Templates */
extern void system_init(void);                          // Initialize the system message dispatcher
extern void handle_dispatched_message(uint8_t, char *); // Dispatch the message
extern char *get_system_log(uint32_t);                  // Get a log at an index

#endif	// !_ADAMANTINE_SYSTEM_H
