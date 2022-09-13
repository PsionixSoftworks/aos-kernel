#ifndef _ADAMANTINE_PAGING_H
#define _ADAMANTINE_PAGING_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <stdint.h>
#include <kernel/isr.h>

/* Define the page struct */
typedef struct page
{
    uint32_t                present    :1;
    uint32_t                rw         :1;
    uint32_t                user       :1;
    uint32_t                accessed   :1;
    uint32_t                dirty      :1;
    uint32_t                unused     :7;
    uint32_t                frame      :20;
} page_t;

typedef struct page_table
{
    page_t                  pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t            *tables[1024];
    uint32_t                tables_physical[1024];
    uint32_t                physical_address;
} page_directory_t;

extern void paging_initialize(void);
extern void switch_page_directory(page_directory_t *dir);
extern page_t *get_page(uint32_t address, int make, page_directory_t *dir);
extern void alloc_frame(page_t *page, int is_kernel, int is_writable);
extern void page_fault(registers_t regs);
extern page_directory_t *clone_directory(page_directory_t *src);

#endif  //!_ADAMANTINE_PAGING_H
