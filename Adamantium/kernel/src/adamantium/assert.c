#include <assert.h>
#include <stdio.h>

void
__panic(const char* _message, const char *_file, uint32_t _line)
{
	__asm__ volatile ( "cli" );

	printf("PANIC(%s) at %s:%d\n", _message, _file, _line);
	for (;;);
}

void
__panic_assert(const char *_file, uint32_t _line, const char *_desc)
{
	__asm__ volatile ( "cli" );

	printf("ASSERTION-FAILED(%s) at %s: Line %d\n", _desc, _file, _line);
	for (;;);
}
