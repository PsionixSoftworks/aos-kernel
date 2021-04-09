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

#ifndef _AOS_DEFS_H
#define _AOS_DEFS_H

#include <adamantine/version.h>
#include <stdint.h>

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
#ifndef NULL
#define NULL								0
#endif
#define NULL_PTR                            (void *)0
#define NULL_STR                            ""
#define NULL_TERM                           '\0'
#define FAILURE								((void *)FALSE)
#define SUCCESS								((void *)TRUE)
#define __AOS_API                           
#endif

// Define the module naming system for later use:
#ifndef ADAMANTINE_MODULE
#define ADAMANTINE_MODULE
#define MODULE(a, b)
#endif	// !MODULE_DESCRIPTOR

#if defined(__GNUC__) && __GNUC__ > 3
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
#define _RODATA                         SECTION(".rodata")
#define _DATA                           SECTION(".data")
#define _BSS                            SECTION(".bss")
#define ACCESS(mode)	                __attribute__((access(mode)))
#endif	// !__STANDARD_ATTRIBUTES__
#endif

/* Setters for types. */
#define SET_VOID(name)                  void name
#define SET_BOOL(name)                  bool name
#define SET_uint8_t(name)               uint8_t name
#define SET_uint16_t(name)              uint16_t name
#define SET_uint32_t(name)              uint32_t name
#define SET_unsigned long(name)         unsigned long name
#define SET_USHORT(name)                ushort name
#define SET_BYTE(name)                  uint8_t name
#define SET_WORD(name)                  word name
#define SET_DWORD(name)                 dword name
#define SET_LONG(name)                  long name
#define SET_SHORT(name)                 short name
#define SET_SIZE(name)                  size_t name
#define SET_CHAR(name)                  char name
#define SET_STRING(name)                char *name
#define SET_FLOAT(name)                 float name
#define SET_DOUBLE(name)                double name
#define SET_STRUCT(name)                struct name
#define SET_UNION(name)                 union name

#ifdef __cplusplus
#define EXTERN                          extern "C"
#else
#define EXTERN                          extern
#endif

#if !defined( CGUARDS ) && defined( __cplusplus )
#define CGUARDS
#define CGUARD_BEGIN                    extern "C" {
#define CGUARD_END                      }
#else
#define CGUARD_BEGIN
#define CGUARD_END
#endif
#endif	// !_AOS_DEFS_H
