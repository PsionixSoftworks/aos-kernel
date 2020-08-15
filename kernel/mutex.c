#include "../include/mutex.h"
#include "../include/aos-defs.h"

MODULE("mutex", "0.01a");

uint8_t __enabled = 0;

static void schedule_noirq(void);

void 
mutex_lock(mutex* m) 
{
	/* if the lock is locked, wait and set its locked state */
	while(m->locked) schedule_noirq();
	m->locked = 1;
}

void 
mutex_unlock(mutex* m) 
{
	/* this code can only be accessed by the holding thread, so unlock it */
	m->locked = 0;
	schedule_noirq();
}

static void 
schedule_noirq(void) 
{
	if(!__enabled)
		return;
	
	// Invoke system call to kernel interrupt:
	asm volatile("int $0x2E");
	return;
}
