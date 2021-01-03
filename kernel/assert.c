#include <assert.h>
#include <kernel/system/terminal.h>
#include <kernel/cpu.h>

void
__assert(char *msg, char *filename, unsigned int lineno)
{
    terminal_printf("AOS_ASSERTION_FAIL: \"%s\" :\n\tIn File: \"%s\"\n\t@Line: %d...\n", msg, filename, lineno);
    cpu_halt();
}
