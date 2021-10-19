#include <i386/gdt.h>
#include <adamantine/tty.h>
#include <i386/tss.h>
#include <stddef.h>
#include <kernel/irq.h>

#include <i386/ldt.h>

/* Define the GDT enties and the pointer to the GDT */
gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
tss_t tss_entry;

/* Define GDT segments */
static inline void gdt_set_null_segment(void);          // MANDATORY Null Segment
static inline void gdt_set_kernel_code_segment(void);   // Kernel Code Segment
static inline void gdt_set_kernel_data_segment(void);   // Kernel Data Segment
static inline void gdt_set_user_code_segment(void);     // User Code Segment
static inline void gdt_set_user_data_segment(void);     // User Data Segment
static inline void gdt_set_tss_segment(void);           // TSS Segment

static inline void gdt_install(void);
static inline void tss_install(void);

extern void tss_flush(void);

/* Initialize the Global Descriptot Table */
void
gdt_init(void)
{    
    gdt_ptr.limit = (sizeof(gdt_entry_t) * MAX_GDT_ENTRIES) - 1;    // Get the size of the GDT (technically 5)
    gdt_ptr.base = (uint32_t)&gdt_entries;                          // Get the base of the GDT

    /* Plug in the segments */
    gdt_set_null_segment();
    gdt_set_kernel_code_segment();
    gdt_set_kernel_data_segment();
    gdt_set_user_code_segment();
    gdt_set_user_data_segment();
    gdt_set_tss_segment();

    gdt_install();
    tss_install();
}

static inline void
gdt_install(void)
{
    /* Load the GDT into memory */
    __asm__ volatile ( "lgdt (%0)" : : "m"(gdt_ptr));
    __asm__ volatile (                                  // Set the segment registers and long jump to 0x08 (DS: 0x10 | CS: 0x08)
        "   movw $0x10, %ax     \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            movw %ax, %ss       \n \
            ljmp $0x08, $flush  \n \
            flush: "
    );
}

static inline void
tss_install(void)
{
	__asm__ volatile ("ltr (%0)" : : "m"(tss_entry));
}

void
set_kernel_stack(uint32_t stack)
{
	tss_entry.esp0 = stack;
}

/* MANDATORY Null Segment */
static inline void
gdt_set_null_segment(void)
{
    gdt_entries[0].base_low     = 0x00;
    gdt_entries[0].base_middle  = 0x00;
    gdt_entries[0].base_high    = 0x00;
    gdt_entries[0].granularity  = 0x00;
    gdt_entries[0].access       = 0x00;
    gdt_entries[0].limit_low    = 0x00;
}

/* Kernel Code Segment */
static inline void
gdt_set_kernel_code_segment(void)
{
    gdt_entries[1].base_low     = 0x00;
    gdt_entries[1].base_middle  = 0x00;
    gdt_entries[1].base_high    = 0x00;
    gdt_entries[1].granularity  = 0xCF;
    gdt_entries[1].access       = 0x9A;
    gdt_entries[1].limit_low    = 0xFFFF;
}

/* Kernel Data Segment */
static inline void
gdt_set_kernel_data_segment(void)
{
    gdt_entries[2].base_low     = 0x00;
    gdt_entries[2].base_middle  = 0x00;
    gdt_entries[2].base_high    = 0x00;
    gdt_entries[2].granularity  = 0xCF;
    gdt_entries[2].access       = 0x92;
    gdt_entries[2].limit_low    = 0xFFFF;
}

/* User Code Segment */
static inline void
gdt_set_user_code_segment(void)
{
    gdt_entries[3].base_low     = 0x00;
    gdt_entries[3].base_middle  = 0x00;
    gdt_entries[3].base_high    = 0x00;
    gdt_entries[3].granularity  = 0xCF;
    gdt_entries[3].access       = 0xFA;
    gdt_entries[3].limit_low    = 0xFFFF;
}

/* User Data Segment */
static inline void
gdt_set_user_data_segment(void)
{
    gdt_entries[4].base_low     = 0x00;
    gdt_entries[4].base_middle  = 0x00;
    gdt_entries[4].base_high    = 0x00;
    gdt_entries[4].granularity  = 0xCF;
    gdt_entries[4].access       = 0xF2;
    gdt_entries[4].limit_low    = 0xFFFF;
}

static inline void
gdt_set_tss_segment(void)
{
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);
    gdt_entries[5].base_low     = base;
    gdt_entries[5].base_middle  = base;
    gdt_entries[5].base_high    = base;
    gdt_entries[5].granularity  = 0x00;
    gdt_entries[5].access       = 0xE9;
    gdt_entries[5].limit_low    = limit;

    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0   = 0x10;
    tss_entry.esp0  = 0x00;

    tss_entry.cs = 0x0b;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}