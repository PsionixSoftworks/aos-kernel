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
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>
#include <kernel/input.h>
#include <kernel/output.h>

typedef struct aos_input 	input_t;
typedef struct aos_output 	output_t;
typedef struct aos_io 		io_t;

struct
aos_input
{
	uint8_t(*inb)(uint16_t);
	uint16_t(*inw)(uint16_t);
	uint32_t(*inl)(uint16_t);
};

struct
aos_output
{
	void(*outb)(uint16_t, uint8_t);
	void(*outw)(uint16_t, uint16_t);
	void(*outl)(uint16_t, uint32_t);
};

struct
aos_io
{
	input_t in;
	output_t out;
};

#if defined(__cplusplus)
extern "C" {
#endif

void io_wait(void);

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_IO
