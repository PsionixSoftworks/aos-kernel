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

#ifndef ADAMANTINE_TYPES
#define ADAMANTINE_TYPES

#include "limits.h"

// Define signed types:
typedef signed char			                int8_t;			    // 8 bit signed integer.
typedef signed short			            int16_t;			// 16 bit signed integer.
typedef signed int				            int32_t;			// 32 bit signed integer.

// Define unsigned types:
typedef unsigned char 		                uint8_t;			// 8 bit unsigned integer.
typedef unsigned short 		                uint16_t;		    // 16 bit unsigned integer.
typedef unsigned int 			            uint32_t;		    // 32 bit unsigned integer.

// Define size_t:
#if defined(__GNUC__) && defined(__SIZE_TYPE__)
typedef __SIZE_TYPE__                       size_t;			    // Define size_t based on gcc.
#else
typedef uint32_t  				            size_t;			    // Define size_t as a 32 bit unsigned integer.
#endif

// Define (unused) 64 bit types:
#ifdef SYS64
typedef unsigned long long	                uint64_t;		    // 64 bit unsigned integer (x64 ONLY!).
typedef signed long long 	                int64_t;			// 64 bit signed integer (x64 ONLY!).
#endif	// !SYS64

// Define string type:
#ifdef __cplusplus
typedef const char *                    string;
#else
typedef char *                          string;
#endif

// Define other types:
typedef int8_t 					        byte;				// byte is an 8 bit signed integer.
typedef int16_t 				        word;			    // word is a 16 bit signed integer.
typedef int32_t 		                dword;			    // dword is a 32 bit signed integer.
typedef uint8_t                         ubyte;              // ubyte is an 8 bit unsighed integer.
typedef uint16_t                        uword;              // uword is a 16 bit unsigned integer.
typedef uint32_t                        udword;             // udword is a 32 bit unsigned integer.

// Define bool if we're using C:
#ifndef __cplusplus
typedef enum {false, true}	                bool;				// Define bool (C ONLY!).
#endif	// !__cplusplus

#endif 	// !ADAMANTINE_TYPES
