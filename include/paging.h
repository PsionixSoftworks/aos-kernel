#ifndef _PAGING_
#define _PAGING_

#define MAX_PAGE_TABLES     0x400
#define PAGE_BLOCK_SIZE     0x1000

#include "aos-defs.h"
#include "types.h"
#include "isr.h"

typedef struct Page
{
    UDWORD Present  : 1;
    UDWORD RW       : 1;
    UDWORD User     : 1;
    UDWORD Accessed : 1;
    UDWORD Dirty    : 1;
    UDWORD Unused   : 7;
    UDWORD Frame    : 20;
} Page_t;

typedef struct PageTable
{
    Page_t Pages[MAX_PAGE_TABLES];
} PageTable_t;

typedef struct PageDirectory
{
    PageTable_t *Tables[MAX_PAGE_TABLES];
    UDWORD TablesPhysical[MAX_PAGE_TABLES];
    UDWORD PhysicalAddress;
} PageDirectory_t;

EXTERN VOID PagingInit(VOID);
EXTERN VOID SwitchPageDirectory(PageDirectory_t *NewPage);
EXTERN Page_t *GetPage(UDWORD Address, int Make, PageDirectory_t *Directory);
EXTERN VOID PageFault(Registers_t Register);

#endif
