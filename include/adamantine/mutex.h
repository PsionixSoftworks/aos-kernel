/** @author Levente Kurusa <levex@linux.com> **/
/** Modified & updated by Vincent C. **/
#ifndef _mutex_
#define _mutex_

#include <stdint.h>

typedef struct {
	uint8_t						locked;
} mutex;

#define DEFINE_mutex(name) static mutex name = { .locked=0 };

void mutex_lock(mutex	*m);
void mutex_unlock(mutex* m);

#endif	// !_mutex_
