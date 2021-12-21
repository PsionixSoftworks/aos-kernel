// WARNING: !!! THIS FILE MAY BE MODIFIED AND/OR REMOVED SOON !!!

/** @author Levente Kurusa <levex@linux.com> **/
/** Modified & updated by Vincent C. **/
#ifndef _MUTEX_H
#define _MUTEX_H

#define _USES_MACROS

#include <adamantine/aos-defs.h>
#include <macros.h>

typedef struct {
	uint8_t					locked;
} mutex;

#define DEFINE_MUTEX(name) static mutex name = { .locked=0 };

__GLOBAL KERNEL_API void mutex_lock(mutex* m);
__GLOBAL KERNEL_API void mutex_unlock(mutex* m);

#endif	// !_MUTEX_H
