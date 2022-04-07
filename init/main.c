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
#include <kernel/rtc.h>
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
#include <termios.h>
#include <timers.h>

#include <kernel/task.h>

#include <memory/linked-list.h>

#include <servers/fs/const.h>
#include <servers/fs/buf.h>

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
system_info_t *system_info;								// Used to retrieve information about the system it is running on. Used throughout the kernel.

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_initialize(void)
{
	gdt_initialize();											// Defined in "gdt.c"
	ldt_initialize();											// Defined in "ldt.c"
	idt_initialize();											// Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);		// Clear the address of the interrupt handlers to zero
	
#if defined(VERBOSE_FLAGS)
	PrintMessage("Descriptor Tables have been initialized.", INFO);
#endif
}

uint32_t stack_pointer;

__GLOBAL kernel_t
k_main(uint32_t _esp)
{
	stack_pointer = _esp;

	k_tty_initialize(VGA_ADDRESS);
	k_tty_set_colors(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_GRAY);
	k_tty_cursor_enable(CURSOR_START, CURSOR_END);
	k_tty_clear();

	/* Initialize the system */
	descriptor_tables_initialize();
	paging_initialize();

	k_tty_printf("Testing...\n");

	initialize_tasking();
	int ret = fork();

	k_tty_printf("fork() returned 0x%X, and getpid() returned 0x%X\n", ret, getpid());

	keyboard_initialize();
	pit_initialize(50);

	cpu_init();

	//set_kernel_stack(stack_pointer);
	//switch_to_user_mode();			// <-- Has to be fixed
}

static inline const char *
convert_severity_to_str(const int _Severity)
{
	if (_Severity == 0)
		return "[INFO]";
	if (_Severity == 1)
		return "[WARNING]";
	if (_Severity == 2)
		return "[ERROR]";
	return "[INFO]";
}

void
print_verbose_message(const char *_Message, const int _Severity)
{
	uint8_t termColor[] = { SYSTEM_COLOR_LT_GREEN, SYSTEM_COLOR_YELLOW, SYSTEM_COLOR_RED };
	
	k_tty_set_foreground(termColor[_Severity]);
	k_tty_printf("%s: %s\n", convert_severity_to_str(_Severity), _Message);
	k_tty_set_foreground(SYSTEM_COLOR_GRAY);
#if !defined(_DISABLE_DISPATCH_LOG)
	// Save the dispatched message to a file using the filesystem (WIP).
#endif
}
