/** @author Levente Kurusa <levex@linux.com> **/
#ifndef _MUTEX_
#define _MUTEX_

#include "types.h"

typedef struct {
	uint8_t locked;
} mutex;

#define DEFINE_MUTEX(name) static mutex name = { .locked=0 };

extern void mutex_lock(mutex* m);
extern void mutex_unlock(mutex* m);

#endif	// !_MUTEX_
