#include <stdio.h>

extern char key_buffer[256];

/* Get the last char key press from the key buffer */
/*char
getchar(void)
{
	char buffer = 0;
	if (key_buffer == '\0')
		return 0;
	buffer = key_buffer[0];
	key_buffer[0] = '\0';
	return buffer;
}
*/