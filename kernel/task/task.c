#include <kernel/task.h>

task_t new_task;
task_t current_task;

void *
task_create(uint32_t task_id, char * task_name)
{
    new_task.task_id = task_id;
    new_task.task_name = task_name;
    current_task = new_task;

    return (0);
}
