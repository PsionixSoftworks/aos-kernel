#include <stdlib.h>

void *
memmove(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    
    if (d < s)
    {
        while (n--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        const char *lasts = s + (n - 1);
        char *lastd = d + (n - 1);
        while (n--)
        {
            *lastd-- = *lasts--;
        }
    }
    return (dest);
}
