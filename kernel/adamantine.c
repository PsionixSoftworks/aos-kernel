/*
 *  File: kernel.c
 *  Author: Vincent Cupo
 *  
 *  This file is the initial startup point of the bootloader.
 *  It is responsible for calling on GRUB and the kernel for boot.
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2020, Psionix Softworks LLC.
 *
 */

#include <adamantine/adamantine.h>
#include <kernel/system/terminal.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <kernel/system/io.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <stdlib.h>
#include <string.h>

extern uint32_t kernel_end;

static inline void test_code(void);

kernel_t
kmain(void)
{
	terminal_init();
	terminal_clear();

	init_descriptor_tables();
	pit_init(60);
	mm_init((uint32_t)&kernel_end);
	initialize_paging();

	keyboard_init();
	
	test_code();

	return (SUCCESS);
}

static inline void
test_code(void)
{

}
