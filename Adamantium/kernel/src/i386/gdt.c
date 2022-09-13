#define __DEBUG__   1

#include <i386/gdt.h>
#include <kernel/version.h>
#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <kernel/irq.h>
#include <i386/ldt.h>
#include <i386/tss.h>
#include <debug.h>

#define GDT_GRAN        0b11001111

/* Define the GDT enties and the pointer to the GDT */
gdt_entry_t gdt_entries[MAX_GDT_ENTRIES];
gdt_ptr_t gdt_ptr;
tss_t tss_entry;

/* Define GDT segments */
static inline void gdt_set_null_segment(void);          // MANDATORY Null Segment
static inline void gdt_set_kernel_code_segment(void);   // Kernel Code Segment
static inline void gdt_set_kernel_data_segment(void);   // Kernel Data Segment
static inline void gdt_set_user_code_segment(void);     // User Code Segment
static inline void gdt_set_user_data_segment(void);     // User Data Segment
static inline void gdt_set_tss_segment(uint32_t _idx, uint16_t ss0, uint32_t esp0);           // TSS Segment

static inline void gdt_install(void);
static inline void tss_install(void);

//extern void tss_install(void);

/* Initialize the Global Descriptot Table */
void
gdt_initialize(void)
{    
    gdt_ptr.limit = (sizeof(gdt_entry_t) * MAX_GDT_ENTRIES) - 1;    // Get the size of the GDT (technically 5)
    gdt_ptr.base = (uint32_t)&gdt_entries;                          // Get the base of the GDT

    /* Plug in the segments */
    gdt_set_null_segment();
    gdt_set_kernel_code_segment();
    gdt_set_kernel_data_segment();
    gdt_set_user_code_segment();
    gdt_set_user_data_segment();
    gdt_set_tss_segment(5, 0x10, 0x00);

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
	__asm__ volatile ("ltr %w0" : : "q" (0x2B));
}

void
set_kernel_stack(uint32_t stack)
{
	tss_entry.esp0 = stack;
}

void 
set_segment_desc_gate(uint32_t _idx, uint32_t _base, uint32_t _limit, uint8_t _access, uint8_t _gran)
{
    gdt_entries[_idx].base_low      = (_base & 0xFFFF);
    gdt_entries[_idx].base_middle   = (_base >> 16) & 0xFF;
    gdt_entries[_idx].base_high     = (_base >> 24) & 0xFF;

    gdt_entries[_idx].limit_low     = (_limit & 0xFFFF);
    gdt_entries[_idx].granularity   = (_limit >> 16) & 0x0F;

    gdt_entries[_idx].granularity   |= _gran & 0xF0;
    gdt_entries[_idx].access        = _access;
}

/* MANDATORY Null Segment */
static inline void
gdt_set_null_segment(void)
{
    set_segment_desc_gate(
        0, 
        0x00000000, 
        0x00000000, 
        0x00, 
        0b00000000
    );
}

/* Kernel Code Segment */
static inline void
gdt_set_kernel_code_segment(void)
{
    set_segment_desc_gate(
        1, 
        0x00000000, 
        0xFFFFFFFF, 
        0x9A, 
        GDT_GRAN
    );
}

/* Kernel Data Segment */
static inline void
gdt_set_kernel_data_segment(void)
{
    set_segment_desc_gate(
        2, 
        0x00000000,
        0xFFFFFFFF,
        0x92,
        GDT_GRAN
    );
}

/* User Code Segment */
static inline void
gdt_set_user_code_segment(void)
{
    set_segment_desc_gate(
        3,
        0x00000000,
        0xFFFFFFFF,
        0xFA,
        GDT_GRAN
    );
}

/* User Data Segment */
static inline void
gdt_set_user_data_segment(void)
{
    set_segment_desc_gate(
        4,
        0x00000000,
        0xFFFFFFFF,
        0xF2,
        GDT_GRAN
    );
}

static inline void
gdt_set_tss_segment(uint32_t _idx, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);
    
    set_segment_desc_gate(
        _idx,
        base,
        limit,
        0xE9,
        0x00
    );

    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0   = ss0;
    tss_entry.esp0  = esp0;

    tss_entry.cs = 0x0B;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}
