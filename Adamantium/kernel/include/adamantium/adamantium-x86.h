/*
 * File: adamantine-x86.h
 * Author: Vincent C.
 * Description:
 * Used as a base for all subsequent files that utilize AOS32,
 * both in the kernel and in user space.
 *
 * Copyright (C) 2018-2021, Psionix Softworks LLC.
 * 
 */

#ifndef _ADAMANTINE_X86_H
#define _ADAMANTINE_X86_H

#include <kernel/version.h>
#include <aos-base.h>

/* Define 'INFINITY' as the maximum 32-bit value */
#ifndef INFINITY
#define INFINITY    	0xFFFFFFFF     					// Max 32-bit value
#endif

/* Check if Adamantine Standard Types were defined */
#ifndef ADAMANTINE_STYPES
#define ADAMANTINE_STYPES

/* Define 'CONST' */
#ifndef CONST
#define CONST 			const;
#endif

/* Define 'VOID' */
#ifndef VOID
#define VOID 			void
#endif

#ifndef VOIDPTR
#define VOIDPTR			void*
#endif

/* Define 'BYTE' */
#ifndef BYTE											// Perhaps 'BYTE' was defined elsewhere. If not,
#define BYTE			unsigned char					// define it.
#endif	// BYTE

/* Define 'WORD' */
#ifndef WORD											// Perhaps 'WORD' was defined elsewhere. If not,
#define WORD			unsigned short					// define it.
#endif	// WORD

/* Define 'DWORD' */
#ifndef DWORD											// Perhaps 'DWORD' was defined elsewhere. If not,
#define DWORD			unsigned int					// define it.
#endif	// DWORD

/* Define 'UINTPTR' */
#ifndef UINTPTR
#define UINTPTR			unsigned int
#endif	// UINTPTR
#endif	// !ADAMANTINE_STYPES
#endif	// !_ADAMANTINE_X86_H
