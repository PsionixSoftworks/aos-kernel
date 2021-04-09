#include <assert.h>
#include <kernel/system/terminal.h>
#include <kernel/cpu.h>

void
__assert(char *msg, char *filename, unsigned int lineno)
{
#if !defined(DEBUG)
    terminal_printf("AOS_ASSERTION_FAIL: \"%s\" :\n\tIn File: \"%s\"\n\t@Line: %d...\n", msg, filename, lineno);
#else
    terminal_printf("$DEBUG{ AOS_ASSERTION_FAIL: \"%s\" :\n\tIn File: \"%s\"\n\t@Line: %d... }\n", msg, filename, lineno);
#endif
    cpu_halt();
}
