#ifndef _INTERRUPT_REQUESTS_
#define _INTERRUPT_REQUESTS_

#include "types.h"

#if KERNEL32

#if defined(__cplusplus)
extern "C" {
#endif

extern bool are_interrupts_enabled(void);
extern unsigned long save_irqdisable(void);
extern void irq_restore(unsigned long flags);
extern void clear_interrupts(void);

#if defined(__cplusplus)
}
#endif

#endif
#endif
