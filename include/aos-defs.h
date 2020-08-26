/*
 *  File: aos-defs.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_STANDARD_DEFINITIONS
#define ADAMANTINE_STANDARD_DEFINITIONS

#include "types.h"
#include "string.h"

#define OS_NAME                             "AdamantineOS"
#define OS_VERSION                          "0.04a"
#define OS_SIGNATURE                        "{0:0:0:0~0}"

// Define the boolean operators true and false:
#ifndef BOOLEAN_OPS

#ifndef FALSE
#define FALSE								0
#endif

#ifndef TRUE
#define TRUE								1
#endif
#endif

// Define Adamantine API macros:
#ifndef ADAMANTINE_MACROS
#define FAILSAFE
#define NULL								(void *)0
#define FAILURE								FALSE
#define SUCCESS								TRUE
#define AOS_BASE_CNTRL                      0xCE0
#endif

// Define the module naming system for later use:
#ifndef ADAMANTINE_MODULE
#define ADAMANTINE_MODULE
#define MODULE(name, version) 	        
#endif	// !MODULE_DESCRIPTOR

#ifndef __STANDARD_ATTRIBUTES__
#define __STANDARD_ATTRIBUTES__
#define PACKED				            __attribute__((__packed__))
#define USED					        __attribute__((__used__))
#define UNUSED				            __attribute__((__unused__))
#define HOT                             __attribute__((__hot__))
#define COLD                            __attribute__((__cold__))
#define DEPRECATED		                __attribute__((deprecated))
#define SECTION(name)	                __attribute__((section(name)))
#define _TEXT                           SECTION(".text")
#define _MULTIBOOT                      SECTION(".multiboot")
#define _RODATA                         SECTION(".rodata")
#define _DATA                           SECTION(".data")
#define _BSS                            SECTION(".bss")
#define ACCESS(mode)	                __attribute__((access(mode)))
#endif	// !__STANDARD_ATTRIBUTES__

/* Define common types. */
#define VOID                            void
#define BOOL                            bool
#define UBYTE                           uint8_t
#define UWORD                           uint16_t
#define UDWORD                          uint32_t
#define ULONG                           unsigned long
#define USHORT                          unsigned short
#define BYTE                            int8_t
#define WORD                            int16_t
#define DWORD                           int32_t
#define LONG                            signed long
#define SHORT                           signed short
#define SIZE                            size_t
#define CHAR                            char
#define STRING                          string
#define FLOAT                           float
#define DOUBLE                          double
#define STRUCT                          struct
#define UNION                           union

/* Setters for types. */
#define SET_VOID(name)                  VOID    name
#define SET_BOOL(name)                  BOOL    name
#define SET_UBYTE(name)                 UBYTE   name
#define SET_UWORD(name)                 UWORD   name
#define SET_UDWORD(name)                UDWORD  name
#define SET_ULONG(name)                 ULONG   name
#define SET_USHORT(name)                USHORT  name
#define SET_BYTE(name)                  BYTE    name
#define SET_WORD(name)                  WORD    name
#define SET_DWORD(name)                 DWORD   name
#define SET_LONG(name)                  LONG    name
#define SET_SHORT(name)                 SHORT   name
#define SET_SIZE(name)                  SIZE    name
#define SET_CHAR(name)                  CHAR    name
#define SET_STRING(name)                STRING  name
#define SET_FLOAT(name)                 FLOAT   name
#define SET_DOUBLE(name)                DOUBLE  name
#define SET_STRUCT(name)                STRUCT  name
#define SET_UNION(name)                 UNION   name

#define EXTERN                          extern

#define PACK(name)                      PACKED name

#endif	// !ADAMANTINE_STANDARD_DEFINITIONS
