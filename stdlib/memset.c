#include <string.h>

/* Set memory to up to a specified size to a specified value (usually zero) */
void *
memset(void *dest, int c, size_t n)
{
    uint8_t *ptr = dest;
    while (n-- > 0)
    {
        *ptr++ = c;
    }
    return (dest);
}
