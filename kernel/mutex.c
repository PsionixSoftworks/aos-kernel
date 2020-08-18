/*
 *  File: mutex.c
 *  Author: Levente Kurusa
 *  Modified By: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/mutex.h"
#include "../include/aos-defs.h"

MODULE("Mutex", "0.01a");

UBYTE Enabled = 0;

static VOID 
ScheduleNoIRQ(VOID);

VOID 
MutexLock(Mutex* m) 
{
	/* if the lock is locked, wait and set its locked state */
	while(m->Locked) ScheduleNoIRQ();
	m->Locked = 1;
}

VOID 
MutexUnlock(Mutex* m) 
{
	/* this code can only be accessed by the holding thread, so unlock it */
	m->Locked = 0;
	ScheduleNoIRQ();
}

static VOID 
ScheduleNoIRQ(VOID) 
{
	if(!Enabled)
		return;
	
	// Invoke system call to kernel interrupt:
	asm volatile("INT $0x2E");
	return;
}
