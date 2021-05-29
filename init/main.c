#include <adamantine/tty.h>
#include <kernel/drivers/vga.h>
#include <i386/gdt.h>
#include <i386/ldt.h>
#include <i386/idt.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/cpu.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/system/system.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/kernel.h>

#include <compiler.h>
#include <string.h>

#define CURSOR_START	0x0
#define CURSOR_END		0xF

extern uint32_t kernel_end;
extern isr_t interrupt_handlers[MAX_INTERRUPTS];

HOT kernel_t k_main(void);

static inline void
descriptor_tables_init(void)
{
	gdt_init();
	ldt_init();
	idt_init();

	memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);
    tty_puts("[INFO]: Descriptor tables initialized!\n");
}

HOT kernel_t
k_main(void)
{
	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);
	tty_set_foreground(SYSTEM_COLOR_LT_GREEN);
	tty_cursor_enable(CURSOR_START, CURSOR_END);
	tty_clear();
	
	descriptor_tables_init();
	pit_init(50);
	mm_init((uint32_t)&kernel_end);					// The cast is mandatory to avoid warnings.
	initialize_paging();
	cpu_init();

	keyboard_init();
	system_init();
}
