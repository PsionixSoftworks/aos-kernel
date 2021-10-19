#include <string.h>

/* Compare two strings */
int
strcmp(const char *_str1, const char *_str2) 
{
	register const uint8_t *s1 = (const uint8_t *)_str1;
    register const uint8_t *s2 = (const uint8_t *)_str2;
    uint8_t c1;
    uint8_t c2;

    do
    {
        c1 = (uint8_t) *s1++;
        c2 = (uint8_t) *s2++;
        if (c1 == '\0')
        {
            return (c1 - c2);
        }
    } while (c1 == c2);
    
    return (c1 - c2);
}
