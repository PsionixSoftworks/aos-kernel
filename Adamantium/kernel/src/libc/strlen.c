#include <string.h>

/* Get the length of a string */
size_t
strlen(const char *s) 
{
	size_t i = 0;
	while (s[i] != 0) i++;
	return (i);
}
