/*
 *  File: types.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef AOS_KERNEL_TYPES
#define AOS_KERNEL_TYPES

#include "limits.h"

// Define string type here:
#if defined(__cplusplus)
typedef const char *            string;
#else
typedef char *                  string;
#endif

// Define unsigned types:
typedef unsigned char           uint8_t;			// 8 bit unsigned integer.
typedef unsigned short          uint16_t;		    // 16 bit unsigned integer.
typedef unsigned int            uint32_t;		    // 32 bit unsigned integer.

// Define signed types:
typedef signed char			    int8_t;			    // 8 bit signed integer.
typedef signed short			int16_t;			// 16 bit signed integer.
typedef signed int				int32_t;			// 32 bit signed integer.

// Define size_t:
#if defined(__GNUC__) && defined(__SIZE_TYPE__)
typedef __SIZE_TYPE__           size_t;			    // Define size_t based on gcc.
#else
typedef uint32_t  				size_t;			    // Define size_t as a 32 bit unsigned integer.
#endif

// Define (unused) 64 bit types:
#ifdef SYS64
typedef unsigned long long	    uint64_t;		    // 64 bit unsigned integer (x64 ONLY!).
typedef signed long long 	    int64_t;			// 64 bit signed integer (x64 ONLY!).
#endif	// !SYS64

// Define string type:
#ifdef __cplusplus
typedef const char *            string;
#else
typedef char *                  string;
#endif

// Define other types:
typedef int8_t 				    byte;				// byte is an 8 bit unsigned integer.
typedef int16_t 				word;			    // word is a 16 bit unsigned integer.
typedef int32_t 		        dword;			    // dword is a 32 bit unsigned long.

typedef uint8_t                 ubyte;
typedef uint16_t                uword;
typedef uint32_t                udword;

// Define bool if we're using C:
#ifndef __cplusplus
typedef enum {false, true}	    bool;				// Define bool (C ONLY!).
#endif	// !__cplusplus

// Define kernel_types:
#if __KERNEL__
typedef char                    __kernel_only __kernel_char;
typedef string                  __kernel_only __kernel_string;

typedef int8_t                  __kernel_only __kernel_int8_t;
typedef int16_t                 __kernel_only __kernel_int16_t;
typedef int32_t                 __kernel_only __kernel_int32_t;
typedef uint8_t                 __kernel_only __kernel_uint8_t;
typedef uint16_t                __kernel_only __kernel_uint16_t;
typedef uint32_t                __kernel_only __kernel_uint32_t;

typedef float                   __kernel_only __kernel_float;
typedef double                  __kernel_only __kernel_double;

typedef void                    __kernel_only __kernel_void;
typedef void                    __kernel_only *__kernel_pvoid;
typedef bool                    __kernel_only __kernel_bool;
#endif
#endif 	// !ADAMANTINE_TYPES
