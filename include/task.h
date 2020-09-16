#ifndef AOS_TASK_H
#define AOS_TASK_H

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

typedef struct task task_t;
typedef void(*task_type_t)(udword, string);

struct
task 
{
    udword              task_id;
    string              task_name;
};

EXTERN void *task_create(udword task_id, string task_name);
EXTERN void task_start(task_type_t *task);
EXTERN void task_switch(task_type_t *task1, task_type_t *task2);
EXTERN void task_end(task_type_t *task);

#endif
