#include <stdio.h>
#include <adamantine/tty.h>
#include <kernel/drivers/keyboard.h>

extern void backspace(char);

char *
gets(char *str_buffer)
{
	char c = getchar();
	if (c)
	{
		append(str_buffer, c);
		tty_putchar(c);
	}
	return str_buffer;
}
