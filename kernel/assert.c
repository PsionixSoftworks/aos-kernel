#include <assert.h>
#include <adamantine/tty.h>
#include <kernel/cpu.h>

void
__assert(char *msg, char *filename, unsigned int lineno)
{
#if !defined(DEBUG)
    tty_printf("AOS_ASSERTION_FAIL: \"%s\" :\n\tIn File: \"%s\"\n\t@Line: %d...\n", msg, filename, lineno);
#else
    tty_printf("$DEBUG{ AOS_ASSERTION_FAIL: \"%s\" :\n\tIn File: \"%s\"\n\t@Line: %d... }\n", msg, filename, lineno);
#endif
    cpu_halt();
}
