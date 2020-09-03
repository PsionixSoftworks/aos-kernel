#include "../include/task.h"
#include "../include/tss.h"

Task_t new_task;
Task_t current_task;

void *
CreateTask(udword task_id, string task_name)
{
    new_task.task_id = task_id;
    new_task.task_name = task_name;
    current_task = new_task;
}

void
StartTask(task_type_t *task)
{

}

void
SwitchTask(task_type_t *task1, task_type_t *task2)
{

}

void
EndTask(task_type_t *task)
{

}