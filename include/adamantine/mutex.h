/** @author Levente Kurusa <levex@linux.com> **/
#ifndef _mutex_
#define _mutex_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

typedef struct {
	byte 				locked;
} mutex;

#define DEFINE_mutex(name) static mutex name = { .locked=0 };

EXTERN void (mutex_lock(mutex	*m));
EXTERN void (mutex_unlock(mutex* m));

// TODO: Finish writing mutex...

#endif	// !_mutex_
