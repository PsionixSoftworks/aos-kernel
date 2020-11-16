/*
 *  File: map.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef AMAMANTINE_MAP
#define AMAMANTINE_MAP

// Includes go here:
#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

// Declare the map node struct:
struct map_node 
{
	dword 				key;									// The key for the map.
	dword 				value;									// The value of the key fro the map.
	struct 				map_node *next;							// next index?
} PACKED;

// Declare the map struct:
struct map 
{
	size_t 				size;									// size of the map.
	struct 				map_node **list;						// Um, next index also?
} PACKED;

#if defined(__cplusplus)
extern "C" {
#endif

// Declare global functions:
struct map *map_create(size_t size);							// Create a map data structure.
uint32_t (map_hash_code(struct map *m, dword key));				// map hash code... Duh?
uint32_t (map_get(struct map *m, dword key));					// Get the value by key.
void (map_add(struct map *m, dword key, uint32_t value));		// Add a value to the key.
void (map_free(void));											// free the memory created by the map.

#if defined(__cplusplus)
}
#endif

#endif	// !AMAMANTINE_MAP
