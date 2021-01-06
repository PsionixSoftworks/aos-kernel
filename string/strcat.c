#include <string.h>

char *
strcat(char *dest, char *src) 
{
	strcpy(dest + strlen(dest), src);
    return (dest);
}
