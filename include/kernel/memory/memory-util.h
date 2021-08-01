/*
 *  File: mem-util.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

/**
 * NOTE: THIS SOURCE FILE IS TAKEN FROM http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html
 * It is a temporary heap allocator for use within the Virtual File System and other memory related
 * functions.
 * 
 * Almost everything in here will be replaced once understood!
 *
 **/

#ifndef _ADAMANTINE_MEMORY_UTIL_H
#define _ADAMANTINE_MEMORY_UTIL_H

#include <kernel/memory/ordered-array.h>

#define KHEAP_START			0xC0000000
#define KHEAP_INITIAL_SIZE	0x100000
#define HEAP_INDEX_SIZE		0x20000
#define HEAP_MAGIC			0x123890AB
#define HEAP_MIN_SIZE		0x70000

/**
 * Size information for a hole/block
 **/
typedef struct
{
	uint32_t magic;			// Magic number, used for error checking and identification.
	uint8_t is_hole;		// 1 if this is a hole. 0 if this is a block. (Could be 'bool'?)
	uint32_t size;			// Size of the block, including the block footer.
} header_t;

typedef struct
{
	uint32_t magic;			// Magic number, same as in header_t.
	header_t *header;		// Pointer to the block header.
} footer_t;

typedef struct
{
	ordered_array_t index;	
	uint32_t start_address;	// The start of our allocated space.
	uint32_t end_address;	// The end of our allocated space. May be expanded up to max_address.
	uint32_t max_address;	// The maximum address the heap can be expanded to.
	uint8_t supervisor;		// Should extra pages requested by us be mapped as supervisor-only?
	uint8_t readonly;		// Should extra pages requested by us be mapped as read-only?
} heap_t;

/**
 * Create a new heap
 **/
heap_t *create_heap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readonly);

/**
 * Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting
 * on a page boundary.
 **/
void *alloc(uint32_t size, uint8_t page_align, heap_t *heap);

/**
 * Releases a block allocated with 'alloc'.
 **/
void free(void *p, heap_t *heap);

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
void kfree(void *p);

#endif	// !_ADAMANTINE_MEMORY_UTIL_H
