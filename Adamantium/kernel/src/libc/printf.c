#include <drivers/cursor.h>
#include <drivers/tty.h>
#include <drivers/vga.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

void
printf(const char* restrict format, ...)
{
	va_list ap;
	va_start(ap, format);
	for (size_t i = 0; i < strlen(format); ++i)
	{
		if (format[i] == '%')
		{
			switch (format[i+1])
			{
				case 's':
				{
					char* str = va_arg(ap, char*);
					puts(str);
					i++;
					continue;
				}
				case 'b': 
				{
					uint32_t str = va_arg(ap, uint32_t);
					char buffer[16];
					puts(itoa(str, buffer, 2));
					i++;
					continue;
				}
				case 'c':
				{
					char* str = va_arg(ap, char*);
					putchar((int)str);
					i++;
					continue;
				}
				case 'd':
				{
					int str = va_arg(ap, int);
					char buffer[16];
					puts(itoa(str, buffer, 10));
					i++;
					continue;
				}
				case 'u':		/* Broken. Unsigned integers are supposed to wrap around when their limits are reached... */
				{
					unsigned int str = va_arg(ap, unsigned int);
					char buffer[256];
					puts(itoa(str, buffer, 10));
					i++;
					continue;
				}
				case 'o':
				{
					int str = va_arg(ap, int);
					char buffer[16];
					puts(itoa(str, buffer, 8));
					i++;
					continue;
				}
				case 'x':
				{
					unsigned int str = va_arg(ap, unsigned int);
					char buffer[16];
					char* result = itoa(str, buffer, 16);
					to_lower(result);
					puts(result);
					i++;
					continue;
				}
				case 'X':
				{
					unsigned int str = va_arg(ap, unsigned int);
					char buffer[16];
					char* result = itoa(str, buffer, 16);
					to_upper(result);
					puts(result);
					i++;
					continue;
				}
			};
		}
		else
		{
			putchar(format[i]);
		}
	}
	va_end(ap);
}