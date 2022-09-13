#include <drivers/cursor.h>
#include <drivers/tty.h>
#include <drivers/vga.h>
#include <string.h>
#include <stdio.h>

void
puts(const char* str)
{
	for (size_t i = 0; i < strlen(str); i++)
		putchar(str[i]);
}
