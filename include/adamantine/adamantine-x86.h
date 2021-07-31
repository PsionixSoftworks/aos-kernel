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

/* Define 'INFINITY' as the maximum 32-bit value */
#ifndef INFINITY
#define INFINITY    	0xFFFFFFFF     					// Max 32-bit value
#endif

/* Check if Adamantine Standard Types were defined */
#ifndef ADAMANTINE_STYPES
#define ADAMANTINE_STYPES

/* Define 'BYTE' */
#ifndef _BYTE											// Perhaps 'BYTE' was defined elsewhere. If not,
#define _BYTE											// define it,
typedef char			BYTE;							// then set its type to unsigned char.
#endif	// !BYTE

/* Define 'WORD' */
#ifndef _WORD											// Perhaps 'WORD' was defined elsewhere. If not,
#define _WORD											// define it,
typedef short			WORD;							// then set its type to unsigned short.
#endif	// !WORD

/* Define 'DWORD' */
#ifndef _DWORD											// Perhaps 'DWORD' was defined elsewhere. If not,
#define _DWORD											// define it,
typedef long			DWORD;							// then set its type to unsigned long.
#endif	// !DWORD

/* Define 'UBYTE' */
#ifndef _UBYTE											// Perhaps 'UBYTE' was defined elsewhere. If not,
#define _UBYTE											// define it,
typedef unsigned char	UBYTE;							// then set its type to unsigned BYTE.
#endif	// !UBYTE

/* Define 'UWORD' */
#ifndef _UWORD											// Perhaps 'UWORD' was defined elsewhere. If not,
#define _UWORD											// define it,
typedef unsigned short	UWORD;							// then set its type to unsigned WORD.
#endif	// !UWORD

/* Define 'UDWORD' */
#ifndef _UDWORD											// Perhaps 'UDWORD' was defined elsewhere. If not,
#define _UDWORD											// define it,
typedef unsigned long	UDWORD;							// then set its type to unsigned DWORD.
#endif	// !UDWORD

/* Define 'UINTPTR' */
#ifndef _UINTPTR
#define _UINTPTR
typedef unsigned int 	UINTPTR;
#endif	// !UINTPTR
#endif	// !ADAMANTINE_STYPES
#endif	// !_ADAMANTINE_X86_H
