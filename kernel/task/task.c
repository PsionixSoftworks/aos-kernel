#include <kernel/task.h>
#include <string.h>
#include <adamantine/aos-defs.h>

process_t *pqueue;
process_t *current_proc;

volatile void
switch_task(registers_t *regs)
{
    memcpy(&current_proc->regs, regs, sizeof(registers_t));

    if (current_proc->next != NULL)
        current_proc = current_proc->next;
    else
        current_proc = pqueue;
    
    memcpy(regs, &current_proc->regs, sizeof(registers_t));
    switch_page_directory(current_proc->cr3);
}
