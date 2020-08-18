/*
 *  File: main.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/main.h"
#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"
#include "../include/centrix.h"
#include "../include/pit.h"

#include "../include/x86/gdt.h"
#include "../include/x86/ldt.h"
#include "../include/x86/idt.h"
#include "../include/syscall.h"
#include "../include/tss.h"
#include "../include/vga.h"

MODULE("main", "0.01a");

void _TEXT 
kmain(void) 
{
	terminal_init(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
	terminal_clear_screen();

	gdt_init();
	//ldt_init();
	idt_init();

	

	//initialize_syscalls();
	//switch_to_user_mode();
	//terminal_printf("Result: 0x%X\n", 0xABCD);

	/*KernelInstall(OS_NAME);
	uint32_t status = Verify();
	if (status == SUCCESS)
	{
		kernel_init(KERNEL_MODE_NO_GUI);
		while (kernel_is_running())
		{
			kernel_update();
		}
		kernel_quit(0x0);
	} else {
		ERROR("Unable to start. Invalid OS...");
		kernel_quit(0x1);
	}*/
}
