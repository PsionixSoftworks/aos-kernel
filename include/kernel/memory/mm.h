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

#ifndef _MEMORY_UTIL_H
#define _MEMORY_UTIL_H

#include <stdint.h>

static uint32_t last_alloc 	= 0;
static uint32_t heap_end	= 0;
static uint32_t heap_begin 	= 0;
static uint32_t pheap_begin = 0;
static uint32_t pheap_end 	= 0;
static uint32_t memory_used = 0;
static uint8_t *pheap_desc 	= 0;

// Declare the allocation type:
typedef struct 
{
	uint8_t				status;
	size_t 				size;
} alloc_t;

#if defined(__cplusplus)
extern "C" {
#endif

typedef unsigned int uint32_t;

void mm_init(uint32_t kernel_end);
void paging_map_virtual_to_physical(uint32_t virt, uint32_t physical);

uint32_t	kmalloc_int(uint32_t size, uint32_t align, uint32_t *physical_address);
uint32_t	kmalloc_a(uint32_t size);
uint32_t	kmalloc_p(uint32_t size_t, uint32_t *physical_address);
uint32_t	kmalloc_ap(uint32_t size, uint32_t *physical_address);
uint32_t	kmalloc(uint32_t size);

#if defined(__cplusplus)
}
#endif

#endif	// !ADAMANTINE_MEMORY_UTILITY
