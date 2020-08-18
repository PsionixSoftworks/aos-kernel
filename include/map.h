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
#include "aos-defs.h"
#include "types.h"

// Declare the map node struct:
struct MapNode 
{
	DWORD 				Key;										// The key for the map.
	DWORD 				Value;										// The value of the key fro the map.
	STRUCT 				MapNode *Next;								// Next index?
} PACKED;

// Declare the map struct:
struct Map 
{
	SIZE 				Size;										// Size of the map.
	STRUCT 				MapNode **List;								// Um, next index also?
} PACKED;

// Declare global functions:
EXTERN SET_STRUCT(Map *MapCreate(SIZE Size));						// Create a map data structure.
EXTERN SET_UDWORD(MapHashCode(STRUCT Map *M, DWORD Key));			// Map hash code... Duh?
EXTERN SET_UDWORD(MapGet(STRUCT Map *M, DWORD Key));				// Get the value by key.
EXTERN SET_VOID(MapAdd(STRUCT Map *M, DWORD Key, UDWORD Value));	// Add a value to the key.
EXTERN SET_VOID(MapFree(VOID));										// Free the memory created by the map.

#endif	// !AMAMANTINE_MAP
