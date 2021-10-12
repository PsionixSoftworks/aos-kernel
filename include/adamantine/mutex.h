// WARNING: !!! THIS FILE MAY BE MODIFIED AND/OR REMOVED SOON !!!

/** @author Levente Kurusa <levex@linux.com> **/
/** Modified & updated by Vincent C. **/
#ifndef _MUTEX_H
#define _MUTEX_H

#define _USES_MACROS

#include <common.h>
#include <adamantine/aos-defs.h>
#include <kernel/kernel.h>

typedef struct {
	uint8_t					locked;
} mutex;

#define DEFINE_MUTEX(name) static mutex name = { .locked=0 };

EXTERN KERNEL_API __GLOBAL _PROTO(void mutex_lock, (mutex	*m)	);
EXTERN KERNEL_API __GLOBAL _PROTO(void mutex_unlock, (mutex* m)	);

#endif	// !_MUTEX_H
