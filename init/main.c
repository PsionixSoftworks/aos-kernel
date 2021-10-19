#define CURSOR_TYPE 	1

#define __DEBUG__		1

#include <debug.h>
#include <adamantine/tty.h> 
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

#include <termios.h>

/* 
 * TODO: FINISH FIXING ALL PARAMETERS WITH AN "_" IN FRONT OF THE VARIABLE NAMES...
 * TODO: FINISH UPDATING ALL FUNCTIONS WITH THE "_init" SUFFIX TO "_initialize."y
 */

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_initialize(void)
{
	gdt_init();											// Defined in "gdt.c"
	ldt_init();											// Defined in "ldt.c"
	idt_init();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);	// Clear the address of the interrupt handlers to zero
	show_debug_info("Descriptor tables are initialized!");
}

__GLOBAL kernel_t
k_main(void)
{
	tty_initialize((uint16_t *)VGA_TEXT_MODE_COLOR);
	tty_set_colors(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_YELLOW);
	tty_cursor_enable(CURSOR_START, CURSOR_END);
	tty_clear();

	descriptor_tables_initialize();
	paging_initialize();

	keyboard_initialize();
	pit_initialize(50);

	//switch_to_user_mode();
}
