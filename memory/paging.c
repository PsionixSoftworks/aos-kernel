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

#include "../include/paging.h"
#include "../include/mem-util.h"
#include "../include/terminal.h"

MODULE("paging", "0.01a");

/* James Molloy... */
static UDWORD *Frames;
static UDWORD nFrames;
static PageDirectory_t *KernelDirectory;
static PageDirectory_t *CurrentDirectory;

EXTERN UDWORD PlacementAddress;

#define INDEX_FROM_BIT(a)       (a / (8 * 4))
#define OFFSET_FROM_BIT(a)      (a % (8 * 4))

static VOID
FrameSet(UDWORD FrameAddress)
{
    UDWORD Frame = FrameAddress / PAGE_BLOCK_SIZE;
    UDWORD Index = INDEX_FROM_BIT(Frame);
    UDWORD Offset = OFFSET_FROM_BIT(Frame);
    Frames[Index] |= (0x1 << Offset);
}

static VOID
FrameClear(UDWORD FrameAddress)
{
    UDWORD Frame = FrameAddress / PAGE_BLOCK_SIZE;
    UDWORD Index = INDEX_FROM_BIT(Frame);
    UDWORD Offset = OFFSET_FROM_BIT(Frame);
    Frames[Index] &= ~(0x1 << Offset);
}

static UDWORD
FrameTest(UDWORD FrameAddress)
{
    UDWORD Frame = FrameAddress / PAGE_BLOCK_SIZE;
    UDWORD Index = INDEX_FROM_BIT(Frame);
    UDWORD Offset = OFFSET_FROM_BIT(Frame);
    return (Frames[Index] & (0x1 << Offset));
}

static UDWORD
FrameFirst(VOID)
{
    UDWORD i, j;
    for (i = 0; i < INDEX_FROM_BIT(nFrames); i++)
    {
        if (Frames[i] != 0xFFFFFFFF)
        {
            for (j = 0; j < 32; j++)
            {
                UDWORD ToTest = 0x1 << j;
                if (!(Frames[i] & ToTest))
                {
                    return (i * 4 * 8 + j);
                }
            }
        }
    }
}

VOID
FrameAlloc(Page_t *Page, int IsKernel, int IsWritable)
{
    if (Page->Frame != 0) 
    {
        return;
    }
    else
    {
        UDWORD Index = FrameFirst();
        if (Index == (UDWORD)-1)
        {
            PANIC("No free frames...");
        }
        FrameSet(Index * PAGE_BLOCK_SIZE);
        Page->Present = 1;
        Page->RW = (IsWritable) ? 1 : 0;
        Page->User = (IsKernel) ? 1 : 0;
        Page->Frame = Index;
    }
}

VOID
FrameFree(Page_t *Page)
{
    UDWORD Frame;
    if (!(Frame = Page->Frame))
    {
        return;
    }
    else
    {
        FrameClear(Frame);
        Page->Frame = 0x0;
    }
}

VOID
PagingInit(VOID)
{
    UDWORD MemEndPage = 0x1000000;

    nFrames = MemEndPage / PAGE_BLOCK_SIZE;
    Frames = (UDWORD *)kMalloc(INDEX_FROM_BIT(nFrames));
    MemSet(Frames, 0, INDEX_FROM_BIT(nFrames));

    KernelDirectory = (PageDirectory_t *)kMalloc_a(sizeof(PageDirectory_t));
    MemSet(KernelDirectory, 0, sizeof(PageDirectory_t));
    CurrentDirectory = KernelDirectory;

    UDWORD i = 0;
    while (i < PlacementAddress)
    {
        FrameAlloc(GetPage(i, 1, KernelDirectory), 0, 0);
        i += 0x1000;
    }
    RegisterInterruptHandler(14, PageFault);
    SwitchPageDirectory(KernelDirectory);

    INFO("Paging is initialized!");
}

VOID
SwitchPageDirectory(PageDirectory_t *Directory)
{
    CurrentDirectory = Directory;
    asm volatile("mov %0, %%cr3":: "r"(&Directory->TablesPhysical));
    UDWORD CR0;
    asm volatile("mov %%cr0, %0": "=r"(CR0));
    CR0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(CR0));
}

Page_t *GetPage(UDWORD Address, int Make, PageDirectory_t *Directory)
{
    Address /= 0x1000;

    UDWORD TableIndex = Address / MAX_PAGE_TABLES;
    if (Directory->Tables[TableIndex])
    {
        return (&Directory->Tables[TableIndex]->Pages[Address % MAX_PAGE_TABLES]);
    }
    else if (Make)
    {
        UDWORD Temp;
        Directory->Tables[TableIndex] = (PageTable_t *)kMalloc_ap(sizeof(PageTable_t), &Temp);
        MemSet(Directory->Tables[TableIndex], 0, PAGE_BLOCK_SIZE);
        Directory->TablesPhysical[TableIndex] = Temp | 0x7;
        return (&Directory->Tables[TableIndex]->Pages[Address % MAX_PAGE_TABLES]);
    } 
    else
    {
        return 0;
    }
}

VOID
PageFault(Registers_t Register)
{
    UDWORD FaultingAddress;
    asm("mov %%cr2, %0" : "=r" (FaultingAddress));

    UDWORD Present  = !(Register.ERR_CODE & 0x1);
    UDWORD RW       = Register.ERR_CODE & 0x2;
    UDWORD US       = Register.ERR_CODE & 0x4;
    UDWORD Reserved = Register.ERR_CODE & 0x8;
    UDWORD ID       = Register.ERR_CODE & 0x10;

    TerminalPrintf("Page Fault! ( ");
    if (Present)    {TerminalPrintf("Present ");}
    if (RW)         {TerminalPrintf("Read-Only ");}
    if (US)         {TerminalPrintf("User-Mode ");}
    if (Reserved)   {TerminalPrintf("Reserved ");}
    TerminalPrintf(") - at 0x%X.\n", FaultingAddress);
    PANIC(" [AOS PAGE FAULT] ");
}

/* Me! */
/*
static UDWORD *PageDirectory    = 0;
static UDWORD *PageDirLocation  = 0;
static UDWORD *LastPage         = 0;

VOID 
PagingMapVirtualToPhysical(UDWORD Virtual, UDWORD Physical)
{
    UWORD ID = Virtual >> 22;
    for (DWORD i = 0; i < 1024; i++) 
    {
        LastPage[i] = Physical | 3;
        Physical += 4096;
    }
    PageDirectory[ID] = ((UDWORD)LastPage) | 3;
    LastPage = (UDWORD *)(((UDWORD)LastPage) + 4096);
}

VOID 
PagingEnable(VOID)
{
    asm volatile("MOV %%EAX, %%CR3": :"a"(PageDirLocation));
    asm volatile("MOV %CR0, %EAX");
    asm volatile("ORL $0x80000000, %EAX");
    asm volatile("MOV %EAX, %CR0");
}

VOID 
PagingInit(VOID) 
{
    PageDirectory = (UDWORD *)0x400000;
    PageDirLocation = (UDWORD)PageDirectory;
    LastPage = (UDWORD *)0x404000;
    for (DWORD i = 0; i < 1024; i++) 
    {
        PageDirectory[i] = 0x00 | 0x02;
    }
    PagingMapVirtualToPhysical(0x00, 0x00);
    PagingMapVirtualToPhysical(0x400000, 0x400000);
    PagingEnable();
}
*/
