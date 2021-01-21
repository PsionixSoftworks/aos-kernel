#ifndef _AOS_TASK_H
#define _AOS_TASK_H

#include <stdint.h>

typedef struct task task_t;
typedef void(*task_type_t)(uint32_t, char *);

struct
task 
{
    uint32_t                    task_id;
    char *                      task_name;
};

#if defined(__cplusplus)
extern "C" {
#endif

void *task_create(uint32_t task_id, char *task_name);
void task_start(task_type_t *task);
void task_switch(task_type_t *task1, task_type_t *task2);
void task_end(task_type_t *task);

#if defined(__cplusplus)
}
#endif

#endif  // !_AOS_TASK_H
