#ifndef CENTRIX
#define CENTRIX

#include "centrix-core.h"
#include "types.h"
#include "mem_util.h"
#include "terminal.h"

#if CENTRIX_VERSION <= 100

static uint32_t *
BEGIN_PROC_ANALYZER(void)
{
	uint32_t *proctest = (uint32_t *)malloc(256);
	int x = (int)memset(proctest, 0xFF, 0xFF);

	terminal_printf("Result of x: %x\n", x);

	return (proctest);
}

static void 
FREE_PROC_ANALYZER(uint32_t *proc)
{
	free(proc);
}

#endif	/* !CENTRIX_VERSION */
#endif	/* !CENTRIX */
