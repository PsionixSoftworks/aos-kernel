/*
 *  File: limits.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _ADAMANTINE_LIMITS_H
#define _ADAMANTINE_LIMITS_H

/* size of "char" type. */
#define SIGNED_CHAR_SIZE_MIN                0x7F - 0xFF
#define SIGNED_CHAR_SIZE_MAX                SIGNED_CHAR_SIZE_MIN + 0xFF
#define UNSIGNED_CHAR_SIZE_MIN              (SIGNED_CHAR_SIZE_MIN + 0x7F) + 1
#define UNSIGNED_CHAR_SIZE_MAX              (SIGNED_CHAR_SIZE_MAX + 0x7F) + 1

/* size of "short" type. */
#define SIGNED_SHORT_SIZE_MIN               0x7FFF - 0xFFFF
#define SIGNED_SHORT_SIZE_MAX               SIGNED_SHORT_SIZE_MIN + 0xFFFF
#define UNSIGNED_SHORT_SIZE_MIN             (SIGNED_SHORT_SIZE_MIN + 0x7FFF) + 1
#define UNSIGNED_SHORT_SIZE_MAX             (SIGNED_SHORT_SIZE_MAX + 0x7FFF) + 1

/* size of "uint32_t" type. */
#define SIGNED_INT_SIZE_MIN                 0x7FFFFFFF - 0xFFFFFFFF
#define SIGNED_INT_SIZE_MAX                 SIGNED_INT_SIZE_MIN + 0xFFFFFFFF
#define UNSIGNED_INT_SIZE_MIN               (SIGNED_INT_SIZE_MIN + 0x7FFFFFFF) + 1
#define UNSIGNED_INT_SIZE_MAX               (SIGNED_INT_SIZE_MAX + 0x7FFFFFFF) + 1 

/* size of "long long" type. */
#if defined(__AOS64__)
#define SIGNED_LONG_LONG_SIZE_MIN           -0x7FFFFFFFFFFFFFFF - 0xFFFFFFFFFFFFFFFF
#define SIGNED_LONG_LONG_SIZE_MAX           SIGNED_LONG_LONG_SIZE_MIN + 0xFFFFFFFFFFFFFFFF
#define UNSIGNED_LONG_LONG_SIZE_MIN         (SIGNED_LONG_LONG_SIZE_MIN + 0x7FFFFFFFFFFFFFFF) + 1
#define UNSIGNED_LONG_LONG_SIZE_MAX         (SIGNED_LONG_LONG_SIZE_MAX + 0x7FFFFFFFFFFFFFFF) + 1
#endif

/* size of "int8_t" type. */
#define INT8_SIZE_MIN                       SIGNED_CHAR_SIZE_MIN
#define INT8_SIZE_MAX                       SIGNED_CHAR_SIZE_MAX
#define UINT8_SIZE_MIN                      UNSIGNED_CHAR_SIZE_MIN
#define UINT8_SIZE_MAX                      UNSIGNED_CHAR_SIZE_MAX

/* size of "int16_t" type. */
#define INT16_SIZE_MIN                       SIGNED_SHORT_SIZE_MIN
#define INT16_SIZE_MAX                       SIGNED_SHORT_SIZE_MAX
#define UINT16_SIZE_MIN                      UNSIGNED_SHORT_SIZE_MIN
#define UINT16_SIZE_MAX                      UNSIGNED_SHORT_SIZE_MAX

/* size of "int32_t" type. */
#define INT32_SIZE_MIN                       SIGNED_INT_SIZE_MIN
#define INT32_SIZE_MAX                       SIGNED_INT_SIZE_MAX
#define UINT32_SIZE_MIN                      UNSIGNED_INT_SIZE_MIN  
#define UINT32_SIZE_MAX                      UNSIGNED_INT_SIZE_MAX

#endif  // !_ADAMANTINE_LIMITS_H
