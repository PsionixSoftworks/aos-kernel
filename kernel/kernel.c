/*
 *	AdamantineOS Kernel - Version 0.01a
 *	Written By: Vincent Cupo
 *
 */

/* Used to chack if this module is part of the kernel. */
#define KERNEL32	1

/* Include all modules the kernel requires here. */
#include "../include/kernel.h"
#include "../include/x86/gdt.h"
#include "../include/x86/idt.h"
#include "../include/terminal.h"
#include "../include/mem_util.h"
#include "../include/isr.h"
#include "../include/pit.h"
#include "../include/keyboard.h"
#include "../include/keys.h"
#include "../include/vfs.h"
#include "../include/pic.h"
#include "../include/irq.h"
#include "../include/init.h"
#include "../include/io.h"
#include "../include/device.h"
#include "../include/vga.h"
#include "../include/cmd/cmd.h"
#include "../include/aos-defs.h"
#include "../include/centrix-core.h"
#include "../include/centrix.h"

/* Tell the kernel what module and version we are using. */
MODULE("kernel", "0.02a");

/* Used for later when we enable 3D. */
#define RUNNING_IN_3D_MODE		FALSE

/* Locate external references here. */
extern uint32_t kernel_end;
extern uint32_t kernel_base;

/* Declare the kernel structure. */
kernel_t kernel;

/* Check to see if we have a GDT loaded. */
static void check_gdt(void) 
{
#if !defined(GLOBAL_DESCRIPTOR)
	ERROR("No Global Descriptor Table loaded! Exitting.");
#else
	gdt_init();
#endif
}

/* Check to see if we have a IDT loaded. */
static void check_idt(void) 
{
#if !defined(INTERRUPT_DESCRIPTOR)
	ERROR("No Interrupt Descriptor Table loaded! Exitting.");
#else
	idt_init();
#endif
}

/* Check to see if we have the basic kernel keyboard loaded. */
static void check_keyboard(void) 
{
#if !defined(KEYBOARD_DRIVER)
	ERROR("No valid keyboard driver found! Exitting.");
#else
	keyboard_init();
#endif
}

/* Handle normal mode. */
static inline void __kernel_mode_run_normal(void)
{
	terminal_print("AdamantineOS (AOS) Kernel/Shell - Version: 0.04a\n");

	INFO("Starting modules...");

	mm_init(&kernel_end);
	check_gdt();
	check_idt();

	terminal_print("Done!\n\n");
}

/* Handle safe mode. */
static inline void __kernel_mode_run_safe(void) 
{
	terminal_print("AdamantineOS (AOS) Kernel/Shell - Version: 0.04a\n");
	WARNING("Running in Safe Mode. Some functions will be disabled...\n");
	check_gdt();
	check_idt();
	mm_init(&kernel_end);

	kernel.running = true;
}

/* Handle no-gui mode. */
static inline void __kernel_mode_run_nogui(void)
{
	terminal_print("AdamantineOS (AOS) Kernel/Shell - Version: 0.04a\n");
	INFO("Running in NoGUI Mode. This is for experts only.\n");
	INFO("Starting modules...");

	check_gdt();
	check_idt();
	mm_init(&kernel_end);
	check_keyboard();

	terminal_print("Done!\n\n");

	terminal_print("For help type \"$(help) <command>\"\n");
	terminal_print("$ AdamantineOS: ");
	kernel.running = true;
}

/* Initialize the kernel. */
void __initcall kernel_init(uint8_t mode) 
{
	/* Check which mode we're using. */
	if (mode == KERNEL_MODE_NORMAL)
		goto Normal;
	if (mode == KERNEL_MODE_SAFE)
		goto Safe;
	if (mode == KERNEL_MODE_NO_GUI)
		goto NoGUI;

Normal:
	/* Jump to normal mode. */
	__kernel_mode_run_normal();
Safe:
	/* Jump to safe mode. */
	__kernel_mode_run_safe();
NoGUI:
	/* Jump to no-gui mode. */
	__kernel_mode_run_nogui();
}

/* Update the kernel. */
void __initcall kernel_update(void) 
{
	const string key_str = keyboard_get_key();
	if (key_str > KEYBOARD_KEY_DOWN_NONE) 
	{
		terminal_print(key_str);

		uint8_t keylast = keyboard_get_keylast();
		if (keylast == KEYBOARD_KEY_DOWN_ENTER) 
		{
			/* Process command here...*/
			terminal_print("$ AdamantineOS: ");
		}
	}
}

/* Quit the kernel on shutdown. */
void __initcall kernel_quit(uint8_t status) 
{
	aos_device_free();
	keyboard_free();
	idt_free();
	kernel.exit_status = SUCCESS;
}

/* Check if the kernel is running. */
bool
kernel_is_running(void) 
{
	return (kernel.running);
}

/* Set the mode of the kernel. */
void
kernel_begin_mode(kfunc_t init_func, uint8_t mode) 
{
	if (mode == KERNEL_MODE_NORMAL)
	{
		INFO("Starting up in Normal Mode.");
		init_func = &kernel_init;
	}
	if (mode == KERNEL_MODE_SAFE)
	{
		INFO("Starting up in Safe Mode. Some functionality will not be available...");
		init_func = &kernel_init;
	}
	if (mode == KERNEL_MODE_NO_GUI)
	{
		INFO("Starting up in NoGUI Mode. System will run as a terminal only...");
		init_func = &kernel_init;
	}

	init_func(mode);
}
