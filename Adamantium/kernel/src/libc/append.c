#include <string.h>

/* Append a string */
void
append(char s[], char n)
{
	int len = strlen(s);
	s[len] = n;
	s[len + 1] = '\0';
}
