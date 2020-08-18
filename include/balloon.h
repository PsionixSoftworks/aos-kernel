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
#include "aos-defs.h"
#include "types.h"

// Define the "balloon" memory sizes:
#define BALLOON_SIZE_1			1024								// 1KB
#define BALLOON_SIZE_2			2048								// 2KB
#define BALLOON_SIZE_4			4096								// 4KB
#define BALLOON_SIZE_8			8192								// 8KB
#define BALLOON_SIZE_16			16384								// 16KB
#define BALLOON_SIZE_32			32768								// 32KB
#define BALLOON_SIZE_64			65536								// 64KB
#define BALLOON_SIZE_MIN		BALLOON_SIZE_1						// Minimum size is 1KB.
#define BALLOON_SIZE_MAX		BALLOON_SIZE_64						// Maximum size is 64KB.

typedef struct AOS_Balloon Balloon_t;

// Define the balloon type struct:
struct AOS_Balloon 
{
	SIZE 				Size;										// The size of the current index.
	UDWORD 				Capacity;									// The capacity of the balloon.
	UDWORD 				*Buffer;
	UDWORD 				*Data;
	BOOL 				Valid;
} PACKED;

// Declare global functions:
EXTERN 	SET_BOOL(BalloonInit(SIZE Size));							// Initialize the balloon memory type.
EXTERN 	SET_UDWORD(*BalloonInflate(UDWORD Amount, UDWORD Value));	// Inflate balloon data.
EXTERN 	SET_UDWORD(*BalloonPop(VOID));								// Pop the balloon off the stack.
EXTERN 	SET_VOID(BalloonCleanup(VOID));								// Cleanup when no longer needed.
EXTERN 	SET_SIZE(BalloonSize(VOID));								// Get the balloon memory size.
EXTERN 	SET_SIZE(BalloonCapacity(VOID));

#endif	// !ADAMANTINE_BALLOON
