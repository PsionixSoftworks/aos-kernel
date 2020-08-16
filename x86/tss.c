#define KERNEL32    1

#include "../include/tss.h"
#include "../include/mem_util.h"
#include "../include/x86/gdt.h"

tss_t tss_entry;

#define REPLACE_KERNEL_DATA_SEGMENT 0x18
#define REPLACE_KERNEL_STACK_ADDR   0x20

/* 0x23 = 35: User Mode Data Selector. */
/* 0x1B = 27: CS Selector Value. */
void
switch_to_user_mode(void)
{
    asm volatile
    (
        "               \
        cli;            \
        mov $0x23, %ax; \
        mov %ax, %ds;   \
        mov %ax, %es;   \
        mov %ax, %fs;   \
        mov %ax, %gs;   \
                        \
        mov %esp, %eax; \
        pushl $0x23;    \
        pushl %eax;     \
        pushf;          \
        pushl $0x1B;    \
        push $1f;       \
        iret;           \
        1:              \
        "
    );
}

static void 
write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.tss_ss0 	= ss0;
	tss_entry.tss_esp0 	= esp0;

	tss_entry.tss_cs = 0x0B;
	tss_entry.tss_ss = tss_entry.tss_ds = tss_entry.tss_es = tss_entry.tss_fs = tss_entry.tss_gs = 0x13; 
}

void
set_kernel_stack(uint32_t stack)
{
	tss_entry.tss_esp0 = stack;
}


/*
void 
write_tss(gdt_entry_t *g)
{
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = sizeof(tss);

    g->limit_low = limit & 0xFFFF;
    g->base_low = base & 0xFFFFFF;
    g->access = 1;
    g->read_write = 0;
    g->conforming_expand_down = 0;
    g->code = 1;
    g->always1 = 0;
    g->dpl = 3;
    g->present = 1;
    g->limit_high = (limit & 0xF0000) >> 16;
    g->available = 0;
    g->always0 = 0;
    g->big = 0;
    g->granularity = 0;
    g->base_high = (base & 0xFF000000) >> 24;

    memset(&tss, 0, sizeof(tss));

    tss.tss_ss0 = REPLACE_KERNEL_DATA_SEGMENT;
    tss.tss_esp0 = REPLACE_KERNEL_STACK_ADDR;
}

void
set_kernel_stack(uint32_t stack)
{
    tss.tss_esp0 = stack;
}
*/
