/*
 *  File: io.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_IO
#define ADAMANTINE_IO

// Include files go here:
#include "aos-defs.h"
#include "types.h"
#include "string.h"
#include "input.h"
#include "output.h"

typedef struct aos_input 	input_t;
typedef struct aos_output 	output_t;
typedef struct aos_io 		io_t;

struct
aos_input
{
	const ubyte(*inb)(uword);
	const uword(*inw)(uword);
	const udword(*inl)(uword);
};

struct
aos_output
{
	const void(*outb)(uword, ubyte);
	const void(*outw)(uword, uword);
	const void(*outl)(uword, udword);
};

struct
aos_io
{
	input_t in;
	output_t out;
};

// Declare io functions:
EXTERN void (io_wait(void));

#endif	// !ADAMANTINE_IO
