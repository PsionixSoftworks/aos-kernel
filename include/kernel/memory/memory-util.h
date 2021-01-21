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

// Declare the allocation type:
typedef struct 
{
	uint8_t					status;
	size_t 					size;
} alloc_t;

typedef unsigned int uint32_t;

void mm_init(uint32_t kernel_end);
void paging_map_virtual_to_physical(uint32_t virt, uint32_t physical);

uint32_t	kmalloc_int(uint32_t size, uint32_t align, uint32_t *physical_address);
uint32_t	kmalloc_a(uint32_t size);
uint32_t	kmalloc_p(uint32_t size_t, uint32_t *physical_address);
uint32_t	kmalloc_ap(uint32_t size, uint32_t *physical_address);
uint32_t	kmalloc(uint32_t size);

#endif	// !_MEMORY_UTIL_H
