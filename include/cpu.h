#ifndef ADAMANTINE_CPU
#define ADAMANTINE_CPU

#if KERNEL32

#include "types.h"
#include "cpuid.h"

struct cpu 
{
	uint32_t node_id;
};

// Declare function templates:
extern struct cpu cpu_init(void);
extern void cpu_register(struct cpu, int id);
extern void cpu_halt(void);											// Halts the CPU from C.
extern void cpu_suspend(void);										// Suspends the CPU from C.
extern int cpu_broke_a_sweat(void);

extern int cpuid(void);
extern char *cpuid_supported(void);



#endif

#endif	// !ADAMANTINE_CPU
