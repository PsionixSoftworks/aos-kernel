#define CURSOR_TYPE 	1
#define __DEBUG__		1

#include <debug.h>
#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <adamantine/aos-defs.h>
#include <adamantine/aos-int.h>
#include <adamantine/aos-string.h>
#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <memory/memory-util.h>
#include <memory/paging.h>
#include <kernel/kernel.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <i386/gdt.h>
#include <i386/ldt.h>
#include <i386/idt.h>
#include <compiler.h>
#include <macros.h>
#include <task.h>

#include <drivers/device.h>
#include <drivers/driver.h>

#include <math/math-util.h>
#include <termios.h>

#include <multiboot.h>

/* 
 * 
 * TODO: FINISH UPDATING ALL FUNCTIONS WITH THE "_init" SUFFIX TO "_initialize."y
 */

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")
extern void set_kernel_stack(uint32_t stack);
extern void tty_printf(const char *restrict fmt, ...);

driver_t *drv_test;

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
	k_tty_initialize((uint16_t *)VGA_TEXT_MODE_COLOR);
	k_tty_set_colors(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_YELLOW);
	k_tty_cursor_enable(CURSOR_START, CURSOR_END);
	k_tty_clear();

	multiboot_info_t *info;
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		tty_printf("[Error]: Multiboot magic number is invalid [at 0x%X]!\n", magic);
		return;
	}

	descriptor_tables_initialize();
	paging_initialize();

	keyboard_initialize();
	pit_initialize(50);

	info = (multiboot_info_t *)addr;
	tty_printf("Flags: 0x%X\n", info->flags);
}

int
driver_config(void)
{
	drv_test->name[MAX_NAME_LENGTH] = "Test Driver";
	drv_test->id = 0;
}