#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>		// Officially removed as of version 64 (v0.5.32.2a). Using this is strictly prohibited!
#else
#include <drivers/tty.h>
#endif

#include <adamantium/adamantium.h>
#include <adamantium/config.h>
#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <i386/gdt.h>
#include <i386/idt.h>
#include <i386/ldt.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/kernel.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <kernel/rtc.h>
#include <math/math-util.h>
#include <math/simple-math.h>
#include <memory/memory-util.h>
#include <memory/ordered-array.h>
#include <memory/paging.h>
#include <filesystem/vfs.h>
#include <config.h>
#include <stdint.h>
#include <stdio.h>

#include <multiboot.h>

#include <drivers/device.h>

#include <system/portio.h>

#ifndef CHECK_FLAG
#define CHECK_FLAG(_flags, _bit) 	((_flags)&1 << (_bit))
#endif

#define ASSIGN_ADDR(x, y) 			(y = (multiboot_info_t *)x)

/* External references */
extern isr_t interrupt_handlers[MAX_INTERRUPTS]; // The interrupt handler (defined in "isr.c")
extern void set_kernel_stack(uint32_t _stack);

uint32_t stack_pointer;
system_info_t* system_info;

/* Initialize the GDT, LDT, and IDT */
static inline void
descriptor_tables_init(void)
{
	gdt_initialize(); // Defined in "gdt.c"
	ldt_initialize(); // Defined in "ldt.c"
	idt_initialize(); // Defined in "idt.c"

	memset(&interrupt_handlers, 0, sizeof(isr_t) * 256); // Clear the address of the interrupt handlers to zero
}

extern struct vga vga;

static inline void
move_to_user_mode(void)
{
	__asm__ ("movl %%esp, %%eax\n\t"	\
			"pushl $0x17\n\t"			\
			"pushl %%eax\n\t"			\
			"pushfl\n\t"				\
			"pushl $0x0f\n\t"			\
			"pushl $1f\n\t"				\
			"iret\n"					\
			"1:\tmovl $0x17, %%eax\n\t"	\
			"movw %%ax, %%ds\n\t"		\
			"movw %%ax, %%es\n\t"		\
			"movw %%ax, %%fs\n\t"		\
			"movw %%ax, %%gs\n\t"		\
			:::"ax"
	);
}

multiboot_info_t* mbi;

extern struct device tty_device;

void
k_main(unsigned long magic, unsigned long addr)
{
	if (tty_init((uint16_t*)VGA_ADDRESS) == DEVICE_SUCCESS)
	{
		tty_set_foreground(SYSTEM_COLOR_LT_GREEN);
		printf("[AOS_INFO]:!~ Starting AdamantiumOS - Version: v%s.\n", KERNEL_VERSION_STRING);

		/* Since we're using GRUB as a bootloader for now, we need to verify the Magic Number is valid */
		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		{
			tty_set_foreground(SYSTEM_COLOR_RED);
			printf("[AOS_ERROR]:!~ Invalid magic number: 0x%X\n", magic);
			return;
		}

		mbi = (multiboot_info_t*)addr;
	#if defined(DEBUG_MODE) && defined(VERBOSE_MSG_FLAGS_ON)
		printf("Multiboot Flags: 0x%X\n", mbi->flags);
	#endif

		descriptor_tables_init();
		paging_initialize();

		pit_initialize(50);
		cpu_init();

		/* Print all the details of the TTY device Driver */
		printf("\n== Device Driver information for TTY ==\n");
		printf("Device ID: %d\n", tty_device.device_id);
		printf("Device Name: \"%s\"\n", tty_device.device_name);
		printf("Device Type: %s\n", device_get_type_str(&tty_device));
		printf("Device IO Type: %s\n", device_get_io_type_str(&tty_device));
		printf("Device Port Address: 0x%X\n", device_get_port(&tty_device));
		printf("This device is working properly.\n");
	}
}
