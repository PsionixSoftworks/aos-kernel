#define CURSOR_TYPE 	1
#define __DEBUG__		1

#include <debug.h>
#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <adamantine/adamantine.h>
#include <adamantine/aos-bool.h>
#include <adamantine/aos-int.h>
#include <adamantine/aos-string.h>
#include <adamantine/config.h>
#include <adamantine/input.h>
#include <adamantine/mutex.h>
#include <drivers/device.h>
#include <drivers/driver.h>
#include <drivers/i8042.h>
#include <drivers/keyboard.h>
#include <drivers/keys.h>
#include <drivers/vga.h>
#include <filesystem/vfs.h>
#include <filesystem/initrd.h>
#include <i386/gdt.h>
#include <i386/idt.h>
#include <i386/ldt.h>
#include <i386/tss.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/kernel.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/procmgr.h>
#include <math/math-util.h>
#include <math/simple-math.h>
#include <memory/memory-util.h>
#include <memory/ordered-array.h>
#include <memory/paging.h>
#include <system/portio.h>
#include <system/types.h>
#include <ansi.h>
#include <aos-base.h>
#include <assert.h>
#include <compiler.h>
#include <config.h>
#include <errno.h>
#include <iso646.h>
#include <limits.h>
#include <macros.h>
#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <task.h>
#include <termios.h>
#include <timers.h>
#include <unistd.h>

#include <memory/linked-list.h>

#ifndef CHECK_FLAG
#define CHECK_FLAG(_flags, _bit)	((_flags) & 1 << (_bit))
#endif

#define ASSIGN_ADDR(x, y)			(y = (multiboot_info_t *)x)

#define MEM_INFO					0x00
#define BOOT_INFO					0x01

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")
extern void set_kernel_stack(uint32_t _stack);
extern void tty_printf(const char *restrict _fmt, ...);

/* Put the GRUB multiboot functionality to use */
multiboot_info_t *info;
system_info_t *system_info;								// Used to retrieve information about the system it is running on. Used throughout the kernel.

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_initialize(void)
{
	gdt_initialize();											// Defined in "gdt.c"
	ldt_initialize();											// Defined in "ldt.c"
	idt_initialize();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);		// Clear the address of the interrupt handlers to zero
	show_debug_info("Descriptor tables are initialized!");
}

__GLOBAL kernel_t
k_main(unsigned long magic, unsigned long addr)
{
	/* Setup text mode */
	k_tty_initialize((uint16_t *)VGA_TEXT_MODE_COLOR);
	k_tty_set_colors(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_LT_GREEN);
	k_tty_cursor_enable(CURSOR_START, CURSOR_END);
	k_tty_clear();

	/* Check if the magic number is valid. */
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		/* If not, print an error message */
		show_debug_error("Multiboot magic number is invalid!\n");
		return;
	}

	/* Initialize the system */
	descriptor_tables_initialize();
	paging_initialize();

	keyboard_initialize();
	pit_initialize(50);
	
	cpu_init();

	/* If all went well, assign the address to the info struct */
	ASSIGN_ADDR(addr + 0xC0000000, info);

	if (CHECK_FLAG(info->flags, BOOT_INFO))
		show_debug_info("Boot device is valid!");
	if (CHECK_FLAG(info->flags, MEM_INFO))
		k_tty_printf("[INFO]: Memory Lower: %dKB\nMemory Upper: %dKB\n", (unsigned)info->mem_lower, (unsigned)info->mem_upper);
}
