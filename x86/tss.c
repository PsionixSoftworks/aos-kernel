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

tss_t tss_entry __attribute__((aligned(4096)));

#define REPLACE_KERNEL_DATA_SEGMENT 0x18
#define REPLACE_KERNEL_STACK_ADDR   0x20

/* 0x23 = 35: user Mode data selector. */
/* 0x1B = 27: CS selector value. */
EXTERN uint32_t jump_usermode(void);

static char irq_stack[4096];

void
tss_init(void)
{
	memset(&tss_entry, 0, sizeof(struct aos_tss_entry));
	tss_entry.ss0 = 0x10;
	tss_entry.iomap_base = 0xDFFF;
	memset(irq_stack, 0, sizeof(irq_stack));
}

/*
static void
jump_usermode(void)
{
	asm volatile
	(	"		\
		cli; 			\
		mov $0x23, %ax;	\
		mov %ax, %ds;	\
		mov %ax, %es;	\
		mov %ax, %fs;	\
		mov %ax, %gs;	\
						\
		mov  %esp, %eax;\
		pushl $0x23;	\
		pushl %eax;		\
		pushf;			\
		pushl $0x1B;	\
		push $1f;		\
		iret;			\
	1:	\
		pop %eax;		\
		or %eax, 0x200;	\
		push %eax;		\
		"
	);
}
*/

void
tss_user_mode_switch(void)
{
    //jump_usermode();
	asm volatile("  \
     cli; \
     mov $0x23, %ax; \
     mov %ax, %ds; \
     mov %ax, %es; \
     mov %ax, %fs; \
     mov %ax, %gs; \
                   \
     mov %esp, %eax; \
     pushl $0x23; \
     pushl %eax; \
     pushf; \
     pushl $0x1B; \
     push $1f; \
     iret; \
   1: \
     ");
}

void
test_user_function(void)
{
	udword a = 0;
}

/*
void
write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

	//GDT_SetGate(num, base, limit, 0xE9, 0x00);

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