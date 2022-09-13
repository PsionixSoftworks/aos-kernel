#ifndef _ADAMANTINE_TYPES_H
#define _ADAMANTINE_TYPES_H

#ifndef SYS_TYPES_DEFINED
#define SYS_TYPES_DEFINED   1
#include <sys/types.h>
#endif

/* Check if the '_KERNEL_T_' type has been defined */
#ifndef _KERNEL_T_										// If it hasn't
#define _KERNEL_T_										// define it,
typedef void kernel_t;									// and create 'kernel_t' type
#endif	// !_KERNEL_T_

#endif	// !_ADAMANTINE_TYPES_H
