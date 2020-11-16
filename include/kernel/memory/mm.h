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

#ifndef ADAMANTINE_memORY_UTILITY
#define ADAMANTINE_memORY_UTILITY

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

// Declare the allocation type:
typedef struct 
{
	byte 				status;
	size_t 				size;
} alloc_t;

#if defined(__cplusplus)
extern "C" {
#endif

void mm_init(uint32_t kernel_end);
void paging_map_virtual_to_physical(uint32_t virt, uint32_t physical);

void *pmalloc(size_t size);
void *malloc(size_t size);
void pfree(void *mem);
void free(void *mem);

void *memchr(const void *str, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
void *memset16(void *pointer,  uint32_t value, size_t size);

uint32_t	kmalloc_int(uint32_t size, uint32_t align, uint32_t *physical_address);
uint32_t	kmalloc_a(uint32_t size);
uint32_t	kmalloc_p(uint32_t size_t, uint32_t *physical_address);
uint32_t	kmalloc_ap(uint32_t size, uint32_t *physical_address);
uint32_t	kmalloc(uint32_t size);

#if defined(__cplusplus)
extern "C" {
#endif

#endif	// !ADAMANTINE_memORY_UTILITY
