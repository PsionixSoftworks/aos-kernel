/*
 *  File: balloon.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <kernel/memory/balloon.h>
#include <kernel/memory/mm.h>
#include <kernel/system/terminal.h>
#include <adamantine/mutex.h>

MODULE("Balloon", "0.01a");

static balloon_t balloon;

bool
balloon_init(size_t size) 
{
	balloon.valid = 	
	(
		(size == BALLOON_SIZE_MIN)	||
		(size == BALLOON_SIZE_1) 	||
		(size == BALLOON_SIZE_2) 	||
		(size == BALLOON_SIZE_4) 	||
		(size == BALLOON_SIZE_8) 	||
		(size == BALLOON_SIZE_16) 	||
		(size == BALLOON_SIZE_32) 	||
		(size == BALLOON_SIZE_64)	||
		(size == BALLOON_SIZE_MAX)
	);
	if (!balloon.valid) 
	{
		//_PANIC("balloon memory size must be one of the supported values!");
		return (-1);
	}

	// Allocate a specified balloon size for the data structure.
	// This code should only be reachable if the size is one of the macro's.
	balloon.buffer = (uint32_t *)malloc(size);
	balloon.size = size;

	return (0);
}

uint32_t *
balloon_inflate(uint32_t amount, uint32_t value) 
{
	if (amount > balloon.capacity) 
	{
		uint32_t *result = balloon_pop();
		return (result);
	}
	balloon.data = memset(balloon.buffer, value, balloon.size);

	return (0);
}

void
balloon_cleanup(void) 
{
	if ((balloon.size <= BALLOON_SIZE_MIN) || balloon.size > BALLOON_SIZE_MAX)
		return;
	free(balloon.buffer);
}

uint32_t *
balloon_pop(void) 
{
	return (balloon.data);
}

size_t
balloon_size(void)
{
	return (balloon.size);
}

size_t
balloon_capacity(void)
{
	return (balloon.capacity);
}
