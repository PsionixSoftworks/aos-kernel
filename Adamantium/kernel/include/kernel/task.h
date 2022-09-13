#ifndef _TASK_H
#define _TASK_H

#include <system/types.h>
#include <memory/paging.h>

typedef struct task
{
    int id;
    uint32_t esp, ebp;
    uint32_t eip;
    page_directory_t *page_directory;
    struct task *next;
} task_t;

extern void initialize_tasking(void);
extern void task_switch(void);
int fork(void);
void move_stack(void *new_stack_start, uint32_t size);
int getpid(void);
extern void switch_to_user_mode(void);

#endif
