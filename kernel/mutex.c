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

#include <adamantine/mutex.h>

MODULE("Mutex", "0.01a");

ubyte Enabled = 0;

static inline void 
schedule_no_irq(void);

inline void 
mutex_lock(mutex* m) 
{
	/* if the lock is locked, wait and set its locked state */
	while(m->locked) schedule_no_irq();
	m->locked = 1;
}

inline void 
mutex_unlock(mutex* m) 
{
	/* this code can only be accessed by the holding thread, so unlock it */
	m->locked = 0;
	schedule_no_irq();
}

static inline void 
schedule_no_irq(void) 
{
	if(!Enabled)
		return;
	
	// Invoke system call to kernel interrupt:
	asm volatile("INT $0x2E");
	return;
}
