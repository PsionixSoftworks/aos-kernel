#ifndef AOS_TASK_H
#define AOS_TASK_H

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

typedef struct task task_t;
typedef void(*task_type_t)(uint32_t, string);

struct
task 
{
    uint32_t                    task_id;
    string                      task_name;
};

#if defined(__cplusplus)
extern "C" {
#endif

void *task_create(uint32_t task_id, string task_name);
void task_start(task_type_t *task);
void task_switch(task_type_t *task1, task_type_t *task2);
void task_end(task_type_t *task);

#if defined(__cplusplus)
}
#endif

#endif
