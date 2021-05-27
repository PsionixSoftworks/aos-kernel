#include <kernel/kernel.h>
#include <compiler.h>

#include <adamantine/tty.h>
#include <kernel/drivers/vga.h>

#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/memory/memory-util.h>
#include <kernel/memory/paging.h>
#include <kernel/cpu.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/system/system.h>

#define CURSOR_START	0x0
#define CURSOR_END		0xF

extern uint32_t kernel_end;

kernel_t
k_main(void)
{
	tty_init((uint16_t *)VGA_TEXT_MODE_COLOR);
	tty_set_foreground(SYSTEM_COLOR_LT_CYAN);
	tty_cursor_enable(CURSOR_START, CURSOR_END);
	tty_clear();
	
	init_descriptor_tables();
	pit_init(50);
	mm_init((uint32_t)&kernel_end);					// The cast is mandatory to avoid warnings.
	initialize_paging();
	cpu_init();

	keyboard_init();
	system_init();
}
