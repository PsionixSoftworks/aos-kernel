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

#include <adamantium/mutex.h>

uint8_t enabled = 0;

static inline void 
schedule_no_irq(void);

inline void 
mutex_lock(mutex* _mutex) 
{
	/* if the lock is locked, wait and set its locked state */
	while(_mutex->locked) schedule_no_irq();
	_mutex->locked = 1;
}

inline void 
mutex_unlock(mutex* _mutex) 
{
	/* this code can only be accessed by the holding thread, so unlock it */
	_mutex->locked = 0;
	schedule_no_irq();
}

static inline void 
schedule_no_irq(void) 
{
	if(!enabled)
		return;
	
	// Invoke system call to kernel interrupt:
	__asm__ volatile("int $0x2E");
	return;
}
