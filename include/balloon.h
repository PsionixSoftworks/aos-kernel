/*
 *  File: balloon.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_BALLOON
#define ADAMANTINE_BALLOON

// Include files here:
#include "types.h"

// Define the "balloon" memory sizes:
#define BALLOON_SIZE_1			1024							// 1KB
#define BALLOON_SIZE_2			2048							// 2KB
#define BALLOON_SIZE_4			4096							// 4KB
#define BALLOON_SIZE_8			8192							// 8KB
#define BALLOON_SIZE_16			16384							// 16KB
#define BALLOON_SIZE_32			32768							// 32KB
#define BALLOON_SIZE_64			65536							// 64KB
#define BALLOON_SIZE_MIN		BALLOON_SIZE_1					// Minimum size is 1KB.
#define BALLOON_SIZE_MAX		BALLOON_SIZE_64					// Maximum size is 64KB.

// Declare global functions:
extern bool balloon_init(size_t size);							// Initialize the balloon memory type.
extern uint32_t *balloon_inflate(uint32_t amt, uint32_t val);	// Inflate balloon data.
extern uint32_t *balloon_pop(void);								// Pop the balloon memory type.
extern void balloon_cleanup(void);								// Cleanup when no longer needed.
extern size_t balloon_size(void);								// Get the balloon memory size.

// Define the balloon type struct:
struct aos_balloon 
{
	size_t size;												// The size of the current index.
	uint32_t capacity;											// The capacity of the balloon.
	uint32_t *bm_buffer;
	uint32_t *data;
	bool valid;
} __attribute__((packed));
typedef struct aos_balloon balloon_t;

#endif	// !ADAMANTINE_BALLOON
