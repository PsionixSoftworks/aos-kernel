#ifndef _ADAMANTINE_STDINT_H
#define _ADAMANTINE_STDINT_H       1

#include <limits.h>

/* Signed Integers */
typedef signed char     int8_t;							// 8-bit signed integer
typedef signed short    int16_t;						// 16-bit signed integer
typedef signed int      int32_t;						// 32-bit signed integer

/* Unsigned Integers: */
typedef unsigned char   uint8_t;						// 8-bit unsigned integer
typedef unsigned short  uint16_t;						// 16-bit unsigned integer
typedef unsigned int    uint32_t;						// 32-bit unsigned integer

/* Size Integer: */
typedef unsigned long   size_t;							// Size

/* Integer Pointer */
typedef int             intptr_t;						// Signed integer pointer
typedef unsigned int    uintptr_t;						// Unsigned integer pointer

#endif  // !_ADAMANTINE_STDINT_H
