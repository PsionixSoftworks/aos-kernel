#include <string.h>

/* Concatenate two strings */
char *
strcat(char *dest, char *src) 
{
	strcpy(dest + strlen(dest), src);
    return (dest);
}
