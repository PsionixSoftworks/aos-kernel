#include "../include/task.h"
#include "../include/tss.h"

task_t new_task;
task_t current_task;

void *
task_create(udword task_id, string task_name)
{
    new_task.task_id = task_id;
    new_task.task_name = task_name;
    current_task = new_task;
}

void
task_start(task_type_t *task)
{

}

void
task_switch(task_type_t *task1, task_type_t *task2)
{

}

void
task_end(task_type_t *task)
{

}