/*
 *  File: tss.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */


#include "../include/tss.h"
#include "../include/mem-util.h"
//#include "../include/x86/gdt.h"
/*
tss_t tss_entry;

#define REPLACE_KERNEL_DATA_SEGMENT 0x18
#define REPLACE_KERNEL_STACK_ADDR   0x20

/* 0x23 = 35: User Mode Data Selector. */
/* 0x1B = 27: CS Selector Value. */
VOID
SwitchToUserMode(VOID)
{
    asm volatile
    (
        "               \
        CLI;            \
        MOV $0x23, %AX; \
        MOV %ax, %DS;   \
        MOV %ax, %ES;   \
        MOV %ax, %FS;   \
        MOV %ax, %GS;   \
                        \
        MOV %ESP, %EAX; \
        pushl $0x23;    \
        pushl %EAX;     \
        pushf;          \
        pushl $0x1B;    \
        push $1f;       \
        IRET;           \
        1:              \
        "
    );
}

/*
void
write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0 	= ss0;
	tss_entry.esp0 	= esp0;

	tss_entry.cs = 0x0B;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13; 
}

void
set_kernel_stack(uint32_t stack)
{
	tss_entry.esp0 = stack;
}
*/