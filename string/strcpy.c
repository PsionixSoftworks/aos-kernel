#include <string.h>

/* Copy the contents of one string (src) into another (dest) */
char *
strcpy(char *dest, char *src) 
{
	return (memcpy(dest, src, strlen(src) + 1));
}
