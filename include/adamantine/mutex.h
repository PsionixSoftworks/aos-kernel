/** @author Levente Kurusa <levex@linux.com> **/
/** Modified & updated by Vincent C. **/
#ifndef _MUTEX_H
#define _MUTEX_H

#include <stdint.h>

typedef struct {
	uint8_t					locked;
} mutex;

#define DEFINE_MUTEX(name) static mutex name = { .locked=0 };

void mutex_lock(mutex	*m);
void mutex_unlock(mutex* m);

#endif	// !_MUTEX_H
