#ifndef _ADAMANTINE_PROCMGR_H
#define _ADAMANTINE_PROCMGR_H

#include <stdbool.h>

#include <adamantine/aos-int.h>
#include <kernel/kernel.h>

typedef struct AdamantineProcess
{
	long p_id;
	char *p_name;
	uint8_t priority;
	bool systask;
	int exit_code;
} Process_t;

#ifndef PROCMGR_API
#define PROCMGR_API									KERNEL_API

#define PROCMGR_PRIORITY_LOW						0x01
#define PROCMGR_PRIORITY_NORMAL						0x02
#define PROCMGR_PRIORITY_HIGH						0x04
#define PROCMGR_PRIORITY_VERY_HIGH					0x08

#define PROCMGR_FALSE								false
#define PROCMGR_TRUE								true

#define PROCMGR_SYSTASK_MAX							0xFF

// Define API specific function macros:
#define proc_create(p_struct, p_id, p_name)			__proc_create(p_struct, p_id, p_name);
#define proc_start(p_struct)						__proc_start(p_struct);
#define proc_suspend(p_struct)						__proc_suspend(p_struct);
#define proc_stop(p_struct)							__proc_stop(p_struct);
#define proc_switch_priority(p_struct, p_priority)	__proc_switch_priority(p_struct);
#define proc_switch_to_task(p_struct)				__proc_switch_to_task(p_struct);
#endif

// Create all function templates here:
KERNEL_API extern void 	__proc_create(Process_t *, long, char *);
KERNEL_API extern void 	__proc_start(Process_t);
KERNEL_API extern void 	__proc_suspend(Process_t);
KERNEL_API extern int 	__proc_stop(Process_t);
KERNEL_API extern void 	__proc_switch_priority(Process_t, uint8_t);
KERNEL_API extern void 	__proc_switch_to_task(Process_t);
#endif
