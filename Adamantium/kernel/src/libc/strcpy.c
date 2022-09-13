#include <string.h>

/* Copy the contents of one string (src) into another (dest) */
char *
strcpy(char *_dest, char *_src) 
{
	return (memcpy(_dest, _src, strlen(_src) + 1));
}
