#ifndef _ADAMANTINE_TSS_H
#define _ADAMANTINE_TSS_H

#include <adamantine/aos-int.h>
#include <compiler.h>

typedef struct tss_entry_struct tss_t;

struct tss_entry_struct
{
	uint32_t link;			// Reserved
	uint32_t esp0;
	uint32_t ss0;			// Reserved
	uint32_t esp1;
	uint32_t ss1;			// Reserved
	uint32_t esp2;
	uint32_t ss2;			// Reserved
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;			// Reserved
	uint32_t cs;			// Reserved
	uint32_t ss;			// Reserved
	uint32_t ds;			// Reserved
	uint32_t fs;			// Reserved
	uint32_t gs;			// Reserved
	uint16_t ldtr;			// Reserved
	uint16_t iopb_offset;	// Reserved
} PACKED;

static inline void
tss_flush(uint16_t selector)
{
	__asm__ volatile ("ltr (%0)" : : "m"(selector));
}

#endif
