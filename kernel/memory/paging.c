#include <kernel/memory/paging.h>
#include <kernel/system/terminal.h>
#include <kernel/memory/mm.h>

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

uint32_t *frames;
uint32_t nframes;

extern uint32_t placement_address;

#define INDEX_FROM_BIT(a)   (a / (8 * 4))
#define OFFSET_FROM_BIT(a)  (a % (8 * 4))

static void
set_frame(uint32_t frame_address)
{
    uint32_t frame = frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void
clear_frame(uint32_t frame_address)
{
    uint32_t frame = frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

/* Find out if we even need this... *
static uint32_t
test_frame(uint32_t frame_address)
{
    uint32_t frame = frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}
*/

static uint32_t
first_frame(void)
{
    uint32_t i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF)
        {
            for (j = 0; j < 32; j++)
            {
                uint32_t to_test = 0x1 << j;
                if (!(frames[i] & to_test))
                {
                    return (i * 4 * 8 + j);
                }
            }
        }
    }
    return (0);
}

void
alloc_frame(page_t *page, int is_kernel, int is_writable)
{
    if (page->frame != 0)
    {
        return;
    }
    else
    {
        uint32_t idx = first_frame();
        if (idx == (uint32_t)-1)
        {
            PANIC("No free frames!");
        }
        set_frame(idx * 0x1000);
        page->present = 1;
        page->rw = (is_writable) ? 1 : 0;
        page->user = (is_kernel) ? 0 : 1;
        page->frame = idx;
    }
}

void
free_frame(page_t *page)
{
    uint32_t frame;
    if (!(frame = page->frame))
    {
        return;
    }
    else
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void
initialize_paging(void)
{
    uint32_t mem_end_page = 0x1000000;
    nframes = mem_end_page / 0x1000;
    frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    kernel_directory = (page_directory_t *)kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    unsigned int i = 0;
    while (i < placement_address)
    {
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
    register_interrupt_handler(14, page_fault);

    switch_page_directory(kernel_directory);

    terminal_printf("[INFO]: Paging is initialized!\n");
}

void
switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tables_physical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *
get_page(uint32_t address, int make, page_directory_t *dir)
{
    address /= 0x1000;
    uint32_t table_idx = address / 1024;
    if (dir->tables[table_idx])
    {
        return (&dir->tables[table_idx]->pages[address % 1024]);
    }
    else if (make)
    {
        uint32_t tmp;
        dir->tables[table_idx] = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(dir->tables[table_idx], 0, 0x1000);
        dir->tables_physical[table_idx] = tmp | 0x7;
        return (&dir->tables[table_idx]->pages[address % 1024]);
    }
    else
    {
        return (0);
    }
}

void
page_fault(registers_t regs)
{
    uint32_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address));

    int present     = !(regs.ERR_CODE & 0x1);
    int rw          = regs.ERR_CODE & 0x2;
    int us          = regs.ERR_CODE & 0x4;
    int reserved    = regs.ERR_CODE & 0x8;
    // int id          = regs.ERR_CODE & 0x10;

    terminal_print("Page fault! ( ");
    if (present) {terminal_print("present ");}
    if (rw) {terminal_print("read-only ");}
    if (us) {terminal_print("user-mode ");}
    if (reserved) {terminal_print("reserved ");}
    terminal_printf(") at 0x%X\n", faulting_address);
    PANIC("Page fault");
}
