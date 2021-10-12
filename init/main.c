#define CURSOR_TYPE 	1

#include <adamantine/tty.h>
#include <adamantine/aos-defs.h>
#include <adamantine/aos-int.h>
#include <adamantine/aos-string.h>
#include <kernel/drivers/vga.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/kernel.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <i386/gdt.h>
#include <i386/ldt.h>
#include <i386/idt.h>
#include <compiler.h>
#include <macros.h>

#include <termios.h>

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_init(void)
{void
	gdt_init();											// Defined in "gdt.c"
	ldt_init();											// Defined in "ldt.c"
	idt_init();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t)*256);	// Clear the address of the interrupt handlers to zero
	tty_printf("Descriptor tables are initialized!\n");
}

__GLOBAL kernel_t
k_main(void)
{
	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);
	tty_set_colors(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_YELLOW);
	tty_cursor_enable(CURSOR_START, CURSOR_END);
	tty_clear();

	descriptor_tables_init();
	initialize_paging();
}
