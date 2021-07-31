#include <adamantine/tty.h>
#include <kernel/procmgr.h>

// Define static function templates:
static void __proc_create_int(Process_t *proc, long p_id, char *p_name, uint8_t priority, bool systask);

// Create a new process, assign it a name & id:
void
__proc_create(Process_t *proc, long p_id, char *p_name)
{
	// If the process id is less than the system task max, it is a kernel task, otherwise it's a user task:
	if (p_id < PROCMGR_SYSTASK_MAX)
		__proc_create_int(proc, p_id, p_name, PROCMGR_PRIORITY_NORMAL, PROCMGR_TRUE);
	else
		__proc_create_int(proc, p_id, p_name, PROCMGR_PRIORITY_NORMAL, PROCMGR_FALSE);
}

// Start a specified process:
void
__proc_start(Process_t proc)
{
	tty_printf("[INFO]: Starting process... Process ID: %d | Process Name: %s\n", proc.p_id, proc.p_name);
}

void
__proc_suspend(Process_t UNUSED proc)
{

}

int
__proc_stop(Process_t UNUSED proc)
{
	return proc.exit_code;
}

void
__proc_switch_priority(Process_t proc, uint8_t priority_new)
{
	proc.priority = priority_new;
}

void
__proc_switch_to_task(Process_t UNUSED proc)
{

}

// Creates a process internally based on a specific set of ranges:
static void
__proc_create_int(Process_t *proc, long p_id, char *p_name, uint8_t priority, bool systask)
{
	// Assign the id and name
	proc->p_id 	= p_id;
	proc->p_name = p_name;
	proc->priority = priority;
	proc->systask = systask;
}
