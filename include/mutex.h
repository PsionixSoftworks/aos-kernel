/** @author Levente Kurusa <levex@linux.com> **/
#ifndef _MUTEX_
#define _MUTEX_

#include "aos-defs.h"
#include "types.h"

typedef struct {
	BYTE 				Locked;
} Mutex;

#define DEFINE_MUTEX(name) static Mutex name = { .Locked=0 };

EXTERN SET_VOID(MutexLock(Mutex	*M));
EXTERN SET_VOID(MutexUnlock(Mutex* M));

// TODO: Finish writing Mutex...

#endif	// !_MUTEX_
