#include <i386/ldt.h>

/* Define the LDT enties and the pointer to the LDT */
ldt_entry_t ldt_entries[2];
ldt_ptr_t ldt_ptr;

/* Setup the LDT gates (to be replaced) */
static inline void ldt_set_gate(uint32_t, uint8_t, uint8_t);

/* Initialize the Local Descriptor Table */
void
ldt_initialize(void)
{
    ldt_ptr.limit = sizeof(ldt_entry_t) - 1;            // Get the size of the LDT (2 for now)
    ldt_ptr.base = (uint32_t)&ldt_entries;              // Get the base of the LDT

    /* Tell the LDT how to work */
    ldt_set_gate(0, 2, 0x0A);

    /* Load the LDT into memory */
    __asm__ volatile ("lldt (%0)" : : "m"(ldt_ptr));
}

/* Tell the LDT what to do */
static inline void
ldt_set_gate(uint32_t num, uint8_t table, uint8_t rpl)
{
    ldt_entries[num].table = table;
    ldt_entries[num].rpl = rpl;
}
