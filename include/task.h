#ifndef AOS_TASK_H
#define AOS_TASK_H

#include "aos-defs.h"
#include "types.h"

typedef struct Task Task_t;
typedef void(*task_type_t)(udword, string);

struct
Task 
{
    udword              task_id;
    string              task_name;
};

EXTERN void *CreateTask(udword task_id, string task_name);
EXTERN void StartTask(task_type_t *task);
EXTERN void SwitchTask(task_type_t *task1, task_type_t *task2);
EXTERN void EndTask(task_type_t *task);

#endif
