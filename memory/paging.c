/*
 *  File: paging.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <paging.h>
#include <memory/mm.h>
#include <system/terminal.h>

MODULE("Paging", "0.01a");

/* James Molloy... */
static udword *Frames;
static udword nFrames;
static page_directory_t *KernelDirectory;
static page_directory_t *CurrentDirectory;

EXTERN udword placement_address;

#define INDEX_FROM_BIT(a)       (a / (8 * 4))
#define OFFSET_FROM_BIT(a)      (a % (8 * 4))

static void
FrameSet(udword FrameAddress)
{
    udword frame = FrameAddress / PAGE_BLOCK_SIZE;
    udword Index = INDEX_FROM_BIT(frame);
    udword Offset = OFFSET_FROM_BIT(frame);
    Frames[Index] |= (0x1 << Offset);
}

static void
FrameClear(udword FrameAddress)
{
    udword frame = FrameAddress / PAGE_BLOCK_SIZE;
    udword Index = INDEX_FROM_BIT(frame);
    udword Offset = OFFSET_FROM_BIT(frame);
    Frames[Index] &= ~(0x1 << Offset);
}

static udword
FrameTest(udword FrameAddress)
{
    udword frame = FrameAddress / PAGE_BLOCK_SIZE;
    udword Index = INDEX_FROM_BIT(frame);
    udword Offset = OFFSET_FROM_BIT(frame);
    return (Frames[Index] & (0x1 << Offset));
}

static udword
FrameFirst(void)
{
    udword i, j;
    for (i = 0; i < INDEX_FROM_BIT(nFrames); i++)
    {
        if (Frames[i] != 0xFFFFFFFF)
        {
            for (j = 0; j < 32; j++)
            {
                udword ToTest = 0x1 << j;
                if (!(Frames[i] & ToTest))
                {
                    return (i * 4 * 8 + j);
                }
            }
        }
    }
}

void
FrameAlloc(page_t *page, udword IsKernel, udword IsWritable)
{
    if (page->frame != 0) 
    {
        return;
    }
    else
    {
        udword Index = FrameFirst();
        if (Index == (udword)-1)
        {
            //_PANIC("No free frames...");
        }
        FrameSet(Index * PAGE_BLOCK_SIZE);
        page->present = 1;
        page->rw = (IsWritable) ? 1 : 0;
        page->user = (IsKernel) ? 1 : 0;
        page->frame = Index;
    }
}

void
FrameFree(page_t *page)
{
    udword frame;
    if (!(frame = page->frame))
    {
        return;
    }
    else
    {
        FrameClear(frame);
        page->frame = 0x0;
    }
}

void
paging_init(void)
{
    udword memEndPage = 0x1000000;

    nFrames = memEndPage / PAGE_BLOCK_SIZE;
    Frames = (udword *)kmalloc(INDEX_FROM_BIT(nFrames));
    memset(Frames, 0, INDEX_FROM_BIT(nFrames));

    KernelDirectory = (page_directory_t *)kmalloc_a(sizeof(page_directory_t));
    memset(KernelDirectory, 0, sizeof(page_directory_t));
    CurrentDirectory = KernelDirectory;

    udword i = 0;
    while (i < placement_address)
    {
        FrameAlloc(paging_get_page(i, 1, KernelDirectory), 0, 0);
        i += 0x1000;
    }
    register_interrupt_handler(14, paging_get_fault);
    paging_switch_directory(KernelDirectory);

    //_INFO("Paging is initialized!");
    //system_logf(INFORMATION, "Paging is initialized!\n");
}

void
paging_switch_directory(page_directory_t *directory)
{
    CurrentDirectory = directory;
    asm volatile("mov %0, %%cr3":: "r"(&directory->tables_physical));
    udword CR0;
    asm volatile("mov %%cr0, %0": "=r"(CR0));
    CR0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(CR0));
}

page_t *paging_get_page(udword address, udword make, page_directory_t *directory)
{
    address /= 0x1000;

    udword TableIndex = address / MAX_PAGE_TABLES;
    if (directory->tables[TableIndex])
    {
        return (&directory->tables[TableIndex]->pages[address % MAX_PAGE_TABLES]);
    }
    else if (make)
    {
        udword Temp;
        directory->tables[TableIndex] = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &Temp);
        memset(directory->tables[TableIndex], 0, PAGE_BLOCK_SIZE);
        directory->tables_physical[TableIndex] = Temp | 0x7;
        return (&directory->tables[TableIndex]->pages[address % MAX_PAGE_TABLES]);
    } 
    else
    {
        return 0;
    }
}

void
paging_get_fault(registers_t registers)
{
    udword FaultingAddress;
    asm("mov %%cr2, %0" : "=r" (FaultingAddress));

    udword present  = !(registers.ERR_CODE & 0x01);
    udword rw       = registers.ERR_CODE & 0x02;
    udword US       = registers.ERR_CODE & 0x04;
    udword Reserved = registers.ERR_CODE & 0x08;
    udword ID       = registers.ERR_CODE & 0x10;

    terminal_printf("page Fault! ( ");
    if (present)    {terminal_printf("present ");}
    if (rw)         {terminal_printf("read-Only ");}
    if (US)         {terminal_printf("user-Mode ");}
    if (Reserved)   {terminal_printf("Reserved ");}
    terminal_printf(") - at 0x%X.\n", FaultingAddress);
    //_PANIC(" [AOS PAGE FAULT] ");
}

/* Me! */
/*
static udword *page_directory    = 0;
static udword *PageDirLocation  = 0;
static udword *LastPage         = 0;

void 
paging_map_virtual_to_physical(udword virtual, udword physical)
{
    uword ID = virtual >> 22;
    for (dword i = 0; i < 1024; i++) 
    {
        LastPage[i] = physical | 3;
        physical += 4096;
    }
    page_directory[ID] = ((udword)LastPage) | 3;
    LastPage = (udword *)(((udword)LastPage) + 4096);
}

void 
PagingEnable(void)
{
    asm volatile("MOV %%EAX, %%CR3": :"a"(PageDirLocation));
    asm volatile("MOV %CR0, %EAX");
    asm volatile("ORL $0x80000000, %EAX");
    asm volatile("MOV %EAX, %CR0");
}

void 
paging_init(void) 
{
    page_directory = (udword *)0x400000;
    PageDirLocation = (udword)page_directory;
    LastPage = (udword *)0x404000;
    for (dword i = 0; i < 1024; i++) 
    {
        page_directory[i] = 0x00 | 0x02;
    }
    paging_map_virtual_to_physical(0x00, 0x00);
    paging_map_virtual_to_physical(0x400000, 0x400000);
    PagingEnable();
}
*/
