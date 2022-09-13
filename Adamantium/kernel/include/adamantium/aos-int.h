#ifndef _ADAMANTIUM_AOS_INT_H
#define _ADAMANTIUM_AOS_INT_H

#include <limits.h>
#include <stdint.h>

/* Signed Integers */
typedef signed char		__aos_int8_t;				// 8-bit signed integer
typedef signed short	__aos_int16_t;				// 16-bit signed integer
typedef signed int		__aos_int32_t;				// 32-bit signed integer

/* Unsigned Integers: */
typedef unsigned char	__aos_uint8_t;				// 8-bit unsigned integer
typedef unsigned short	__aos_uint16_t;				// 16-bit unsigned integer
typedef unsigned int	__aos_uint32_t;				// 32-bit unsigned integer

/* Integer Pointer */
typedef signed int 		__aos_intptr_t;				// Signed integer pointer
typedef unsigned int	__aos_uintptr_t;			// Unsigned integer pointer

#endif	// _AOS_INT_H
