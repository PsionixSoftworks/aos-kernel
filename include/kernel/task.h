#ifndef _AOS_TASK_H
#define _AOS_TASK_H

#include <stdint.h>
#include <kernel/isr.h>
#include <kernel/memory/paging.h>

typedef struct task task_t;
typedef void(*task_type_t)(uint32_t, char *);

typedef struct process_struct
{
    registers_t             regs;
    page_directory_t        *cr3;
    struct process_struct   *next;
} process_t;

#endif  // !_AOS_TASK_H
