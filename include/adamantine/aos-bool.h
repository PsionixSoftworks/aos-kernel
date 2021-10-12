#ifndef _AOS_BOOL_H
#define _AOS_BOOL_H

/* This can only be used in C. C++ already has a bool type built in */
#if !defined(__cplusplus)
typedef enum {false, true} bool;
#endif

/* Check if 'BOOLEAN_OPS' is defined elsewhere */
#ifndef BOOLEAN_OPS
#ifndef FALSE								// If not, check if the 'FALSE' macro is defined anywhere.
#define FALSE			0					// If not, define it here.
#endif	// !FALSE

#ifndef TRUE								// If not, check if the 'TRUE' macro is defined anywhere.
#define TRUE			1					// If not, define it here.
#endif	// !TRUE
#endif	// !BOOLEAN_OPS

#endif
