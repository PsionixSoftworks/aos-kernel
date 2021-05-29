#include <i386/gdt.h>
#include <adamantine/tty.h>
#include <stddef.h>

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

static inline void gdt_set_null_segment(void);
static inline void gdt_set_kernel_code_segment(void);
static inline void gdt_set_kernel_data_segment(void);
static inline void gdt_set_user_code_segment(void);
static inline void gdt_set_user_data_segment(void);

void
gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_null_segment();
    gdt_set_kernel_code_segment();
    gdt_set_kernel_data_segment();
    gdt_set_user_code_segment();
    gdt_set_user_data_segment();

    __asm__ volatile ( "lgdt (%0)" : : "m"(gdt_ptr));
    __asm__ volatile (
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
gdt_set_null_segment(void)
{
    gdt_entries[0].base_low     = 0x00;
    gdt_entries[0].base_middle  = 0x00;
    gdt_entries[0].base_high    = 0x00;
    gdt_entries[0].granularity  = 0x00;
    gdt_entries[0].access       = 0x00;
    gdt_entries[0].limit_low    = 0x00;
}

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
