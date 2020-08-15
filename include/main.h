#ifndef ADAMANTINE_MAIN
#define ADAMANTINE_MAIN

#if KERNEL32

#include "types.h"
#include "aos-defs.h"
#include "adamantine.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern void kmain(void);

#if defined(__cplusplus)
}
#endif

#endif

#endif	// !ADAMANTINE_MAIN
