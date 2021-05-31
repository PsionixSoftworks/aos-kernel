/*
 *  File: pit.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _ADAMANTINE_PIT_H
#define _ADAMANTINE_PIT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <stdint.h>

/* Define the PIT macros */
#define PIT_BASE_FREQ       0x1234DC					// The frequency of the PIT (1193180MHz)
#define PIT_CHANNEL_0       0x40						// Used for the timer
#define PIT_CHANNEL_1       0x41						// Refresh DRAM (obsolete)
#define PIT_CHANNEL_2       0x42						// PC Speaker
#define PIT_CMD_PORT        0x43						// Command port

/* Function Templates */
extern void pit_init(uint32_t);							// Initialize the Programmable Interval Timer
extern void pit_install(int);							// Install the PIT
extern void pit_wait(int);								// Tell the PIT to wait

#endif	// !_ADAMANTINE_PIT_H
