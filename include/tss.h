#ifndef _AOS_TASK_STATE_SEGMENT_
#define _AOS_TASK_STATE_SEGMENT_

#include "types.h"

#ifndef TSS_REGISTERS
#define TSS_LINK    0x00
#define TSS_ESP0    0x04
#define TSS_SS0     0x08
#define TSS_ESP1    0x0C
#define TSS_SS1     0x10
#define TSS_ESP2    0x14
#define TSS_SS2     0x18
#define TSS_CR3     0x1C
#define TSS_EIP     0x20
#define TSS_EFLAGS  0X24
#define TSS_EAX     0x28
#define TSS_ECX     0x2C
#define TSS_EDX     0x30
#define TSS_EBX     0x34
#define TSS_ESP     0x38
#define TSS_EBP     0x3C
#define TSS_ESI     0x40
#define TSS_EDI     0x44
#define TSS_ES      0x48
#define TSS_CS      0x4C
#define TSS_SS      0x50
#define TSS_DS      0x54
#define TSS_FS      0x58
#define TSS_GS      0x5C
#define TSS_LDTR    0x60
#endif

typedef struct task_state_segment 
{
    uint32_t tss_link;
    uint32_t tss_esp0;
    uint32_t tss_ss0;
    uint32_t tss_esp1;
    uint32_t tss_ss1;
    uint32_t tss_esp2;
    uint32_t tss_ss2;
    uint32_t tss_cr3;
    uint32_t tss_eip;
    uint32_t tss_eflags;
    uint32_t tss_eax;
    uint32_t tss_ecx;
    uint32_t tss_edx;
    uint32_t tss_ebx;
    uint32_t tss_esp;
    uint32_t tss_ebp;
    uint32_t tss_esi;
    uint32_t tss_edi;
    uint32_t tss_es;
    uint32_t tss_cs;
    uint32_t tss_ss;
    uint32_t tss_ds;
    uint32_t tss_fs;
    uint32_t tss_gs;
    uint32_t tss_ldtr;
    uint32_t tss_io_opt;
} tss_t;

extern void *tss_install(void);
extern void tss_init(void *ptr);
extern void tss_set_entry(tss_t *tss);
extern int tss_create_task(void *ptr, char *name);
extern void tss_kill_task(int id, char *name);

#endif
