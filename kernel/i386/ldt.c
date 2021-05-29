#include <i386/ldt.h>
#include <adamantine/tty.h>

ldt_entry_t ldt_entries[2];
ldt_ptr_t ldt_ptr;

static inline void ldt_set_gate(uint32_t, uint8_t, uint8_t);

void
ldt_init(void)
{
    ldt_ptr.limit = sizeof(ldt_entry_t) - 1;
    ldt_ptr.base = (uint32_t)&ldt_entries;

    ldt_set_gate(0, 0, 0);
    ldt_set_gate(1, 2, 0xA);

    __asm__ volatile ("lldt (%0)" : : "m"(ldt_ptr));
}

static inline void
ldt_set_gate(uint32_t num, uint8_t table, uint8_t rpl)
{
    ldt_entries[num].table = table;
    ldt_entries[num].rpl = rpl;
}
