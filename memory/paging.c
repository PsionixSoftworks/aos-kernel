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

#include "../include/mem-util.h"
#include "../include/aos-defs.h"

MODULE("paging", "0.01a");

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
