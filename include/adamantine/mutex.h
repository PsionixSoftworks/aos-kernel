// WARNING: !!! THIS FILE MAY BE MODIFIED AND/OR REMOVED SOON !!!

/** @author Levente Kurusa <levex@linux.com> **/
/** Modified & updated by Vincent C. **/
#ifndef _MUTEX_H
#define _MUTEX_H

#include <stdint.h>

typedef struct {
	uint8_t					locked;
} mutex;

#define DEFINE_MUTEX(name) static mutex name = { .locked=0 };

extern void mutex_lock(mutex	*m);
extern void mutex_unlock(mutex* m);

#endif	// !_MUTEX_H
