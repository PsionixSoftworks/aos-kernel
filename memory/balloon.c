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

#include "../include/balloon.h"
#include "../include/mem-util.h"
#include "../include/mutex.h"
#include "../include/terminal.h"

MODULE("Balloon", "0.01a");

static Balloon_t Balloon;

BOOL
BalloonInit(SIZE Size) 
{
	Balloon.Valid = 	
	(
		(Size == BALLOON_SIZE_MIN)	||
		(Size == BALLOON_SIZE_1) 	||
		(Size == BALLOON_SIZE_2) 	||
		(Size == BALLOON_SIZE_4) 	||
		(Size == BALLOON_SIZE_8) 	||
		(Size == BALLOON_SIZE_16) 	||
		(Size == BALLOON_SIZE_32) 	||
		(Size == BALLOON_SIZE_64)	||
		(Size == BALLOON_SIZE_MAX)
	);
	if (!Balloon.Valid) 
	{
		PANIC("Balloon memory size must be one of the supported values!");
		return;
	}

	// Allocate a specified balloon size for the data structure.
	// This code should only be reachable if the size is one of the macro's.
	Balloon.Buffer = (UDWORD *)Malloc(Size);
	Balloon.Size = Size;
}

UDWORD *
BalloonInflate(UDWORD Amount, UDWORD Value) 
{
	if (Amount > Balloon.Capacity) 
	{
		UDWORD *Result = BalloonPop();
		return (Result);
	}
	Balloon.Data = MemSet(Balloon.Buffer, Value, Balloon.Size);
}

VOID
BalloonCleanup(VOID) 
{
	if ((Balloon.Size <= BALLOON_SIZE_MIN) || Balloon.Size > BALLOON_SIZE_MAX)
		return;
	Free(Balloon.Buffer);
}

UDWORD *
BalloonPop(VOID) 
{
	return (Balloon.Data);
}

SIZE
BalloonSize(VOID)
{
	return (Balloon.Size);
}

SIZE
BalloonCapacity(VOID)
{
	return (Balloon.Capacity);
}

/*
// Initialize the data to fill:
static uint32_t *data;

// Declare the balloon struct:
balloon_t balloon;

// For checking if the memory type can still be used:
bool popped;

// Initialize the balloon memory util with one of the available sizes:
bool balloon_init(uint32_t size) {
	for (uint32_t i = 0; i < size; i++) {
		data[i] = 0;
	}
	bool is_valid = ((size == BALLOON_SIZE_4) || (size == BALLOON_SIZE_8) || (size == BALLOON_SIZE_16) || (size == BALLOON_SIZE_32) || (size == BALLOON_SIZE_64));
	if (is_valid) {
		balloon.size = 0;
		balloon.capacity = size;
	} else {
		//_int_10();
	}
	popped = false;
	return (is_valid);
}

// Add data to the memory module:
uint32_t *balloon_inflate(uint32_t amount, uint32_t value) {
	if (!popped) {
		if ((amount >= balloon.size) && (amount < balloon.capacity)) {
			balloon.size = amount;
			data[amount] = value;
		}
	}
	if (balloon.size > balloon.capacity) {
		return (balloon_pop());
	}
	return (0);
}

// Delete memory from the memory module:
void balloon_deflate(uint32_t amount) {
	if (!popped) {
		if (amount > 0) {
			for (uint32_t i = balloon.size; i > balloon.size - amount; i--) {
				data[i] = 0;
			}
		}
	}
}

// Free the memory in the module:
void balloon_cleanup() {
	for (uint32_t i = 0; i < balloon.capacity; i++) {
		data[i] = 0;
	}
	balloon.size = 0;
	balloon.capacity = 0;
}

// Disable this memory module and get the data in it:
uint32_t *balloon_pop() {
	uint32_t *tmp = data;
	if (balloon.size > 0) {
		if (!popped) {
			popped = true;
		}
	}
	return (tmp);
}

// Get the size of the current memory heap:
uint32_t balloon_size() {
	return (balloon.size);
}

// Get the capacity of the balloon module:
uint32_t balloon_capacity() {
	return (balloon.capacity);
}
*/