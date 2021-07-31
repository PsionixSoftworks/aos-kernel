/*
 * File: aos-defs.h
 * Author: Vincent C.
 * Description:
 * Commonly used macros.
 *
 * Copyright (C) 2018-2021, Psionix Softworks LLC.
 * 
 */

#ifndef _AOS_DEFS_H
#define _AOS_DEFS_H

#include <stdint.h>

/* Check if 'BOOLEAN_OPS' is defined elsewhere */
#ifndef BOOLEAN_OPS
#ifndef FALSE								// If not, check if the 'FALSE' macro is defined anywhere.
#define FALSE			0					// If not, define it here.
#endif	// !FALSE

#ifndef TRUE								// If not, check if the 'TRUE' macro is defined anywhere.
#define TRUE			1					// If not, define it here.
#endif	// !TRUE
#endif	// !BOOLEAN_OPS

/* Check if Adamantine macros are defined */
#ifndef ADAMANTINE_MACROS

/* Check if 'NULL' was previously defined */
#ifndef NULL
#ifdef __cplusplus							// If it wasn't and we're using C
#define NULL		0						// just define it as '0'
#else										// otherwise,
#define NULL			((void *)0)			// define it as a null void ptr
#endif

#ifndef FAILURE								// Check if 'FAILURE' was defined. If not,
#define FAILURE			((void *)FALSE)		// define it as a 'FALSE' void ptr.
#endif	// !FAILURE

#ifndef SUCCESS								// Check if 'SUCCESS' was defined. If not,
#define SUCCESS			((void *)TRUE)		// define it as a 'TRUE' void ptr.
#endif	// !SUCCESS
#endif	// !NULL
#endif	// !ADAMANTINE_MACROS

/* Define a quick way to use 'extern "C"' on C++ files */
#ifdef __cplusplus
#define EXTERN 			extern "C"			// If C++ is defined, set 'EXTERN' to mean 'extern "C"'.
#else
#define EXTERN 			extern				// Otherwise, it's just extern...
#endif
#endif