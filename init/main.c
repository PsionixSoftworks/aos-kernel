#define CURSOR_TYPE 	0

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

#include <kernel/procmgr.h>

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS];		// The interrupt handler (defined in "isr.c")

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_init(void)
{
	gdt_init();											// Defined in "gdt.c"
	ldt_init();											// Defined in "ldt.c"
	idt_init();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t)*256);	// Clear the address of the interrupt handlers to zero
}

typedef struct fruit
{
	uint32_t apples;
	uint32_t pears;
} fruits_t;

kernel_t HOT
init(void)
{
	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);			// Initialize the teletype with color Text Mode enabled
	tty_set_foreground(SYSTEM_COLOR_LT_GREEN);			// Set the default text color to light green (the color of adamntine)
	tty_cursor_enable(CURSOR_START, CURSOR_END);		// Enable the Text Mode cursor as a block cursor
	tty_clear();										// Clear the teletype screen
	
	descriptor_tables_init();							// Call the function which initialized the GDT, LDT, and IDT
	pit_init(50);										// Initialize the PIT at 50Hz
	//mm_init((uint32_t)&kernel_end);						// Initialize the kernel heap (to be replaced...)
	initialize_paging();								// Initialize memory paging
	cpu_init();											// Initialize the CPU

	fruits_t *a = (fruits_t *)kmalloc(sizeof(fruits_t));
	a->apples = 10;
	a->pears = 2;

	keyboard_init();
}

typedef struct test test_t;
struct test
{
	int apple;
};

kernel_t HOT
k_main(void)
{
	//init();

	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);
	tty_set_colors(SYSTEM_COLOR_BLUE, SYSTEM_COLOR_YELLOW);
	tty_cursor_enable(CURSOR_START, CURSOR_END);
	tty_clear();

	descriptor_tables_init();

	uint32_t a = kmalloc(8);
	initialize_paging();
	uint32_t b = kmalloc(8);
	uint32_t c = kmalloc(8);

	tty_printf("a: 0x%X, ", a);
	tty_printf("b: 0x%X\n", b);
	tty_printf("c: 0x%X\n", c);

	kfree(c);
	kfree(b);
}
