#include <i386/gdt.h>
#include <adamantine/tty.h>
#include <i386/tss.h>
#include <stddef.h>

/* Define the GDT enties and the pointer to the GDT */
gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

/* Define GDT segments */
static inline void gdt_set_null_segment(void);          // MANDATORY Null Segment
static inline void gdt_set_kernel_code_segment(void);   // Kernel Code Segment
static inline void gdt_set_kernel_data_segment(void);   // Kernel Data Segment
static inline void gdt_set_user_code_segment(void);     // User Code Segment
static inline void gdt_set_user_data_segment(void);     // User Data Segment

static inline void tss_install(uint32_t, uint16_t, uint16_t);

/* Initialize the Global Descriptot Table */
void
gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;      // Get the size of the GDT (technically 4)
    gdt_ptr.base = (uint32_t)&gdt_entries;              // Get the base of the GDT

    /* Plug in the segments */
    gdt_set_null_segment();
    gdt_set_kernel_code_segment();
    gdt_set_kernel_data_segment();
    gdt_set_user_code_segment();
    gdt_set_user_data_segment();

    /* Load the GDT into memory */
    __asm__ volatile ( "lgdt (%0)" : : "m"(gdt_ptr));
    __asm__ volatile (                                  // Set the segment registers and long jump to 0x08
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
