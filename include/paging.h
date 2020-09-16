#ifndef _PAGING_
#define _PAGING_

#define MAX_PAGE_TABLES     0x400
#define PAGE_BLOCK_SIZE     0x1000

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <kernel/isr.h>

typedef struct page
{
    udword present  : 1;
    udword rw       : 1;
    udword user     : 1;
    udword access : 1;
    udword dirty    : 1;
    udword unused   : 7;
    udword frame    : 20;
} page_t;

typedef struct page_table
{
    page_t pages[MAX_PAGE_TABLES];
} page_table_t;

typedef struct page_directory
{
    page_table_t *tables[MAX_PAGE_TABLES];
    udword tables_physical[MAX_PAGE_TABLES];
    udword physical_address;
} page_directory_t;

EXTERN void paging_init(void);
EXTERN void paging_switch_directory(page_directory_t *new_page);
EXTERN page_t *paging_get_page(udword address, udword make, page_directory_t *directory);
EXTERN void paging_get_fault(registers_t registers);

#endif
