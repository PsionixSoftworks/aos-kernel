#include <i386/gdt.h>
#include <adamantine/tty.h>
#include <stddef.h>

static inline void gdt_add_entry(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

static gdt_entry_t gdt_entries[5];

void
gdt_init(void)
{
	static 	gdt_ptr_t gdt_ptr;
			gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
			gdt_ptr.base = (unsigned int)&gdt_entries;
	gdt_add_entry(0, NULL, NULL, NULL, NULL);
	gdt_add_entry(1, GDT_MEMORY_START, GDT_MEMORY_END, GDT_KERNEL_CODE, GDT_GRANULARITY);
	gdt_add_entry(2, GDT_MEMORY_START, GDT_MEMORY_END, GDT_KERNEL_DATA, GDT_GRANULARITY);
	gdt_add_entry(3, GDT_MEMORY_START, GDT_MEMORY_END, GDT_USER_CODE, GDT_GRANULARITY);
	gdt_add_entry(4, GDT_MEMORY_START, GDT_MEMORY_END, GDT_USER_DATA, GDT_GRANULARITY);
	__asm__ volatile ( "lgdt (%0)" : : "m"(gdt_ptr));

	tty_printf("The GDT is installed.\n");
}

static inline void
gdt_add_entry(int32_t num, uint32_t gdt_base, uint32_t gdt_limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base			= (gdt_base 	& 0xFFFF);
	gdt_entries[num].limit			= (gdt_limit 	& 0xFFFF);
	gdt_entries[num].granularity	= gran;
	gdt_entries[num].access			= access;
}
