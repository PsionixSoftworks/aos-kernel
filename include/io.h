#ifndef ADAMANTINE_IO
#define ADAMANTINE_IO

// Include files go here:
#include "types.h"
#include "string.h"
#include "input.h"
#include "output.h"

#if KERNEL32

#if defined(__cplusplus)
extern "C" {
#endif

// Declare io functions:
extern void io_wait(void);

#if defined(__cplusplus)
}
#endif

#endif
#endif	// !ADAMANTINE_IO
