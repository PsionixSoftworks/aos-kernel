#include <string.h>

/* Concatenate two strings */
char *
strcat(char *_dest, char *_src) 
{
	strcpy(_dest + strlen(_dest), _src);
    return (_dest);
}
