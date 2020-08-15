#ifndef SYSTEM_TIMER
#define SYSTEM_TIMER

#include "types.h"

#if KERNEL32

#if defined(__cplusplus)
extern "C" {
#endif

extern void timer_init(uint32_t frequency);

#if defined(__cplusplus)
}
#endif

#endif
#endif	// !SYSTEM_TIMER
