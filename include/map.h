#ifndef AMAMANTINE_MAP
#define AMAMANTINE_MAP

// Includes go here:
#include "types.h"

// Declare the map node struct:
struct map_node 
{
	int key;																				// The key for the map.
	int value;																			// The value of the key fro the map.
	struct map_node *next;														// Next index?
} __attribute__((packed));

// Declare the map struct:
struct map 
{
	size_t size;																		// Size of the map.
	struct map_node **list;														// Um, next index also?
} __attribute__((packed));

// Declare global functions:
extern struct map *map_create(size_t size);							// Create a map data structure.
extern uint32_t map_hash_code(struct map *m, int key);					// Map hash code... Duh?
extern void map_add(struct map *m, int key, uint32_t value);	// Add a value to the key.
extern uint32_t map_get(struct map *m, int key);						// Get the value by key.
extern void map_free();															// Free the memory created by the map.

#endif	// !AMAMANTINE_MAP
