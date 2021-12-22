#include <memory/paging.h>
#include <adamantine/tty.h>
#include <memory/memory-util.h>
#include <kernel/cpu.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

// The kernel's page directory:
page_directory_t *kernel_directory = 0;

// The current page directory:
page_directory_t *current_directory = 0;

// A bitset of frames - used or free:
uint32_t *frames;
uint32_t nframes;

// Defined in mem-util.c:
extern uint32_t placement_address;
extern heap_t *kheap;

#define INDEX_FROM_BIT(a)   (a / (8 * 4))
#define OFFSET_FROM_BIT(a)  (a % (8 * 4))

static void
set_frame(uint32_t _frame_address)
{
    uint32_t frame = _frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void
clear_frame(uint32_t _frame_address)
{
    uint32_t frame = _frame_address / 0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

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
alloc_frame(page_t *_page, int _is_kernel, int _is_writable)
{
    if (_page->frame != 0)
    {
        return;
    }
    else
    {
        uint32_t idx = first_frame();
        if (idx == (uint32_t)-1)
        {
            tty_puts("No free frames!");
        }
        set_frame(idx * 0x1000);
        _page->present = 1;
        _page->rw = (_is_writable) ? 1 : 0;
        _page->user = (_is_kernel) ? 0 : 1;
        _page->frame = idx;
    }
}

void
free_frame(page_t *_page)
{
    uint32_t frame;
    if (!(frame = _page->frame))
    {
        return;
    }
    else
    {
        clear_frame(frame);
        _page->frame = 0x0;
    }
}

void
paging_initialize(void)
{
    uint32_t mem_end_page = 0x1000000;
    nframes = mem_end_page / 0x1000;
    frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    kernel_directory = (page_directory_t *)kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    uint32_t i = 0;
    for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
        get_page(i, 1, kernel_directory);
    
    i = 0;
    while (i < placement_address + 0x1000)
    {
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }

    for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

    register_interrupt_handler(14, page_fault);

    switch_page_directory(kernel_directory);

    kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
#ifdef __DEBUG__
    k_tty_puts("[INFO]: Paging is initialized!\n");
#endif
}

void
switch_page_directory(page_directory_t *_dir)
{
    current_directory = _dir;
    asm volatile("mov %0, %%cr3":: "r"(&_dir->tables_physical));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *
get_page(uint32_t _address, int _make, page_directory_t *_dir)
{
    _address /= 0x1000;
    uint32_t table_idx = _address / 1024;
    if (_dir->tables[table_idx])
    {
        return (&_dir->tables[table_idx]->pages[_address % 1024]);
    }
    else if (_make)
    {
        uint32_t tmp;
        _dir->tables[table_idx] = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(_dir->tables[table_idx], 0, 0x1000);
        _dir->tables_physical[table_idx] = tmp | 0x7;
        return (&_dir->tables[table_idx]->pages[_address % 1024]);
    }
    else
    {
        return (0);
    }
}

void
page_fault(registers_t _regs)
{
    uint32_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address));

    int present     = !(_regs.err_code & 0x1);
    int rw          = _regs.err_code & 0x2;
    int us          = _regs.err_code & 0x4;
    int reserved    = _regs.err_code & 0x8;
    //int id          = regs.err_code & 0x10;

    tty_puts("Page fault! ( ");
    if (present) {tty_puts("present ");}
    if (rw) {tty_puts("read-only ");}
    if (us) {tty_puts("user-mode ");}
    if (reserved) {tty_puts("reserved ");}
    tty_puts(") at 0x");
    char buffer[64];
    tty_puts(itoa(faulting_address, buffer, 16));
    tty_puts("\n");

    PANIC("Page fault");
}
