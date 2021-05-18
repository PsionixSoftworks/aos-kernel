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
#ifndef NULL
#ifdef __cplusplus
#define NULL								((void *)0)
#else
#define NULL								0
#endif
#endif

#define FAILURE								((void *)FALSE)
#define SUCCESS								((void *)TRUE)
#define __AOS_API                           
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
#endif