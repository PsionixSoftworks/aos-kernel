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

#include <backend/back.h>
#include <adamantine/aos-types.h>

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
#endif

// Define the module naming system for later use:
#ifndef ADAMANTINE_MODULE
#define ADAMANTINE_MODULE
#define MODULE(name, version) 	            static char *n = name; \
                                            static char *v = version;
#endif	// !MODULE_DESCRIPTOR

#define OS_NAME                             "AdamantineOS"
#define OS_SIGNATURE                        "{0:0:0:0~0}"
#define OS_MODULE_NAME                      n
#define OS_VERSION                          v

#ifndef __STANDARD_ATTRIBUTES__
#define __STANDARD_ATTRIBUTES__
#define PACKED				            __attribute__((__packed__))
#define USED					        __attribute__((__used__))
#define UNUSED				            __attribute__((__unused__))
#define HOT                             __attribute__((__hot__))
#define COLD                            __attribute__((__cold__))
#define DEPRECATED		                __attribute__((deprecated))
#define SECTION(name)	                __attribute__((section(name)))
#define ALIGN(x)                        __attribute__((aligned(x)))
#define _TEXT                           SECTION(".text")
#define _MULTIBOOT                      SECTION(".multiboot")
#define _RODATA                         SECTION(".rodata")
#define _DATA                           SECTION(".data")
#define _BSS                            SECTION(".bss")
#define ACCESS(mode)	                __attribute__((access(mode)))
#endif	// !__STANDARD_ATTRIBUTES__

/* Setters for types. */
#define SET_VOID(name)                  void    name
#define SET_BOOL(name)                  bool    name
#define SET_UBYTE(name)                 ubyte   name
#define SET_UWORD(name)                 uword   name
#define SET_UDWORD(name)                udword  name
#define SET_ULONG(name)                 ulong   name
#define SET_USHORT(name)                ushort  name
#define SET_BYTE(name)                  byte    name
#define SET_WORD(name)                  word    name
#define SET_DWORD(name)                 dword   name
#define SET_LONG(name)                  long    name
#define SET_SHORT(name)                 short   name
#define SET_SIZE(name)                  size_t  name
#define SET_CHAR(name)                  char    name
#define SET_STRING(name)                string  name
#define SET_FLOAT(name)                 float   name
#define SET_DOUBLE(name)                double  name
#define SET_STRUCT(name)                struct  name
#define SET_UNION(name)                 union   name

#ifdef __cplusplus
#define EXTERN                          extern "C"
#else
#define EXTERN                          extern
#endif
#endif	// !ADAMANTINE_STANDARD_DEFINITIONS